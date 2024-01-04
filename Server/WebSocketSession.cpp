#include "WebSocketSession.h"

#include <iostream>

WebSocketSession::WebSocketSession(tcp::socket&& socket,
    const boost::shared_ptr<InteractionHandler>& handler)
    : webSocket(std::move(socket)), handler(handler), pingTimer(socket.get_executor())
{}

WebSocketSession::~WebSocketSession()
{
    handler->leaveClient(username);
}

void WebSocketSession::run()
{
    std::cout << "Run WebSocketSession\n";

    // Set suggested timeout settings for the websocket
    webSocket.set_option(websocket::stream_base::timeout::suggested(
        beast::role_type::server));

    // Set a decorator to change the Server of the handshake
    webSocket.set_option(websocket::stream_base::decorator(
        [](websocket::response_type& res)
        {
            res.set(http::field::server,
                std::string(BOOST_BEAST_VERSION_STRING) +
                " websocket-chat-multi");
        }));

    acceptWebSocketHandshake();
}

void WebSocketSession::acceptWebSocketHandshake()
{
    auto self = shared_from_this();
    webSocket.async_accept(
        [this, self](beast::error_code ec)
        {
            if (ec)
            {
                return self->printError(ec, "acceptWebSocket");
            }

            std::cout << "Accept WebSocket handshake\n";

            self->pongControl();
            self->pingClient();

            self->readMessage();
        });
}

void WebSocketSession::readMessage()
{
    auto self = shared_from_this();
    webSocket.async_read(buffer,
        [self](beast::error_code ec, std::size_t length)
        {
            if (ec)
            {
                return self->printError(ec, "readMessage");
            }

            std::cout << "Read message from " + self->username + "\n";

            self->handler->processMessage(beast::buffers_to_string(self->buffer.data()), self->weak_from_this());
            self->buffer.consume(self->buffer.size());

            self->readMessage();
        });
}

void WebSocketSession::sendMessage(const boost::shared_ptr<std::string>& message)
{
    auto self = shared_from_this();
    asio::post(webSocket.get_executor(),
        [self, message]()
        {
            self->msgQueue.push_back(message);

            if (self->msgQueue.size() > 1)
            {
                return;
            }

            self->writeMessage();
        });
}

void WebSocketSession::dispatchMessage(const boost::shared_ptr<std::string>& message)
{
    auto self = shared_from_this();
    asio::dispatch(webSocket.get_executor(),
        [self, message]()
        {
            self->msgQueue.push_back(message);

            self->writeMessage();
        });
}

void WebSocketSession::writeMessage()
{
    auto self = shared_from_this();
    webSocket.async_write(asio::buffer(*msgQueue.front()),
        [self](beast::error_code ec, std::size_t length)
        {
            if (ec)
            {
                return self->printError(ec, "writeMessage");
            }

            std::cout << "Wrote message to " + self->username + "\n";

            self->msgQueue.erase(self->msgQueue.begin());

            if (!self->msgQueue.empty())
            {
                self->writeMessage();
            }
        });
}

void WebSocketSession::setUsername(const std::string& username)
{
    this->username = username;
}

void WebSocketSession::pongControl()
{
    webSocket.control_callback(
        [this](auto type, auto payload)
        {
            if (type == websocket::frame_type::pong)
            {
                std::cout << "Received pong from client " + username + "\n";
                isPongReceived = true;
            }
        });
}

void WebSocketSession::pingClient()
{
    if (!isPongReceived) {
        std::cout << "Close connection with " + username + " because client didn't send pong.\n";
        
        return closeWebSocket();
    }

    webSocket.async_ping("",
        [this](beast::error_code ec) {
            if (ec)
            {
                return printError(ec, "pingClient");
            }
            isPongReceived = false;

            pingTimer.expires_after(boost::asio::chrono::seconds(pingTimeout));
            pingTimer.async_wait(
                [this](beast::error_code ec)
                {
                    if (ec)
                    {
                        return printError(ec, "pingClient");
                    }

                    pingClient();
                });
        });
}

void WebSocketSession::closeConnection()
{
    auto self = shared_from_this();
    asio::post(webSocket.get_executor(),
        [self]()
        {
            self->closeWebSocket();
        });
}

void WebSocketSession::closeWebSocket()
{
    webSocket.next_layer().close();
}

void WebSocketSession::printError(beast::error_code ec, const char* what)
{
    if (ec == asio::error::operation_aborted || ec == websocket::error::closed)
    {
        return;
    }

    std::cerr << "Error from " << what << ": " << ec.message() << "\n";
}