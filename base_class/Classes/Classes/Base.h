//���� ��������� ���������� � ��������� ������� �������� ������------------------//
//���������� ������� �����(�����) ������������ ������� � Base.h------------------//
#pragma once
#include <windows.h>

class Base {
public:
//�������� �������� � ���������� ������������ � ������ � ��� �����������---------//
//-------------------------------------------------------------------------------//
	const int sector_size = 512;	// ������ �������
	WCHAR* path;					// ���� �� �����
	int cluster_size;				// ������ �������� (�� ���������� ���������)
	HANDLE file_handle;				// ���������� �����
//��������� ������� �������� ������----------------------------------------------//
//-------------------------------------------------------------------------------//
	virtual void getClusterData(
		HANDLE file_handle,
		unsigned int cluster_number,
		BYTE* read_buffer) = 0;
	virtual int getClusterSize(HANDLE file_handle) = 0;
	HANDLE getFileHandle();
//��������� ������������ � ����������� �������� ������---------------------------//
//-------------------------------------------------------------------------------//
	Base(WCHAR* file_path);
	Base();							// ����������� ����������
	~Base();
};
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//