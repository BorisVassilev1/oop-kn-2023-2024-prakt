#include <iostream>
#include <vector>

class MathExpression {
   public:
	virtual void   print(std::ostream &) = 0;
	virtual double value()				 = 0;
};

class Constant : public MathExpression {
	double v;

   public:
	Constant(double v) : v(v) {}
	void   print(std::ostream &out) override { out << v; }
	double value() override { return v; }
};

class Min : public MathExpression {
	MathExpression *a, *b;

   public:
	Min(MathExpression &a, MathExpression &b) : a(&a), b(&b) {}
	void print(std::ostream &out) override {
		out << "Min(";
		a->print(out);
		out << ", ";
		b->print(out);
		out << ")";
	}
	double value() override { return std::min(a->value(), b->value()); }
};

class Sum : public MathExpression {
	std::vector<MathExpression *> v;

   public:
	void print(std::ostream &out) override {
		out << "Sum(";
		for (std::size_t i = 0; i < v.size(); ++i) {
			v[i]->print(out);
			if (i != v.size() - 1) out << ", ";
		}
		out << ")";
	}

	double value() override {
		double sum = 0;
		for (auto exp : v) {
			double v = exp->value();
			sum += v;
		}
		return sum;
	}

	void									add(MathExpression &exp) { v.push_back(&exp); }
	std::vector<MathExpression *>::iterator begin() { return v.begin(); }
	std::vector<MathExpression *>::iterator end() { return v.end(); }
};

int main() {
	Constant c1 = 1, c2 = 2, c3 = 1, c4 = 3, c5 = 4, c6 = 5;
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
	//{ // adding a scope breaks it
	Constant c7 = 10;
	s3.add(c7);
	//}
	s3.print(std::cout);
	std::cout << std::endl << s3.value() << std::endl;

	//s3.add(s3); // works
	//s3.print(std::cout); // infinite recursion
	//std::cout << std::endl << s3.value() << std::endl; // infinite recursion
}
