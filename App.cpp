#include "App.h"
#include "Auth.h"
#include "Utils.h"
#include <iostream>
#include <limits>

using namespace std;

static mt19937& globalRNG() {
    static random_device rd;
    static mt19937 rng(rd());
    return rng;
}

void display(const Student& s) {
    cout << "Name: "     << s.name     << "\n"
         << "DOB: "      << s.dob      << "\n"
         << "Username: " << s.username << "\n"
         << "ID: "       << s.id       << "\n";
}

void createAccount(vector<Student>& students) {
    auto& rng = globalRNG();
    Student s;
    cout << "Enter name: ";
    getline(cin, s.name);
    cout << "Enter DOB: ";
    getline(cin, s.dob);

    // Ensure unique username
    while (true) {
        cout << "Enter Username: ";
        getline(cin, s.username);
        if (findUserIndex(students, s.username) == -1) break;
        cout << "Username already exists. Try another.\n";
    }

    cout << "Enter Password: ";
    string pw; getline(cin, pw);

    s.salt          = randomHex(rng, 12);
    s.password_hash = hashPassword(s.salt, pw);
    s.id            = generateId(rng);

    students.push_back(move(s));
    cout << "Account created. Assigned ID: " << students.back().id << "\n";
}

void loginFlow(vector<Student>& students) {
    cout << "Username: ";
    string uname; getline(cin, uname);
    int idx = findUserIndex(students, uname);
    if (idx < 0) {
        cout << "Not in database. Create account? (y/n): ";
        string resp; getline(cin, resp);
        if (!resp.empty() && (resp[0] == 'y' || resp[0] == 'Y')) {
            createAccount(students);
        }
        return;
    }
    cout << "Password: ";
    string pw; getline(cin, pw);
    if (verifyPassword(students[idx], pw)) {
        cout << "Login successful.\n";
        display(students[idx]);
    } else {
        cout << "Incorrect password. Reset? (y/n): ";
        string resp; getline(cin, resp);
        if (!resp.empty() && (resp[0] == 'y' || resp[0] == 'Y')) {
            cout << "New password: ";
            string npw; getline(cin, npw);
            resetPassword(students[idx], npw, globalRNG());
            cout << "Password reset.\n";
        }
    }
}
