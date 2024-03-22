#include <iostream>
#include <functional>
#include <cmath>

#include "../4/vector.hpp"

template <class T, class U>
Vector<U> map (const Vector<T> &arr, std::function<U(T)> f) {
	Vector<U> result(arr.Size(), 0);
	
	for(std::size_t i = 0; i < arr.Size(); ++i) {
		result.Get(i) = f(arr.Get(i));
	}

	return result;
}

int main() {
	
	Vector<int> arr(10, 0);
	for(std::size_t i = 0; i < arr.Size(); ++i) {
		arr.Get(i) = i;
	}
	Vector<float> res = map<int, float>(arr, [](int x) -> float {return std::sqrt(x);});
	
	for(std::size_t i = 0; i < res.Size(); ++i) {
		std::cout << res.Get(i) << " ";
	}


}
