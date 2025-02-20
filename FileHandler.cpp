#include "FileHandler.h"
#include "DispatchCall.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Implementation of safeTimeToString
string safeTimeToString(const chrono::system_clock::time_point& timePoint) {
    time_t time = chrono::system_clock::to_time_t(timePoint);
    char buffer[26]; // Buffer to hold the time string

    // Use ctime_s if available, otherwise fall back to ctime
#ifdef _WIN32
    if (ctime_s(buffer, sizeof(buffer), &time) != 0) {
        return "Invalid Time";
    }
#else
    if (ctime_r(&time, buffer) == nullptr) {
        return "Invalid Time";
    }
#endif

    // Remove the newline character added by ctime
    string timeStr(buffer);
    timeStr.erase(timeStr.find_last_not_of('\n') + 1);
    return timeStr;
}

// Implementation of parseTime
chrono::system_clock::time_point parseTime(const string& timeStr) {
    tm tm = {};
    istringstream ss(timeStr);
    ss >> get_time(&tm, "%a %b %d %H:%M:%S %Y"); // Parse time string
    if (ss.fail()) {
        throw runtime_error("Failed to parse time: " + timeStr);
    }
    return chrono::system_clock::from_time_t(mktime(&tm));
}

void logDispatchCall(const DispatchCall& call) {
    ofstream txtFile("dispatch_log.txt", ios::app);
    ofstream csvFile("dispatch_log.csv", ios::app);

    if (!txtFile.is_open() || !csvFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string startTimeStr = safeTimeToString(call.startTime);
    string endTimeStr = (call.endTime != chrono::system_clock::time_point{})
        ? safeTimeToString(call.endTime)
        : "Not Resolved";

    // Log to .txt file
    txtFile << "Report Number: " << call.reportNumber << "\n"
        << "Location: " << call.location << "\n"
        << "Code/Situation: " << call.codeSituation << "\n"
        << "Caller ID: " << call.callerID << "\n"
        << "Description: " << call.description << "\n"
        << "Contact Route: " << call.contactRoute << "\n"
        << "Resolved: " << (call.resolved ? "Yes" : "No") << "\n"
        << "Start Time: " << startTimeStr << "\n" // Add newline after Start Time
        << "End Time: " << endTimeStr << "\n"     // Add newline after End Time
        << "--------------------------\n";

    // Log to .csv file
    csvFile << call.reportNumber << ","
        << call.location << ","
        << call.codeSituation << ","
        << call.callerID << ","
        << call.description << ","
        << call.contactRoute << ","
        << (call.resolved ? "Yes" : "No") << ","
        << startTimeStr << ","
        << endTimeStr << "\n";

    txtFile.close();
    csvFile.close();
}

void saveDataToFile(const std::vector<DispatchCall>& calls) {
    ofstream txtFile("dispatch_log.txt");
    ofstream csvFile("dispatch_log.csv");

    for (const auto& call : calls) {
        logDispatchCall(call); // Re-log all calls to update files
    }

    cout << "Data saved to files successfully!" << endl;
}

bool loadDataFromFile(std::vector<DispatchCall>& calls) {
    ifstream txtFile("dispatch_log.txt");
    if (!txtFile.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return false;
    }

    calls.clear(); // Clear existing data

    string line;
    DispatchCall call;
    while (getline(txtFile, line)) {
        if (line.find("Report Number: ") != string::npos) {
            call.reportNumber = line.substr(14);
        }
        else if (line.find("Location: ") != string::npos) {
            call.location = line.substr(10);
        }
        else if (line.find("Code/Situation: ") != string::npos) {
            call.codeSituation = line.substr(16);
        }
        else if (line.find("Caller ID: ") != string::npos) {
            call.callerID = line.substr(11);
        }
        else if (line.find("Description: ") != string::npos) {
            call.description = line.substr(13);
        }
        else if (line.find("Contact Route: ") != string::npos) {
            call.contactRoute = line.substr(15);
        }
        else if (line.find("Resolved: ") != string::npos) {
            call.resolved = (line.substr(10) == "Yes");
        }
        else if (line.find("Start Time: ") != string::npos) {
            string timeStr = line.substr(12);
            try {
                call.startTime = parseTime(timeStr); // Parse start time
            }
            catch (const exception& e) {
                cerr << "Error parsing Start Time: " << e.what() << endl;
                call.startTime = chrono::system_clock::time_point{};
            }
        }
        else if (line.find("End Time: ") != string::npos) {
            string timeStr = line.substr(10);
            if (timeStr != "Not Resolved") {
                try {
                    call.endTime = parseTime(timeStr); // Parse end time
                }
                catch (const exception& e) {
                    cerr << "Error parsing End Time: " << e.what() << endl;
                    call.endTime = chrono::system_clock::time_point{};
                }
            }
            else {
                call.endTime = chrono::system_clock::time_point{};
            }
        }
        else if (line.find("--------------------------") != string::npos) {
            // End of a call entry
            calls.push_back(call);
            call = DispatchCall{}; // Reset for the next call
        }
    }

    txtFile.close();
    return true;
}