#pragma once

#include <string>
#include <memory>
#include <vector>

class LoginService
{
private:

public:
    explicit LoginService();

    std::string loginClient(
        const std::shared_ptr<std::vector<std::string>>& usernames,
        const std::string& username);
};