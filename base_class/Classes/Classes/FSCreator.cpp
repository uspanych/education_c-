#include "FSCreator.h"
#include <iostream>
#include <Windows.h>

FSType FSCreator::DetectFS(BYTE* buffer)
{

}


Base* FSCreator::CreateFS(WCHAR* FSpath)
{
	HANDLE handle = CreateFile(
		FSpath,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	BYTE* buffer = new BYTE[2048];
	DWORD pointerstatus = SetFilePointer(handle, 0, 0, FILE_BEGIN);
	BOOL readstatus = ReadFile(handle, buffer, 2048, NULL, NULL);



}
