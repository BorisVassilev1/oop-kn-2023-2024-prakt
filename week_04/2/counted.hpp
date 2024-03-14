#pragma once
#include <cstddef>

class Counted {
   public:
	Counted() { ++count; }

	~Counted() { --count; }

   private:
	static std::size_t count;

   public:
	static std::size_t getCount() { return count; }
};
std::size_t Counted::count = 0;
