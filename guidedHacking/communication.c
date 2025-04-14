#include "communication.h"
#include "guidedhacking.h"
#include "data.h"

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    DebugMessage("Connection terminated");

    return STATUS_SUCCESS;
}

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;

    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    DebugMessage("Create call was called. Connection established");

    return STATUS_SUCCESS;
}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
    UNREFERENCED_PARAMETER(DeviceObject);

    NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
    ULONG bytesReturned = 0;

    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
    ULONG controlCode = stack->Parameters.DeviceIoControl.IoControlCode;

    switch (controlCode)
    {
    case IO_GET_CLIENT_ADDRESS:
    {
        if (Irp->AssociatedIrp.SystemBuffer)
        {
            PULONG output = (PULONG)Irp->AssociatedIrp.SystemBuffer;
            *output = BlackMesaDLLAddress;

            status = STATUS_SUCCESS;
            bytesReturned = sizeof(ULONG);

            DebugMessage("Client requested client address.");
        }
        else
        {
            status = STATUS_INVALID_PARAMETER;
            DebugMessage("Invalid system buffer.");
        }
        break;
    }

    default:
        DebugMessage("Unknown IOCTL control code.");
        break;
    }

    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = bytesReturned;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return status;
}
