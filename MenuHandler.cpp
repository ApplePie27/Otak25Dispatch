#include "MenuHandler.h"
#include "FileHandler.h"
#include <iostream>
#include <algorithm> // For std::remove_if and std::isspace

using namespace std;

// Helper function to trim whitespace from a string
string trim(const string& str) {
    auto start = str.begin();
    auto end = str.end();
    while (start != end && isspace(*start)) {
        start++;
    }
    while (end != start && isspace(*(end - 1))) {
        end--;
    }
    return string(start, end);
}

void addCall(vector<DispatchCall>& calls) {
    DispatchCall call;
    call.reportNumber = generateReportNumber();

    cout << "\n" << "Enter Location: ";
    getline(cin, call.location);

    cout << "Enter Code/Situation: ";
    getline(cin, call.codeSituation);

    cout << "Enter Caller ID: ";
    getline(cin, call.callerID);

    cout << "Enter Description: ";
    getline(cin, call.description);

    cout << "Enter Contact Route: ";
    getline(cin, call.contactRoute);

    cout << "Was the call resolved? (1 for Yes, 0 for No): ";
    cin >> call.resolved;
    cin.ignore(); // Clear the input buffer

    call.startTime = chrono::system_clock::now();
    if (call.resolved) {
        call.endTime = chrono::system_clock::now();
    }
    else {
        call.endTime = chrono::system_clock::time_point{};
    }

    calls.push_back(call); // Add call to memory
    logDispatchCall(call); // Log call to files

    cout << "Dispatch call added and logged successfully!" << endl;
}

void viewAllCalls(const vector<DispatchCall>& calls) {
    if (calls.empty()) {
        cout << "No calls found!" << endl;
        return;
    }

    for (const auto& call : calls) {
        string startTimeStr = safeTimeToString(call.startTime);
        string endTimeStr = (call.endTime != chrono::system_clock::time_point{})
            ? safeTimeToString(call.endTime)
            : "Not Resolved";

        cout << "\n" << "Report Number: " << call.reportNumber << "\n"
            << "Location: " << call.location << "\n"
            << "Code/Situation: " << call.codeSituation << "\n"
            << "Caller ID: " << call.callerID << "\n"
            << "Description: " << call.description << "\n"
            << "Contact Route: " << call.contactRoute << "\n"
            << "Resolved: " << (call.resolved ? "Yes" : "No") << "\n"
            << "Start Time: " << startTimeStr << "\n"
            << "End Time: " << endTimeStr << "\n"
            << "--------------------------\n";
    }
}

void modifyCall(vector<DispatchCall>& calls) {
    string reportNumber;
    cout << "\n" << "Enter the Report Number of the call to modify: ";
    getline(cin, reportNumber);
    reportNumber = trim(reportNumber); // Trim whitespace

    for (auto& call : calls) {
        if (trim(call.reportNumber) == reportNumber) {
            cout << "Current Details:\n";
            string startTimeStr = safeTimeToString(call.startTime);
            string endTimeStr = (call.endTime != chrono::system_clock::time_point{})
                ? safeTimeToString(call.endTime)
                : "Not Resolved";

            cout << "Report Number: " << call.reportNumber << "\n"
                << "1. Location: " << call.location << "\n"
                << "2. Code/Situation: " << call.codeSituation << "\n"
                << "3. Caller ID: " << call.callerID << "\n"
                << "4. Description: " << call.description << "\n"
                << "5. Contact Route: " << call.contactRoute << "\n"
                << "6. Resolved: " << (call.resolved ? "Yes" : "No") << "\n"
                << "7. Resolve the Report (Set Resolved to Yes)\n"
                << "Start Time: " << startTimeStr << "\n"
                << "End Time: " << endTimeStr << "\n";

            int fieldChoice;
            cout << "Enter the number of the field to modify (1-7): ";
            cin >> fieldChoice;
            cin.ignore(); // Clear the input buffer

            switch (fieldChoice) {
            case 1:
                cout << "Enter new Location: ";
                getline(cin, call.location);
                break;
            case 2:
                cout << "Enter new Code/Situation: ";
                getline(cin, call.codeSituation);
                break;
            case 3:
                cout << "Enter new Caller ID: ";
                getline(cin, call.callerID);
                break;
            case 4:
                cout << "Enter new Description: ";
                getline(cin, call.description);
                break;
            case 5:
                cout << "Enter new Contact Route: ";
                getline(cin, call.contactRoute);
                break;
            case 6:
                cout << "Was the call resolved? (1 for Yes, 0 for No): ";
                cin >> call.resolved;
                cin.ignore(); // Clear the input buffer
                break;
            case 7:
                if (call.resolved) {
                    cout << "This call is already resolved!" << endl;
                }
                else {
                    call.resolved = true;
                    call.endTime = chrono::system_clock::now(); // Set end time to current time
                    cout << "Call resolved successfully!" << endl;
                }
                break;
            default:
                cout << "Invalid choice! No changes made." << endl;
                return;
            }

            cout << "Call details updated successfully!" << endl;
            return;
        }
    }

    cout << "Call with Report Number " << reportNumber << " not found!" << endl;
}

void resolveCall(vector<DispatchCall>& calls) {
    string reportNumber;
    cout << "Enter the Report Number of the call to resolve: ";
    getline(cin, reportNumber);
    reportNumber = trim(reportNumber); // Trim whitespace

    for (auto& call : calls) {
        if (trim(call.reportNumber) == reportNumber) {
            if (call.resolved) {
                cout << "This call is already resolved!" << endl;
            }
            else {
                call.resolved = true;
                call.endTime = chrono::system_clock::now(); // Set end time to current time
                cout << "Call resolved successfully!" << endl;
            }
            return;
        }
    }

    cout << "Call with Report Number " << reportNumber << " not found!" << endl;
}