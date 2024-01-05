#include "LoginService.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

LoginService::LoginService(const std::shared_ptr<IUserRepository>& userRepository, const std::shared_ptr<IEncoder>& encoder)
    : userRepository(userRepository), encoder(encoder)
{}

std::string LoginService::registerUser(const std::string& username, const std::string& password)
{
    json reply;
    if (username.empty())
    {
        reply["type"] = "register";
        reply["username"] = username;
        reply["success"] = false;
        reply["reason"] = "Username must contain at least one symbol.";
    }
    else if (password.empty())
    {
        reply["type"] = "register";
        reply["username"] = username;
        reply["success"] = false;
        reply["reason"] = "Password must contain at least one symbol.";
    }
    else if (userRepository->findByUsername(username))
    {
        reply["type"] = "register";
        reply["username"] = username;
        reply["success"] = false;
        reply["reason"] = "Username already exists.";
    }
    else
    {
        std::string salt = encoder->generateSalt();
        std::string hashedPassword = encoder->sha1(password, salt);

        userRepository->save(User(username, hashedPassword, salt));

        reply["type"] = "register";
        reply["username"] = username;
        reply["success"] = true;
    }

    return reply.dump();
}

std::string LoginService::loginUser(const std::string& username, const std::string& password)
{
    std::optional<User> user = userRepository->findByUsername(username);

    json reply;
    if (user)
    {
        std::string currentHashedPassword = encoder->sha1(password, user->getSalt());

        if (currentHashedPassword == user->getPassword())
        {
            reply["type"] = "login";
            reply["username"] = username;
            reply["success"] = true;
        }
        else
        {
            reply["type"] = "login";
            reply["username"] = username;
            reply["success"] = false;
            reply["reason"] = "Wrong username or password.";
        }
    } 
    else
    {
        reply["type"] = "login";
        reply["username"] = username;
        reply["success"] = false;
        reply["reason"] = "Wrong username or password.";
    }

    return reply.dump();
}