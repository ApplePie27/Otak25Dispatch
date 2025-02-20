#include "DispatchCall.h"
#include <ctime>

string generateReportNumber() {
    static int reportCounter = 0;
    return "REPORT-" + to_string(++reportCounter);
}

string safeTimeToString(const chrono::system_clock::time_point& timePoint) {
    time_t time = chrono::system_clock::to_time_t(timePoint);
    char buffer[26]; // Buffer to hold the time string

    // Use ctime_s if available, otherwise fall back to ctime
#ifdef _WIN32
    if (ctime_s(buffer, sizeof(buffer), &time)) {
        return "Invalid Time";
    }
#else
    if (ctime_r(&time, buffer) == nullptr) {
        return "Invalid Time";
    }
#endif

    return string(buffer);
}