#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include <string>

class Food {
public:
	Food(std::string _code, std::string _name, std::string _type, long _cost, int _owner) : code(_code), name(_name), type(_type), cost(_cost), owner(_owner) {}
	void make_food(std::string _code, std::string _name, std::string _type, long _cost, int _owner);
	std::string get_code();
	std::string get_name();
	std::string get_type();
	long get_cost();
	int get_owner();
	void set_owner(int _owner);
private:
	std::string code;
	std::string name;
	std::string type;
	long cost;
	int owner;
};

#endif