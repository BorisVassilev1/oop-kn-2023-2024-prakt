#pragma once
#include <cstddef>

template <class T>
class UncopiableArray {
	T*			arr;
	std::size_t _size;

   public:
	UncopiableArray(int size) _size(size) { arr = new T[size]; }

	UncopiableArray& operator=(const UncopiableArray&) = delete;
	UncopiableArray(const UncopiableArray&)			   = delete;

	~UncopiableArray() { delete[] arr; }

	size_t size() const { return _size; }

	T& get(int i) { return arr[i]; }

	const T& get(int i) const { return arr[i]; }
};
