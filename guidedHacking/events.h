#pragma once
#include <ntifs.h>

VOID ImageLoadCallback(PUNICODE_STRING pFullImageFilePath, HANDLE hProcess, PIMAGE_INFO pImageInfo);