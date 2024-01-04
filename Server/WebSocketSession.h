#pragma once

#include "Boost.h"
#include "InteractionHandler.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

class InteractionHandler;

class WebSocketSession : public boost::enable_shared_from_this<WebSocketSession>
{
private:
    websocket::stream<beast::tcp_stream> webSocket;
    beast::flat_buffer buffer;
    boost::shared_ptr<InteractionHandler> handler;
    std::vector<boost::shared_ptr<std::string>> msgQueue;
    std::string username;

    boost::asio::steady_timer pingTimer;
    size_t pingTimeout = 60;
    bool isPongReceived = true;

    void acceptWebSocketHandshake();
    void readMessage();
    void writeMessage();
    void closeWebSocket();
    void pongControl();
    void pingClient();
    void printError(beast::error_code ec, const char* what);

public:
    explicit WebSocketSession(tcp::socket&& socket, const boost::shared_ptr<InteractionHandler>& handler);

    ~WebSocketSession();

    void run();
    void setUsername(const std::string& username);
    void sendMessage(const boost::shared_ptr<std::string>& message);
    void dispatchMessage(const boost::shared_ptr<std::string>& message);
    void closeConnection();
};