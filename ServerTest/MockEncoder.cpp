#include "MockEncoder.h"

MockEncoder::MockEncoder()
{}

std::string MockEncoder::generateSalt()
{
    return "salt123456";
}

std::string MockEncoder::sha1(const std::string& password, const std::string& salt)
{
    return password + salt;
}