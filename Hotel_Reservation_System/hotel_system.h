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
	int floor; // Huoneen kerros
	int number; // Huone numero
	bool reserved; // Varattu?
	std::string type; // Single, Double
	std::string tier; // Basic, Premium, Deluxe
	int coupon; // Kupongin alennus
};

struct reservation_data {
	int reservation; // Varaus numero
	int room_floor; // Huoneen kerros
	int room_number; // Huoneen numero
	std::string name; // Käyttäjän nimi
	int stay; // Keston pituus
};

void generate_room_data();
vector<int> define_hotel_size();

int random_num(int, int);
int input_int(int, int);
bool yes_no();
void enter();
std::string input_name();
std::string type_desc(room_data);
std::string tier_desc(room_data);
void print_room(room_data);