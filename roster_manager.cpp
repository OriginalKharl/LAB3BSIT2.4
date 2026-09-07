#include <iostream>
#include <iomanip>
#include <string>

const int MAX_CAPACITY = 50;

struct StudentRecord {
    int id;
    std::string name;
};

class StudentRoster {
private:
    StudentRecord records[MAX_CAPACITY];
    int currentCount;

public:
    StudentRoster() : currentCount(0) {}

    // 1. Add Student Record
    bool addStudent(int id, const std::string& name) {
        if (currentCount >= MAX_CAPACITY) {
            std::cout << "Warning: Roster is full. Cannot add another student.\n";
            return false;
        }

        // Ensure the ID is unique.
        if (findStudentById(id, false) != -1) {
            std::cout << "Warning: Student ID " << id
                      << " already exists. IDs must be unique.\n";
            return false;
        }

        records[currentCount].id = id;
        records[currentCount].name = name;
        ++currentCount;

        std::cout << "Student added successfully.\n";
        return true;
    }

    // 2. Search Student by ID using Linear Search
    int findStudentById(int id, bool printComparisons = true) const {
        if (currentCount == 0) {
            if (printComparisons) {
                std::cout << "Roster is currently empty.\n";
                std::cout << "Total element comparisons: 0\n";
            }
            return -1;
        }

        int comparisons = 0;

        for (int i = 0; i < currentCount; ++i) {
            ++comparisons;

            if (records[i].id == id) {
                if (printComparisons) {
                    std::cout << "Student found at index " << i << ".\n";
                    std::cout << "Total element comparisons: "
                              << comparisons << "\n";
                }
                return i;
            }
        }

        if (printComparisons) {
            std::cout << "Student ID " << id << " was not found.\n";
            std::cout << "Total element comparisons: "
                      << comparisons << "\n";
        }

        return -1;
    }

    // 3. Remove Student Record
    bool removeStudentById(int id) {
        if (currentCount == 0) {
            std::cout << "Roster is currently empty.\n";
            return false;
        }

        int index = findStudentById(id);

        if (index == -1) {
            return false;
        }

        // Left-shift all subsequent elements.
        for (int i = index; i < currentCount - 1; ++i) {
            records[i] = records[i + 1];
        }

        --currentCount;

        std::cout << "Student ID " << id << " removed successfully.\n";
        std::cout << "Active record count: " << currentCount << "\n";

        return true;
    }

    // 4. Safe Element Retrieval
    StudentRecord safeGetRecord(int index, bool& success) const {
        success = false;

        if (currentCount == 0) {
            std::cout << "Roster is currently empty.\n";
            return StudentRecord{-1, ""};
        }

        if (index < 0 || index >= currentCount) {
            std::cout << "Warning: Index " << index
                      << " is out of bounds.\n";
            return StudentRecord{-1, ""};
        }

        success = true;
        return records[index];
    }

    // 5. Display Full Roster
    void printRoster() const {
        if (currentCount == 0) {
            std::cout << "Roster is currently empty.\n";
            return;
        }

        std::cout << "\n========== STUDENT ROSTER ==========\n";

        std::cout << std::left
                  << std::setw(10) << "Index"
                  << std::setw(10) << "ID"
                  << std::setw(30) << "Name"
                  << "\n";

        std::cout << std::string(50, '-') << "\n";

        for (int i = 0; i < currentCount; ++i) {
            std::cout << std::left
                      << std::setw(10) << i
                      << std::setw(10) << records[i].id
                      << std::setw(30) << records[i].name
                      << "\n";
        }

        std::cout << "-------------------------------------\n";
        std::cout << "Active records: " << currentCount
                  << " / " << MAX_CAPACITY << "\n";
    }

    int getCurrentCount() const {
        return currentCount;
    }
};


// =========================
// Interactive Menu
// =========================

void printMenu() {
    std::cout << "\n========== STUDENT RECORD SYSTEM ==========\n";
    std::cout << "1. Add Student Record\n";
    std::cout << "2. Search Student by ID\n";
    std::cout << "3. Remove Student Record\n";
    std::cout << "4. Safe Element Retrieval\n";
    std::cout << "5. Display Full Roster\n";
    std::cout << "6. Exit\n";
    std::cout << "============================================\n";
    std::cout << "Enter choice: ";
}


int main() {
    StudentRoster roster;

    int choice;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {

        case 1: {
            int id;
            std::string name;

            std::cout << "Enter student ID: ";
            std::cin >> id;

            std::cin.ignore();
            std::cout << "Enter student name: ";
            std::getline(std::cin, name);

            roster.addStudent(id, name);
            break;
        }

        case 2: {
            int id;

            std::cout << "Enter student ID to search: ";
            std::cin >> id;

            roster.findStudentById(id);
            break;
        }

        case 3: {
            int id;

            std::cout << "Enter student ID to remove: ";
            std::cin >> id;

            roster.removeStudentById(id);
            break;
        }

        case 4: {
            int index;
            bool success;

            std::cout << "Enter array index to retrieve: ";
            std::cin >> index;

            StudentRecord record =
                roster.safeGetRecord(index, success);

            if (success) {
                std::cout << "Record retrieved successfully:\n";
                std::cout << "ID: " << record.id << "\n";
                std::cout << "Name: " << record.name << "\n";
            } else {
                std::cout << "Record retrieval failed safely.\n";
            }

            break;
        }

        case 5:
            roster.printRoster();
            break;

        case 6:
            std::cout << "Exiting program.\n";
            break;

        default:
            std::cout << "Invalid menu choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}