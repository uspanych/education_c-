#include "FSCreator.h"
#include <iostream>
#include <Windows.h>

FStype FSCreator::DetectFS(BYTE* buffer)
{
	FStype filesystem;

	return filesystem;
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
	
	FStype flesystem = DetectFS(buffer);

	delete[] buffer;

}
