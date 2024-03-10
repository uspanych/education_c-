#include <iostream>
#include "..\DLL1\Header.h"



int main() {
	char const *data = "Uspanov Rustam Borisovich";
	int number = 591220;
	user_name(data);
	group_number(number);
	std::cin.get();
	return 0;
}