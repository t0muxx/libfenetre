#ifndef __MEMORY_H
#define __MEMORY_H

#include <Windows.h>

template <typename T>
DWORD change_memory_protection(HANDLE proc, LPVOID adr, DWORD prot);

template <typename T> BOOL write_memory(HANDLE proc, LPVOID adr, T val);

template <typename T> T read_memory(HANDLE proc, LPVOID adr);

#endif