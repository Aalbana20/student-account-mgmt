#pragma once
#include <vector>
#include "Student.h"

// User flows
void display(const Student& s);
void createAccount(std::vector<Student>& students);
void loginFlow(std::vector<Student>& students);
