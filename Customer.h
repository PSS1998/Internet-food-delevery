#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <string>

class Customer {
public:
	Customer(std::string _name, std::string _telephone, std::string _place) : name(_name), telephone(_telephone), place(_place) {}
	void create_customer(std::string _name, std::string _telephone, std::string _place);
	std::string get_telephone();
	std::string get_place();
	std::string get_name();
	void print_info();
private:
	std::string name;
	std::string telephone;
	std::string place;
};

#endif