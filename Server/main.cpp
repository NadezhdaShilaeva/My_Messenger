#include "Listener.h"
#include "InteractionHandler.h"
#include "LoginService.h"
#include "ChatService.h"

#include <iostream>

int main(int argc, char* argv[])
{
    auto address = asio::ip::make_address("127.0.0.1");
    auto port = static_cast<unsigned short>(std::atoi("8001"));

    auto loginService = std::make_shared<LoginService>();
    auto chatService = std::make_shared<ChatService>();

    asio::io_context context;

    boost::make_shared<Listener>(context, tcp::endpoint{ address, port }, 
        boost::make_shared<InteractionHandler>(loginService, chatService))->accept();

    context.run();

    return 0;
}