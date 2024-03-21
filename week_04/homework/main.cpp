#include <iostream>
#include <functional>
#include <cmath>
#include <vector>

#include "../3/uncopiable.hpp"

template <class T, class U>
std::vector<U> map (const std::vector<T> &arr, std::function<U(T)> f) {
	std::vector<U> result(arr.size());
	
	for(std::size_t i = 0; i < arr.size(); ++i) {
		result[i] = f(arr[i]);
	}

	return result;
}

int main() {
	
	std::vector<int> arr(10);
	for(std::size_t i = 0; i < arr.size(); ++i) {
		arr[i] = i;
	}
	std::vector<float> res = map<int, float>(arr, [](int x) -> float {return std::sqrt(x);});
	
	for(std::size_t i = 0; i < res.size(); ++i) {
		std::cout << res[i] << " ";
	}


}
