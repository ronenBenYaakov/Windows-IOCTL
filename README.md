# 🧠 Windows IOCTL Kernel Driver – Guided Hacking Edition

This project is a Windows kernel-mode driver demonstrating IOCTL communication, image load notifications, and secure device creation. Built for educational purposes and inspired by Guided Hacking practices.

## 📦 Overview

This driver allows a user-mode application to send IOCTL requests to the kernel, retrieve specific memory addresses (like a DLL image base), and handle basic device operations such as create, close, and control.

## ⚙️ Features

- Kernel-mode device creation
- IOCTL dispatching using `DeviceIoControl`
- Handles `IRP_MJ_CREATE`, `IRP_MJ_CLOSE`, `IRP_MJ_DEVICE_CONTROL`
- Load image notification callback with `PsSetLoadImageNotifyRoutine`
- Communicates DLL base addresses back to user-mode
- Proper cleanup with `IoDeleteDevice` and `IoDeleteSymbolicLink`

## 📂 Directory Structure
guidedHacking/ ├── communication.c # Handles IRP functions and IOCTL logic ├── events.c # Contains image load notification callback ├── data.h # Shared global variables like DLL address ├── guidedhacking.h # Logging macros and headers ├── DriverEntry.c # Entry point, device creation, unload logic ├── README.md # You are here!

## 🔧 Building

Use Visual Studio with the Windows Driver Kit (WDK). Build in `Release | x64`.

## 🧪 Testing

1. Load the driver with `OSR Loader` or `SC.exe`.
2. Use a user-mode app to call `DeviceIoControl` with your custom IOCTL.
3. Check debug messages with `DbgView`.

## 📌 Notes

- Make sure to disable Driver Signature Enforcement if testing on a non-signed driver.
- The IOCTL handler only responds to `IO_GET_CLIENT_ADDRESS` defined in a shared header.
- The image load callback watches for `client.dll` inside `Black Mesa`.

## 🛡️ Disclaimer

This is for educational and reverse-engineering learning purposes only. Do **not** use this for malicious intent.

## 🧠 Credits

- Guided Hacking
- Microsoft Docs
- Reverse Engineering communities
