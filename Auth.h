#pragma once
#include <vector>
#include <string>
#include <random>          // <-- ADD THIS
#include "Student.h"

// Returns index or -1 if not found
int findUserIndex(const std::vector<Student>& students, const std::string& username);

// Verifies salted password
bool verifyPassword(const Student& s, const std::string& password);

// Resets password for a student (in-place)
void resetPassword(Student& s, const std::string& newPassword, std::mt19937& rng);
