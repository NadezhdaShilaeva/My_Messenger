#pragma once

#include "Boost.h"

#include <boost/smart_ptr.hpp>
#include <memory>
#include <string>

class InteractionHandler;

class Listener : public boost::enable_shared_from_this<Listener>
{
private:
    asio::io_context& context;
    tcp::acceptor acceptor;
    boost::shared_ptr<InteractionHandler> handler;

    void printError(beast::error_code ec, const char* what);

public:
    explicit Listener(asio::io_context& context, tcp::endpoint endpoint,
        const boost::shared_ptr<InteractionHandler>& handler);

    void accept();
};