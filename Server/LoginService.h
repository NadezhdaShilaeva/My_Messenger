#pragma once

#include <string>
#include <memory>
#include <vector>

#include "IUserRepository.h"
#include "IEncoder.h"

class LoginService
{
private:
    std::shared_ptr<IUserRepository> userRepository;
    std::shared_ptr<IEncoder> encoder;

public:
    explicit LoginService(const std::shared_ptr<IUserRepository>& userRepository, const std::shared_ptr<IEncoder>& encoder);

    std::string registerUser(const std::string& username, const std::string& password);
    std::string loginUser(const std::string& username, const std::string& password);
};