#include <iostream>

template <class T>
class smart_ptr {
	T *ptr;

   public:
	//smart_ptr(T *ptr) : ptr(ptr) {}
	template<class ... Args>
	explicit smart_ptr(Args &&... args)  {
		ptr = new T(args...);
	}
	smart_ptr(const smart_ptr<T> &) = delete;
	smart_ptr(smart_ptr<T> &&other) : ptr(other.ptr) { other.ptr = nullptr; }
	smart_ptr<T> &operator=(const smart_ptr<T> &) = delete;
	smart_ptr<T> &operator=(smart_ptr<T> &&other) {
		ptr		  = other.ptr;
		other.ptr = nullptr;
	}

	~smart_ptr() { delete ptr; }

	T &operator*() { return *ptr; }
	T *operator->() { return ptr; }
};

struct Human {
	std::string name;
	int			age;
	Human(const std::string &name, int age) : name(name), age(age) {} 
};

smart_ptr<Human> createGosho() { return smart_ptr<Human>("gosho", 10); }

smart_ptr<Human> createGosho2() {
	auto h	= createGosho();
	h->name = "asidhawkd";
	return h;
}

int main() {
	smart_ptr<Human> gosho = createGosho2();
	// smart_ptr<Human> gosho2 = std::move(gosho);
	std::cout << "HELLO WORLD" << std::endl;
}
