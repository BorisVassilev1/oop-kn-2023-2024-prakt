#include <iostream>

class Animal {
public:
	/// this must make the animal speak
	virtual void makeSound() = 0;
};

class Dog : public Animal {
public:
	void makeSound() final {
		std::cout << "bow" << std::endl; 
	}
};

class Chiwawa : public Dog {
};

class Cat : public Animal {
public:
	void makeSound() override {
		std::cout << "meow" << std::endl; 
	}
};


int main() {

	std::cout << sizeof(Animal) << std::endl;
	std::cout << sizeof(Dog) << std::endl;
	std::cout << sizeof(Cat) << std::endl;
	
	Animal *c = new Cat();
	Animal *d = new Dog();
	c->makeSound(); // -> meow
	d->makeSound(); // -> bow
	return 0;
}
