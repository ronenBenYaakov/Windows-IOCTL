#include "guidedhacking.h"
#pragma warning(disable : 4100)

#include <ntddk.h>
#include "events.h"
#include "data.h"
#include "communication.h"

PDEVICE_OBJECT pDeviceObject = NULL;
UNICODE_STRING dos, dev;

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
    UNREFERENCED_PARAMETER(pRegistryPath);

    pDriverObject->DriverUnload = UnloadDriver;
    pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
    pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
    pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

    RtlInitUnicodeString(&dos, L"\\DosDevices\\guidedhacking");
    RtlInitUnicodeString(&dev, L"\\Device\\guidedhacking");

    NTSTATUS status = IoCreateDevice(
        pDriverObject,
        0,
        &dev,
        FILE_DEVICE_UNKNOWN,
        FILE_DEVICE_SECURE_OPEN,
        FALSE,
        &pDeviceObject
    );

    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] IoCreateDevice failed: 0x%X\n", status);
        return status;
    }

    status = IoCreateSymbolicLink(&dos, &dev);
    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] IoCreateSymbolicLink failed: 0x%X\n", status);
        IoDeleteDevice(pDeviceObject);
        return status;
    }

    status = PsSetLoadImageNotifyRoutine(ImageLoadCallback);
    if (!NT_SUCCESS(status)) {
        DbgPrint("[-] PsSetLoadImageNotifyRoutine failed: 0x%X\n", status);
        IoDeleteSymbolicLink(&dos);
        IoDeleteDevice(pDeviceObject);
        return status;
    }

    pDeviceObject->Flags |= DO_DIRECT_IO;
    pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

    DbgPrint("[+] Driver loaded successfully\n");

    return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
    IoDeleteSymbolicLink(&dos);
    IoDeleteDevice(pDriverObject->DeviceObject);
    PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);

    IoDeleteSymbolicLink(&dos);
    IoDeleteDevice(&dev);

    DbgPrint("[+] Driver unloaded\n");

    return STATUS_SUCCESS;
}
