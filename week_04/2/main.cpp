#include <iostream>
#include "counted.hpp"

int main() {
	std::cout << Counted::getCount() << std::endl;

	Counted x;
	Counted y;
	
	std::cout << Counted::getCount() << std::endl;
	
	{
		Counted z;
		std::cout << Counted::getCount() << std::endl;
	}

	std::cout << Counted::getCount() << std::endl;
}
