#include "invoke.h"
#include "messages.h"
#include "events.h"
#include "data.h"


NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information= 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	DebugMessage("CreateCall was called, connection established!!");
	return STATUS_SUCCESS;

}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
	UNREFERENCED_PARAMETER(DeviceObject);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	DebugMessage("Connection Terminated!!");
	return STATUS_SUCCESS;

}

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp) {

	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS Status = STATUS_UNSUCCESSFUL;
	ULONG ByteIO = 0;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;
	if (ControlCode == IO_GET_ADDRESS) {

		PULONG Output = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*Output = NotePadAddress;

		DebugMessage("Address Requested!!");
		Status = STATUS_SUCCESS;
		ByteIO = sizeof(*Output);
			
	}

	else
	{
		ByteIO = 0;

	}

	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = ByteIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return Status;


	





}

