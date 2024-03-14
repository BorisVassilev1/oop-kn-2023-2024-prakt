#include <iostream>
#include "vector.hpp"

template <class T>
void print(const Vector<T> &vec) {
	for (std::size_t i = 0; i < vec.Size(); ++i) {
		std::cout << vec.Get(i) << " ";
	}
	std::cout << std::endl;
}

int main() {
	Vector<int> vec;
	vec.Push(10);
	vec.Push(9);
	vec.Push(8);
	vec.Push(7);
	vec.Push(6);

	int arr[] = {5, 4, 3, 2, 1};
	vec.Push(arr, 5);

	print(vec);
	
	Vector<int> sub = vec.Subvec(2, 8);
	print(sub);
	sub.Sort(std::less<int>());
	print(sub);
}
