#include "ChatService.h"
#include "IMessageRepository.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

ChatService::ChatService(const std::shared_ptr<IUserRepository>& userRepository,
    const std::shared_ptr<IMessageRepository>& messageRepository)
    : userRepository(userRepository), messageRepository(messageRepository)
{}

void ChatService::saveMessage(const std::string& receiver, const std::string& sender, const std::string& text, const std::string& time)
{
    messageRepository->save(Message(*userRepository->findByUsername(receiver),
        *userRepository->findByUsername(sender), text, time));
}

std::string ChatService::createChatMessagesList(const std::string& username)
{
    json messagesList;
    messagesList["type"] = "messages";

    User user = *userRepository->findByUsername(username);

    for (const Message& message : messageRepository->findBySenderOrReceiver(user))
    {
        json messageJson;
        messageJson["receiver"] = message.getReceiver().getUsername();
        messageJson["sender"] = message.getSender().getUsername();
        messageJson["text"] = message.getText();
        messageJson["time"] = message.getTime();

        messagesList["list"].push_back(messageJson);
    }

    return messagesList.dump();
}

std::string ChatService::createFailMessage(const std::string& message)
{
    json reply = json::parse(message);

    reply["type"] = "messageFail";
    reply["reason"] = "Message was not delivered. " + std::string(reply["receiver"]) + " no longer exists.";
    
    return reply.dump();
}

std::string ChatService::createUsersList()
{
    json usersList;
    usersList["type"] = "users";

    for (auto& user : userRepository->findAll())
    {
        usersList["list"].push_back(user.getUsername());
    }

    return usersList.dump();
}