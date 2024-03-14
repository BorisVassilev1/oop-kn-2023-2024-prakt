#pragma once

#include <cstring>
#include <ostream>

class Student {
	char name[100];
	std::size_t id;
public:

	Student(const char *Name) {
		std::strcpy(this->name, Name);
		this->id = counter;
		++ counter;
	}

	void printInfo(std::ostream &out) {
		out << "name: " << name << " , id: " << id << "\n";
	}

private:
	static std::size_t counter;
};

std::size_t Student::counter = 0;
