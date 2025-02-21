#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "DispatchCall.h"
#include <vector>
#include <fstream>

// Function declarations
void logDispatchCall(const DispatchCall& call);
void saveDataToFile(const std::vector<DispatchCall>& calls);
bool loadDataFromFile(std::vector<DispatchCall>& calls);
chrono::system_clock::time_point parseTime(const string& timeStr);

#endif