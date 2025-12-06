// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

# include "hotel_system.h"


// Generoi random numer väliltä min - max ---------------------------------------------------------
int random_num(int min, int max) {

	return rand() % (max + 1 - min) + min;
}

int input_int(int min, int max) {
	int result;

	while (!(cin >> result) || result < min || result > max) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Huono syöte, yritä uudelleen. >> ";
	}

	return result;
}

bool yes_no() {
	char result;

	while (!(cin >> result) || (result != 'n' && result != 'N' && result != 'y' && result != 'Y')) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Huono syöte, yritä uudelleen. >> ";
	}
	if (result == 'y' || result == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

void enter() {
	cout << endl << "Paina enter jatkaaksesi.";

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cin.get();
}

string input_name() {

	string name = "<Undefined User>";

	while (!getline(cin, name) || name.empty() || all_of(name.begin(), name.end(), [](unsigned char c) { return isspace(c); })) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Huono syöte, yritä uudelleen. >> ";
	}

	name.erase(remove(name.begin(), name.end(), ';'), name.end());

	if (!cin.putback('\n')) {
		if (!cin) {
			cin.clear();
		}
	}

	return name;
}

string type_desc(room_data room) {
	if (room.type == "single") return "yhden hengen";
	if (room.type == "double") return "kahden hengen";
	if (room.type != "single" && room.type != "double") return "<Room Type Undefined>";
}

string tier_desc(room_data room) {
	if (room.tier == "basic") return "perus";
	if (room.tier == "premium") return "preemium";
	if (room.tier == "deluxe") return "luksus";
	if (room.tier != "basic" && room.tier != "premium" && room.tier != "deluxe") return "<Room Tier Undefined>";
}

void print_room(room_data room) {
	cout << left << setw(25) << "Huone numero" << ":" << output_room_number(room.floor, room.number) << endl;
	cout << left << setw(25) << "Huone malli" << ":" << type_desc(room) << endl;
	cout << left << setw(25) << "Huone taso" << ":" << tier_desc(room) << endl;
}

void print_reservation(reservation_data reservation) {
	cout << left << setw(25) << "Varaus numero" << ":" << reservation.reservation << endl;
	cout << left << setw(25) << "Varaajan nimi" << ":" << reservation.name << endl;
	cout << left << setw(25) << "Varauksen kesto" << ":" << reservation.stay << " päivää" << endl;
}

bool any_free_rooms(vector<vector<room_data>> rooms_array) {

	vector<int> hotel_size = define_hotel_size();

	bool return_value = false;

	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			if (rooms_array[i][j].reserved == false) {
				return_value = true;
			}
		}
	}
	return return_value;
}

bool free_rooms(vector<vector<room_data>> rooms_array, int floor, int type, int tier) {

	string room_type = "single";
	string room_tier = "basic";
	vector<int> hotel_size = define_hotel_size();
	vector<room_data> return_array;

	if (type == 2) {
		room_type = "double";
	}

	if (tier == 2) {
		room_tier = "premium";
	}
	else if (tier == 3) {
		room_tier = "deluxe";
	}

	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			if ((rooms_array[i][j].type == room_type || type == -1) && (rooms_array[i][j].tier == room_tier || tier == -1) && (rooms_array[i][j].floor == floor - 1 || floor == -1)) {
				return true;
			}
		}
	}

	return false;

}

int output_room_number(int floor, int number) {
	return ((floor + 1) * 100) + number;
}

vector<int> index_from_number(int number) {

	int floor = number / 100 - 1;
	int index = number % 100 - 1;

	return { floor, index };
}

void create_reservation(vector<reservation_data>& reservations_array, int floor, int number, string name, int stay) {

	reservation_data new_reservation;

	new_reservation.reservation = create_reservation_number(reservations_array);
	new_reservation.room_floor = floor;
	new_reservation.room_number = number;
	new_reservation.name = name;
	new_reservation.stay = stay;

	reservations_array.insert(reservations_array.begin(),new_reservation);
}

int create_reservation_number(vector<reservation_data> reservations_array) {
	int number = -1;
	int length = reservations_array.size();

	do {

		number = random_num(10000, 99999);

		if (length > 0) {
			for (int i = 0; i < length; i++) {
				if (reservations_array[i].reservation == number) {
					number = -1;
				}
			}
		}

	} while (number == -1);

	return number;
}

vector<room_data> collect_rooms(vector<vector<room_data>> rooms_array, int floor, int type, int tier) {
	string room_type = "single";
	string room_tier = "basic";
	vector<int> hotel_size = define_hotel_size();
	vector<room_data> return_array;

	if (type == 2) {
		room_type = "double";
	}

	if (tier == 2) {
		room_tier = "premium";
	}
	else if (tier == 3) {
		room_tier = "deluxe";
	}

	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			if ((rooms_array[i][j].type == room_type || type == -1) && (rooms_array[i][j].tier == room_tier || tier == -1) && (rooms_array[i][j].floor == floor - 1 || floor == -1)) {
				return_array.push_back(rooms_array[i][j]);
			}
		}
	}

	return return_array;
}

vector<int> random_from_list(vector<room_data> room_list) {

	int random = -1;

	do {
		random = random_num(0, room_list.size() - 1);
		if (room_list[random].reserved == true) {
			random = -1;
		}

	} while (random == -1);
	return { room_list[random].floor, room_list[random].number - 1};
}

void print_bill(room_data room, reservation_data reservation) {

	double base_cost = 100.0, cost_multiplier = 1.0;

	if (room.type == "double") {
		base_cost = 150.0;
	}

	if (room.tier == "premium") {
		cost_multiplier = 1.5;
	}
	else if (room.tier == "deluxe") {
		cost_multiplier = 2.0;
	}

	cout << left << setw(25) << "Huoneen pohja hinta" << ":" << base_cost << " Euroa" << endl;
	cout << left << setw(25) << "Huoneen lisä hinta" << ":" << base_cost * (cost_multiplier - 1.0) << " Euroa" << endl;
	cout << left << setw(25) << "Varauksen kesto" << ":" << reservation.stay << " Päivää" << endl;
	cout << left << setw(25) << "Huone alennus" << ":" << room.coupon << "%" << endl;

	cout << left << setw(25) << "Kokonaishinta" << ":" << print_cost(room, reservation) << " Euroa" << endl;;
}

double print_cost(room_data room, reservation_data reservation) {
	double base_cost = 100.0, cost_multiplier = 1.0;

	if (room.type == "double") {
		base_cost = 150.0;
	}

	if (room.tier == "premium") {
		cost_multiplier = 1.5;
	}
	else if (room.tier == "deluxe") {
		cost_multiplier = 2.0;
	}

	return (base_cost * cost_multiplier * reservation.stay) - (base_cost * cost_multiplier * reservation.stay / 100 * room.coupon);

}

vector<reservation_data> find_by_name(vector<reservation_data> reservations_array, string name) {
	vector<reservation_data> reservations_list;

	for (int i = 0; i < reservations_array.size(); i++) {
		if (reservations_array[i].name == name) {
			reservations_list.push_back(reservations_array[i]);
		}
	}

	return reservations_list;
}

vector<reservation_data> find_by_reservation(vector<reservation_data> reservations_array, int reservation) {
	vector<reservation_data> reservations_list;
	for (int i = 0; i < reservations_array.size(); i++) {
		if (reservations_array[i].reservation == reservation) {
			reservations_list.push_back(reservations_array[i]);
		}
	}
	return reservations_list;
}

void clear_reservations(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	int floor, number;

	while (reservations_array.empty() == false) {

		floor = reservations_array[0].room_floor;
		number = reservations_array[0].room_number;

		rooms_array[floor][number].reserved = false;

		reservations_array.erase(reservations_array.begin());

		empty_reservation_data();

	}

}