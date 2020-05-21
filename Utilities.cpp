#include < vector >
#include <iostream>
#include < algorithm >
#include <string>

#include "Utilities.h"
int get_int(int min, int max) {
	std::string s;
	int x;
	while (true) {
		getline(std::cin, s);
		try {
			x = stoi(s);
			if (x<min || x>max) throw 1;
			return x;
		}
		catch (...) {
			std::cout << "¬ведите корректную информацию:" << std::endl;

		}

	}
}

