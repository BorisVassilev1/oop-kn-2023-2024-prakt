#include <cassert>
#include <iostream>

enum AnimalType {
	BASE,
	DOG, CAT
};

void makeSoundCat() {std::cout << "meow" << std::endl;};
void makeSoundDog() {std::cout << "bow" << std::endl;};
void (*vtable_makeSound[])(void) = {
	nullptr,
	makeSoundCat, makeSoundDog
};

class Animal {
public:
	AnimalType type;
	Animal(AnimalType type) : type(type) {}
	void makeSound() {
		vtable_makeSound[type]();
	};
};

class Cat : public Animal {
public:
	Cat() : Animal(CAT) {}
};

class Dog : public Animal {
public:
	Dog() : Animal(DOG) {}
};

int main() {
	Animal* d = new Dog();
	Animal* c = new Cat();

	d->makeSound();
	c->makeSound();

	delete d;
	delete c;
	return 0;
}
