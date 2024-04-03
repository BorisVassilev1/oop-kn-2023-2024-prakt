#include <cassert>
#include <iostream>
#include <cstring>

class Word {
	char *contents;

	void shiftLeft() {
		char first = contents[0];
		std::size_t size = strlen(contents);
		for(std::size_t i = 0; i < size-1; ++i) {
			contents[i] = contents[i+1];
		}
		contents[size - 1] = first;
	}

   public:
	Word() : contents(new char[1]{'\0'}) {}
	Word(const char *content) : contents(new char[std::strlen(content) + 1]) { strcpy(contents, content); }
	Word(const Word &w) : contents(new char[w.size() + 1]) { strcpy(contents, w.contents); }

	~Word() { delete[] contents; }

	std::size_t size() const { return std::strlen(contents); }

	Word &operator=(const Word &w) {
		if (this == &w) return *this;
		delete[] contents;
		contents = new char[w.size() + 1];
		strcpy(contents, w.contents);
		return *this;
	}

	Word &operator+=(const Word &w) {
		std::size_t size   = this->size();
		std::size_t w_size = w.size();
		if (w_size == 0) return *this;

		char *newContents = new char[size + w_size + 1];
		strcpy(newContents, contents);
		strcat(newContents, w.contents);
		delete [] contents;
		contents = newContents;

		return *this;
	}

	Word operator +(const Word &other) {
		Word result(*this);
		result += other;
		return result;
	}

	Word operator<<(int n) {
		assert(n>=0);
		Word res(*this);
		for(int i = 0; i < n; ++i) res.shiftLeft();
		return res;
	}

	Word operator~() {
		Word res(*this);
		std::size_t size = strlen(contents);
		for(std::size_t i = 0; i < size / 2; ++i) {
			std::swap(res.contents[i], res.contents[size - 1 - i]);
		}
		return res;
	}

	friend std::ostream &operator<<(std::ostream &out, const Word &w);
};

std::ostream &operator<<(std::ostream &out, const Word &w) { return out << w.contents; }

int main() {
	Word hello("Hello");
	Word world("World");

	Word HelloWorld = hello + world;
	std::cout << HelloWorld << std::endl;

	Word traicho("Traicho");
	std::cout << (traicho << 2) << std::endl;
	std::cout << (~traicho) << std::endl;
}
