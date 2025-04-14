#pragma warning(disable : 4047)

#include "events.h"
#include "guidedhacking.h"
#include "data.h"
#include <ntddk.h>

// Correctly defined image load callback
VOID ImageLoadCallback(
    PUNICODE_STRING FullImageName,
    HANDLE ProcessId,
    PIMAGE_INFO ImageInfo
)
{
    if (!FullImageName || !FullImageName->Buffer || !ImageInfo)
        return;

    DebugMessage("Image Loaded: %ls", FullImageName->Buffer);

    if (wcsstr(FullImageName->Buffer, L"\\Black Mesa\\bms\\bin\\client.dll")) {
        DebugMessage("Black Mesa DLL found!");

        BlackMesaDLLAddress = BlackMesaDLLAddress = (ULONG)(ULONG_PTR)ImageInfo->ImageBase;

        DebugMessage("Image address: %p", ImageInfo->ImageBase);
    }
}
