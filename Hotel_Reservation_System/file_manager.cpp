// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

/*
* Lataa huoneiden datan arrayihin helppoa käsittelyä varten
* Tallentaa päivitetyt datat uudestaan, jotta niitä voidaan yhä käyttää
*/


# include "hotel_system.h"

using namespace std;

// Lataa huoneet käytettäviksi ---------------------------------------------------------
room_data* load_room_data(room_data rooms_array[]) {

	ifstream room_data("room_data.txt");

	string line;

	for (int i = 0; i < 10 && getline(room_data, line); i++) {
		stringstream ss(line);
		string floor, number, reserved, type, tier, coupon;

		getline(ss, floor, ';');
		getline(ss, number, ';');
		getline(ss, reserved, ';');
		getline(ss, type, ';');
		getline(ss, tier, ';');
		getline(ss, coupon, ';');

		rooms_array[i].floor = stoi(number);
		rooms_array[i].number = stoi(number);
		rooms_array[i].reserved = stoi(reserved);
		rooms_array[i].type = type;
		rooms_array[i].tier = tier;
		rooms_array[i].coupon = stoi(coupon);
	}

	return rooms_array;
}

// Tallentaa uudet informaatiot tiedostoon ---------------------------------------------------------
void save_room_data(room_data rooms_array[]) {

	ofstream room_data("room_data.txt", ofstream::out | ofstream::trunc);

	for (int i = 0; i < 10; i++) {
		room_data << rooms_array[i].floor << ";";
		room_data << rooms_array[i].number << ";";
		room_data << rooms_array[i].reserved << ";";
		room_data << rooms_array[i].type << ";";
		room_data << rooms_array[i].tier << ";";
		room_data << rooms_array[i].coupon << ";" << endl;
	}

}

// Generoi pohjatiedoston huoneita varten ---------------------------------------------------------
void generate_room_data() {

	int random;

	vector<int> hotel_size = define_hotel_size();

	for (int i = 0; i <= hotel_size[0]; i++) {
		for (int j = 0; j <= hotel_size[1] - 1; j++) {
			cout << "i = " << i << " : j = " << j << endl;
			room_data << rooms_array[i].floor << ";";
			room_data << rooms_array[i].number << ";";
			room_data << rooms_array[i].reserved << ";";
			room_data << rooms_array[i].type << ";";
			room_data << rooms_array[i].tier << ";";
			room_data << rooms_array[i].coupon << ";" << endl;

		}
	}

}

vector<int> define_hotel_size() {
	return {2, 50};
}