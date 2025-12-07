#pragma once

// Sisältää kaikki tarvittavat Include ja Namespace asiat, jotta cpp tiedostoissa on vähemmän roskaa
# include <iostream>
# include <string>
# include <algorithm>
# include <functional>
# include <fstream>
# include <sstream>
# include <vector>
# include <iomanip>
# include <limits>

using namespace std;

// Room_data struct joka sisältää kaiken huone datan
// floor		= Huoneen kerros + osa indexiä
// number		= Huoneen numero + osa indexiä
// reserved		= Huoneen tila
// type			= Yhden vai Kahden hengen huone
// tier			= Perus, Preemium vai Luksus huone
// coupon		= Huoneeseen sidottu alennus
struct room_data {
	int floor = 0;
	int number = 0;
	bool reserved = false;
	std::string type = "single";
	std::string tier = "basic";
	int coupon = 0;
};

// Reservation_data struct joka sisältää kaiken varaus datan
// index		= Varauksen indexi helpompaa löytämistä varten
// reservation	= Varauksen numero
// room_floor	= Varatun huoneen kerros
// room_number	= Varatun huoneen numero
// name			= Varaajan käyttäjänimi
// stay			= Kuinka monta päivää huone on varattu
struct reservation_data {
	int index = -1;
	int reservation = -1;
	int room_floor = -1;
	int room_number = -1;
	std::string name = "<Undefined User>";
	int stay = 1;
};

// Main.cpp functiot
// menu			= Pää käyttö menu
// dev_menu		= Dev menu
void menu(vector<vector<room_data>>&, vector<reservation_data>&);
void dev_menu(vector<vector<room_data>>&, vector<reservation_data>&);

// File Manager.cpp functiot
// check_hotel				= Tarkistaa hotel_data.txt tiedoston olemassa olon
// check_rooms				= Tarkistaa room_data.txt tiedoston olemassa olon
// check_reservations		= Tarkistaa reservation_data.txt tiedoston olemassa olon
// load_room_data			= Lataa room_data.txt tiedoston sisällön käytettävään muotoon
// save_room_data			= Tallentaa muutetun huone datan room_data.txt tiedostoon
// generate_room_data		= Luo uuden huone datan tarvittaessa
// load_reservation_data	= Lataa reservation_data.txt tiedoston sisällön käytettävään muotoon
// save_reservation_data	= Tallentaa muutetun varaus datan reservation_data.txt tiedostoon
// empty_reservation_data	= Luo tai tyhjentää reservation_data.txt tiedoston tarvittaessa
// define_hotel_size		= Lukee hotel_data.txt tiedostosta hotellin kerros ja huone määrän, palauttaa tämän informaation vectorina
// create_hotel_size_random	= Luo satunnaisen hotelli informaation
// create_hotel_size_input	= Luo hotellin koko informaation käyttäjän syötteestä
void check_hotel();
void check_rooms(vector<vector<room_data>>&);
void check_reservations();
void load_room_data(vector<vector<room_data>>&);
void save_room_data(vector<vector<room_data>>);
void generate_room_data(vector<vector<room_data>>&);
void load_reservation_data(vector<reservation_data>&, vector<vector<room_data>>&);
void save_reservation_data(vector<reservation_data>);
void empty_reservation_data();
vector<int> define_hotel_size();
void create_hotel_size_random();
void create_hotel_size_input( int, int);

// Tasks.cpp functiot
// random_num					= Palauttaa satunnaisen arvon 2 annetun int arvon väliltä
// input_int					= Ottaa syötteeksi int arvon 2 annetun int arvon väliltä. Palauttaa onnistuneen syötteen
// input_name					= Ottaa syötteeksi tekstiä ja palauttaa sen ilman ; merkkejä teknisistä syöstä
// yes_no						= Ottaa syötteenä Y tai N. Palauttaa bool arvon
// enter						= Pyytää käyttäjää painamaan enter näppäintä jatkaakseen
// type_desc					= Palauttaa kuvaavan tekstin huoneen tyypistä
// tier_desc					= Palauttaa kuvaavan tekstin huoneen tasosta
// print_room					= Tulostaa huoneen numeron, tyypin ja tason
// print_reservation			= Tulostaa varauksen numeron, nimen ja keston
// any_free_rooms				= Palauttaa onko hotellissa yhtään vapaata huonetta
// free_rooms					= Palauttaa onko vapaita huoneita tietyltä kerrokselta, tyypiltä tai tasolta
// output_room_number			= Palauttaa huoneen numeron käyttäen sen indexi arvoja
// index_from_number			= Palauttaa huoneen indexit vectorina sen numerosta
// create_reservation			= Luo varauksen annetuista tiedoista
// create_reservation_number	= Luo uniikin varaus numeron 10000-99999 väliltä
// collect_rooms				= Kerää tietynlaisia huoneita vector taulukkoon
// random_from_list				= Valitsee satunnaisen vaihtoehdon vector taulukosta
// print_bill					= Tulostaa laskun
// print_cost					= Laskee varauksen kokonais hinnan
// find_by_name					= Etsii varauksen nimellä
// find_by_reservation			= Etsii varauksen sen numerolla
// clear_reservations			= Poistaa varauksen
int random_num(int, int);
int input_int(int, int);
std::string input_name();
bool yes_no();
void enter();
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

// Commands.cpp function | nimetty suomeksi, koska ne on suoraan sidottu käyttäjän komentoihin
// varaa_huone				= Kerää informaation tehdäkseen varauksen
// tulosta_varaus			= Tulostaa viimeisimmän varauksen
// tulosta_kaikki_varaukset	= Tulostaa kaikki varaukset
// etsi_varaus				= Etsii varauksen joko nimellä tai varausnumerolla
// muokkaa_varaus			= Muokkaa varausta
// peru_varaus				= Peruuta varaus (muokkaa_varaus aliohjelma)
// muokkaa_nimi				= Muokkaa varaajan nimeä (muokkaa_varaus aliohjelma)
// muokkaa_kesto			= Muokkaa varauksen kestoa (muokkaa_varaus aliohjelma)
// muokkaa_huone			= Muokkaa varattua huonetta (muokkaa_varaus aliohjelma)
// uusi_hotelli				= Luo kokonaan uuden hotellin
void varaa_huone(vector<vector<room_data>>&, vector<reservation_data>&);
void tulosta_varaus(vector<vector<room_data>>, vector<reservation_data>);
void tulosta_kaikki_varaukset(vector<vector<room_data>>, vector<reservation_data>);
void etsi_varaus(vector<vector<room_data>>, vector<reservation_data>);
void muokkaa_varaus(vector<vector<room_data>>&, vector<reservation_data>&);
int peru_varaus(vector<vector<room_data>>&, vector<reservation_data>&, reservation_data);
void muokkaa_nimi(vector<reservation_data>&, reservation_data);
void muokkaa_kesto(vector<reservation_data>&, reservation_data);
void muokkaa_huone(vector<vector<room_data>>&, vector<reservation_data>&, reservation_data);
void uusi_hotelli();
