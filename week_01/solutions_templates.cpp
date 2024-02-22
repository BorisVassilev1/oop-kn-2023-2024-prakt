#include <iostream>

using std::size_t;

// 0
template <class T>
void print(const T *arr, const size_t size) {
	for (size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

// 1
template <class T>
T sum(const T *arr, const size_t size) {
	T sum = arr[0];
	for (size_t i = 1; i < size; ++i) {
		sum += arr[i];
	}
	return sum;
}

// 2
template <class T>
T max(const T *arr, const size_t size) {
	T max = arr[0];
	for (size_t i = 1; i < size; ++i) {
		if (max < arr[i]) max = arr[i];
	}
	return max;
}

// 3
template <class T>
size_t positiveCount(const T *arr, const size_t size) {
	size_t cnt = 0;
	for (size_t i = 0; i < size; ++i) {
		if (arr[i] >= 0) ++cnt;
	}
	return cnt;
}

// 4
template <class T>
T *filterMoreThan(const T *arr, const size_t size, T k, size_t &retSize) {
	retSize = 0;
	for (size_t i = 0; i < size; ++i) {
		retSize += (arr[i] > k);
	}
	T *filtered = new T[retSize];

	size_t j = 0;
	for (size_t i = 0; i < size; ++i) {
		if (arr[i] > k) { filtered[j++] = arr[i]; }
	}
	return filtered;
}

int main() {
	double arr1[] = {1, 2, 3, 4, 5};
	print(arr1, 5);
	int arr2[] = {3, 4, 5, 6, 4};
	print(arr2, 5);

	std::cout << sum(arr1, 5) << std::endl;
	std::cout << max(arr2, 5) << std::endl;
	float arr3[] = {-2, 1, 3, -1, 3, -10};
	std::cout << positiveCount(arr3, 6) << std::endl;

	size_t filteredSize;
	float *filtered = filterMoreThan(arr3, 6, -1.f, filteredSize);
	print(filtered, filteredSize);

	delete[] filtered;

	return 0;
}
