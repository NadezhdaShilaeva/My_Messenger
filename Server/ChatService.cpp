#include "ChatService.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

ChatService::ChatService()
{}

std::string ChatService::createFailMessage(const std::string& message)
{
    json reply = json::parse(message);

    reply["type"] = "messageFail";
    reply["reason"] = "Message was not delivered. " + std::string(reply["receiver"]) + " leave the chat.";
    
    return reply.dump();
}

std::string ChatService::createUsersList(const std::shared_ptr<std::vector<std::string>>& usernames)
{
    json usersList;
    usersList["type"] = "users";

    for (auto& user : *usernames)
    {
        usersList["list"].push_back(user);
    }

    return usersList.dump();
}