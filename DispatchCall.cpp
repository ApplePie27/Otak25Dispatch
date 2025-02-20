#include "DispatchCall.h"
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// Helper function to convert time_point to string
string safeTimeToString(const chrono::system_clock::time_point& timePoint) {
    time_t time = chrono::system_clock::to_time_t(timePoint);
    char buffer[26]; // Buffer to hold the time string

    // Use ctime_s if available, otherwise fall back to ctime
#ifdef _WIN32
    if (ctime_s(buffer, sizeof(buffer), &time) {
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

// Helper function to extract the numeric part of the report number
int extractReportNumber(const string& reportNumber) {
    size_t dashPos = reportNumber.find('-');
    if (dashPos != string::npos) {
        string numStr = reportNumber.substr(dashPos + 1);
        try {
            return stoi(numStr);
        }
        catch (const invalid_argument&) {
            return 0; // Default to 0 if parsing fails
        }
    }
    return 0; // Default to 0 if no dash is found
}

// Initialize reportCounter based on the highest report number in the file
int initializeReportCounter() {
    ifstream txtFile("dispatch_log.txt");
    if (!txtFile.is_open()) {
        return 0; // No file exists, start from 0
    }

    int maxReportNumber = 0;
    string line;
    while (getline(txtFile, line)) {
        if (line.find("Report Number: ") != string::npos) {
            string reportNumber = line.substr(14);
            int currentNumber = extractReportNumber(reportNumber);
            if (currentNumber > maxReportNumber) {
                maxReportNumber = currentNumber;
            }
        }
    }

    txtFile.close();
    return maxReportNumber;
}

string generateReportNumber() {
    static int reportCounter = initializeReportCounter(); // Initialize based on file
    return "REPORT-" + to_string(++reportCounter);
}