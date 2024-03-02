#ifndef PROCESS__H
#define PROCESS__H

#include "peb.h"

namespace process {
PPEB getPEB();

uintptr_t get_module_ba(DWORD pid, const wchar_t *modName);
DWORD pid_from_windows_title(LPCWSTR windowTitle);
DWORD pid_from_processname(LPCWSTR execName);

} // namespace process

#endif