#include "filearray.h"
#include <fstream>
#include <ios>
#include <iostream>

static void zeroArray(int *arr, std::size_t size) {
	for (std::size_t i = 0; i < size; ++i) {
		arr[i] = 0;
	}
}

ArrayFile::ArrayFile(const char *fileName) : fileName(fileName), size(100), arr(new int[100]), readSuccess(false){
	std::ifstream in;
	in.open(fileName, std::ios_base::binary);

	if (!in) {
		std::cerr << "Cannot open file for reading!!!\n";
		zeroArray(arr, size);
		return;
	}

	std::size_t sizeInFile = -1;
	in.read((char *)&sizeInFile, sizeof(sizeInFile));
	std::cout << sizeInFile << std::endl;
	if (!in || sizeInFile != size) {
		std::cerr << "Contents of file wrong or corrupted!!\n";
		zeroArray(arr, size);
		return;
	}

	in.read((char *)arr, size * sizeof(int));
	if (!in) {
		std::cerr << "File read failed!!\n";
		zeroArray(arr, size);
		return;
	}
	readSuccess = true;
}

ArrayFile::~ArrayFile() {
	std::ofstream out(fileName, std::ios_base::binary);

	out.write((const char *)&size, sizeof(size));
	out.write((const char *)arr, size * sizeof(int));

	if (!out) { std::cerr << "SOMETHING WENT WRONG WITH WRITING THE FILE!!\n"; }

	delete[] arr;
}

int		  &ArrayFile::operator[](int i) { return arr[i]; }
const int &ArrayFile::operator[](int i) const { return arr[i]; }
