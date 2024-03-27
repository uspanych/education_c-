//���� ��������� ���������� � ��������� ������� ������ NTFS----------------------//
//���������� ������� �����(�����) ������������ ������� � Base.h------------------//
#pragma once
#include "Base.h"

class NTFS :
    public Base
{
public:
//��������� ���������������� ������� ������ ���������----------------------------//
//-------------------------------------------------------------------------------//
    int getClusterSize();
    void getClusterData( 
        unsigned int cluster_number,
        BYTE* read_buffer);
//��������� ���������������� ������� ������ ���������----------------------------//
//-------------------------------------------------------------------------------//
    NTFS(WCHAR* file_path);
    ~NTFS();
};
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
