#include <iostream>
#include "DispatchCall.h"
#include "FileHandler.h"
#include "MenuHandler.h"

using namespace std;

int main() {
    vector<DispatchCall> calls;
    cout << "VERSION 1.3 DISPATCH LOGGER - nhpha" << endl;

    // Load data from file at startup
    if (loadDataFromFile(calls)) {
        cout << "Data loaded successfully!" << endl;
    }
    else {
        cout << "No existing data found or error loading data." << endl;
    }

    int choice;
    do {
        cout << "\nDispatch Call Logging System\n";
        cout << "1. Add New Call\n";
        cout << "2. View All Calls\n";
        cout << "3. Modify Call\n";
        cout << "4. Resolve Call\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice) {
        case 1:
            addCall(calls);
            break;
        case 2:
            viewAllCalls(calls);
            break;
        case 3:
            modifyCall(calls);
            break;
        case 4:
            resolveCall(calls);
            break;
        case 5:
            saveDataToFile(calls); // Save data before exiting
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}