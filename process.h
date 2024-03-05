#ifndef __PROCESS__H
#define __PROCESS__H

#include "peb.h"

namespace process {
PPEB getPEB();

uintptr_t get_module_ba(DWORD pid, const char *modName);
uintptr_t get_exe_ba(HANDLE proc);
DWORD pid_from_windows_title(LPCSTR windowTitle);
DWORD pid_from_processname(LPCSTR execName);

} // namespace process

#endif