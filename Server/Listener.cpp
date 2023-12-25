#include "Listener.h"
#include "WebSocketSession.h"

#include <iostream>

Listener::Listener(asio::io_context& context, tcp::endpoint endpoint, 
    boost::shared_ptr<InteractionHandler> const& handler)
    : context(context), acceptor(context), handler(handler)
{
    beast::error_code ec;

    acceptor.open(endpoint.protocol(), ec);
    if (ec)
    {
        printError(ec, "open");
        return;
    }

    acceptor.set_option(asio::socket_base::reuse_address(true), ec);
    if (ec)
    {
        printError(ec, "set_option");
        return;
    }

    acceptor.bind(endpoint, ec);
    if (ec)
    {
        printError(ec, "bind");
        return;
    }

    acceptor.listen(asio::socket_base::max_listen_connections, ec);
    if (ec)
    {
        printError(ec, "listen");
        return;
    }
}

void Listener::accept()
{
    auto self = shared_from_this();
    acceptor.async_accept(asio::make_strand(context),
        [self](beast::error_code ec, tcp::socket socket)
        {
            if (ec)
            {
                return self->printError(ec, "accept");
            }
            else
            {
                std::cout << "Accepted connection\n";

                boost::make_shared<WebSocketSession>(std::move(socket), self->handler)->run();
            }

            self->accept();
        });
}

void Listener::printError(beast::error_code ec, const char* what)
{
    if (ec == asio::error::operation_aborted)
    {
        return;
    }

    std::cerr << "Error from " << what << ": " << ec.message() << "\n";
}