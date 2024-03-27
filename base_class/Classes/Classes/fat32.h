#pragma once
#include "Base.h"
class FAT32 :
	public Base
{
public:
//��������� ������� �������� ������----------------------------------------------//
//-------------------------------------------------------------------------------//
	void getClusterData(
		unsigned int cluster_number,
		BYTE* read_buffer);

	int getClusterSize();

//��������� ������������ � ����������� �������� ������---------------------------//
//-------------------------------------------------------------------------------//
	FAT32(WCHAR* file_path);
	~FAT32();
};
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//


