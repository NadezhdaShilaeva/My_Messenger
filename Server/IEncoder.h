#pragma once

#include <string>

class IEncoder
{
public:
    virtual std::string generateSalt() = 0;
    virtual std::string sha1(const std::string& password, const std::string& salt) = 0;
};