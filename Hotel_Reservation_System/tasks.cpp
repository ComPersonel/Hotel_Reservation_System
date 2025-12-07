// Eetu ParÈn

// Harjoitustyˆ - Hotellivaraus systeemi
// 
// Sis‰lt‰‰ satunnaisia pieni‰ itsen‰isi‰ komentoja jotka suorittavat yhden ja vain ja ainoastaan yhden teht‰v‰n
//

// hotel_system.h sis‰lt‰‰ kaikki namespacet, included, structit ja functiot
# include "hotel_system.h"

// random_num
// Luo satunnaisen arvon annettujen arvojen v‰lilt‰ ja palauttaa sen
int random_num(int min, int max) {
	// Luo satunnaisen arvon k‰ytt‰en minimi ja maximi arvoja rajoina
	return rand() % (max + 1 - min) + min;
}

// input_int
// Ottaa k‰ytt‰j‰lt‰ int inputin kahden annetun arvon v‰lilt‰
int input_int(int min, int max) {

	// Alustetaan muuttujat
	int input;

	// Jos cin ei saa hyv‰ksytt‰v‰‰ arvoa, syˆte on liian pieni tai iso ignoraa se ja pyyd‰ uutta arvoa
	while (!(cin >> input) || input < min || input > max) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Huono syˆte, yrit‰ uudelleen. >> ";
	}
	
	// Palauta toimiva arvo
	return input;
}

// yes_no
// Ottaa k‰ytt‰j‰lt‰ syˆtteen‰ Y (kyll‰) tai N (ei) ja palauttaa bool arvon
bool yes_no() {

	// Alustetaan muuttujat
	char input;

	// Jos cin ei saa hyv‰ksytt‰v‰‰ arvoa tai se ei ole Y/N ignoraa se ja pyyd‰ uutta arvoa
	while (!(cin >> input) || (input != 'n' && input != 'N' && input != 'y' && input != 'Y')) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Huono syˆte, yrit‰ uudelleen. >> ";
	}

	// Jos syˆte on Y palauta True, jos ei palauta False
	if (input == 'y' || input == 'Y') {
		return true;
	}
	else {
		return false;
	}
}

// enter
// Pyyt‰‰ k‰ytt‰j‰‰ painamaan enter jatkaakseen
// K‰ytet‰‰n v‰lipisteen‰, jotta k‰ytt‰j‰ voi lukea t‰ytetyt tiedot rauhassa
void enter() {
	// Tulosta viest
	cout << endl << "Paina enter jatkaaksesi.";

	// Poista leftover syˆtteet ja odota, ett‰ cin saa arvon
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

// input_name
// Ottaa k‰ytt‰j‰lt‰ string syˆtteen‰ nimen, jonka se palauttaa
string input_name() {

	// Alustetaan muuttujat
	string name = "<Undefined User>";

	// Jos getline ei saa hyv‰ksytt‰v‰‰ arvoa, se on tyhj‰ tai sis‰lt‰‰ vain "tyhji‰ merkkej‰" ignoraa se ja pyyd‰ uutta arvoa
	while (!getline(cin, name) || name.empty() || all_of(name.begin(), name.end(), [](unsigned char c) { return isspace(c); })) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Huono syˆte, yrit‰ uudelleen. >> ";
	}

	// Poistaa nimest‰ ";" merkit koska n‰m‰ haittaavat tallentamis prosessia
	name.erase(remove(name.begin(), name.end(), ';'), name.end());

	// Lis‰‰ bufferiin yhden v‰lilyˆnnin (korjaa hyvin pienen ja obscure bugin)
	if (!cin.putback('\n')) {
		if (!cin) {
			cin.clear();
		}
	}

	// Palauttaa saadun nimen
	return name;
}

// type_desc
// Tulostaa huoneen tyyppi‰ vastaavan tulosteen
string type_desc(room_data room) {
	// Jos huoneen tyyppi vastaa joko single tai double tulosta viestit, muuten tulosta <Room Type Undefined>
	if (room.type == "single") return "yhden hengen";
	if (room.type == "double") return "kahden hengen";
	if (room.type != "single" && room.type != "double") return "<Room Type Undefined>";
}

// type_tier
// Tulostaa huoneen tasoa vastaavan tulosteen
string tier_desc(room_data room) {
	// Jos huoneen tyyppi vastaa joko basic, premium, deluxe tulosta viestit, muuten tulosta <Room Tier Undefined>
	if (room.tier == "basic") return "perus";
	if (room.tier == "premium") return "preemium";
	if (room.tier == "deluxe") return "luksus";
	if (room.tier != "basic" && room.tier != "premium" && room.tier != "deluxe") return "<Room Tier Undefined>";
}

// print_room
// Tulostaa huoneen numeron, tyypin ja tason k‰ytt‰en annetun huoneen dataa
void print_room(room_data room) {
	// Tulostaa viestit j‰rjestyksess‰ k‰ytt‰en aliohjelmia
	cout << left << setw(25) << "Huone numero" << ": " << output_room_number(room.floor, room.number) << endl;
	cout << left << setw(25) << "Huone malli" << ": " << type_desc(room) << endl;
	cout << left << setw(25) << "Huone taso" << ": " << tier_desc(room) << endl;
}

// print_reservation
// Tulostaa varauksen numeron, varaajan nimen ja varauksen keston
void print_reservation(reservation_data reservation) {
	// Tulostaa viestit j‰rjestyksess‰ k‰ytt‰en varauksen informaatiota
	cout << left << setw(25) << "Varaus numero" << ": " << reservation.reservation << endl;
	cout << left << setw(25) << "Varaajan nimi" << ": " << reservation.name << endl;
	cout << left << setw(25) << "Varauksen kesto" << ": " << reservation.stay << " p‰iv‰‰" << endl;
}

// any_free_rooms
// Tarkistaa onko hotellissa yht‰k‰‰n vapaata huonetta
bool any_free_rooms(vector<vector<room_data>> rooms_array) {

	// Otetaan hotellin koko talteen
	vector<int> hotel_size = define_hotel_size();

	// Alustetaan muuttujat, default on false
	bool return_value = false;

	// Nestattu For-loop joka k‰ jokaisen huoneen l‰pi
	// ja vaihtaa palautus arvon true tilaan jos se kohtaa yhdenk‰‰n huoneen joka ei ole varattu
	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			if (rooms_array[i][j].reserved == false) {
				return_value = true;
			}
		}
	}
	// Palauttaa palautus arvon
	return return_value;
}

// free_rooms
// Hakee vapaita huoneita tietylt‰ kerrokselta, tyypilt‰ tai tasolta
// Jos syˆtteiss‰ on -1 se syˆte ignorataan
bool free_rooms(vector<vector<room_data>> rooms_array, int floor, int type, int tier) {

	// Alustetaan muuttujat joissa on default arvot
	string room_type = "single", room_tier = "basic";
	vector<int> hotel_size = define_hotel_size();
	vector<room_data> return_array;

	// Jos huone tyyppi on 2 etsit‰‰n kahden hengen huoneita
	if (type == 2) {
		room_type = "double";
	}

	// Huoneen taso on 2 etsit‰‰n premium huoneita
	// Huoneen taso on 3 etsit‰‰n luksus huoneita
	if (tier == 2) {
		room_tier = "premium";
	}
	else if (tier == 3) {
		room_tier = "deluxe";
	}

	// Nestattu for-loop joka k‰y jokaisen huoneen l‰pi ja vertaa sen kerrosta, tyyppi‰ ja tasoa
	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			if ((rooms_array[i][j].type == room_type || type == -1) && (rooms_array[i][j].tier == room_tier || tier == -1) && (rooms_array[i][j].floor == floor - 1 || floor == -1)) {
				return true;
			}
		}
	}
	return false;
}

// output_room_number
// Palauttaa huoneen numeron sen indexeist‰
int output_room_number(int floor, int number) {
	return ((floor + 1) * 100) + number;
}

// index_from_number
// Palauttaa vectorin jossa on huoneen kerros ja numero
vector<int> index_from_number(int number) {

	int floor = number / 100 - 1;
	int index = number % 100 - 1;

	return { floor, index };
}

// create_reservation
// Luo varauksen k‰ytt‰en annettua dataa
void create_reservation(vector<reservation_data>& reservations_array, int floor, int number, string name, int stay) {

	// Luodaan uusi reservation_data joka insertataan varauksiin
	reservation_data new_reservation;

	// Syˆtet‰‰n kaikki data new_reservation structiin
	new_reservation.reservation = create_reservation_number(reservations_array);
	new_reservation.room_floor = floor;
	new_reservation.room_number = number;
	new_reservation.name = name;
	new_reservation.stay = stay;

	// Insertataan new_reservation reservations_arrayihin ensimm‰iseen indexiin
	reservations_array.insert(reservations_array.begin(),new_reservation);
}

// create_reservation_number
// Luo uniikin varaus numeron
// Ottaa syˆtteen‰ reservations_array jotta se voi verrata olemassa olevia numeroita
int create_reservation_number(vector<reservation_data> reservations_array) {

	// Alustetaan muuttujat
	int number = -1;
	int length = reservations_array.size();

	// Do-While loop joka luo satunnaisen luvun 10000-99999 v‰lilt‰ ja tarkistaa onko sit‰ k‰ytetty
	// Jos arvo lˆytyy vaihdetaan arvottu arvo -1 jotta looppi toistuu
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

	// palauttaa arvon
	return number;
}

// collect_rooms
// Ker‰‰ tietynlaisia huoneita listaan
// Jos syˆtteiss‰ on -1 se syˆte ignorataan
vector<room_data> collect_rooms(vector<vector<room_data>> rooms_array, int floor, int type, int tier) {

	// Alustetaan muuttujat
	string room_type = "single";
	string room_tier = "basic";
	vector<int> hotel_size = define_hotel_size();
	vector<room_data> return_array;

	// Jos huone tyyppi on 2 etsit‰‰n kahden hengen huoneita
	if (type == 2) {
		room_type = "double";
	}

	// Huoneen taso on 2 etsit‰‰n premium huoneita
	// Huoneen taso on 3 etsit‰‰n luksus huoneita
	if (tier == 2) {
		room_tier = "premium";
	}
	else if (tier == 3) {
		room_tier = "deluxe";
	}

	// Nestattu For-loop joka k‰y kaikki huoneet l‰pi ja ker‰‰ ne return_arrayihin jos ne vastaa syˆtteit‰
	for (int i = 0; i < hotel_size[0]; i++) {
		for (int j = 0; j < hotel_size[1]; j++) {
			if ((rooms_array[i][j].type == room_type || type == -1) && (rooms_array[i][j].tier == room_tier || tier == -1) && (rooms_array[i][j].floor == floor - 1 || floor == -1)) {
				return_array.push_back(rooms_array[i][j]);
			}
		}
	}

	// Palauttaa listan
	return return_array;
}

// return_from_list
// Palauttaa vectorin satunnaisen vapaan huoneen indexeist‰
vector<int> random_from_list(vector<room_data> room_list) {

	// Alustetaan muuttujat
	int random = -1;

	// Do-while loop joka hakee satunnaisen huoneen
	// Ja tarkastaa onko se varattu, jos on aseta random muuttuja -1 jotta loop voidaan toistaa
	do {
		random = random_num(0, room_list.size() - 1);
		if (room_list[random].reserved == true) {
			random = -1;
		}
	} while (random == -1);

	// Palauttaa huoneen koordinaatit vectorina
	return { room_list[random].floor, room_list[random].number - 1};
}

// print_bill
// Tulostaa varauksen laskun sen huoneesta riippune
void print_bill(room_data room, reservation_data reservation) {

	// ALustetaan muuttujat
	double base_cost = 100.0, cost_multiplier = 1.0;

	// Jos huone on double asetetaan sen pohja hinnaksi 150Ä
	if (room.type == "double") {
		base_cost = 150.0;
	}

	// Jos huone on premium nosta huoneen hinta modifieria 1.5x
	// Jos huone on deluxe nosta huoneen hinta modifieria 2.0x
	if (room.tier == "premium") {
		cost_multiplier = 1.5;
	}
	else if (room.tier == "deluxe") {
		cost_multiplier = 2.0;
	}

	// Tulostetaan huoneen pohja hinta, sen lis‰ hinta, kesto ja lˆytyv‰ alennus
	cout << left << setw(25) << "Huoneen pohja hinta" << ": " << base_cost << " Euroa" << endl;
	cout << left << setw(25) << "Huoneen lis‰ hinta" << ": " << base_cost * (cost_multiplier - 1.0) << " Euroa" << endl;
	cout << left << setw(25) << "Varauksen kesto" << ": " << reservation.stay << " P‰iv‰‰" << endl;
	cout << left << setw(25) << "Huone alennus" << ": " << room.coupon << "%" << endl;

	cout << left << setw(25) << "Kokonaishinta" << ": " << print_cost(room, reservation) << " Euroa" << endl;;
}

// print_cost
// Palauttaa huoneen kokonais hinnan
double print_cost(room_data room, reservation_data reservation) {

	// Alustetaan muuttujat
	double base_cost = 100.0, cost_multiplier = 1.0;

	// Jos huone on double asetetaan sen pohja hinnaksi 150Ä
	if (room.type == "double") {
		base_cost = 150.0;
	}

	// Jos huone on premium nosta huoneen hinta modifieria 1.5x
	// Jos huone on deluxe nosta huoneen hinta modifieria 2.0x
	if (room.tier == "premium") {
		cost_multiplier = 1.5;
	}
	else if (room.tier == "deluxe") {
		cost_multiplier = 2.0;
	}

	// Palautetaan laskettu kokonais hinta
	// Totaali hinta = perus hinta * hinta kerroin * p‰iv‰t - alennus m‰‰r‰
	return (base_cost * cost_multiplier * reservation.stay) - (base_cost * cost_multiplier * reservation.stay / 100 * room.coupon);
}

// find_by_name
// Hakee varauksia nimell‰ reservations_array listasta
vector<reservation_data> find_by_name(vector<reservation_data> reservations_array, string name) {

	// Alustetaan muuttujat
	vector<reservation_data> reservations_list;

	// K‰yd‰‰n jokainen varaus l‰pi ja lis‰t‰‰n t‰m‰‰v‰t varaukset uuteen listaan
	for (int i = 0; i < reservations_array.size(); i++) {
		if (reservations_array[i].name == name) {
			reservations_list.push_back(reservations_array[i]);
		}
	}
	// Palautetaan uusi lista
	return reservations_list;
}

// find_by_reservation
// Hakee varauksia numerolla reservations_array listasta
vector<reservation_data> find_by_reservation(vector<reservation_data> reservations_array, int reservation) {

	// Alustetaan muuttujat
	vector<reservation_data> reservations_list;

	// K‰yd‰‰n jokainen varaus l‰pi ja lis‰t‰‰n t‰m‰‰v‰t varaukset uuteen listaan
	for (int i = 0; i < reservations_array.size(); i++) {
		if (reservations_array[i].reservation == reservation) {
			reservations_list.push_back(reservations_array[i]);
		}
	}
	// Palautetaan uusi lista
	return reservations_list;
}

// clear_reservations
// Poistaa olemassa olevat varaukset
void clear_reservations(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	// while-loop joka k‰y niinkauan kunnes reservations_array on tyhj‰
	while (reservations_array.empty() == false) {

		// Asettaa huoneen ei varatuksi
		// Poistaa huoneen arraysta
		rooms_array[reservations_array[0].room_floor][reservations_array[0].room_number].reserved = false;
		reservations_array.erase(reservations_array.begin());

		// tyhjent‰‰ reservation_data.txt tiedoston
		empty_reservation_data();
	}
}