// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

# include "hotel_system.h"

using namespace std;

void dev_menu(vector<vector<room_data>>&);

// Valikko ---------------------------------------------------------
int main() {
	srand(time(0)); // Generoi random siemen
	cout << fixed << setprecision(2);
	setlocale(LC_ALL, "FI_fi"); // Aseta Ääkköset oikein näkymiin

	// Alusta muuttuujat
	vector<int> hotel = define_hotel_size();
	int command;

	vector<vector<room_data>> rooms_array(hotel[0], vector<room_data>(hotel[1]));
	vector<reservation_data> reservations_array;

	load_room_data(rooms_array);
	load_reservation_data(reservations_array, rooms_array);

	cout << "suc";

	do { // Pyydä tehtävä Numeroa
		system("cls");

		cout << "--------------------------" << endl;
		cout << "Tehtävät : " << "\t\t|" << endl;
		cout << "[1] : Varaa Huone" << "\t|" << endl;
		cout << "[2] : Tulosta Varaus" << "\t|" << endl;
		cout << "[3] : Etsi Varaus" << "\t|" << endl;
		cout << "[4] : Muokkaa Varaus" << "\t|" << endl;
		cout << "[5] : Kaikki Varaukset" << "\t|" << endl;
		cout << "[0] : sulje ohjelma" << "\t|" << endl;
		cout << "--------------------------" << endl;
		cout << "Syötä toiminto >> ";

		if (!(cin >> command)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			command = -1;
		}

		switch (command) {
		case 1: varaa_huone(rooms_array, reservations_array);  break;
		case 2: tulosta_varaus(rooms_array, reservations_array);  break;
		case 3: etsi_varaus(rooms_array, reservations_array);  break;
		case 4: muokkaa_varaus(rooms_array, reservations_array);  break;
		case 5: tulosta_kaikki_varaukset(rooms_array, reservations_array);  break;

		case 0: cout << "Suljetaan Ohjelma";  break;

		case 420: dev_menu(rooms_array);  break;

		default: cout << "Virhetilanne";
		}

	} while (command != 0);

	save_room_data(rooms_array);

	if (!reservations_array.empty()) {
		save_reservation_data(reservations_array);
	}

	return 0;
}


// Dev Valikko ---------------------------------------------------------
void dev_menu(vector<vector<room_data>>& rooms_array) {

	// Alusta muuttuujat
	int command;

	do { // Pyydä tehtävä Numeroa

		system("cls");

		cout << "--------------------------" << endl;
		cout << "Developer Menu" << "\t\t|" << endl;
		cout << "[1] : Luo Huoonedata" << "\t|" << endl;
		cout << "[2] : Arvo Kuponkeja" << "\t|" << endl;
		cout << "[0] : sulje ohjelma" << "\t|" << endl;
		cout << "--------------------------" << endl;
		cout << "Syötä toiminto >> ";

		if (!(cin >> command)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			command = -1;
		}

		switch (command) {
		case 1: generate_room_data(rooms_array);  break;
		case 2: cout << "2";  break;

		case 0: cout << "Suljetaan Ohjelma";  break;

		default: cout << "Virhetilanne";
		}

	} while (command != 0);
}