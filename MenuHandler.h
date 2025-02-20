#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include "DispatchCall.h"
#include <vector>

// Function declarations
void addCall(std::vector<DispatchCall>& calls);
void viewAllCalls(const std::vector<DispatchCall>& calls);
void modifyCall(std::vector<DispatchCall>& calls);
void resolveCall(std::vector<DispatchCall>& calls);

#endif