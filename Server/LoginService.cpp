#include "LoginService.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

LoginService::LoginService()
{}

std::string LoginService::loginClient(
    const std::shared_ptr<std::vector<std::string>>& usernames,
    const std::string& username)
{
    json reply;
    if (username.empty())
    {
        reply["type"] = "login";
        reply["success"] = false;
        reply["reason"] = "Username must contain at least one symbol.";
    }
    else if (std::find(usernames->begin(), usernames->end(), username) != usernames->end())
    {
        reply["type"] = "login";
        reply["success"] = false;
        reply["reason"] = "Username already exists.";
    }
    else
    {
        reply["type"] = "login";
        reply["success"] = true;
    }

    return reply.dump();
}