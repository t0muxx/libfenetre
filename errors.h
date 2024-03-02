#include <windows.h>

#include <cstdio>
#include <cstring>
#include <errhandlingapi.h>
#include <minwinbase.h>
#include <processthreadsapi.h>
#include <strsafe.h>
#include <winnt.h>

namespace error {
void error_exit(LPSTR function_name);
}