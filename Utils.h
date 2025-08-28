#pragma once
#include <string>
#include <random>
#include <sstream>
#include <iomanip>
#include <functional>

// NOTE: For demo purposes we use std::hash + salt (NOT cryptographically secure).
// Swap hashPassword() with a real SHA-256 later if you need real security.

inline std::string randomHex(std::mt19937& rng, size_t bytes = 16) {
    std::uniform_int_distribution<int> dist(0, 255);
    std::ostringstream oss;
    for (size_t i = 0; i < bytes; ++i) {
        int v = dist(rng);
        oss << std::hex << std::setw(2) << std::setfill('0') << v;
    }
    return oss.str();
}

inline std::string hashPassword(const std::string& salt, const std::string& password) {
    // Simple salted hash; replace with real SHA-256 for production.
    std::hash<std::string> hasher;
    size_t hv = hasher(salt + ":" + password);
    std::ostringstream oss;
    oss << std::hex << hv;
    return oss.str();
}

inline std::string generateId(std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(1500000, 1599999);
    return std::to_string(dist(rng));
}
