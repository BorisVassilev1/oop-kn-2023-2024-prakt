#include <iostream>
#include <vector>

class MathExpression {
   public:
	virtual double			value()					 = 0;
	virtual void			print(std::ostream &out) = 0;
	virtual MathExpression *clone()					 = 0;
	virtual ~MathExpression()						 = default;
};

class Constant : public MathExpression {
	double val;

   public:
	Constant(double val) : val(val) {}
	double	  value() override { return val; }
	void	  print(std::ostream &out) override { out << val; }
	Constant *clone() override { return new Constant(val); }
};

class Min : public MathExpression {
	MathExpression *e1, *e2;

   public:
	Min(MathExpression &e1, MathExpression &e2) : e1(e1.clone()), e2(e2.clone()) {}
	Min(const Min &other) : e1(other.e1->clone()), e2(other.e2->clone()) {}
	Min(Min &&other) : e1(other.e1), e2(other.e2) {
		other.e1 = nullptr;
		other.e2 = nullptr;
	}
	Min &operator=(const Min &other) {
		delete e1;
		delete e2;
		e1 = other.e1->clone();
		e2 = other.e2->clone();
		return *this;
	}
	Min &operator=(Min &&other) {
		delete e1;
		delete e2;
		e1		 = other.e1;
		e2		 = other.e2;
		other.e1 = nullptr;
		other.e2 = nullptr;
		return *this;
	}
	~Min() {
		delete e1;
		delete e2;
	}

	double value() override { return std::min(e1->value(), e2->value()); }
	void   print(std::ostream &out) override {
		  out << "min(";
		  e1->print(out);
		  out << ", ";
		  e2->print(out);
		  out << ")";
	}
	Min *clone() override { return new Min(*this); }
};

class Sum : public MathExpression {
	std::vector<MathExpression *> exps;

   public:
	Sum(){};
	Sum(const Sum &other) {
		for (auto exp : other)
			add(*exp);
	}
	Sum(Sum &&other) {
		exps = other.exps;
		other.exps.clear();
	}
	Sum &operator=(const Sum &other) {
		for (auto exp : exps)
			delete exp;
		exps.clear();
		for (auto exp : other)
			add(*exp);
		return *this;
	}
	Sum &operator=(Sum &&other) {
		for (auto exp : exps)
			delete exp;
		exps = other.exps;
		other.exps.clear();
		return *this;
	}
	~Sum() {
		for (auto exp : exps)
			delete exp;
	}

	double value() override {
		double s = 0;
		for (auto exp : exps)
			s += exp->value();
		return s;
	}
	void print(std::ostream &out) override {
		out << "sum(";

		for (std::size_t i = 0; i < exps.size(); ++i) {
			if (i) out << ", ";
			exps[i]->print(out);
		}
		out << ")";
	}
	Sum *clone() override { return new Sum(*this); }
	void add(MathExpression &exp) { exps.push_back(exp.clone()); }

	std::vector<MathExpression *>::iterator		  begin() { return exps.begin(); }
	std::vector<MathExpression *>::iterator		  end() { return exps.end(); }
	std::vector<MathExpression *>::const_iterator begin() const { return exps.begin(); }
	std::vector<MathExpression *>::const_iterator end() const { return exps.end(); }
};

int main() {
	Constant c1 = 1, c2 = 2, c3 = 1, c4 = 3, c5 = 4, c6 = 5, c7 = 10;
	Sum		 s1;
	s1.add(c2);
	s1.add(c3);
	Min m1 = Min(c1, s1);
	Sum s2;
	s2.add(c4);
	s2.add(c5);
	s2.add(c6);
	Sum s3;
	s3.add(m1);
	s3.add(s2);
	s3.add(c7);

	s3.print(std::cout);
	std::cout << std::endl << s3.value() << std::endl;

	s3.add(s3); // works, but adds it only once, no cycles are created
	s3.print(std::cout); // works
	std::cout << std::endl << s3.value() << std::endl; // works
}
