#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>

class Order {
public:
	Order(Customer* _owner, Food* _meal, int _num_meal, std::string _special) : owner(_owner), meal(_meal), num_meal(_num_meal), special(_special) {}
	void make_order(Customer* _owner, Food* _meal, int _num_meal, std::string _special);
	Customer* get_owner();
	Food* get_meal();
	int get_num_meal();
	void set_order_serie(int _order_serie);
	int get_order_serie();
	std::string get_special();
private:
	int order_serie;
	Customer* owner;
	Food* meal;
	int num_meal;
	std::string special;
};

#endif