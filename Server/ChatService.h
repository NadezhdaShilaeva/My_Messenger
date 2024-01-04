#pragma once

#include <string>
#include <memory>
#include <vector>

#include "IUserRepository.h"
#include "IMessageRepository.h"

class ChatService
{
private:
    std::shared_ptr<IUserRepository> userRepository;
    std::shared_ptr<IMessageRepository> messageRepository;

public:
    explicit ChatService(const std::shared_ptr<IUserRepository>& userRepository, 
        const std::shared_ptr<IMessageRepository>& messageRepository);

    void saveMessage(const std::string& receiver, const std::string& sender, const std::string& text, const std::string& time);
    std::string createChatMessagesList(const std::string& username);
    std::string createFailMessage(const std::string& message);
    std::string createUsersList();
};