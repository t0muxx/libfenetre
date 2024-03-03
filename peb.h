#ifndef __PEB__H
#define __PEB__H

#include <Windows.h>

#include <SubAuth.h>

//
// The PEB_LDR_DATA, LDR_DATA_TABLE_ENTRY, RTL_USER_PROCESS_PARAMETERS, PEB
// and TEB structures are subject to changes between Windows releases; thus,
// the field offsets and reserved fields may change. The reserved fields are
// reserved for use only by the Windows operating systems. Do not assume a
// maximum size for these structures.
//
// Instead of using the InMemoryOrderModuleList field of the
//     LDR_DATA_TABLE_ENTRY structure, use the Win32 API EnumProcessModules
//
// Instead of using the IsBeingDebugged field of the PEB structure, use the
//     Win32 APIs IsDebuggerPresent or CheckRemoteDebuggerPresent
//
// Instead of using the SessionId field of the PEB structure, use the Win32
//     APIs GetCurrentProcessId and ProcessIdToSessionId
//
// Instead of using the Tls fields of the TEB structure, use the Win32 APIs
//     TlsAlloc, TlsGetValue, TlsSetValue and TlsFree
//
// Instead of using the ReservedForOle field, use the COM API
//     CoGetContextToken
//
// Sample x86 assembly code that gets the SessionId (subject to change
//     between Windows releases, use the Win32 APIs to make your application
//     resilient to changes)
//     mov     eax,fs:[00000018]
//     mov     eax,[eax+0x30]
//     mov     eax,[eax+0x1d4]
//

//
// N.B. Fields marked as reserved do not necessarily reflect the structure
//      of the real struct. They may simply guarantee that the offets of
//      the exposed fields are correct. When code matches this pattern,
//
//          TYPE1 ExposedField1;
//          BYTE ReservedBytes[b];
//          PVOID ReservedPtrs[p];
//          TYPE2 ExposedField2;
//
//      or that pattern with ReservedBytes and ReservedPtrs swapped, it is
//      likely that 'b' and 'p' are derived from the following system:
//
//          GapThirtyTwo = 4p + b
//          GapSixtyFour = 8p + b
//
//      where GapThirtyTwo is the number of bytes between the two exposed
//      fields in the 32-bit version of the real struct and GapSixtyFour
//      is the number of bytes between the two exposed fields in the 64-bit
//      version of the real struct.
//
//      Also note that such code must take into account the alignment of
//      the ReservedPtrs field.
//

typedef struct _PEB_LDR_DATA {
  BYTE Reserved1[8];
  PVOID Reserved2[3];
  LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY {
  PVOID Reserved1[2];
  LIST_ENTRY InMemoryOrderLinks;
  PVOID Reserved2[2];
  PVOID DllBase;
  PVOID Reserved3[2];
  UNICODE_STRING FullDllName;
  BYTE Reserved4[8];
  PVOID Reserved5[3];
#pragma warning(push)
#pragma warning(disable : 4201) // we'll always use the Microsoft compiler
  union {
    ULONG CheckSum;
    PVOID Reserved6;
  } DUMMYUNIONNAME;
#pragma warning(pop)
  ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
  BYTE Reserved1[16];
  PVOID Reserved2[10];
  UNICODE_STRING ImagePathName;
  UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef VOID(NTAPI *PPS_POST_PROCESS_INIT_ROUTINE)(VOID);

typedef struct _PEB {
  BYTE Reserved1[2];
  BYTE BeingDebugged;
  BYTE Reserved2[1];
  PVOID Reserved3[2];
  PPEB_LDR_DATA Ldr;
  PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
  PVOID Reserved4[3];
  PVOID AtlThunkSListPtr;
  PVOID Reserved5;
  ULONG Reserved6;
  PVOID Reserved7;
  ULONG Reserved8;
  ULONG AtlThunkSListPtr32;
  PVOID Reserved9[45];
  BYTE Reserved10[96];
  PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
  BYTE Reserved11[128];
  PVOID Reserved12[1];
  ULONG SessionId;
} PEB, *PPEB;

typedef struct _TEB {
  PVOID Reserved1[12];
  PPEB ProcessEnvironmentBlock;
  PVOID Reserved2[399];
  BYTE Reserved3[1952];
  PVOID TlsSlots[64];
  BYTE Reserved4[8];
  PVOID Reserved5[26];
  PVOID ReservedForOle; // Windows 2000 only
  PVOID Reserved6[4];
  PVOID TlsExpansionSlots;
} TEB, *PTEB;

typedef struct _OBJECT_ATTRIBUTES {
  ULONG Length;
  HANDLE RootDirectory;
  PUNICODE_STRING ObjectName;
  ULONG Attributes;
  PVOID SecurityDescriptor;
  PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

#endif