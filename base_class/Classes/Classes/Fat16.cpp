#include "Fat16.h"
#include <iostream>
#include <typeinfo>

void Fat16::getClusterData(
	ULONGLONG cluster_number,
	BYTE* read_buffer
)
{
	DWORD dwPtr  = SetFilePointer(
		this->file_handle,
		0,
		0,
		FILE_BEGIN
	);

	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		// Obtain the error code. 
		DWORD dwError = GetLastError();
	}


	BYTE* buffer = new BYTE[this->sector_size];
	bool is_read = ReadFile(
		this->file_handle,
		buffer,
		this->sector_size,
		NULL,
		NULL
	);

	if (!is_read) {
		std::cout << "Can't read cluster data";
	}

	#pragma pack(push, 1) // ��� ������� �� ������ ��������� � ������ ������
	struct TestStruct
	{
		BYTE jump[14];
		UINT16 boot_record_size;
		BYTE fats_table_count;
		UINT16 count_recrod_root;
		BYTE jump2[3];
		BYTE fat_table_size;
	};
	#pragma pack(pop)

	TestStruct* boot_st;
	boot_st = (TestStruct*)buffer;

	// ������ ������������ �������
	int load_sector_size = boot_st->boot_record_size * this->sector_size;

	// ������ ������� ���
	int fat_table_size = boot_st->fat_table_size * this->sector_size;

	// ���-�� ������ ���
	int fat_table_count = boot_st->fats_table_count;

	std::cout << fat_table_count;

	// ������� ���
	int fat_all_size = fat_table_size * fat_table_count;

	// ���������� ������� � �������� ��������
	uint16_t count_root_record = boot_st->count_recrod_root;
	
	// ������ ��������� ��������
	int size_root_directory = count_root_record * 32;

	// �������� ������� ��������
	int cluster_offset_start = load_sector_size + fat_all_size + size_root_directory;
	this->cluster_offset = cluster_offset_start;

	// �������� ������� ��������
	cluster_offset_start += this->cluster_size * (cluster_number - 2);

	DWORD dwPtr1 = SetFilePointer(
		file_handle,
		cluster_offset_start,
		0,
		FILE_BEGIN
	);

	if (dwPtr1 == INVALID_SET_FILE_POINTER)
	{
		// Obtain the error code. 
		DWORD dwError = GetLastError();
	}

	bool is_read1 = ReadFile(
		file_handle,
		read_buffer,
		this->cluster_size,
		NULL,
		NULL
	);
	
	if (!is_read1) {
		std::cout << "Can't read cluster data";
	}
	

}

int Fat16::getClusterInfo()
{	
	SetFilePointer(
		file_handle,
		0,
		0,
		FILE_BEGIN
	);
	BYTE* buffer = new BYTE[sector_size];

	bool is_read = ReadFile(
		file_handle,
		buffer,
		sector_size,
		NULL,
		NULL
		);

	#pragma pack(push,1)
	struct BootRecord
	{
		BYTE jump[32];
		UINT32 sectors_count;;
	};
	#pragma pack(pop)

	BootRecord* boot_st;
	boot_st = (BootRecord*)buffer;
	
	int tom_size = boot_st->sectors_count * 512;
	
	if (is_read) {
		unsigned __int64 sec_count = ReadBytes(buffer, 13, 1);

		delete[] buffer;

		this->cluster_size = sec_count * sector_size;
	}
	else {
		std::cout << "Can't read file";
		return 1;
	}



	this->cluster_count = (tom_size - this->cluster_offset) / this->cluster_size;
	
	return this->cluster_size;

}
