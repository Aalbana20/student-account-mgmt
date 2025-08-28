#include <iostream>
#include <limits>
#include "Storage.h"
#include "App.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string DB_FILE = "login_DB.csv";
    auto students = loadCSV(DB_FILE);

    // Seed data if file empty
    if (students.empty()) {
        students.push_back({"Rick", "7/21/1892", "Rick1892",
                            "5f3759df", "deadbeef", "1500001"}); // demo hash/salt
        // Note: Above is placeholder; in a real flow you'd create via createAccount
    }

    bool online = true;
    while (online) {
        cout << "\nPick an option:\n"
             << "1) Login\n2) Create account\n3) Save students\n4) List users\n5) Exit\n> ";
        int choice = 0;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush newline

        switch (choice) {
            case 1: loginFlow(students); break;
            case 2: createAccount(students); break;
            case 3:
                if (saveCSV(DB_FILE, students))
                    cout << "Saved to " << DB_FILE << ".\n";
                break;
            case 4:
                for (const auto& s : students) cout << s.username << " (" << s.id << ")\n";
                break;
            case 5: online = false; break;
            default: cout << "Invalid input.\n"; break;
        }
    }
    // Auto-save on exit (optional)
    saveCSV(DB_FILE, students);
    return 0;
}
