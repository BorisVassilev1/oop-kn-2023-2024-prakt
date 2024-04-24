#include <iostream>
#include <utility>
#include "vector.hpp"

Vector<int> makeVec(int size) {
	Vector<int> v;
	for(int i =0; i < size; ++i) {
		v.Push(i);
	}
	return v;
}

int main() {
	Vector<int> v1;
	v1 = makeVec(100);

	for(std::size_t i = 0; i < v1.Size(); ++i) {
		std::cout << v1[i] << " ";
	}
	std::cout << std::endl;
	
	Vector<int> v2;
	v2 = std::move(v1);

	v2.Push(1);
	return 0;
}
