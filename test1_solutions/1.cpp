#include <climits>
#include <iostream>

class Statistics {
	int m_cnt;
	int m_sum;
	int m_max;
	int m_prod;
	
public:
	Statistics() : m_cnt(0), m_sum(0), m_max(INT_MIN), m_prod(1) {}

	void add(int n) {
		++m_cnt;
		m_sum += n;
		m_max = std::max(m_max, n);
		m_prod *= n;
	}

	int num() const {return m_cnt;}
	int sum() const {return m_sum;}
	int max() const {return m_max;}
	int prod() const {return m_prod;}
	float average() const {return m_sum / (float)m_cnt;}

	Statistics& operator += (int n) {
		add(n);
		return *this;
	}
	Statistics operator + (int n) const {
		Statistics s(*this);
		s.add(n);
		return s;
	}
};

int main() {

	Statistics seq1;
	seq1 += 10;
	seq1 += 5;
	std::cout << seq1.num() << std::endl;
	std::cout << seq1.sum() << std::endl;
	std::cout << seq1.max() << std::endl;
	std::cout << seq1.prod() << std::endl;
	std::cout << seq1.average() << std::endl;
}
