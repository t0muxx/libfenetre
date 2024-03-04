#include <windows.h>

#include <cstdio>
#include <iostream>
#include <memoryapi.h>
#include <minwindef.h>
#include <processthreadsapi.h>
#include <string>
#include <winnt.h>


#include "errors.h"

namespace injection {

using namespace errors;

int reopen_streams() {
  if (!AllocConsole()) {
    return (-1);
  }
  FILE *fDummy;
  freopen_s(&fDummy, "CONOUT$", "w", stdout);
  freopen_s(&fDummy, "CONOUT$", "w", stderr);
  freopen_s(&fDummy, "CONIN$", "r", stdin);
  std::cout.clear();
  std::clog.clear();
  std::cerr.clear();
  std::cin.clear();

  return (0);
}

static BOOL inject_into_handle(HANDLE proc, std::string dllPath) {

  DWORD errcode;

  if (GetFileAttributesA(dllPath.c_str()) == INVALID_FILE_ATTRIBUTES) {
    fprintf(stderr, "%s not found\n", dllPath.c_str());
    return (-1);
  }

  size_t nameLen = strlen(dllPath.c_str()) + 1;
  LPVOID remoteStr =
      VirtualAllocEx(proc, NULL, nameLen, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  if (remoteStr == NULL) {
    errcode = error_print(std::string("VirtualAllocEx"));
    return (errcode);
  }

  if (WriteProcessMemory(proc, remoteStr, dllPath.c_str(), nameLen, NULL) ==
      FALSE) {
    errcode = error_print(std::string("WriteProcessMemory"));
    return (errcode);
  }

  HMODULE k32 = GetModuleHandleA("kernel32.dll");
  if (k32 == NULL) {
    errcode = error_print(std::string("GetModuleHandleA"));
    return (errcode);
  }
  LPVOID addrLoadLibrary = (LPVOID)GetProcAddress(k32, "LoadLibraryA");
  if (addrLoadLibrary == NULL) {
    errcode = error_print(std::string("LoadLibraryA"));
    return (errcode);
  }

  HANDLE thread = CreateRemoteThread(proc, NULL, NULL,
                                     (LPTHREAD_START_ROUTINE)addrLoadLibrary,
                                     remoteStr, NULL, NULL);
  if (thread == NULL) {
    errcode = error_print(std::string("CreateRemoteThread"));
    return (errcode);
  }

  WaitForSingleObject(thread, INFINITE);
  CloseHandle(thread);
  return (TRUE);
}

/// Inject dll into remote process using
/// classical OpenProcess/CreateRemoteThread(LoadLibraryA)
int inject_dll(DWORD pid, std::string dllPath) {
  // OpenProcess
  HANDLE proc;
  HANDLE th;
  LPVOID addr;
  BOOL ret;
  char *str1, *str2;
  DWORD errcode;

  ret = 0;
  proc = NULL;
  proc = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
  if (proc == NULL) {
    errcode = error_print(std::string("OpenProcess"));
    return (errcode);
  }
  inject_into_handle(proc, dllPath);

  CloseHandle(proc);
  return (0);
}
} // namespace injection