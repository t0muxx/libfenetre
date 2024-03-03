#ifndef __ERRORS_H
#define __ERRORS_H

#include <windows.h>

#include <cstdio>
#include <cstring>
#include <errhandlingapi.h>
#include <minwinbase.h>
#include <processthreadsapi.h>
#include <string>
#include <strsafe.h>
#include <winnt.h>

namespace errors {
void error_exit(LPSTR function_name);
DWORD error_print(std::string function_name);
} // namespace errors

#endif