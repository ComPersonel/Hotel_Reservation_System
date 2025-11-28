#pragma once

# include <iostream>
# include <string>
# include <algorithm>
# include <functional>
# include <fstream>
# include <sstream>
# include <vector>

using namespace std;

struct room_data {
	int floor = 0; // Huoneen kerros
	int number = 0; // Huone numero
	bool reserved = false; // Varattu?
	std::string type = "single"; // Single, Double
	std::string tier = "basic"; // Basic, Premium, Deluxe
	int coupon = 0; // Kupongin alennus
};

struct reservation_data {
	int reservation; // Varaus numero
	int room_floor; // Huoneen kerros
	int room_number; // Huoneen numero
	std::string name; // Käyttäjän nimi
	int stay; // Keston pituus
};

void save_room_data(vector<vector<room_data>>&);
void generate_room_data(vector<vector<room_data>>&);
vector<int> define_hotel_size();

int random_num(int, int);
int input_int(int, int);
bool yes_no();
void enter();
std::string input_name();
std::string type_desc(room_data);
std::string tier_desc(room_data);
void print_room(room_data);