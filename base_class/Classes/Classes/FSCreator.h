#pragma once
#include "Base.h"
#include "EXT4.h"
#include "Fat16.h"
#include "fat32.h"
#include "NTFS.h"

enum class FStype {NTFS, FAT16, FAT32, EXT4, None};

class FSCreator
{
private:

	FStype DetectFS(BYTE* buffer);

public:

	Base* CreateFS(WCHAR* FSpath);

};

