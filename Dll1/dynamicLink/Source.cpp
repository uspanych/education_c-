#include <iostream>
#include "wtypes.h"


int main() {
	HINSTANCE MyDLL;

	typedef void(__stdcall* userName)(const char* name);
	typedef void(__stdcall* groupNumber)(int);
	
	// Добавил новое изменение
	userName user_name;
	groupNumber group_number;

	if ((MyDLL = LoadLibraryW(L"DLL1.dll")) == NULL) {
		std::cout << "Library not found";
		return 1;
	}

	char const *first_func = "user_name";
	char const *second_func = "group_number";
	char const *user_data = "Uspanov Rustam Borisovich";
	int group_num = 591220;

	user_name = (userName)GetProcAddress(MyDLL, first_func);
	group_number = (groupNumber)GetProcAddress(MyDLL, second_func);

	if (user_name == NULL) {
		std::cout << "Function " << user_name << " not found\n";
	}
	else {
		user_name(user_data);
	}

	if (group_number == NULL) {
		std::cout << "Function " << second_func << " not found\n";
	}
	else {
		group_number(group_num);
	}

	std::cin.get();


	// Добавлены изменения 123123123123123123131

	return 0;
}
