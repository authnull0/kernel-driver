#pragma warning (disable : 4100 4047 4024)

#include "kerneldriver.h"
#include "invoke.h"
#include "events.h"
#include "messages.h"
#include "data.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);
	pDriverObject->DriverUnload = UnloadDriver;
	DebugMessage("Welcome!!!");

	PsSetLoadImageNotifyRoutine(ImageLoadCallBack);

	RtlInitUnicodeString(&dev, L"\\Device\\kerneldriver");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\kerneldriver");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)

{
	UNREFERENCED_PARAMETER(pDriverObject);
	DebugMessage("Goodbye!!!");

	PsRemoveLoadImageNotifyRoutine(ImageLoadCallBack);

	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);


	return STATUS_SUCCESS;


}
