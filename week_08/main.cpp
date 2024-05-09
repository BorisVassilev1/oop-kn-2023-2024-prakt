#include <iostream>
#include <utility>
#include "vector.hpp"

Vector<int> makeVec(int size) {
	Vector<int> v;
	for(int i =0; i < size; ++i) {
		v.Push(rand() % 1000);
	}
	return v;
}

int main() {
	Vector<int> v1;
	v1 = makeVec(50);

	for(std::size_t i = 0; i < v1.Size(); ++i) {
		std::cout << v1[i] << " ";
	}
	std::cout << std::endl;
	
	Vector<int> v2;
	v2 = std::move(v1);

	v2.Push(1);
	
	// homework

	std::cout << "original: ";
	for(auto a : v2) {
		std::cout << a << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "reverse: ";
	for(auto i = v2.rbegin(); i != v2.rend(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "sorted: ";
	for(auto i = v2.ordBegin(); i != v2.ordEnd(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "sorted reverse: ";
	for(auto i = v2.rordBegin(); i != v2.rordEnd(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << std::endl << std::endl;

	return 0;
}
