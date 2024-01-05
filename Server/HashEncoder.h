#pragma once

#include "IEncoder.h"

class HashEncoder : public IEncoder
{
public:
    HashEncoder();

    std::string generateSalt();
    std::string sha1(const std::string& password, const std::string& salt);
};