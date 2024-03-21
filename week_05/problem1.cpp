#include <iostream>
#include <cmath>

const float EPS = 0.0001;

struct Vector2 {
	float x, y;

	Vector2(float x, float y) : x(x), y(y) {}

	bool operator<(const Vector2 &other) const {
		float l1 = lenSquared();
		float l2 = other.lenSquared();

		if (std::abs(l1 - l2) >= EPS) return l1 < l2;
		float phi1 = atan2(y, x);
		float phi2 = atan2(other.y, other.x);
		return phi1 < phi2;
	}

	Vector2 &operator*=(float r) {
		this->x *= r;
		this->y *= r;
		return *this;
	}

	Vector2 operator*(float r) const { return Vector2(r * x, r * y); }
	Vector2 operator+(const Vector2 &other) const { return Vector2(x + other.x, y + other.y); }
	Vector2 operator-(const Vector2 &other) const { return Vector2(x - other.x, y - other.y); }
	Vector2 operator*(const Vector2 &other) const { return Vector2(x * other.x, y * other.y); }
	Vector2 operator/(const Vector2 &other) const { return Vector2(x / other.x, y / other.y); }
	
	float lenSquared() const {
		return dot(*this, *this);
	}
	float len() const {return std::sqrt(lenSquared());}

	static float dot(const Vector2 &a, const Vector2 &b) {
		return a.x * b.x + a.y * b.y;
	}
};

Vector2 operator*(float r, const Vector2 &vec) { return Vector2(r * vec.x, r * vec.y); }

int main() {
	Vector2 a(1, 2), b(2, 1);

	std::cout << (a < b) << std::endl;

	Vector2 c = 2 * a;
	a *= 2;

	std::cout << c.x << " " << c.y << std::endl;
}
