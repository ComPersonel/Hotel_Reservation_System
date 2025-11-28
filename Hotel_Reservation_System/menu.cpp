// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

# include "hotel_system.h"

using namespace std;

void dev_menu();

// Valikko ---------------------------------------------------------
int main() {
	srand(time(0)); // Generoi random siemen

	setlocale(LC_ALL, "FI_fi"); // Aseta Ääkköset oikein näkymiin

	// Alusta muuttuujat
	vector<int> hotel = define_hotel_size();
	int command;

	vector<vector<room_data>> rooms_array(hotel[0], vector<room_data>(hotel[1]));

	do { // Pyydä tehtävä Numeroa

		system("cls");

		generate_room_data();

		cout << "--------------------------" << endl;
		cout << "Tehtävät : " << "\t\t|" << endl;
		cout << "1. Varaa Huone" << "\t\t|" << endl;
		cout << "2. Tulosta Varaus" << "\t|" << endl;
		cout << "3. Etsi Varaus" << "\t\t|" << endl;
		cout << "4. Peru Varaus" << "\t\t|" << endl;
		cout << "5. Kaikki Varaukset" << "\t|" << endl;
		cout << "0. sulje ohjelma" << "\t|" << endl;
		cout << "--------------------------" << endl;
		cout << "Syötä toiminto >> ";

		if (!(cin >> command)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			command = -1;
		}

		switch (command) {
		case 1: cout << "1";  break;
		case 2: cout << "2";  break;
		case 3: cout << "3";  break;
		case 4: cout << "4";  break;

		case 0: cout << "Suljetaan Ohjelma";  break;

		case 420: dev_menu();  break;

		default: cout << "Virhetilanne";
		}

	} while (command != 0);

	return 0;
}


// Dev Valikko ---------------------------------------------------------
void dev_menu() {

	// Alusta muuttuujat
	int command;

	do { // Pyydä tehtävä Numeroa

		system("cls");

		cout << "--------------------------" << endl;
		cout << "Developer Menu" << "\t\t|" << endl;
		cout << "1. Luo Huoonedata" << "\t|" << endl;
		cout << "2. Arvo Kuponkeja" << "\t|" << endl;
		cout << "0. sulje ohjelma" << "\t|" << endl;
		cout << "--------------------------" << endl;
		cout << "Syötä toiminto >> ";

		if (!(cin >> command)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			command = -1;
		}

		switch (command) {
		case 1: cout << "1";  break;
		case 2: cout << "2";  break;

		case 0: cout << "Suljetaan Ohjelma";  break;

		default: cout << "Virhetilanne";
		}

	} while (command != 0);
}