#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>

template <class T>
class Vector {
	T*			arr;
	std::size_t capacity;
	std::size_t size;

   public:
	template <class Child>
	class IteratorBase {
	   protected:
		Vector<T>*	v;
		std::size_t index;
		IteratorBase(Vector<T>* v, std::size_t index) : v(v), index(index) {}

	   public:
		inline Child&	operator++();
		inline Child	operator++(int);
		inline Child&	operator--();
		inline Child	operator--(int);
		inline const T& operator*() const { return (*v)[index]; }
		inline T&		operator*() { return (*v)[index]; }
		inline bool		operator!=(Child other) const { return index != other.index || v != other.v; }
		inline bool		operator==(Child other) const { return index == other.index && v == other.v; }
		friend class Vector<T>;
	};

	class Iterator : public IteratorBase<Iterator> {
		using IteratorBase<Iterator>::IteratorBase;

	   public:
		using IteratorBase<Iterator>::operator++;
		using IteratorBase<Iterator>::operator--;
	};

	class ReverseIterator : public IteratorBase<ReverseIterator> {
		using IteratorBase<ReverseIterator>::IteratorBase;

	   public:
		using IteratorBase<ReverseIterator>::operator++;
		using IteratorBase<ReverseIterator>::operator--;
		inline ReverseIterator& operator++() { return this->IteratorBase<ReverseIterator>::operator--(); }
		inline ReverseIterator& operator--() { return this->IteratorBase<ReverseIterator>::operator++(); }
	};

	class OrderedIterator : public IteratorBase<OrderedIterator> {
		using IteratorBase<OrderedIterator>::IteratorBase;

	   public:
		using IteratorBase<OrderedIterator>::operator++;
		using IteratorBase<OrderedIterator>::operator--;
		inline OrderedIterator& operator++();
		inline OrderedIterator& operator--();
	};

	class ReverseOrderedIterator : public IteratorBase<ReverseOrderedIterator> {
		using IteratorBase<ReverseOrderedIterator>::IteratorBase;

	   public:
		using IteratorBase<ReverseOrderedIterator>::operator++;
		using IteratorBase<ReverseOrderedIterator>::operator--;
		inline ReverseOrderedIterator& operator++() {
			((OrderedIterator*)this)->operator--();
			return *this;
		}
		inline ReverseOrderedIterator& operator--() {
			((OrderedIterator*)this)->operator++();
			return *this;
		}
	};

	Vector();
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector(std::size_t size, const T& el);
	~Vector();
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);

	void		Push(const T& x);
	void		Push(const T* src, std::size_t cnt);
	std::size_t Size() const;

	T&		 Get(int i);
	const T& Get(int i) const;

	T&		 operator[](int i);
	const T& operator[](int i) const;

	Vector<T> Subvec(int i, int j) const;
	void	  Sort(std::function<bool(const T&, const T&)> f);

	Iterator begin() { return Iterator(this, 0); }
	Iterator end() { return Iterator(this, size); }

	ReverseIterator rbegin() { return ReverseIterator(this, size - 1); }
	ReverseIterator rend() { return ReverseIterator(this, -1); }

	OrderedIterator ordBegin() { return OrderedIterator(this, std::min_element(arr, arr + size) - arr); }
	OrderedIterator ordEnd() { return OrderedIterator(this, -1); }

	ReverseOrderedIterator rordBegin() { return ReverseOrderedIterator(this, std::max_element(arr, arr + size) - arr); }
	ReverseOrderedIterator rordEnd() { return ReverseOrderedIterator(this, -1); }

   private:
	void resize(std::size_t newSize);
};

template <class T>
Vector<T>::Vector() : arr(new T[1]), capacity(1), size(0) {
	std::cout << "default constructor " << this << std::endl;
}

template <class T>
Vector<T>::Vector(std::size_t size, const T& el) : arr(new T[size]), capacity(size), size(size) {
	std::cout << "constructor with arguments" << this << std::endl;
	for (std::size_t i = 0; i < size; ++i) {
		arr[i] = el;
	}
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) : arr(new T[other.Size()]), capacity(other.Size()), size(other.Size()) {
	std::cout << "copy constructor " << this << std::endl;
	for (std::size_t i = 0; i < size; ++i) {
		arr[i] = other.Get(i);
	}
}
template <class T>
Vector<T>::Vector(Vector<T>&& other) : arr(other.arr), capacity(other.capacity), size(other.size) {
	std::cout << "move constructor " << this << std::endl;
	other.arr = nullptr;
}

template <class T>
Vector<T>::~Vector() {
	std::cout << "destructor " << this << std::endl;
	delete[] arr;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	std::cout << "copy operator = " << this << std::endl;
	if (this == &other) return *this;
	delete[] arr;
	arr		 = new T[other.capacity];
	capacity = other.capacity;
	size	 = other.size;
	for (std::size_t i = 0; i < size; ++i) {
		arr[i] = other[i];
	}
	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	std::cout << "move operator = " << this << std::endl;
	if (this == &other) return *this;
	delete[] arr;
	arr		  = other.arr;
	capacity  = other.capacity;
	size	  = other.size;
	other.arr = nullptr;
	return *this;
}

template <class T>
void Vector<T>::Push(const T& x) {
	if (size == capacity) resize(2 * capacity);
	arr[size++] = x;
}

template <class T>
void Vector<T>::Push(const T* src, std::size_t cnt) {
	if (size + cnt >= capacity + 1) {
		std::size_t newCapacity = capacity;
		while (size + cnt >= newCapacity + 1) {
			newCapacity *= 2;
		}
		resize(newCapacity);
	}
	for (std::size_t i = 0; i < cnt; ++i) {
		arr[Size() + i] = src[i];
	}
	size += cnt;
}

template <class T>
std::size_t Vector<T>::Size() const {
	return size;
}

template <class T>
T& Vector<T>::Get(int i) {
	return arr[i];
}

template <class T>
const T& Vector<T>::Get(int i) const {
	return arr[i];
}

template <class T>
T& Vector<T>::operator[](int i) {
	return arr[i];
}

template <class T>
const T& Vector<T>::operator[](int i) const {
	return arr[i];
}

template <class T>
Vector<T> Vector<T>::Subvec(int i, int j) const {
	Vector<T> res;
	assert(i <= j);
	res.Push(arr + i, j - i);
	return res;
}

template <class T>
void Vector<T>::Sort(std::function<bool(const T&, const T&)> f) {
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size - 1 - i; ++j) {
			if (!f(arr[j], arr[j + 1])) { std::swap(arr[j], arr[j + 1]); }
		}
	}
}

template <class T>
void Vector<T>::resize(std::size_t newSize) {
	assert(newSize > size);
	T* new_arr = new T[newSize];
	for (size_t i = 0; i < size; ++i) {
		new_arr[i] = std::move(arr[i]);
	}
	capacity = newSize;
	delete[] arr;
	arr = new_arr;
}

template <class T>
template <class Child>
Child& Vector<T>::IteratorBase<Child>::operator++() {
	++this->index;
	return *(Child*)this;
}

template <class T>
template <class Child>
Child Vector<T>::IteratorBase<Child>::operator++(int) {
	Child res = *(Child*)this;
	((Child*)this)->operator++();
	return res;
}

template <class T>
template <class Child>
Child& Vector<T>::IteratorBase<Child>::operator--() {
	--this->index;
	return *(Child*)this;
}

template <class T>
template <class Child>
Child Vector<T>::IteratorBase<Child>::operator--(int) {
	Child res = *(Child*)this;
	((Child*)this)->operator--();
	return res;
}

template <class T>
typename Vector<T>::OrderedIterator& Vector<T>::OrderedIterator::operator++() {
	std::size_t best_ind = -1;
	for (std::size_t i = 0; i < this->v->Size(); ++i) {
		if (this->v->Get(i) > **this) {
			if (best_ind == -1ul) best_ind = i;
			else if (this->v->Get(i) < this->v->Get(best_ind)) best_ind = i;
		}
	}
	this->index = best_ind;
	return *this;
}

template <class T>
typename Vector<T>::OrderedIterator& Vector<T>::OrderedIterator::operator--() {
	std::size_t best_ind = -1;
	for (std::size_t i = 0; i < this->v->Size(); ++i) {
		if (this->v->Get(i) < **this) {
			if (best_ind == -1ul) best_ind = i;
			else if (this->v->Get(i) > this->v->Get(best_ind)) best_ind = i;
		}
	}
	this->index = best_ind;
	return *this;
}
