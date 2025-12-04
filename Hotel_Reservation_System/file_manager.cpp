// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

/*
* Lataa huoneiden datan arrayihin helppoa käsittelyä varten
* Tallentaa päivitetyt datat uudestaan, jotta niitä voidaan yhä käyttää
*/


# include "hotel_system.h"

using namespace std;

// Tarkista onko huone data olemassa ---------------------------------------------------
void check_files() {

}


// Lataa huoneet käytettäviksi ---------------------------------------------------------
void load_room_data(vector<vector<room_data>>& rooms_array) {

	ifstream room_data("room_data.txt");

	string line;
	vector<int> hotel_size = define_hotel_size();

	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1] && getline(room_data, line); j++) {
			stringstream ss(line);
			string floor, number, reserved, type, tier, coupon;

			getline(ss, floor, ';');
			getline(ss, number, ';');
			getline(ss, reserved, ';');
			getline(ss, type, ';');
			getline(ss, tier, ';');
			getline(ss, coupon, ';');

			rooms_array[i][j].floor = stoi(floor);
			rooms_array[i][j].number = stoi(number);
			rooms_array[i][j].reserved = false;
			rooms_array[i][j].type = type;
			rooms_array[i][j].tier = tier;
			rooms_array[i][j].coupon = stoi(coupon);
		}
	}

}

// Tallentaa uudet informaatiot tiedostoon ---------------------------------------------------------
void save_room_data(vector<vector<room_data>> rooms_array) {

	ofstream room_data("room_data.txt", ofstream::out | ofstream::trunc);

	vector<int> hotel_size = define_hotel_size();

	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			room_data << rooms_array[i][j].floor << ";";
			room_data << rooms_array[i][j].number << ";";
			room_data << rooms_array[i][j].reserved << ";";
			room_data << rooms_array[i][j].type << ";";
			room_data << rooms_array[i][j].tier << ";";
			room_data << rooms_array[i][j].coupon << ";" << endl;

		}
	}

}

// Generoi pohjatiedoston huoneita varten ---------------------------------------------------------
void generate_room_data(vector<vector<room_data>>& rooms_array) {

	ofstream room_data("room_data.txt", ofstream::out | ofstream::trunc);
	int random;

	vector<int> hotel_size = define_hotel_size();

	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			rooms_array[i][j].floor  = i;
			rooms_array[i][j].number = j + 1;
			rooms_array[i][j].reserved = false;

			if (j >= hotel_size[1] / 2) {
				rooms_array[i][j].type = "double";
			}
			else {
				rooms_array[i][j].type = "single";
			}

			if (j == hotel_size[1] / 2 - 1 || j == hotel_size[1] - 1) {
				rooms_array[i][j].tier = "deluxe";
			}
			else if ((j > hotel_size[1] / 4 && j < hotel_size[1] / 2) || j > hotel_size[1] / 4 + hotel_size[1] / 2) {
				rooms_array[i][j].tier = "premium";
			}
			else {
				rooms_array[i][j].tier = "basic";
			}

			random = random_num(1, 10);

			if (random == 10) {
				rooms_array[i][j].coupon = 20;
			}
			else if (random > 5) {
				rooms_array[i][j].coupon = 10;
			}else{
				rooms_array[i][j].coupon = 0;
			}

		}
	}

}

vector<int> define_hotel_size() {
	ifstream hotel_information("hotel_information.txt");

	string line;
	vector<int> result;

	while (getline(hotel_information, line)) {
		stringstream ss(line);
		result.push_back(stoi(line));

	}

	return result;
}

// Lataa Varaukset ---------------------------------------------------------
void load_reservation_data(vector<reservation_data>& reservations_array, vector<vector<room_data>>& rooms_array) {

	ifstream reservation_data("reservation_data.txt");

	string line;

	int index = 0;

	while (getline(reservation_data, line)) {
		stringstream ss(line);
		string reservation, floor, number, name, stay;

		if (line.length() != 0) {
			getline(ss, reservation, ';');
			getline(ss, floor, ';');
			getline(ss, number, ';');
			getline(ss, name, ';');
			getline(ss, stay, ';');

			rooms_array[stoi(floor)][stoi(number)].reserved = true;

			reservations_array.push_back({ index, stoi(reservation), stoi(floor), stoi(number), name, stoi(stay) });

			index++;

		}

	}

}

// Tallentaa uudet informaatiot tiedostoon ---------------------------------------------------------
void save_reservation_data(vector<reservation_data> reservations_array) {

	ofstream reservation_data("reservation_data.txt", ofstream::out | ofstream::trunc);

	for (int i = 0; i <= reservations_array.size() - 1; i++) {
		reservation_data << reservations_array[i].reservation << ";";
		reservation_data << reservations_array[i].room_floor << ";";
		reservation_data << reservations_array[i].room_number << ";";
		reservation_data << reservations_array[i].name << ";";
		reservation_data << reservations_array[i].stay << ";" << endl;
	}

}

vector<int> define_hotel_size() {
	ifstream hotel_information("hotel_information.txt");

	string line;
	vector<int> result;

	while (getline(hotel_information, line)) {
		stringstream ss(line);
		result.push_back(stoi(line));

	}

	return result;
}