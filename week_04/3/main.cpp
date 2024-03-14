#include "uncopiable.hpp"
#include <iostream>

void print(const UncopiableArray<int> &arr) {
	for(size_t i = 0; i < arr.size(); ++i) {
		std::cout << arr.get(i) << " "; 
	}
	std::cout << std::endl;
}

int main() {
	UncopiableArray<int> a(10), b(10);
	for(size_t i = 0; i < a.size(); ++i) { a.get(i) = i;}
	// a = b;
	// UncopiableArray c(b);
	print(a);
}
