#include <string>
#include <iostream>
#include "Customer.h"

using namespace std;


void Customer::create_customer(string _name, string _telephone, string _place){ 
	name = _name; 
	telephone = _telephone; 
	place = _place; 
}

string Customer::get_telephone(){ 
	return telephone; 
}

string Customer::get_place(){ 
	return place; 
}

string Customer::get_name(){ 
	return name; 
}

void Customer::print_info(){ 
	cout << name << " " << telephone.substr(1) << endl; 
}