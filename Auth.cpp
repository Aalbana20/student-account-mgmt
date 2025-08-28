#include "Auth.h"
#include "Utils.h"

int findUserIndex(const std::vector<Student>& students, const std::string& username) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].username == username) return static_cast<int>(i);
    }
    return -1;
}

bool verifyPassword(const Student& s, const std::string& password) {
    return s.password_hash == hashPassword(s.salt, password);
}

void resetPassword(Student& s, const std::string& newPassword, std::mt19937& rng) {
    // Optionally rotate salt; here we keep the same salt.
    s.password_hash = hashPassword(s.salt, newPassword);
}
