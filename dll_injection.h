#ifndef __DLL_INJECTION_H
#define __DLL_INJECTION_H

#include <windows.h>

#include <string>

namespace injection {
int inject_dll(DWORD pid, std::string dllPath);
int reopen_streams();
} // namespace injection

#endif