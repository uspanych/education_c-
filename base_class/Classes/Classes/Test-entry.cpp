#pragma once
#include "EXT4.h"
#include "Fat16.h"
#include "fat32.h"
#include "NTFS.h"
#include "iostream"

using namespace std;

/*
int main()
{
	WCHAR disk[] = L"\\\\.\\C:";
	Base* fs = new NTFS(disk);
	int CS = fs->getClusterSize();
	cout << CS;
}
*/