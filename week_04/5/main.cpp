#include <iostream>
#include <cmath>

#include "generator.hpp"

int main() {
	Generator<int> nats(0, [](int x) -> int { return x + 1; });
	std::cout << nats.next() << std::endl;	 // 0
	std::cout << nats.next() << std::endl;	 // 1
	std::cout << nats.next() << std::endl;	 // 2
	
	Generator<double> rand(0.5, [](double x) -> double {
		x = std::abs(std::sin(x * 123872.9898) * 43758.5453 + 1.2315);
		return x - (int)x;
	});
	for(int i = 0; i < 100; ++i) {
		std::cout << rand.next() << std::endl;
	}
}
