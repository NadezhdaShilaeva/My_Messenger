#include "HashEncoder.h"

#include <time.h>
#include <boost/uuid/detail/sha1.hpp>

HashEncoder::HashEncoder()
{}

std::string HashEncoder::generateSalt()
{
    srand(time(nullptr));

    char symbols[37] = "abcdefghijklmnopqrstuvwxyz1234567890";

    char salt[11] = { 0 };
    for (int i = 0; i < 10; ++i) {
        salt[i] = symbols[rand() % 36];
    }

    return salt;
}

std::string HashEncoder::sha1(const std::string& password, const std::string& salt)
{
    using boost::uuids::detail::sha1;

    std::string result = password + salt;

    sha1 sha;
    sha.process_bytes(result.data(), result.size());
    unsigned hash[5] = { 0 };
    sha.get_digest(hash);

    char buf[20] = { 0 };
    for (int i = 0; i < 5; ++i)
    {
        const char* tmp = reinterpret_cast<char*>(hash);
        buf[i * 4] = tmp[i * 4 + 3];
        buf[i * 4 + 1] = tmp[i * 4 + 2];
        buf[i * 4 + 2] = tmp[i * 4 + 1];
        buf[i * 4 + 3] = tmp[i * 4];
    }

    return buf;
}