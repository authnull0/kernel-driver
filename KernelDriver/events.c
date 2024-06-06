#pragma warning (disable : 4047)

#include "events.h"
#include "messages.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallBack(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{

	if (FullImageName == NULL || FullImageName->Buffer == NULL)
	{
		return STATUS_UNSUCCESSFUL;
	}

	//DebugMessage("Image loaded: %ls \n", FullImageName->Buffer);
	

	if (wcsstr(FullImageName->Buffer, L"\\notepad.exe")) 
	{
	
	DebugMessage("Notepad Application is opened!!\n");
	NotePadAddress = ImageInfo->ImageBase;

	DebugMessage("ProcessId: %d \n", ProcessId);

	
	}
	return STATUS_SUCCESS;

}