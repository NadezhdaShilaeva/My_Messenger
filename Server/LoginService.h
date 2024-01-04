#pragma once

#include <string>
#include <memory>
#include <vector>

#include "IUserRepository.h"

class LoginService
{
private:
    std::shared_ptr<IUserRepository> userRepository;

public:
    explicit LoginService(const std::shared_ptr<IUserRepository>& userRepository);

    std::string registerUser(const std::string& username, const std::string& password);
    std::string loginUser(const std::string& username, const std::string& password); // return message with success or not success
};