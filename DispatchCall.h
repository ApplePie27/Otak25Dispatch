#ifndef DISPATCHCALL_H
#define DISPATCHCALL_H

#include <string>
#include <chrono>

using namespace std;

struct DispatchCall {
    string location = "";
    string codeSituation = "";
    string callerID = "";
    string description = "";
    string contactRoute = "";
    bool resolved = false;
    string reportNumber = "";
    chrono::system_clock::time_point startTime;
    chrono::system_clock::time_point endTime{};
};

// Function declarations
string generateReportNumber();
string safeTimeToString(const chrono::system_clock::time_point& timePoint);

#endif