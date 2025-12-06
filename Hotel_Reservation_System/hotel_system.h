#pragma once

// Sis‰lt‰‰ kaikki tarvittavat Include ja Namespace asiat headeriss‰, jotta cpp tiedostoissa on v‰hemm‰n clutter
# include <iostream>
# include <string>
# include <algorithm>
# include <functional>
# include <fstream>
# include <sstream>
# include <vector>
# include <iomanip>
# include <limits>
# include <locale>

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
	int index; // Varauksen index
	int reservation; // Varaus numero
	int room_floor; // Huoneen kerros
	int room_number; // Huoneen numero
	std::string name; // K‰ytt‰j‰n nimi
	int stay; // Keston pituus
};

// Main
void menu(vector<vector<room_data>>&, vector<reservation_data>&);
void dev_menu(vector<vector<room_data>>&, vector<reservation_data>&);

// File Manager funktiot
void check_hotel();
void check_rooms(vector<vector<room_data>>&);
void check_reservations();
void load_room_data(vector<vector<room_data>>&);
void save_room_data(vector<vector<room_data>>);
void generate_room_data(vector<vector<room_data>>&);
void load_reservation_data(vector<reservation_data>&, vector<vector<room_data>>&);
void save_reservation_data(vector<reservation_data>);
vector<int> define_hotel_size();
void empty_reservation_data();
void create_hotel_size_random();
void create_hotel_size_input( int, int);

// Tasks funktiot
int random_num(int, int);
int input_int(int, int);
bool yes_no();
void enter();
std::string input_name();
std::string type_desc(room_data);
std::string tier_desc(room_data);
void print_room(room_data);
void print_reservation(reservation_data);
bool any_free_rooms(vector<vector<room_data>>);
bool free_rooms(vector<vector<room_data>>, int, int, int);
int output_room_number(int, int);
vector<int> index_from_number(int);
void create_reservation(vector<reservation_data>&, int, int, std::string, int);
int create_reservation_number(vector<reservation_data>);
vector<room_data> collect_rooms(vector<vector<room_data>>, int, int, int);
vector<int> random_from_list(vector<room_data>);
void print_bill(room_data, reservation_data);
double print_cost(room_data, reservation_data);
vector<reservation_data> find_by_name(vector<reservation_data>, std::string);
vector<reservation_data> find_by_reservation(vector<reservation_data>, int);
void clear_reservations(vector<vector<room_data>>&, vector<reservation_data>&);

// Komento funktiot
void varaa_huone(vector<vector<room_data>>&, vector<reservation_data>&);
void tulosta_varaus(vector<vector<room_data>>, vector<reservation_data>);
void etsi_varaus(vector<vector<room_data>>, vector<reservation_data>);
void muokkaa_varaus(vector<vector<room_data>>&, vector<reservation_data>&);
void tulosta_kaikki_varaukset(vector<vector<room_data>>, vector<reservation_data>);
int peru_varaus(vector<vector<room_data>>&, vector<reservation_data>&, reservation_data);
void muokkaa_nimi(vector<reservation_data>&, reservation_data);
void muokkaa_kesto(vector<reservation_data>&, reservation_data);
void muokkaa_huone(vector<vector<room_data>>&, vector<reservation_data>&, reservation_data);
void uusi_hotelli();