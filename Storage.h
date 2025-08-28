#pragma once
#include <vector>
#include "Student.h"

// CSV format:
// name,dob,username,password_hash,salt,id
std::vector<Student> loadCSV(const std::string& filename);
bool saveCSV(const std::string& filename, const std::vector<Student>& students);
