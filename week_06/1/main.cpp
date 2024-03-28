#include <iostream>
#include <cmath>
#include "filearray.h"

int main() {
	std::cout << "HELLO, FMI!!" << std::endl;
	
	ArrayFile myNums("array.bin");

	if(!myNums.didRead()) {
		std::cout << "INITIALIZING..." << std::endl;
		for(std::size_t i = 0; i < myNums.getSize(); ++i) {
			myNums[i] = i * i * i * std::sin(i / 100.f);
		}
	}

	for(std::size_t i = 0; i < myNums.getSize(); ++i) {
		std::cout << myNums[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
