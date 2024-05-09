#include <algorithm>

enum class AttackType : int {
	PHYSICAL,
	FIRE,
	WATER,
	LIGHTNINg,
	HOLY,

	COUNT
};

/// base Character class
class Character {
   public:
	virtual void takeDamage(int power, AttackType type){};
	virtual bool isAlive() { return false; }
	virtual void attack(Character *other) {}
};

/// uuuurgh
class Zombie {
   public:
	int	 health = 20;
	void takeDamage(int power, AttackType type) {
		int modifier = 1 + (type == AttackType::FIRE);
		health		 = std::max(health - power * modifier, 0);
	}
	bool isAlive() { return health > 0; }
	void attack(Character *other) { other->takeDamage(2, AttackType::PHYSICAL); }
};

/// player with three lives
class Player {
	int health = 50;
	int lives  = 3;

   public:
	void takeDamage(int power, AttackType type) {
		health = std::max(health - power, 0);
		if (health == 0 && lives) {
			--lives;
			health = 50;
		}
	}
	bool isAlive() { return health > 0; }
	void attack(Character *other) { other->takeDamage(4, AttackType(rand() % int(AttackType::COUNT))); }
};

/// a creature from the depths of Hell!! Does not like water.
class FireElemental {
	int health = 30;

   public:
	void takeDamage(int power, AttackType type) {
		float modifier = 1;
		if (type == AttackType::FIRE) {
			modifier = -0.5f;
		} else if (type == AttackType::WATER) {
			modifier = 2;
		}
		health = std::max(health - int(power * modifier), 0);
	}
	bool isAlive() { return health > 0; }
	void attack(Character *other) { other->takeDamage(8, AttackType::FIRE); }
};

/// Yipee!
class Goomba {
	int alive = true;

   public:
	void takeDamage(int, AttackType) { alive = false; }
	bool isAlive() { return alive; }
	void AttackType(Character *) {}
};

int main() {}
