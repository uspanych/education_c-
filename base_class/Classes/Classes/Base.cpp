//���� ��������� ���������� ������� �������� ������------------------------------//
//���������� ������� �����(�����) ������������ ������� � Base.h------------------//
#include <iostream>
#include "Base.h"
//���������� ������ ��� ���� ������ ������ ������ ������-------------------------//
//-------------------------------------------------------------------------------//
unsigned __int64 Base::ReadBytes(
	BYTE* read_buffer, 
	unsigned int offset,
	unsigned int bytes_to_read)
{
	if (bytes_to_read > 8)
	{
		std::cout << "Only can read up to 8 bytes";
		return 0;
	}
	else 
	{
		unsigned __int64 result = NULL;
		for (int i = 0; i < bytes_to_read; i++)
		{
			result = static_cast<unsigned long long>(read_buffer[offset+i]) << (i*8) | result;
		}
		return result;
	}
}
//���������� ������������ � ����������� ������-----------------------------------//
//-------------------------------------------------------------------------------//
Base::Base(WCHAR* file_path)
{
	cluster_size = NULL;
	file_handle = CreateFileW(
		file_path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	// ���������� ������ ��� �������� ����������� ����� //
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Can't open file with error code: " << GetLastError() << '\n';
		file_handle=NULL;
	}
}
Base::Base()
{
	cluster_size = NULL;
	file_handle = NULL;
}
Base::~Base()
{
	CloseHandle(file_handle);
}
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//