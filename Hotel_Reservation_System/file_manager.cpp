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

	for (int i = 0; i <= hotel_size[0] - 1; i++) {
		for (int j = 0; j <= hotel_size[1] - 1 && getline(room_data, line); j++) {
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
			rooms_array[i][j].reserved = stoi(reserved);
			rooms_array[i][j].type = type;
			rooms_array[i][j].tier = tier;
			rooms_array[i][j].coupon = stoi(coupon);
		}
	}

}

// Tallentaa uudet informaatiot tiedostoon ---------------------------------------------------------
void save_room_data(vector<vector<room_data>>& rooms_array) {

	ofstream room_data("room_data.txt", ofstream::out | ofstream::trunc);

	vector<int> hotel_size = define_hotel_size();

	for (int i = 0; i <= hotel_size[0] - 1; i++) {
		for (int j = 0; j <= hotel_size[1] - 1; j++) {
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

	for (int i = 0; i <= hotel_size[0] - 1; i++) {
		for (int j = 0; j <= hotel_size[1] - 1; j++) {
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
	return {3, 50};
}