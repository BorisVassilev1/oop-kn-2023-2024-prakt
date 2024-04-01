#include <cassert>
#include <iostream>

template <class T>
class BoundSet {
	T		   *m_arr;
	std::size_t m_size;
	std::size_t m_maxSize;

	int indexOf(const T &n) {
		for (std::size_t i = 0; i < m_size; ++i) {
			if (n == m_arr[i]) { return i; }
		}
		return -1;
	}

	void copyArray(const BoundSet &other) {
		for (size_t i = 0; i < m_size; ++i) {
			this->m_arr[i] = other.m_arr[i];
		}
	}

   public:
	BoundSet(std::size_t size) : m_arr(new T[size]), m_size(0), m_maxSize(size) {}

	BoundSet(const BoundSet<T> &other, std::size_t reserve)
		: m_arr(new T[other.m_maxSize + reserve]), m_size(other.m_size), m_maxSize(other.m_maxSize + reserve) {
		copyArray(other);
	}

	BoundSet(const BoundSet<T> &other) : BoundSet(other, 0) {}

	BoundSet &operator=(const BoundSet<T> &other) {
		delete[] this->m_arr;
		m_arr	  = new T[other.m_maxSize];
		m_size	  = other.m_size;
		m_maxSize = other.m_maxSize;
		copyArray(other);
	}

	~BoundSet() { delete[] m_arr; }

	bool remove(const T &n) {
		int i = indexOf(n);
		if (i == -1) return false;
		m_arr[i] = m_arr[m_size - 1];
		--m_size;
		return true;
	}

	bool add(const T &n) {
		if (member(n) || m_size == m_maxSize) return false;
		m_arr[m_size++] = n;
		return true;
	}

	bool member(const T &n) const {
		for (std::size_t i = 0; i < m_size; ++i) {
			if (n == m_arr[i]) return true;
		}
		return false;
	}

	BoundSet<T> operator+(const BoundSet<T> &other) const {
		BoundSet<T> result(*this, other.m_maxSize);
		result += other;
		return result;
	}

	BoundSet<T> &operator+=(const BoundSet<T> &other) {
		for (std::size_t i = 0; i < other.m_size; ++i) {
			this->add(other.m_arr[i]);
		}
		return *this;
	}
};

int main() {
	BoundSet<int> bs1(10);
	assert(bs1.add(1));
	assert(bs1.add(2));
	assert(bs1.add(3));
	assert(!bs1.add(3));
	assert(bs1.member(1));
	assert(bs1.member(2));
	assert(bs1.member(3));

	BoundSet<int> bs2(bs1);
	assert(bs2.member(1));
	assert(bs2.member(2));
	assert(bs2.member(3));
	assert(bs2.remove(2));
	assert(!bs2.remove(2));
	assert(bs1.member(2));
	assert(!bs2.member(2));
	assert(bs2.add(6));
	assert(bs2.add(7));
	assert(bs2.add(8));

	BoundSet<int> bs3 = bs1 + bs2;

	assert(bs3.member(1));
	assert(bs3.member(2));
	assert(bs3.member(3));
	assert(!bs3.member(4));
	assert(!bs3.member(5));
	assert(bs3.member(6));
	assert(bs3.member(7));
	assert(bs3.member(8));

	return 0;
}
