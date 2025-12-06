// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

# include "hotel_system.h"

using namespace std;

// Main Funktio ----------------------------------------------------
int main() {

	srand(time(0)); // Generoi random siemen
	cout << fixed << setprecision(2);

	setlocale(LC_ALL, "FI_fi"); // Aseta Ääkköset oikein näkymiin

	// Alusta muuttuujat
	vector<int> hotel = define_hotel_size();

	vector<vector<room_data>> rooms_array(hotel[0], vector<room_data>(hotel[1]));
	vector<reservation_data> reservations_array;

	check_files();

	load_room_data(rooms_array);
	load_reservation_data(reservations_array, rooms_array);

	menu(rooms_array, reservations_array);

	save_room_data(rooms_array);

	if (!reservations_array.empty()) {
		save_reservation_data(reservations_array);
	}
	else {
		empty_reservation_data();
	}

	return 0;
}

// Valikko ---------------------------------------------------------
void menu(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	// Alusta muuttuujat
	int command;

	do { // Pyydä tehtävä Numeroa
		system("cls");

		cout << "--------------------------" << endl;
		cout << left << setw(25) << "Tehtävät : " << "|" << endl;
		cout << left << setw(25) << "[1] : Varaa Huone" << "|" << endl;
		cout << left << setw(25) << "[2] : Tulosta Varaus" << "|" << endl;
		cout << left << setw(25) << "[3] : Etsi Varaus" << "|" << endl;
		cout << left << setw(25) << "[4] : Muokkaa Varaus" << "|" << endl;
		cout << left << setw(25) << "[5] : Kaikki Varaukset" << "|" << endl;
		cout << left << setw(25) << "[0] : sulje ohjelma" << "|" << endl;
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

		case 420: dev_menu(rooms_array, reservations_array);  break;

		default: cout << "Virhetilanne";
		}

	} while (command != 0);

}


// Dev Valikko ---------------------------------------------------------
void dev_menu(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	// Alusta muuttuujat
	int command;

	do { // Pyydä tehtävä Numeroa

		system("cls");

		cout << "--------------------------" << endl;
		cout << left << setw(25) << "Developer Menu" << "|" << endl;
		cout << left << setw(25) << "[1] : Luo Huoonedata" << "|" << endl;
		cout << left << setw(25) << "[2] : Poista varaukset" << "|" << endl;
		cout << left << setw(25) << "[3] : Luo uusi hotelli" << "|" << endl;
		cout << left << setw(25) << "[0] : sulje ohjelma" << "|" << endl;
		cout << "--------------------------" << endl;
		cout << "OSA KOMENNOISTA POISTAA DATAA TAI VAATII OHJELMAN UUDELLEEN KÄYNISTYKSEN" << endl;
		cout << "Syötä toiminto >> ";

		if (!(cin >> command)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			command = -1;
		}

		switch (command) {
		case 1: generate_room_data(rooms_array);  break;
		case 2: clear_reservations(rooms_array, reservations_array);  break;
		case 3: uusi_hotelli(rooms_array, reservations_array);  break;

		case 0: cout << "Suljetaan Ohjelma";  break;

		default: cout << "Virhetilanne";
		}

	} while (command != 0);
}