#pragma once
#include <functional>

template <class T>
class Generator {
	T current;
	std::function<T(T)> f;
public:

	Generator (T init, std::function<T(T)> f) : current(init), f(f) {}

	T next() {
		T copy = current;
		current = f(current);
		return copy;
	}
};
