#include "Storage.h"
#include <fstream>
#include <sstream>
#include <iostream>

static std::vector<std::string> splitCSVLine(const std::string& line) {
    // Simple CSV split (no quoted commas). Good enough for this use-case.
    std::vector<std::string> out;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) out.push_back(cell);
    return out;
}

std::vector<Student> loadCSV(const std::string& filename) {
    std::vector<Student> v;
    std::ifstream in(filename);
    if (!in) {
        // File may not exist yet; return empty set silently
        return v;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto cells = splitCSVLine(line);
        if (cells.size() != 6) {
            std::cerr << "Skipping malformed line: " << line << "\n";
            continue;
        }
        Student s;
        s.name          = cells[0];
        s.dob           = cells[1];
        s.username      = cells[2];
        s.password_hash = cells[3];
        s.salt          = cells[4];
        s.id            = cells[5];
        v.push_back(std::move(s));
    }
    return v;
}

bool saveCSV(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error: cannot open " << filename << " for writing.\n";
        return false;
    }
    for (const auto& s : students) {
        out << s.name << ","
            << s.dob << ","
            << s.username << ","
            << s.password_hash << ","
            << s.salt << ","
            << s.id << "\n";
    }
    return true;
}
