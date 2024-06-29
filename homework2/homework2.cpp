#include <cmath>
#include <functional>
#include <iostream>
#include <ostream>

class Set;
class SetIterator;

class Set {
   public:
	virtual bool contains(int x) const			= 0;
	virtual void describe(std::ostream &) const = 0;

	class SetIterator {
		const Set *set;
		int		   val;

		SetIterator(const Set *set, int val) : set(set), val(val) {}
	   public:
		SetIterator &setSet(const Set *set) {
			this->set = set;
			return *this;
		}
		SetIterator &operator++() {
			++val;
			return validateUp();
		};
		SetIterator operator++(int) {
			auto res = *this;
			operator++();
			return res;
		}
		SetIterator &operator--() {
			--val;
			return validateDown();
		};
		SetIterator operator--(int) {
			auto res = *this;
			operator--();
			return res;
		}
		int			 operator*() { return val; }
		bool		 operator!=(const SetIterator &other) { return set != other.set || val != other.val; }
		bool		 valid() { return set->contains(val); };
		SetIterator &validateUp() {
			while (!set->contains(val) && (*this) != set->end())
				++val;
			return *this;
		}
		SetIterator &validateDown() {
			while (!set->contains(val) && val >= 0)
				++val;
			return *this;
		}
		friend class Set;
	};

	virtual SetIterator begin() const = 0;
	virtual SetIterator end() const	  = 0;
	virtual ~Set() {}
	virtual Set *copy() const = 0;
	protected:
		SetIterator makeIterator(const Set *set, int val) const { return SetIterator(set, val);}
};

class N : public Set {
   public:
	bool		contains(int x) const override { return x >= 0; }
	void		describe(std::ostream &out) const override { out << "N"; }
	SetIterator begin() const override { return makeIterator(this, 0); }
	SetIterator end() const override { return makeIterator(this, -1); }
	N		   *copy() const override { return new N(*this); }
};

class Null : public Set {
   public:
	bool		contains(int) const override { return false; }
	void		describe(std::ostream &out) const override { out << "∅"; }
	SetIterator begin() const override { return makeIterator(this, -1); }
	SetIterator end() const override { return makeIterator(this, -1); }
	Null	   *copy() const override { return new Null(*this); }
};

class Interval : public Set {
	int a, b;

   public:
	Interval(int a, int b) : a(a), b(b) {}
	bool		contains(int x) const override { return x >= a && x <= b; }
	void		describe(std::ostream &out) const override { out << "[" << a << ", " << b << "]"; }
	SetIterator begin() const override { return makeIterator(this, a); }
	SetIterator end() const override { return makeIterator(this, b + 1); }
	Interval   *copy() const override { return new Interval(*this); }
};

class Filter : public Set {
	Set						*a;
	std::function<bool(int)> phi;
	std::string				 desc;

   public:
	Filter(const Set &a, std::function<bool(int)> phi, const std::string &desc = "phi(a)")
		: a(a.copy()), phi(phi), desc(desc) {}
	Filter(const Filter &other) : a(other.a->copy()), phi(other.phi), desc(other.desc) {}
	Filter(Filter &&other) : a(other.a), phi(other.phi), desc(other.desc) {
		other.a = nullptr;
	}
	Filter &operator=(const Filter &other) {
		if(this == &other) return *this;
		a = other.a->copy();
		phi = other.phi;
		desc = other.desc;
		return *this;
	}
	Filter &operator=(Filter &&other) {
		if(this == &other) return *this;
		a = other.a;
		other.a = nullptr;
		phi = other.phi;
		desc = other.desc;
		return *this;
	}
	bool contains(int x) const override { return phi(x); }
	void describe(std::ostream &out) const override {
		out << "{ a ∈ ";
		a->describe(out);
		out << " | " << desc << "}";
	}
	SetIterator begin() const override { return a->begin().setSet(this).validateUp(); }
	SetIterator end() const override { return a->end().setSet(this).validateDown(); }
	Filter	   *copy() const override { return new Filter(*this); }
	~Filter() { delete a; }
};

class Series : public Set {
	Set					   *a;
	std::function<int(int)> f;
	std::string				desc;

   public:
	Series(const Set &a, std::function<int(int)> f, const std::string &desc = "f(n)") : a(a.copy()), f(f), desc(desc) {}
	Series(const Series &other) : a(other.a->copy()), f(other.f), desc(other.desc) {}
	Series(Series &&other) : a(other.a), f(other.f), desc(other.desc) {
		other.a = nullptr;
	}
	Series &operator=(const Series &other) {
		if(this == &other) return *this;
		a = other.a->copy();
		f = other.f;
		desc = other.desc;
		return *this;
	}
	Series &operator=(Series &&other) {
		if(this == &other) return *this;
		a = other.a;
		other.a = nullptr;
		f = other.f;
		desc = other.desc;
		return *this;
	}
	bool contains(int x) const override {
		for (int i : *a) {
			if (f(i) == x) return true;
		}
		return false;
	}
	void describe(std::ostream &out) const override {
		out << "{ " << desc << " | n ∈ ";
		a->describe(out);
		out << " }";
	}
	SetIterator begin() const override { return makeIterator(this, f(*(a->begin()))); }
	SetIterator end() const override { return makeIterator(this, f(*(--a->end())) + 1); }
	Series	   *copy() const override { return new Series(*this); }
	~Series() { delete a; }
};

class Union : public Set {
	const Set *a, *b;

   public:
	Union(const Set &a, const Set &b) : a(a.copy()), b(b.copy()) {}
	Union(const Union &other) : a(other.a->copy()), b(other.b->copy()) {}
	Union(Union &&other) : a(other.a), b(other.b) {
		other.a = nullptr;
		other.b = nullptr;
	}
	Union &operator=(const Union &other) {
		if(this == &other) return *this;
		a = other.a->copy();
		b = other.b->copy();
		return *this;
	}
	Union &operator=(Union &&other) {
		if(this == &other) return *this;
		a = other.a;
		b = other.b;
		other.a = nullptr;
		other.b = nullptr;
		return *this;
	}
	bool contains(int x) const override { return a->contains(x) || b->contains(x); }
	void describe(std::ostream &out) const override {
		a->describe(out);
		out << " U ";
		b->describe(out);
	}
	SetIterator begin() const override { return makeIterator(this, std::min(*(a->begin()), *(b->begin()))); }
	SetIterator end() const override { return makeIterator(this, std::max(*(a->end()), *(b->end()))); }
	Union	   *copy() const override { return new Union(*a, *b); }
	~Union() {
		delete a;
		delete b;
	}
};

class Intersect : public Set {
	const Set *a, *b;

   public:
	Intersect(const Set &a, const Set &b) : a(a.copy()), b(b.copy()) {}
	Intersect(const Intersect &other) : a(other.a->copy()), b(other.b->copy()) {}
	Intersect(Intersect &&other) : a(other.a), b(other.b) {
		other.a = nullptr;
		other.b = nullptr;
	}
	Intersect &operator=(const Intersect &other) {
		if(this == &other) return *this;
		a = other.a->copy();
		b = other.b->copy();
		return *this;
	}
	Intersect &operator=(Intersect &&other) {
		if(this == &other) return *this;
		a = other.a;
		b = other.b;
		other.a = nullptr;
		other.b = nullptr;
		return *this;
	}
	bool contains(int x) const override { return a->contains(x) && b->contains(x); }
	void describe(std::ostream &out) const override {
		a->describe(out);
		out << " ∩ ";
		b->describe(out);
	}
	SetIterator begin() const override { return makeIterator(this, std::max(*(a->begin()), *(b->begin()))); }
	SetIterator end() const override { return makeIterator(this, std::min(*(a->end()), *(b->end()))); }
	Intersect	   *copy() const override { return new Intersect(*a, *b); }
	~Intersect() {
		delete a;
		delete b;
	}
};

void printSet(const Set &s) {
	s.describe(std::cout);
	std::cout << std::endl;

	for (int i : s) {
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;
}

bool prime(int x) {
	if (x < 2) return 0;
	for (int i = 2; i <= sqrt(x); ++i) {
		if (!(x % i)) return 0;
	}
	return 1;
}

class Family;

int main() {
	auto primes = Filter(Interval(0, 100), prime, "a is prime");
	auto evens = Filter(Interval(0, 100), [](int x) {return x % 4 == 0;}, "4 divides a ");
	auto squares = Series(Interval(0, 10), [](int x) { return x * x; }, "n*n");
	auto even_or_square = Union(primes, squares);
	auto even_and_square = Intersect(evens, squares);

	primes.describe(std::cout);
	evens.describe(std::cout);
	squares.describe(std::cout);
	even_or_square.describe(std::cout);
	even_and_square.describe(std::cout);

	//Family family;
	//family += even_or_square += even_and_square;
	//family.describe(std::cout);


	auto int_u = Union(Interval(0, 20), Interval(80, 100));
	printSet(int_u);
	
	auto int_i = Intersect(Interval(0, 20), Interval(20, 100));
	printSet(int_i);

	return 0;
}
