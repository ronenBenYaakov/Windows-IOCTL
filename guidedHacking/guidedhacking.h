#pragma once
#pragma warning(disable : 4100)

#include <ntifs.h>

extern NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegisteryPath);
NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject);

#define DebugMessage(x, ...) DbgPrintEx(0, 0, x, __VA_ARGS__)