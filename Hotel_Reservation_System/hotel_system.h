#pragma once

// Sis‰lt‰‰ kaikki tarvittavat Include ja Namespace asiat headeriss‰, jotta cpp tiedostoissa on v‰hemm‰n clutter
# include <iostream>
# include <string>
# include <algorithm>
# include <functional>
# include <fstream>
# include <sstream>
# include <vector>

using namespace std;

// Room_data struct joka sis‰lt‰‰ kaiken huone datan
struct room_data {
	int floor = 0; // Huoneen kerros
	int number = 0; // Huone numero
	bool reserved = false; // Varattu?
	std::string type = "single"; // Single, Double
	std::string tier = "basic"; // Basic, Premium, Deluxe
	int coupon = 0; // Kupongin alennus
};

// Reservation_data struct joka sis‰lt‰‰ kaiken varaus datan
struct reservation_data {
	int reservation; // Varaus numero
	int room_floor; // Huoneen kerros
	int room_number; // Huoneen numero
	std::string name; // K‰ytt‰j‰n nimi
	int stay; // Keston pituus
};

// File Manager funktiot
void check_files();
void load_room_data(vector<vector<room_data>>&);
void save_room_data(vector<vector<room_data>>&);
void generate_room_data(vector<vector<room_data>>&);
vector<int> define_hotel_size();

// Tasks funktiot
int random_num(int, int);
int input_int(int, int);
bool yes_no();
void enter();
std::string input_name();
std::string type_desc(room_data);
std::string tier_desc(room_data);
void print_room(room_data);
bool any_free_rooms(vector<vector<room_data>>&);
int output_room_number(int, int);
vector<int> index_from_number(int);
void create_reservation(vector<reservation_data>&, int, int, std::string, int);
int create_reservation_number(vector<reservation_data>);