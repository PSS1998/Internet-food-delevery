#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>

class Restaurant {
public:
	Restaurant(std::string _name, std::string _telephone, std::string _place) : name(_name), telephone(_telephone), place(_place) {}
	std::vector<Food> foods;
	void create_restaurant(std::string _name, std::string _telephone, std::string _place);
	void add_food(Food _foods);
	void print_menu();
	void list_food();
	std::string get_telephone();
	std::string get_place();
	std::string get_name();
	void info();
	bool is_near(std::string _place);
	int find_food(std::string _code);
private:
	std::string name;
	std::string telephone;
	std::string place;
};

#endif