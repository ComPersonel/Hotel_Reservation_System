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
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Huono syöte, yritä uudelleen. >> ";
	}

	return result;
}

bool yes_no() {
	char result;

	while (!(cin >> result) || (result != 'n' && result != 'N' && result != 'y' && result != 'Y')) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (cin.get() == '\n') {
	}
}

string input_name() {

	string name = "<Undefined User>";

	while (!getline(cin, name)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Huono syöte, yritä uudelleen. >> ";
	}

	name.erase(std::remove(name.begin(), name.end(), ';'), name.end());

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
	cout << "Huone numero : " << room.number << endl;
	cout << "Huone malli : " << type_desc(room) << endl;
	cout << "Huone taso : " << tier_desc(room) << endl;
}

bool any_free_rooms(vector<vector<room_data>>& rooms_array) {

	vector<int> hotel_size = define_hotel_size();

	for (int i = 0; i <= hotel_size[0] - 1; i++) {
		for (int j = 0; j <= hotel_size[1] - 1; j++) {
			if (rooms_array[i][j].reserved == false) {
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
	int index = number % 100;

	return { floor, index };
}

void create_reservation(vector<reservation_data>& reservations_array, int floor, int number, string name, int stay) {

	reservation_data new_reservation;

	new_reservation.reservation = create_reservation_number(reservations_array);
	new_reservation.room_floor = floor;
	new_reservation.room_number = floor;
	new_reservation.name = name;
	new_reservation.stay = stay;

	reservations_array.push_back(new_reservation);
}

int create_reservation_number(vector<reservation_data> reservations_array) {
	int number = -1;
	int length = reservations_array.size();

	do {

		number = random_num(10000, 99999);

		if (length > 0) {
			for (int i = 0; i <= length - 1; i++) {
				if (reservations_array[i].reservation == number) {
					number = -1;
				}
			}
		}

	} while (number == -1);

	return number;
}