#include <string>
#include "Food.h"

using namespace std;


void Food::make_food(string _code, string _name, string _type, long _cost, int _owner){
	code = _code;
	name = _name;
	type = _type;
	cost = _cost;
	owner = _owner;
}

string Food::get_code(){
	return code;
}

string Food::get_name(){
	return name;
}

string Food::get_type(){ 
	return type;
}

long Food::get_cost(){ 
	return cost;
}

int Food::get_owner(){ 
	return owner;
}

void Food::set_owner(int _owner){ 
	owner = _owner;
}