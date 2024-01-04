#include "InteractionHandler.h"
#include "ChatService.h"
#include "WebSocketSession.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

InteractionHandler::InteractionHandler(const std::shared_ptr<LoginService>& loginService,
    const std::shared_ptr<ChatService>& chatService)
    : loginService(loginService), chatService(chatService)
{}

void InteractionHandler::processMessage(const std::string& message, const boost::weak_ptr<WebSocketSession>& sender)
{
    json messageJson = json::parse(message);
    std::string type = messageJson["type"];

    if (type == "register")
    {
        auto reply = loginService->registerUser(messageJson["username"], messageJson["password"]);
        loginClient(sender, messageJson["username"], reply);
    }
    else if (type == "login")
    {
        auto reply = loginService->loginUser(messageJson["username"], messageJson["password"]);
        loginClient(sender, messageJson["username"], reply);
    }
    else if (type == "message")
    {
        sendMessage(messageJson["receiver"], messageJson["sender"], messageJson["text"], messageJson["time"], message);
    }
    else if (type == "users")
    {
        sendUsersList(sender);
    }
}

void InteractionHandler::loginClient(const boost::weak_ptr<WebSocketSession>& session, const std::string& username, 
    const std::string& reply)
{
    auto replyPtr = boost::make_shared<std::string>(std::move(reply));
    if (json::parse(reply)["success"] == false)
    {
        if (auto sessionSPtr = session.lock())
        {
            sessionSPtr->dispatchMessage(replyPtr);
            sessionSPtr->closeConnection();
        }
    }
    else
    {
        if (auto sessionSPtr = session.lock())
        {
            sessions[username] = session;
            sessionSPtr->setUsername(username);
            sessionSPtr->sendMessage(replyPtr);
        }

        sendMessagesList(username);
    }
}

void InteractionHandler::sendMessagesList(const std::string& username)
{
    auto message = chatService->createChatMessagesList(username);
    auto messagePtr = boost::make_shared<std::string>(std::move(message));
    if (auto sessionSPtr = sessions[username].lock())
    {
        sessionSPtr->sendMessage(messagePtr);
    }
}

void InteractionHandler::sendMessage(const std::string& receiver, const std::string& sender, const std::string& text, 
    const std::string& time, const std::string& message)
{
    chatService->saveMessage(receiver, sender, text, time);

    auto messagePtr = boost::make_shared<std::string>(std::move(message));
    if (auto sessionSPtr = sessions[receiver].lock())
    {
        sessionSPtr->sendMessage(messagePtr);
    }
    else
    {
        if (!sessions.count(receiver))
        {
            auto reply = chatService->createFailMessage(message);
            if (auto sessionSPtr = sessions[sender].lock())
            {
                auto replyPtr = boost::make_shared<std::string>(std::move(reply));
                sessionSPtr->sendMessage(replyPtr);
            }
        }
    }
}

void InteractionHandler::sendUsersList(const boost::weak_ptr<WebSocketSession>& session)
{
    auto usersList = chatService->createUsersList();

    auto messagePtr = boost::make_shared<std::string>(std::move(usersList));
    if (auto sessionSPtr = session.lock())
    {
        sessionSPtr->sendMessage(messagePtr);
    }
}

void InteractionHandler::leaveClient(const std::string& username)
{
    if (!username.empty())
    {
        sessions.erase(username);
    }
}