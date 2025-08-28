#pragma once
#include <string>

struct Student {
    std::string name;
    std::string dob;
    std::string username;
    std::string password_hash; // salted hash
    std::string salt;          // hex-encoded salt
    std::string id;            // 7-digit numeric string
};
