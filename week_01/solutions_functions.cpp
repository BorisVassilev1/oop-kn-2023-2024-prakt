#include <iostream>

void print(int *arr, size_t size);

template <class T>
void loop0(size_t n, T f) {
	for (size_t i = 0; i < n; ++i) {
		f();
	}
}

void loop(size_t n, void (*f)()) {
	for (size_t i = 0; i < n; ++i) {
		f();
	}
}

int repeat(size_t n, int (*f)(int), int x0) {
	int result = x0;
	for (size_t i = 0; i < n; ++i) {
		result = f(result);
	}
	return result;
}

void sort(int *arr, size_t size, bool (*f)(int, int)) {
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size - 1 - i; ++j) {
			if (!f(arr[j], arr[j + 1])) { std::swap(arr[j], arr[j + 1]); }
		}
	}
}

void print(int *arr, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
void printSomething() { std::cout << "[Hello]"; }
int	 mul2(int n) { return 2 * n; }
bool less(int a, int b) { return a < b; }
bool greater(int a, int b) { return a > b; }

int main() {
	loop0(5, printSomething);
	std::cout << std::endl;
	loop(5, printSomething);
	std::cout << std::endl;

	std::cout << repeat(10, mul2, 3) << std::endl;

	int arr[] = {3, 2, 1, 5, 3, 4, 7, 9, 8, 0};
	sort(arr, 10, less);
	print(arr, 10);
	sort(arr, 10, greater);
	print(arr, 10);

	return 0;
}
