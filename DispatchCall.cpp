#include "DispatchCall.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

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