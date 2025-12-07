// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi - main.cpp - toivottavasti 5p toteutus
// 
// Pää ohjelma joka sisältää käyttäjä menun ja dev menun
//

// hotel_system.h sisältää kaikki namespacet, included, structit ja functiot
# include "hotel_system.h"

// Main Function ------------------------------------------------------------------------------------
// Luo pohja datan ja tarkastaa tiedostojen tilan
// Ajaa Menu function, joka suorittaa loput
// Tallentaa uudet tiedot ja sulkee
//
int main() {

	// Luo satunnaisten numeroiden siemenen
	// Asettaa couttiin kahden desimaalin tuloste takkuuden
	// Asettaa Suomalaisen localen ääkkösiä varten
	srand(time(0));
	cout << fixed << setprecision(2);
	setlocale(LC_ALL, "FI_fi");

	// Tarkistaa onko hotel_data.txt tiedost kunnossa
	// Jos ei luo uuden tiedoston, jotta ohjelma voidaan ajaa ilman ongelmia
	check_hotel();

	// Tallentaa hotellin kerros ja huone määrä vectoriin, jotta sitä voidaan käyttää muussa ohjelmassa
	// Luodaan 2d vectori taulukkoon indexinä muotoa [kerros][numero] käyttäen hotellin kokoa pohjana
	// Luodaan vectori taulukko johon säilötään varaukset
	vector<int> hotel = define_hotel_size();
	vector<vector<room_data>> rooms_array(hotel[0], vector<room_data>(hotel[1]));
	vector<reservation_data> reservations_array;

	// Tarkistetaan onko room_data.txt tiedosto olemassa ja jos ei ole luodaan uusi
	// Tarkistetaan onko reservation_data.txt olemassa ja varoitetaan puuttuvista varauksista
	check_rooms(rooms_array);
	check_reservations();

	// Ladataan huone data "rooms_array" taulukkoon, jotta sitä voidaan käyttää
	// Ladataan varaukset "reservations_array" taulukkoon, jotta sitä voidaan käyttää
	load_room_data(rooms_array);
	load_reservation_data(reservations_array, rooms_array);

	// Siirrytään menu ohjelmaan, jotta käyttäjä voi käyttää ohjelmaa
	menu(rooms_array, reservations_array);

	// Kun menu suljetaan tallenetaan päivitetty huone data room_data.txt tiedostoon
	save_room_data(rooms_array);

	// Jos varauksia on tallenetaan ne, mutta muuten tyhjennetään tiedosto, jotta vanhat varaukset eivät jää lojumaan
	if (!reservations_array.empty()) {
		save_reservation_data(reservations_array);
	}
	else {
		empty_reservation_data();
	}

	return 0;
}

// Valikko --------------------------------------------------------------------------------------
// Avataan valikko josta käyttäjä voi siirtyä eri toimintoihin
// 
void menu(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	// Alusta command muuttuja, ojonh käyttäjä laittaa toivotun tehtävän
	int command;

	// käyttäen do-while looppia pysytään menussa kunnes käyttäjä tahtoo sulkea ohjelman
	// syöttämällä 0 ohjelma poistuu loopista ja palaa main ohjelmaan jossa se voidaan sulkea
	do {
		system("cls");

		// Tulostetaan tehtävä vaihtoehdot
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

		// Syötteen tarkistus, joka tarkistaa onko syöte onnistunut
		// Jos syöte ei onnistu tyhjennetään se ja asetetaan command = -1 jotta voimme jatkaa loopissa
		if (!(cin >> command)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			command = -1;
		}

		// Switch-case joka tarkastaa syötetyn arvon ja siirtyy tehtävään jos sitä vastaava arvo on syötetty
		switch (command) {
		case 1: varaa_huone(rooms_array, reservations_array);  break;
		case 2: tulosta_varaus(rooms_array, reservations_array);  break;
		case 3: etsi_varaus(rooms_array, reservations_array);  break;
		case 4: muokkaa_varaus(rooms_array, reservations_array);  break;
		case 5: tulosta_kaikki_varaukset(rooms_array, reservations_array);  break;

		// 0 Erikois tila jossa vain tulostetaan viesti ja poistutaan ohjelmasta
		case 0: cout << "Suljetaan Ohjelma";  break;

		// 420 Erikois tila jossa avataan Dev menu
		case 420: dev_menu(rooms_array, reservations_array);  break;

		// Virhetilanne Tulostus
		default: cout << "Virhetilanne";
		}

	} while (command != 0);

}

// Dev Valikko -------------------------------------------------------------------------------
// Avataan Dev valikko jossa käyttäjä voi vaikuttaa tiedostojen sisältöön, mutta voi aiheuttaa ongelmia
//
void dev_menu(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	// Alusta command muuttuja, ojonh käyttäjä laittaa toivotun tehtävän
	int command;

	// käyttäen do-while looppia pysytään menussa kunnes käyttäjä tahtoo sulkea ohjelman
	// syöttämällä 0 ohjelma poistuu loopista ja palaa main ohjelmaan jossa se voidaan sulkea
	do {

		system("cls");

		// Tulostetaan tehtävä vaihtoehdot
		cout << "--------------------------" << endl;
		cout << left << setw(25) << "Developer Menu" << "|" << endl;
		cout << left << setw(25) << "[1] : Luo Huonedata" << "|" << endl;
		cout << left << setw(25) << "[2] : Poista varaukset" << "|" << endl;
		cout << left << setw(25) << "[3] : Luo uusi hotelli" << "|" << endl;
		cout << left << setw(25) << "[0] : sulje ohjelma" << "|" << endl;
		cout << "--------------------------" << endl;
		cout << "OSA KOMENNOISTA POISTAA DATAA TAI VAATII OHJELMAN UUDELLEEN KÄYNISTYKSEN" << endl;
		cout << "Syötä toiminto >> ";

		// Syötteen tarkistus, joka tarkistaa onko syöte onnistunut
		// Jos syöte ei onnistu tyhjennetään se ja asetetaan command = -1 jotta voimme jatkaa loopissa
		if (!(cin >> command)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			command = -1;
		}

		// Switch-case joka tarkastaa syötetyn arvon ja siirtyy tehtävään jos sitä vastaava arvo on syötetty
		switch (command) {
		case 1: generate_room_data(rooms_array);  break;
		case 2: clear_reservations(rooms_array, reservations_array);  break;
		case 3: uusi_hotelli();  break;

		// 0 Erikois tila jossa vain tulostetaan viesti ja poistutaan ohjelmasta
		case 0: cout << "Suljetaan Ohjelma";  break;

		// Virhetilanne Tulostus
		default: cout << "Virhetilanne";
		}

	} while (command != 0);
}