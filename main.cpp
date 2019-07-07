#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <sstream>

#include "Food.h"
#include "Restaurant.h"
#include "Customer.h"
#include "Order.h"

using namespace std;


bool compare(Restaurant & l, Restaurant & r) {
	return l.get_telephone() < r.get_telephone();
}
bool compare2(Food & l, Food & r) {
	return l.get_code() < r.get_code();
}

void restaurants_read(string &line, string &input_part1, string &input_part2, string &input_part3, string &input_part4, int &input_part5, Restaurant &restaurant_temp, Food &food_temp, vector<Restaurant> &restaurant) {
	int restaurants_num = 0;
	vector<int> foods_num(1);

	ifstream frestaurants;
	frestaurants.open("restaurants.txt", ios_base::binary);

	if (frestaurants.is_open()) {

		while (getline(frestaurants, line)) {
			foods_num[restaurants_num]++;
			if (line.size() == 0) {
				restaurants_num++;
				foods_num.push_back(0);
			}
		}
		restaurants_num++;

		frestaurants.clear();

		foods_num.resize(restaurants_num);
		for (int z = 0; z<restaurants_num - 1; z++)
			foods_num[z] -= 2;
		foods_num[restaurants_num - 1] -= 1;

		frestaurants.seekg(0, frestaurants.beg);


		for (int i = 0; i<restaurants_num; i++) {
			getline(frestaurants, input_part1, ',');
			getline(frestaurants, input_part2, ',');
			getline(frestaurants, input_part3, '\n');
			if (i)
				input_part1 = input_part1.substr(1);
			restaurant_temp.create_restaurant(input_part1, input_part2, input_part3);
			restaurant.push_back(restaurant_temp);
			for (int j = 0; j<foods_num[i]; j++) {
				getline(frestaurants, input_part1, ',');
				getline(frestaurants, input_part2, ',');
				getline(frestaurants, input_part3, ',');
				getline(frestaurants, input_part4, '\n');
				input_part5 = atoi(input_part4.c_str());
				food_temp.make_food(input_part1, input_part2, input_part3, input_part5, restaurant.size() - 1);
				restaurant[i].add_food(food_temp);
			}
		}
	}
}

void customers_read(string &line, string &input_part1, string &input_part2, string &input_part3, string &input_part4, int &input_part5, Customer &customer_temp, vector<Customer> &customer) {
	input_part1 = "";
	input_part2 = "";
	input_part3 = "";
	input_part4 = "";

	int people_num = 0;

	ifstream fcustomers;
	fcustomers.open("customers.txt");

	if (fcustomers.is_open()) {

		while (getline(fcustomers, line))
			people_num++;

		fcustomers.clear();

		fcustomers.seekg(0, ios::beg);
		for (int i = 0; i<people_num; i++) {
			getline(fcustomers, input_part1, ',');
			getline(fcustomers, input_part2, ',');
			getline(fcustomers, input_part3, '\n');
			customer_temp.create_customer(input_part1, input_part2, input_part3);
			customer.push_back(customer_temp);
			fcustomers.clear();
			fcustomers.seekg(0, fcustomers.cur);
		}
	}
}

void get_command(string &command, vector<string> &commands) {
	getline(cin, command);
	commands.resize(0);
	string buf;
	stringstream ss(command);
	while (ss >> buf)
		commands.push_back(buf);
	commands.resize(10);
}

vector<int> check_near(vector<Customer> &customer, vector<string> &commands, bool &near_flag, vector<Restaurant> &restaurant) {
	vector<int> near_places;
	for (int i = 0; i<customer.size(); i++)
		if (commands[2] == customer[i].get_telephone()) {

			near_flag = 1;
			for (int j = 0; j<restaurant.size(); j++)
				if (restaurant[j].is_near(customer[i].get_place()))
					near_places.push_back(j);
		}
	return near_places;
}

void get_order(vector<Customer> &customer, vector<string> &commands, vector<int> &order_cost, vector<int> &delivery_cost, string &command, vector<Restaurant> &restaurant, int &input_part5, Order &order_temp, int &order_counter, vector<Order> &order, bool &flag_no_discount, bool &place_discount) {
	for (int i = 0; i<customer.size(); i++)
		if (commands[1] == customer[i].get_telephone()) {
			order_cost.push_back(0);
			delivery_cost.push_back(5000);
			do {
				commands.resize(0);
				Food* food_address = &(restaurant[0].foods[0]);
				get_command(command, commands);
				string buf = commands[0].substr(0, 8);
				for (int i2 = 0; i2<restaurant.size(); i2++)
					if (buf == restaurant[i2].get_telephone()) {
						buf = commands[0].substr(8, 3);
						if (restaurant[i2].find_food(buf) != -1)
							food_address = &(restaurant[i2].foods[restaurant[i2].find_food(buf)]);
					}
				string special_order = "";
				string space = " ";
				int j = 2;
				while (commands[j] != "") {
					special_order += (commands[j] + space);
					j++;
				}
				if (special_order != "")
					special_order = special_order.substr(0, special_order.size() - 1);
				input_part5 = atoi(commands[1].c_str());
				order_temp.make_order(&customer[i], food_address, input_part5, special_order);
				order_temp.set_order_serie(order_counter);
				order.push_back(order_temp);
				order_cost[order_counter] += (input_part5*food_address->get_cost());
			} while (commands[0] != "$");
			order.pop_back();
			order_cost[order_counter] += 5000;
			for (int z = 0; z<order.size(); z++)
				if (customer[i].get_name() == order[z].get_owner()->get_name()) {
					if (customer[i].get_place() == restaurant[order[z].get_meal()->get_owner()].get_place() && flag_no_discount == 0) {
						place_discount = 1;
					}
					else {
						place_discount = 0;
						flag_no_discount = 1;
					}
				}
			if (place_discount || (order_cost[order_counter] - 5000)>100000) {
				order_cost[order_counter] -= 5000;
				delivery_cost[order_counter] -= 5000;
			}
			cout << customer[i].get_name() << " " << customer[i].get_telephone().substr(1) << " " << order_cost[order_counter] << endl;
			order_counter++;
		}
}

void print_bill(int j, vector<Order> &order, vector<Restaurant> &restaurant, int &checked_order, vector<int> &order_cost, vector<int> &delivery_cost) {
	for (int z = 0; z<order.size(); z++)
		if (order[j].get_order_serie() == order[z].get_order_serie()) {
			if (order[z].get_special() != "")
				cout << restaurant[order[z].get_meal()->get_owner()].get_telephone() << order[z].get_meal()->get_code() << " " << order[z].get_meal()->get_name() << " " << order[z].get_meal()->get_type() << " " << order[z].get_meal()->get_cost() << " " << order[z].get_num_meal() << " " << (order[z].get_meal()->get_cost())*(order[z].get_num_meal()) << " " << order[z].get_special() << endl;
			else
				cout << restaurant[order[z].get_meal()->get_owner()].get_telephone() << order[z].get_meal()->get_code() << " " << order[z].get_meal()->get_name() << " " << order[z].get_meal()->get_type() << " " << order[z].get_meal()->get_cost() << " " << order[z].get_num_meal() << " " << (order[z].get_meal()->get_cost())*(order[z].get_num_meal()) << endl;
			checked_order = order[j].get_order_serie();
		}
	cout << "delivery cost " << delivery_cost[order[j].get_order_serie()] << endl;
	cout << "total cost " << order_cost[order[j].get_order_serie()] << endl;
}

void print_restaurant_info(vector<Customer> &customer, vector<string> &commands, bool &near_flag, vector<Restaurant> &restaurant) {
	for (int i = 0; i<customer.size(); i++)
		if (commands[2] == customer[i].get_telephone()) {
			near_flag = 1;
			for (int j = 0; j<restaurant.size(); j++)
				if (restaurant[j].is_near(customer[i].get_place()))
					restaurant[j].info();
		}
}

void print_same_type(vector<string> &commands, vector<Restaurant> &restaurant){
	for (int i = 0; i<restaurant.size(); i++)
		for(int j = 0; j<restaurant[i].foods.size(); j++)
			if(restaurant[i].foods[j].get_type() == commands[2]){
				string complete_code = restaurant[i].get_telephone() + restaurant[i].foods[j].get_code();
				cout << complete_code << " " << restaurant[i].foods[j].get_name() << " " << restaurant[i].foods[j].get_type() << " " << restaurant[i].foods[j].get_cost() << " " << restaurant[i].get_name() << " " << restaurant[i].get_place() << endl;
			}
}


int main() {
	vector<Restaurant> restaurant;
	vector<Customer> customer;
	vector<Order> order;
	Restaurant restaurant_temp("alibaba", "2288047", "sed khanadan");
	Food food_temp("2288047000", "alibaba", "irani", 100, 0);
	Customer customer_temp("ali", "09301282254", "seyed khandan");
	Order order_temp(&customer_temp, &food_temp, 1, "whith extra pepper");
	string input_part1;
	string input_part2;
	string input_part3;
	string input_part4;
	int input_part5;
	char ch;
	int i = 0;
	string line;

	restaurants_read(line, input_part1, input_part2, input_part3, input_part4, input_part5, restaurant_temp, food_temp, restaurant);

	customers_read(line, input_part1, input_part2, input_part3, input_part4, input_part5, customer_temp, customer);

	sort(restaurant.begin(), restaurant.end(), compare);
	for (int i = 0; i<restaurant.size(); i++)
		sort(restaurant[i].foods.begin(), restaurant[i].foods.end(), compare2);

	for (int i = 0; i<restaurant.size(); i++)
		for (int j = 0; j<restaurant[i].foods.size(); j++)
			restaurant[i].foods[j].set_owner(i);

	string command;
	vector<string> commands;
	string telephone_number;
	bool near_flag = 0;
	vector<int> order_cost;
	vector<int> delivery_cost;
	bool place_discount = 0;
	bool flag_no_discount = 0;
	int order_counter = 0;

	do {

		get_command(command, commands);

		if (commands[0] == "menu") {
			for (int i = 0; i<restaurant.size(); i++)
				if (commands[1] == restaurant[i].get_telephone()) {
					restaurant[i].print_menu();
				}
		}
		if (commands[0] == "restaurants") {
			if (commands[1] == "near") {
				print_restaurant_info(customer, commands, near_flag, restaurant);
			}
			if (!near_flag) {
				for (int i = 0; i<restaurant.size(); i++)
					restaurant[i].info();
			}
		}
		if (commands[0] == "list") {
			if (commands[1] == "near") {
				for (int i = 0; i<customer.size(); i++)
					if (commands[2] == customer[i].get_telephone()) {
						vector<int> near = check_near(customer, commands, near_flag, restaurant);
						for (int q = 0; q<near.size(); q++)
							restaurant[near[q]].list_food();
					}

			}
			if (commands[1] == "type") {
				print_same_type(commands, restaurant);
			}
		}
		if (commands[0] == "order") {
			get_order(customer, commands, order_cost, delivery_cost, command, restaurant, input_part5, order_temp, order_counter, order, flag_no_discount, place_discount);
		}
		if (commands[0] == "bill") {
			int checked_order = -1;
			for (int i = 0; i<customer.size(); i++)
				if (commands[1] == customer[i].get_telephone()) {
					customer[i].print_info();
					for (int j = order.size() - 1; j >= 0; j--)
						if (customer[i].get_name() == order[j].get_owner()->get_name()) {
							print_bill(j, order, restaurant, checked_order, order_cost, delivery_cost);
							break;
						}
				}
			vector<int> customer_total_orders;
			int total_purchase = 0;
			if (commands[1] == "all") {
				for (int i = 0; i<customer.size(); i++) {
					if (commands[2] == customer[i].get_telephone()) {
						customer[i].print_info();
						for (int j = 0; j<order.size(); j++) {
							if (customer[i].get_name() == order[j].get_owner()->get_name() && order[j].get_order_serie() != checked_order) {
								print_bill(j, order, restaurant, checked_order, order_cost, delivery_cost);
								cout << "#" << endl;
								customer_total_orders.push_back(order[j].get_order_serie());
							}
						}
						for (int w = 0; w<customer_total_orders.size(); w++)
							total_purchase += order_cost[customer_total_orders[w]];
						cout << "total purchase " << total_purchase << endl;
					}
				}
			}
		}


		near_flag = 0;
		place_discount = 0;
		flag_no_discount = 0;

	} while (!cin.eof());
}