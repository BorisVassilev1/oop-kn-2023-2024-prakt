#pragma once
#include <ios>
#include <string>
#include <fstream>

class ArrayFile {
	std::string fileName;
	std::size_t size;
	int		   *arr;
	bool readSuccess;

   public:
	ArrayFile() = delete;
	ArrayFile(const char *fileName);
	ArrayFile(const ArrayFile &) = delete;
	ArrayFile &operator=(const ArrayFile &) = delete;

	~ArrayFile();

	int &operator[](int i);
	const int &operator[](int i)const;
	std::size_t getSize() const {return size;}

	bool didRead() { return readSuccess; }
};
