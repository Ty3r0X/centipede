/* 
 *                           .    .
 *                            )  (
 *      _ _ _ _ _ _ _ _ _ _ _(.--.)
 *    {{ { { { { { { { { { { ( '_')
 *  -----------------------------------------
 *   Centipede - Kernel level capture utility
 *   Brought to you by Ty3r0X & friends ^_^
 *  -----------------------------------------
 *
 *  entrypoint.c - Windows driver initialization boilerplate
 *
 *  Copyright (C) 2024 Patrick D. Covaci <ty3r0x@chaox.ro>
 *  Copyright (C) 2024 Rares Iventa <rares.iventa@gmail.com>
 *
 *  The source is distributed for EDUCATIONAL PURPOSES ONLY!
 *  We discourage the use of our project to commit cybercrimes
 *  or to harm others!
 *
 *  The source is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  FITNESS FOR A PARTICULAR PURPOSE.
 *
 * */

#include <wdm.h>
#include <ntdef.h>
#include <sal.h>
#include <ntddk.h>
#include <wdf.h>

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KmdfCentipedeEvtDeviceAdd;

NTSTATUS DriverEntry(
  _In_ PDRIVER_OBJECT DriverObject,
  _In_ PUNICODE_STRING RegistryPath
)
{
    // NTSTATUS variable to record success or failure
    NTSTATUS status = STATUS_SUCCESS;

    // Allocate the driver configuration object
    WDF_DRIVER_CONFIG config;

    // Print "Hello World" for DriverEntry
    KdPrintEx(( DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[!] Centipede: DriverEntry\n" ));

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, KmdfHelloWorldEvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config, 
                           KmdfCentipedeEvtDeviceAdd
                           );

    // Finally, create the driver object
    status = WdfDriverCreate(DriverObject, 
                             RegistryPath, 
                             WDF_NO_OBJECT_ATTRIBUTES, 
                             &config, 
                             WDF_NO_HANDLE
                             );
    return status;
}
NTSTATUS 
KmdfCentipedeEvtDeviceAdd(
    _In_    WDFDRIVER       Driver, 
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    // We're not using the driver object,
    // so we need to mark it as unreferenced
    UNREFERENCED_PARAMETER(Driver);

    NTSTATUS status;

    // Allocate the device object
    WDFDEVICE hDevice;    

    // Print "Hello World"
    KdPrintEx(( DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "[!] Centipede: KmdfHelloWorldEvtDeviceAdd\n" ));

    // Create the device object
    status = WdfDeviceCreate(&DeviceInit, 
                             WDF_NO_OBJECT_ATTRIBUTES,
                             &hDevice
                             );
    return status;
}

VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("[!] Centipede: Driver Unloaded\n");
}
