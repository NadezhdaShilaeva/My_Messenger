#pragma once

#include <string>
#include <memory>
#include <vector>

class ChatService
{
public:
    explicit ChatService();

    std::string createFailMessage(const std::string& message);
    std::string createUsersList(const std::shared_ptr<std::vector<std::string>>& usernames);
};