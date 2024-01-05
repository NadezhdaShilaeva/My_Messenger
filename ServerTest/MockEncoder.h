#pragma once

#include "../Server/IEncoder.h"

class MockEncoder : public IEncoder
{
public:
    MockEncoder();

    std::string generateSalt();
    std::string sha1(const std::string& password, const std::string& salt);
};