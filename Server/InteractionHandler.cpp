#include "InteractionHandler.h"
#include "ChatService.h"
#include "WebSocketSession.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

InteractionHandler::InteractionHandler(const std::shared_ptr<LoginService>& loginService,
    const std::shared_ptr<ChatService>& chatService)
    : loginService(loginService), chatService(chatService)
{}

std::shared_ptr<std::vector<std::string>> InteractionHandler::getUsernames()
{
    std::vector<std::string> usernames;
    for (auto& user : sessions)
    {
        usernames.push_back(user.first);
    }

    return std::make_shared<std::vector<std::string>>(std::move(usernames));
}

void InteractionHandler::processMessage(const std::string& message, const boost::weak_ptr<WebSocketSession>& sender)
{
    json messageJson = json::parse(message);
    std::string type = messageJson["type"];

    if (type == "login")
    {
        auto reply = loginService->loginClient(getUsernames(), messageJson["username"]);
        loginClient(sender, messageJson["username"], reply);
    }
    else if (type == "message")
    {
        sendMessage(messageJson["receiver"], message, messageJson["sender"]);
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
            sessionSPtr->sendMessage(replyPtr);
            sessionSPtr->closeWebSocket();
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
    }
}

void InteractionHandler::sendMessage(const std::string& receiver, const std::string& message, const std::string& sender)
{
    auto messagePtr = boost::make_shared<std::string>(std::move(message));
    if (auto sessionSPtr = sessions[receiver].lock())
    {
        sessionSPtr->sendMessage(messagePtr);
    }
    else
    {
        auto reply = chatService->createFailMessage(message);
        if (auto sessionSPtr = sessions[sender].lock())
        {
            auto replyPtr = boost::make_shared<std::string>(std::move(reply));
            sessionSPtr->sendMessage(replyPtr);
        }
    }
}

void InteractionHandler::sendUsersList(const boost::weak_ptr<WebSocketSession>& session)
{
    auto usersList = chatService->createUsersList(getUsernames());

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