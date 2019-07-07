#include <string>

#include "Food.h"
#include "Restaurant.h"
#include "Customer.h"
#include "Order.h"

using namespace std;


void Order::make_order(Customer* _owner, Food* _meal, int _num_meal, string _special){ 
	owner = _owner; 
	meal = _meal; 
	num_meal = _num_meal; 
	special = _special; 
}

Customer* Order::get_owner(){ 
	return owner; 
}

Food* Order::get_meal(){ 
	return meal; 
}

int Order::get_num_meal(){ 
	return num_meal; 
}

void Order::set_order_serie(int _order_serie){ 
	order_serie = _order_serie; 
}

int Order::get_order_serie(){ 
	return order_serie; 
}

string Order::get_special(){ 
	return special; 
}