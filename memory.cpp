#include "memory.h"
#include <winnt.h>

template <typename T>
DWORD change_memory_protection(HANDLE proc, LPVOID adr, DWORD prot) {
  DWORD oldProt;
  VirtualProtectEx(proc, adr, sizeof(T), prot, &oldProt);
  return oldProt;
}

template <typename T> BOOL read_memory(HANDLE proc, LPVOID adr, T *val) {
  BOOL ret;

  ret = ReadProcessMemory(proc, adr, val, sizeof(T), NULL);

  return (ret);
}

template BOOL read_memory<int>(HANDLE proc, LPVOID adr, int *val);
template BOOL read_memory<float>(HANDLE proc, LPVOID adr, float *val);
template BOOL read_memory<BYTE>(HANDLE proc, LPVOID adr, BYTE *val);
template BOOL read_memory<WORD>(HANDLE proc, LPVOID adr, WORD *val);
template BOOL read_memory<DWORD>(HANDLE proc, LPVOID adr, DWORD *val);
template BOOL read_memory<DWORDLONG>(HANDLE proc, LPVOID adr, DWORDLONG *val);

template <typename T> BOOL write_memory(HANDLE proc, LPVOID adr, T val) {
  BOOL ret;

  ret = WriteProcessMemory(proc, adr, &val, sizeof(T), NULL);
  return (ret);
}

template BOOL write_memory<int>(HANDLE proc, LPVOID adr, int val);
template BOOL write_memory<float>(HANDLE proc, LPVOID adr, float val);
template BOOL write_memory<BYTE>(HANDLE proc, LPVOID adr, BYTE val);
template BOOL write_memory<WORD>(HANDLE proc, LPVOID adr, WORD val);
template BOOL write_memory<DWORD>(HANDLE proc, LPVOID adr, DWORD val);
template BOOL write_memory<DWORDLONG>(HANDLE proc, LPVOID adr, DWORDLONG val);