#include <iostream>

#include "student.hpp"

int main() {
	Student gosho = Student("Gosho");
	Student pesho = Student("Pesho");
	Student traicho = Student("Traicho");
	Student raicho = Student("Raicho");

	gosho.printInfo(std::cout);
	pesho.printInfo(std::cout);
	traicho.printInfo(std::cout);
	raicho.printInfo(std::cout);
}
