#include "peb.h"
#include <cstring>
#include <windows.h>

#include <TlHelp32.h>
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

namespace process {

PPEB getPEB() { return (PPEB)__readgsqword(0x60); }

uintptr_t get_module_ba(DWORD pid, const char *modName) {
  uintptr_t modBaseAddr = 0;
  HANDLE hSnap =
      CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
  if (hSnap != INVALID_HANDLE_VALUE) {
    MODULEENTRY32 modEntry;
    modEntry.dwSize = sizeof(modEntry);
    if (Module32First(hSnap, &modEntry)) {
      do {
        if (strcmp(modEntry.szModule, modName)) {
          modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
          break;
        }
      } while (Module32Next(hSnap, &modEntry));
    }
  }
  CloseHandle(hSnap);
  return modBaseAddr;
}

DWORD pid_from_windows_title(LPCSTR windowTitle) {
  HWND myWindow = FindWindow(NULL, windowTitle);
  DWORD PID;
  GetWindowThreadProcessId(myWindow, &PID);
  return (PID);
}

DWORD pid_from_processname(LPCSTR execName) {

  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(PROCESSENTRY32);
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
  if (Process32First(snapshot, &entry) == TRUE) {
    while (Process32Next(snapshot, &entry) == TRUE) {
      char *binPath = entry.szExeFile;
      if (!strcmp(binPath, execName)) {
        printf("pid is %lu\n", entry.th32ProcessID);
        return (entry.th32ProcessID);
      }
    }
  }
  return (0);
}

} // namespace process