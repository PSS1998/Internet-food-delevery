#include <string>
#include <iostream>
#include <vector>
#include "Food.h"
#include "Restaurant.h"

using namespace std;


void Restaurant::create_restaurant(string _name, string _telephone, string _place){ 
	name = _name; 
	telephone = _telephone; 
	place = _place; 
}

void Restaurant::add_food(Food _foods){ 
	foods.push_back(_foods); 
}

string Restaurant::get_telephone(){ 
	return telephone; 
}

string Restaurant::get_place(){ 
	return place; 
}

string Restaurant::get_name(){
	return name;
}

void Restaurant::info(){ 
	cout << name << " " << place << " " << telephone << endl; 
}

bool Restaurant::is_near(string _place){ 
	if (place == _place) 
		return 1;
	return 0; 
}

void Restaurant::print_menu(){
	for (int i = 0; i<foods.size(); i++) {
		string complete_code = telephone + foods[i].get_code();
		cout << complete_code << " " << foods[i].get_name() << " " << foods[i].get_type() << " " << foods[i].get_cost() << endl;
	}
}

void Restaurant::list_food(){
	for (int i = 0; i<foods.size(); i++) {
		string complete_code = telephone + foods[i].get_code();
		cout << complete_code << " " << foods[i].get_name() << " " << foods[i].get_type() << " " << foods[i].get_cost() << " " << name << " " << place << endl;
	}
}

int Restaurant::find_food(string _code){
	for (int i = 0; i<foods.size(); i++)
		if (_code == foods[i].get_code())
			return i;
	return -1;
}