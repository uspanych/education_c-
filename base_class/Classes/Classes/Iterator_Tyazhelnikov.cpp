#include <iostream>
#include "Cluster_class.h"
#include "EXT4.h"
#include "Base.h"
#include "NTFS.h"
#include "Fat16.h"
#include "fat32.h"

using namespace std;

Container::Container()
{
	Items = new Cluster[100];
	Count = 0;
}
void Container::AddItem(const Cluster &newItem)
{
	Items[Count] = newItem;
	Count++;
}
int Container::GetCount() const
{
	return Count;
}
Cluster::Cluster(ULONGLONG cluster_num, WCHAR* file_path)
{
	cluster_number = cluster_num;
	filename = file_path;
}
Iterator<Cluster>* Container::GetIterator()
{
	return new ContainerIterator(Items, Count);
}

int main()
{
	WCHAR A[] = L"\\\\.\\F:";
	WCHAR* path = A;

	Container myContainer;

	for (int i = 0; i < 20; i++)
	{
		myContainer.AddItem(Cluster(i, path));
	}

	Iterator<Cluster>* it = myContainer.GetIterator();
	BYTE* buffer = new BYTE[4096];
	for (it->First(); !it->IsDone(); it->Next())
	{
		Cluster currentObject = it->GetCurrent(buffer);
	}
	delete[] buffer;
	return 0;
}
