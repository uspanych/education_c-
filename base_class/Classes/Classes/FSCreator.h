#pragma once
#include "Base.h"

enum class FStype {NTFS, FAT16, FAT32, EXT4};

class FSCreator
{
private:

	FStype DetectFS(BYTE* buffer);

public:

	Base* CreateFS(WCHAR* FSpath);

};

