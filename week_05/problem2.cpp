#include <cassert>
#include <iostream>
#include <cstring>
#include <ostream>

class Word {
	std::size_t capacity;
	std::size_t size;

	char *contents;
	
public:
	Word() : capacity(4), size(0), contents(new char[4]) {}
	Word(const char *content) : 
		capacity(std::strlen(content)) , 
		size(capacity), 
		contents(new char[capacity]) 
	{
		for(std::size_t i = 0; i < size; ++i) {
			contents[i] = content[i];
		}
	}

	~Word() {
		delete [] contents;
	}

	Word(const Word& w) {
		copy(w);
	}

	Word &operator =(const Word &w) {
		if(this == &w) return *this;
		delete [] contents;
		copy(w);
		return *this;
	}

	Word &operator += (const Word &w) {
		if(size + w.size > capacity) {
			std::size_t newCap = capacity;
			while(size + w.size > newCap) newCap *= 2;
			resize(newCap);
		}
		for(std::size_t i = 0; i < w.size; ++i) {
			contents[size++] = w.contents[i];
		}
		return *this;
	}

	Word operator +(const Word &other) {
		Word result(*this);
		result += other;
		return result;
	}
	
private: 
	void copy(const Word &w) {
		contents = new char[w.capacity];
		for(std::size_t i = 0; i < w.size; ++i) {
			contents[i] = w.contents[i];
		}
		size = w.size;
		capacity = w.capacity;
	}

	void resize(std::size_t newCap) {
		assert(newCap > size);
		char * newArray = new char[newCap];
		for(std::size_t i = 0; i < size; ++i) {
			newArray[i] = contents[i];
		}
		delete [] contents;
		contents = newArray;
		capacity = newCap;
	}

	friend std::ostream &operator << (std::ostream &out, const Word &w);
};

std::ostream &operator << (std::ostream &out, const Word &w) {
	for(std::size_t i = 0; i < w.size; ++i) {
		out << w.contents[i];
	}
	return out;
}

int main() {
	
	Word hello("Hello");
	Word world("World");

	Word HelloWorld = hello + world;
	std::cout << HelloWorld << std::endl;
}
