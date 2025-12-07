// Eetu ParÈn

// Harjoitustyˆ - Hotellivaraus systeemi - file_manager.cpp - toivottavasti 5p toteutus
// 
// Lataa huoneiden datan arrayihin helppoa k‰sittely‰ varten
// Tallentaa p‰ivitetyt datat uudestaan, jotta niit‰ voidaan yh‰ k‰ytt‰‰
//

// hotel_system.h sis‰lt‰‰ kaikki namespacet, included, structit ja functiot
# include "hotel_system.h"

// check_hotel
// Tarkistaa hotel_data.txt tiedoston olemassa olon ja tarvittaessa luo uuden tiedoston
void check_hotel() {

	// Avataan hotel_data.txt tiedosto
	ifstream hotel_data("hotel_data.txt");

	// Jos avattu tiedosto on "hyv‰" ei tapahdu mit‰‰n
	// Jos se ei ole "hyv‰" tulostetaan viestit ilmoittamaan t‰m‰ ja pyydet‰‰n luomaan uusi hotelli
	if (!hotel_data.good()) {

		cout << "Hotelli Data tiedosto puuttuu." << endl;
		cout << "Joudut luomaan uuden hotelli datan." << endl;

		// Paina enter jatkaaksesi
		enter();

		// Kutsutaan functio jolla luodaan uusi hotelli data
		uusi_hotelli();
	}
}

// check_rooms
// Tarkistaa room_data.txt tiedoston olemassa olon ja tarvittaessa luo uuden tiedoston
// Ottaa rooms_array 2d vectorin syˆtteen‰, jotta se voidaan t‰ytt‰‰ tarvittaessa
void check_rooms(vector<vector<room_data>>& rooms_array) {

	// Avataan room_data.txt tiedosto
	ifstream room_data("room_data.txt");

	// Jos avattu tiedosto on "hyv‰" ei tapahdu mit‰‰n
	// Jos se ei ole "hyv‰" tulostetaan viestit ilmoittamaan t‰m‰ ja luodaan uusi huone data
	if (!room_data.good()) {

		cout << "Huone Data puuttuu." << endl;
		cout << "Uuden hotelli datan luominen poistaa vanhojen huoneiden tiedot." << endl;

		// Paina enter jatkaaksesi
		enter();

		// Kutsutaan huone datan generoiva functio
		generate_room_data(rooms_array);
	}
}

// check_reservations
// Tarkistaa reservation_data.txt tiedoston olemassa olon ja tarvittaessa luo uuden tiedoston
// mekaanisesti ei tee mit‰‰n muuta kuin ilmoita, ett‰ vanhat varaukset ovat poistettu
void check_reservations() {

	// Avataan reservation_data.txt tiedosto
	ifstream reservation_data("reservation_data.txt");

	// Jos avattu tiedosto on "hyv‰" ei tapahdu mit‰‰n
	// Jos se ei ole "hyv‰" tulostetaan viestit ilmoittamaan t‰m‰
	if (!reservation_data.good()) {

		cout << "Varaus Data puuttuu." << endl;
		cout << "Vanhoja varauksia ei voi hakea." << endl;

		// Paina enter jatkaaksesi
		enter();
	}
}

// load_room_data
// Otetaan data room_data.txt tiedostosta k‰ytett‰v‰‰n muotoon ja laitetaan ne rooms_array 2d vectoriin
// Ottaa rooms_array vectorin syˆtteen‰, jotta sen sis‰‰n voidaan lis‰t‰ huoneet
void load_room_data(vector<vector<room_data>>& rooms_array) {

	// Avataan room_data.txt tiedosto
	ifstream room_data("room_data.txt");

	// Alustetaan muuttujat ja haetaan hotellin koko vectoriin
	string line;
	vector<int> hotel_size = define_hotel_size();

	// Nestattu for-loop joka k‰y l‰pi kaikki hotellin kerrokset ja huoneet
	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1] && getline(room_data, line); j++) {

			// Alustaa stringsream ss joka k‰ytt‰‰ line muuttujaa inputtina
			// Alustaa muuttujat kaikille huone_datan komponenteille
			stringstream ss(line);
			string floor, number, reserved, type, tier, coupon;

			// Getline hakee jokaisen rivin palasen eroteltuna ";" merkill‰ ja asettaa ne vastaaville muuttujille
			getline(ss, floor, ';');
			getline(ss, number, ';');
			getline(ss, reserved, ';'); // Reserved arvo s‰ilˆt‰‰n vaikka sit‰ ei k‰ytet‰ getline syist‰
			getline(ss, type, ';');
			getline(ss, tier, ';');
			getline(ss, coupon, ';');

			// T‰m‰n j‰lkeen ne asetetaan rooms_array 2d vectoriin jossa niit‰ voidaan k‰ytt‰‰ muihin toimintoihin
			rooms_array[i][j].floor = stoi(floor);
			rooms_array[i][j].number = stoi(number);
			rooms_array[i][j].reserved = false;
			rooms_array[i][j].type = type;
			rooms_array[i][j].tier = tier;
			rooms_array[i][j].coupon = stoi(coupon);
		}
	}
}

// save_room_data
// Tallenetaan rooms_array 2d vectori room_data.txt tiedostoon tiedon tallentamiseksi ja s‰ilˆmiseksi
// Ottaa rooms_array vectorin syˆtteen‰ jotta se voi tallentaa kyseiset tiedot
void save_room_data(vector<vector<room_data>> rooms_array) {

	// Avataan ja tyhjennet‰‰n room_data.txt tiedosto
	// Tiedosto pit‰‰ tyhjent‰‰ ettei tule kopio dataa
	ofstream room_data("room_data.txt", ofstream::out | ofstream::trunc);

	// Tallenetaan hotellin koko vectorina
	vector<int> hotel_size = define_hotel_size();

	// Nestattu for-loop joka sijoittaa rooms_array tiedot k‰ydylt‰ indexilt‰ tiedostoon erotellen tiedot ";" merkill‰
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

// generate_room_data
// Tarvittaessa generoi uuden huone datan rooms_array vectoriin
// K‰ytetty dev menusta tai uutta hotellia luodessa
void generate_room_data(vector<vector<room_data>>& rooms_array) {

	// Avataan ja tyhjennet‰‰n room_data.txt tiedosto
	// Tiedosto pit‰‰ tyhjent‰‰ ettei tule kopio dataa
	ofstream room_data("room_data.txt", ofstream::out | ofstream::trunc);

	// Alustetaan random muuttuja huoneiden kuponkeja varten ja otetaan hotellin koko vectoriin
	int random;
	vector<int> hotel_size = define_hotel_size();

	// Nestattu for-loop joka k‰y jokaisen tarvittavan indexin
	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {

			// Huoneen kerros luodan ensimm‰isen for-loopin arvolla 
			// Huoneen numero luodaan toisen for-loopin arvolla +1
			// Huoneelle asetetaan pohja arvoksi ei varattu
			rooms_array[i][j].floor  = i;
			rooms_array[i][j].number = j + 1;
			rooms_array[i][j].reserved = false;

			// Jos huoneen numero on enemm‰n kuin puolet kerroksesta se on kahden hengen huone
			// Jos huoneen numero on v‰hemm‰n kuin puolet kerroksesta se on yhden hengen huone
			if (j >= hotel_size[1] / 2) {
				rooms_array[i][j].type = "double";
			}
			else {
				rooms_array[i][j].type = "single";
			}

			// Jos huone on isoin mahdollinen numero yhden tai kahden hengen huoneista se on luksus huone
			// Jos huone on noin yli puolet yhden tai kahden hengen huoneista se on preemium huone
			// Muuten huone on perus huone
			if (j == hotel_size[1] / 2 - 1 || j == hotel_size[1] - 1) {
				rooms_array[i][j].tier = "deluxe";
			}
			else if ((j > hotel_size[1] / 4 && j < hotel_size[1] / 2) || j > hotel_size[1] / 4 + hotel_size[1] / 2) {
				rooms_array[i][j].tier = "premium";
			}
			else {
				rooms_array[i][j].tier = "basic";
			}

			// Luodaan satunnainen kuponki 0%, 10% ja 20% v‰lilt‰
			// satunnainen arvo 10 = 20% alennus
			// satunnainen arvo >5 = 10%
			// muuten 0%
			random = random_num(1, 10);
			if (random == 10) {
				rooms_array[i][j].coupon = 20;
			}
			else if (random > 5) {
				rooms_array[i][j].coupon = 10;
			}
			else {
				rooms_array[i][j].coupon = 0;
			}
		}
	}
}

// load_reservation_data
// Ladataan varaukset reservation_data.txt tiedostosta
// Functio ottaa reservations_arrayn ja rooms_arrayn sis‰‰n muokkaamista varten
void load_reservation_data(vector<reservation_data>& reservations_array, vector<vector<room_data>>& rooms_array) {

	// Avataan reservation_data.txt tiedosto
	ifstream reservation_data("reservation_data.txt");

	// Alustetaan muuttujat
	string line;
	int index = 0;

	// While loop joka k‰y jokaisen varauksen l‰pi
	while (getline(reservation_data, line)) {

		// Alustaa stringsream ss joka k‰ytt‰‰ line muuttujaa inputtina
		// Alustaa muuttujat kaikille huone_datan komponenteille
		stringstream ss(line);
		string reservation, floor, number, name, stay;

		// Jos rivi ei ole tyhj‰ tallenetaan sen tiedot 
		if (line.length() != 0) {

			// Getline hakee jokaisen rivin palasen eroteltuna ";" merkill‰ ja asettaa ne vastaaville muuttujille
			getline(ss, reservation, ';');
			getline(ss, floor, ';');
			getline(ss, number, ';');
			getline(ss, name, ';');
			getline(ss, stay, ';');

			// Asettaa varatun huoneen indexit varatuksi
			rooms_array[stoi(floor)][stoi(number)].reserved = true;

			// Syˆtt‰‰ varauksen tiedot reservations_arrayihin
			reservations_array.push_back({ index, stoi(reservation), stoi(floor), stoi(number), name, stoi(stay) });

			// nostaa indexi‰, jotta varauksia on helpompi hakea
			index++;
		}
	}
}

// save_reservation_data
// Tallenetaan varaukset reservation_data.txt tiedostoon
// Functio ottaa reservations_array vectorin syˆtteen‰ jotta tiedot voidaan tallentaa
void save_reservation_data(vector<reservation_data> reservations_array) {

	// Avataan ja tyhjennet‰‰n reservation_data.txt tiedosto
	ofstream reservation_data("reservation_data.txt", ofstream::out | ofstream::trunc);

	// For-loop joka k‰y l‰pi kaikki varaukset ja tallentaa ne reservation_data.txt tiedostoon
	for (int i = 0; i <= reservations_array.size() - 1; i++) {
		reservation_data << reservations_array[i].reservation << ";";
		reservation_data << reservations_array[i].room_floor << ";";
		reservation_data << reservations_array[i].room_number << ";";
		reservation_data << reservations_array[i].name << ";";
		reservation_data << reservations_array[i].stay << ";" << endl;
	}
}

// empty_reservation_data
// tyhjent‰‰ reservation_data.txt tiedoston
void empty_reservation_data() {

	// Avaa ja tyhjent‰‰ reservation_data.txt tiedoston
	ofstream reservation_data("reservation_data.txt", ofstream::out | ofstream::trunc);
}

// define_hotel_size
// Tulostaa hotel_data.txt:eest‰ hotellin koon vectorina
// Palauttaa int vectorin joka sis‰lt‰‰ kerrosten ja huoneiden m‰‰r‰n
vector<int> define_hotel_size() {

	// Avataan hotel_data.txt tiedosto
	ifstream hotel_data("hotel_data.txt");

	// Alustetaan muuttujat
	string line;
	vector<int> result;

	// While-loop joka k‰y l‰pi kaikki rivit
	while (getline(hotel_data, line)) {

		// syˆtt‰‰ rivin teksti‰ int arvona result vectoriin
		result.push_back(stoi(line));
	}

	// Palauttaa saadut arvot
	return result;
}

// create_hotel_size_random
// Luo uuden hotelli koon satunnaisesti 2-5 kerroksen ja 20-80 huoneen v‰lilt‰ (parillinen m‰‰r‰)
void create_hotel_size_random() {

	// Avaa ja tyhjent‰‰ hotel_data.txt tiedoston
	ofstream hotel_data("hotel_data.txt", ofstream::out | ofstream::trunc);

	// Luo satunnaisen numeron 2-5 v‰lilt‰ ja syˆtt‰‰ sen hotel_data.txt tiedostoon
	// Luo satunnaisen parillisen numeron 20-80 v‰lilt‰ ja syˆtt‰‰ sen hotel_data.txt tiedostoon
	hotel_data << random_num(2, 5) << endl;
	hotel_data << random_num(10, 40) * 2 << endl;
}

// create_hotel_size_input
// Ottaa 2 int inputtia joista se luo uuden hotel_data.txt tiedoston
void create_hotel_size_input(int floor, int number) {

	// Avaa ja tyhjent‰‰ hotel_data.txt tiedoston
	ofstream hotel_data("hotel_data.txt", ofstream::out | ofstream::trunc);

	// Syˆtt‰‰ arvot tiedostoon
	hotel_data << floor << endl << number << endl;
}