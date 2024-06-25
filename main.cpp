#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

// Class to handle item tracking
class ItemTracker {
private:
    map<string, int> itemFrequency;

public:
    // Constructor to initialize and read from input file
    ItemTracker(const string& inputFileName) {
        readInputFile(inputFileName);
        writeBackupFile("frequency.dat");
    }

    // Method to read input file and populate item frequencies
    void readInputFile(const string& inputFileName) {
        ifstream inputFile(inputFileName);
        string item;
        if (inputFile.is_open()) {
            while (inputFile >> item) {
                itemFrequency[item]++;
            }
            inputFile.close();
        }
        else {
            cerr << "Error: Unable to open input file." << endl;
        }
    }

    // Method to write item frequencies to a backup file
    void writeBackupFile(const string& backupFileName) {
        ofstream backupFile(backupFileName);
        if (backupFile.is_open()) {
            for (const auto& entry : itemFrequency) {
                backupFile << entry.first << " " << entry.second << endl;
            }
            backupFile.close();
        }
        else {
            cerr << "Error: Unable to open backup file." << endl;
        }
    }

    // Method to get the frequency of a specific item
    int getItemFrequency(const string& item) const {
        auto it = itemFrequency.find(item);
        if (it != itemFrequency.end()) {
            return it->second;
        }
        else {
            return 0;
        }
    }

    // Method to print all items and their frequencies
    void printItemList() const {
        for (const auto& entry : itemFrequency) {
            cout << entry.first << " " << entry.second << endl;
        }
    }

    // Method to print a histogram of item frequencies
    void printHistogram() const {
        for (const auto& entry : itemFrequency) {
            cout << entry.first << " ";
            for (int i = 0; i < entry.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

// Function to display the menu and get user choice
int displayMenu() {
    int choice;
    cout << "\nMenu Options:\n";
    cout << "1. Search for an item's frequency\n";
    cout << "2. Print all items and their frequencies\n";
    cout << "3. Print histogram of items\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    // Input validation for menu choice
    while (cin.fail() || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter a number between 1 and 4: ";
        cin >> choice;
    }
    return choice;
}

// Main function to run the program
int main() {
    // Create an instance of ItemTracker and read the input file
    ItemTracker tracker("CS210_Project_Three_Input_File.txt");

    int choice;
    string item;

    do {
        choice = displayMenu();
        switch (choice) {
        case 1:
            cout << "Enter the item to search for: ";
            cin >> item;
            cout << item << " frequency: " << tracker.getItemFrequency(item) << endl;
            break;
        case 2:
            tracker.printItemList();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
