#include <sys/types.h>
#include <cwchar>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

enum class AttackType : int {
	PHYSICAL,
	FIRE,
	WATER,
	LIGHTNINg,
	HOLY,

	COUNT
};

enum class ItemType {
	CONSUMABLE = 1,
	WEAPON = 2,
	ARMOR = 3,
	CRAFTING_INGREDIENT = 4
};

class Item {
   protected:
	std::string name, description;
	float		weight;
	Item() {}
	Item(const std::string &name, const std::string &description, float weight)
		: name(name), description(description), weight(weight) {}

   public:
	virtual void print(std::ostream &os = std::cout) {
		os << "name: \"" << name << "\", description: \"" << description << "\", weight: " << weight;
	}
	virtual ItemType getType() =0;

	virtual void serialize(std::ostream &out) {};
	virtual void deserialize(std::istream &in) {};
};

class Consumable : public Item {
	float nutrition;

   public:
	Consumable() {}
	Consumable(const std::string &name, float nutrition) : Item(name, "a refreshing food", 0.1), nutrition(nutrition) {}
	void print(std::ostream &os) override {
		Item::print(os);
		os << ", nutrition: " << this->nutrition << ",";
	}
	ItemType getType() override { return ItemType::CONSUMABLE; };
};

class Weapon : public Item {
	float	   durabiliy;
	int		   attackPower;
	AttackType attackType;

   public:
	Weapon() {}
	Weapon(const std::string &name, const std::string &description, int attackPower, AttackType type)
		: Item(name, description, 3), durabiliy(1.), attackPower(attackPower), attackType(type) {}
	void print(std::ostream &os) override {
		Item::print(os);
		os << ", durability: " << this->durabiliy << ",";
	}
	ItemType getType() override { return ItemType::WEAPON; };
};

class Armor : public Item {
	float					durabiliy;
	int						protection;
	std::vector<AttackType> damageTypes;

   public:
	Armor() {}
	Armor(const std::string &name, const std::string &description, int protection, const std::vector<AttackType> &types)
		: Item(name, description, 3), durabiliy(1.), protection(protection), damageTypes(types) {}
	void print(std::ostream &os) override {
		Item::print(os);
		os << ", durability: " << this->durabiliy << ",";
	}
	ItemType getType() override { return ItemType::ARMOR; };
};

class CraftingIngredient : public Item {
	int	  quantity;
	float one_weight;

   public:
	CraftingIngredient() {}
	CraftingIngredient(const std::string &name, int quantity, int one_weight)
		: Item(name, "crafting ingredient", quantity * one_weight), quantity(quantity), one_weight(one_weight) {}
	void print(std::ostream &os) override {
		Item::print(os);
		os << ", quantity: " << this->quantity << ",";
	}
	ItemType getType() override { return ItemType::CRAFTING_INGREDIENT; };
};



class Inventory : public std::vector<Item *> {
   public:
	void print(std::ostream &out = std::cout) {
		for (Item *i : *this) {
			i->print(out);
			std::cout << std::endl;
		}
	}
	void serialize(std::ostream &out) {
		std::size_t size = this->size();
		out.write((char*) &size, sizeof(std::size_t));
		for (Item *i : *this) {
			ItemType t = i->getType();
			out.write((char*) &t, sizeof(ItemType));
			i->serialize(out);
		}
	}
	
	void deserialize(std::istream &in) {
		std::size_t size;
		in.read((char*) &size, sizeof(std::size_t));
		for(std::size_t i = 0; i < size; ++i) {
			ItemType t;
			in.read((char*)&t, sizeof(ItemType));
			Item *item = nullptr;
			switch(t) {
				case ItemType::CONSUMABLE: item = new Consumable(); break;
				case ItemType::WEAPON: item = new Weapon(); break;
				case ItemType::ARMOR: item = new Armor(); break;
				case ItemType::CRAFTING_INGREDIENT: item = new CraftingIngredient(); break;
			};
			if(item) {
				item->deserialize(in);
				this->push_back(item);
			}
			else throw std::runtime_error("something went very wrong");
		}
	}
};

int main() {
	std::cout << "Hello World" << std::endl;
	Inventory inv;
	inv.push_back(new Weapon("diamond sword", "i said it!", 7, AttackType::PHYSICAL));
	inv.push_back(new Consumable("Parjola", 4));
	inv.push_back(new Armor("Warmog's armor", "is that a LOL reference??", 2, {AttackType::FIRE, AttackType::WATER}));

	inv.print();
}
