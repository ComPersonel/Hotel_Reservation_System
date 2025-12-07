// Eetu ParÈn

// Harjoitustyˆ - Hotellivaraus systeemi - commands.cpp - toivottavasti 5p toteutus
// 
// Sis‰lt‰‰ p‰‰ komennot joihin k‰ytt‰j‰ p‰‰see k‰siksi
// nimetty suomeksi, koska ne on suoraan sidottu k‰ytt‰j‰n komentoihin
//

// hotel_system.h sis‰lt‰‰ kaikki namespacet, included, structit ja functiot
# include "hotel_system.h"

// varaa_huone
// Seuraa huoneen varaus prosessia. Hakee huoneen, sis‰llytt‰‰ k‰ytt‰j‰n infon ja lataa ne ylˆs vectoreihin
void varaa_huone(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	// Tyhjenn‰ terminaali n‰timp‰‰ tulostusta varten
	system("cls");

	// Tulostaa Toiminnon nimen
	cout << "Varaa Huone" << endl << endl;

	// Alustetaan muuttujat
	vector<int> hotel_size = define_hotel_size();
	vector<int> index = { -1, -1 };
	vector<room_data> room_list;
	int floor = -1, number = -1, stay, type, low, high;
	string name;

	// Tarkista onko hotellissa yht‰‰n tilaa
	// Jos ei pahoittele k‰ytt‰j‰‰ ja pakota poistumaan
	// Jos on jatka prosessia
	if (any_free_rooms(rooms_array) == true) {

		// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako he varata huoneen itse vai ei
		cout << "Haluatko valita huoneen itse. (Y/N) >> ";

		// Jos kyll‰ jatka prosessia siten, ett‰ k‰ytt‰j‰ itse valitsee huoneen
		if (yes_no() == true) {

			// Do-while loop joka
			do {
				// Tyhjenn‰ huone lista jos toiminto ajetaan uudestaan
				room_list.clear();

				// Kysyt‰‰n ottaako k‰ytt‰j‰ yhden vai kahden hengen huoneen
				// Tallenetaan huoneen tyyppi type muuttujaan input_intill‰
				cout << "Otatteko yhden vai kahden hengen huoneen? (1-2) >> ";
				type = input_int(1, 2);

				// Jos hotellissa on enemm‰n kuin 1 kerros kysyt‰‰n kerroksesta
				// Muuten asetetaan toivottu kerros automaattisesti
				if (hotel_size[0] == 1) {
					floor = 0;
				}
				else {
					// K‰ytt‰j‰lt‰ kysyt‰‰n mihin kerrokseen h‰n haluaa
					// Tallenetaan kerros floor muuttujaan input_intill‰
					cout << "Mihin kerrokseen haluat huoneen? (1-" << hotel_size[0] << ") >> ";
					floor = input_int(1, hotel_size[0]);

					// Jos kerroksessa ei ole yht‰‰n vapaata huonetta muuta kerros -1
					if (free_rooms(rooms_array, floor, type, -1) == false) {
						floor = -1;
					}

					// Jos floor = -1 niin siirryy while looppiin joka pyyt‰‰ uutta kerrosta
					// Jos kerros on yh‰ varattu pysy loopissa
					while (floor == -1) {
						cout << "Kerroksessa ei ole vapaita t‰m‰n kokoisia huoneita. Yrit‰ uudestaan. >> ";
						floor = input_int(1, hotel_size[0]) - 1;
						if (free_rooms(rooms_array, floor, type, -1) == false) {
							floor = -1;
						}
					}
				}

				// Ker‰‰ huoneita oikealta kerrokselta ja tyypilt‰
				room_list = collect_rooms(rooms_array, floor, type, -1);

				// Asetetaan low ja high arvoihin listan ensimm‰inen ja viimeinen esine
				// Tulostetaan viesti joka pyyt‰‰ huone numeroa
				low = output_room_number(room_list[0].floor, room_list[0].number);
				high = output_room_number(room_list[room_list.size() - 1].floor, room_list[room_list.size() - 1].number);
				cout << "Valitse huone. (" << low << "-" << high << ") >> ";

				// do-while loop joka kiert‰‰ kunnes k‰ytt‰j‰ lˆyt‰‰ vapaan huoneen
				do {
					// K‰ytt‰j‰ inputtaa huoneen numeron joka muunnetaan indexiksi
					number = input_int(low, high);
					index = index_from_number(number);

					// If lauseke joka tarkistaa onko huone vapaa vai varattu
					// Jos huone on varattu aseta number -1 jotta voimme pysy‰ loopissa
					if (rooms_array[index[0]][index[1]].reserved == true) {
						cout << "Huone on varattu. Valitse uusi huone. >> ";
						number = -1;
					}
				} while (number == -1);

				// Tulostetaan huoneen informaato
				cout << endl;
				print_room(rooms_array[index[0]][index[1]]);

				// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako h‰n k‰ytt‰‰ t‰t‰ huonetta
				cout << endl << "Hyv‰ksytkˆ huoneen? (Y/N) >> ";
			} while (yes_no() == false);
		} // Jos k‰ytt‰j‰ ei halua valita huonetta itse valitaan se auttomaattisesti
		else {
			// Do-while loop joka kiert‰‰ kunnes k‰ytt‰j‰ hyv‰ksyy huoneen
			do {
				// Tyhjenn‰ huone lista jos toiminto ajetaan uudestaan
				room_list.clear();

				// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako h‰n 1 vai 2 hengen huoneen
				cout << "Otatteko yhden vai kahden hengen huoneen? (1-2) >> ";
				type = input_int(1, 2);
				cout << endl;

				// Ker‰t‰‰n halutun tyypisi‰ huoneita
				// Haetaan satunnainen index listasta
				room_list = collect_rooms(rooms_array, -1, type, -1);
				index = random_from_list(room_list);

				// Tulostetaan huoneen informaatio
				print_room(rooms_array[index[0]][index[1]]);

				// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako h‰n k‰ytt‰‰ t‰t‰ huonetta
				cout << endl << "Hyv‰ksytkˆ huoneen. (Y/N) >> ";
			} while (yes_no() == false);
		}
		// Kun k‰ytt‰j‰ on hyv‰ksynyt huoneen pyydet‰‰n nime‰ jolle varaus tehd‰‰n
		// T‰t‰ varten t‰ytyy clearaa ja ignoraa cin ensin
		cout << endl << "Syˆt‰ nimesi. >> ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		name = input_name();

		// Kysyt‰‰n kuinka monta vuorokautta k‰ytt‰j‰ aikoo pysy‰
		// Varaus voi kest‰‰ 1-999999 vuorokautta
		cout << "Montako vuorokautta aiotte pysy‰. >> ";
		stay = input_int(1, 999999);
		cout << endl;

		// Luodaan varaus k‰ytt‰j‰lle annetun nimen, keston ja indexin mukaan
		// Varataan indexin huone
		create_reservation(reservations_array, index[0], index[1], name, stay);
		rooms_array[index[0]][index[1]].reserved = true;

		// Tulostetaan varaus informaatio
		print_reservation(reservations_array[0]);

		// Jos huoneessa on alennus ilmoitetaan siit‰
		if (rooms_array[index[0]][index[1]].coupon != 0) {
			cout << "Huoneessa on " << rooms_array[index[0]][index[1]].coupon << "% alennus." << endl;
		}

		// Tulostetaan Lasku huoneesta
		cout << endl;
		print_bill(rooms_array[index[0]][index[1]], reservations_array[0]);

	}
	else {
		// Jos huoneita ei ole 
		cout << "Olemme pahoilamme, mutta vapaita huoneita ei ole";
	}

	// Paina enter jatkaaksesi
	enter();
}

// tulosta_varaus
// Tulostaa viimeisinmm‰n varauksen
void tulosta_varaus(vector<vector<room_data>> rooms_array, vector<reservation_data> reservations_array) {

	// Tyhjenn‰ terminaali n‰timp‰‰ tulostusta varten
	system("cls");

	// Tulostaa Toiminnon nimen
	cout << "Viimeisin Varaus" << endl << endl;

	// Luo viimeisin varaus muuttuja helpompaa k‰sittely‰ varten
	// Luo varatun huoneen muuttujan helpompaa k‰sittely‰ varten
	reservation_data latest_reservation = reservations_array[0];
	room_data reserved_room = rooms_array[latest_reservation.room_floor][latest_reservation.room_number];

	// Tulosta varauksen, huoneen ja laskun
	print_reservation(latest_reservation);
	cout << endl;
	print_room(reserved_room);
	cout << endl;
	print_bill(reserved_room, latest_reservation);

	// Paina enter jatkaaksesi
	enter();
}

// etsi_varaus
// Haetaan varaus joko nimell‰ tai numerolla ja tulostaa ne
void etsi_varaus(vector<vector<room_data>> rooms_array, vector<reservation_data> reservations_array) {

	// Alustetaan muuttujat
	vector<reservation_data> reservation_finds;
	reservation_data reservation;
	room_data room;
	string name;
	int reservation_number;

	// Tyhjenn‰ terminaali n‰timp‰‰ tulostusta varten
	system("cls");

	// Tulostaa Toiminnon nimen
	cout << "Hae Varaus" << endl << endl;

	// Tulostetaan kysymys
	cout << "Haetko varaajan nimell‰ vai varaus numerolla : " << endl;
	cout << "[1] : Varaajan nimi" << endl;
	cout << "[2] : Varausnumero" << endl;
	cout << "Haku tyyppi. (1-2) >> ";

	// Jos k‰ytt‰j‰ hakee nimell‰ haetaan annettu nimi ja lis‰t‰‰n lˆydetyt varaukset reservation_finds vectoriin
	if (input_int(1, 2) == 1) {
		cout << "Syˆt‰ haettava nimi. >> ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		name = input_name();
		reservation_finds = find_by_name(reservations_array, name);
	} 
	else { // muuten k‰ytt‰j‰ syˆtt‰‰ varaus numeron ja lis‰t‰‰n vastaavat varaukset reservation_finds vectoriin
		cout << "Syˆt‰ haettava varaus. >> ";
		reservation_number = input_int(10000, 99999);
		reservation_finds = find_by_reservation(reservations_array, reservation_number);
	}

	// Jos varauksia ei lˆytynyt tulostetaan viesti ja jatketaan
	if (reservation_finds.size() == 0) {
		cout << "Varauksia ei lˆytynyt.";
	}
	else { // Muuten tulostetaan lˆydetyt varaukset k‰ytt‰en for-looppia
		for (int i = 0; i < reservation_finds.size(); i++) {
			// Lˆydetty huone laitetaan reservation muuttujaan helppouden vuoksi
			// Varaukseen sidottu huone tallenetaan room muuttujaan
			reservation = reservation_finds[i];
			room = rooms_array[reservation.room_floor][reservation.room_number];

			// Tulostetaan kaikki varaukset
			cout << "-----------------------------------------------------------" << endl;
			cout << setw(25) << "Varaus" << ": " << i + 1 << endl << endl;
			print_reservation(reservation);
			cout << endl;
			print_room(room);
			cout << endl;
			print_bill(room, reservation);
		}
	}
	 // Paina enter jatkaaksesi
	enter();
}

// muokkaa_varaus
// Sis‰lt‰‰ varauksen perumisen, huoneen vaihdon, varaajan nimen muutoksen ja varauksen keston vaihdon
void muokkaa_varaus(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	// Alustetaan muuttujat
	vector<reservation_data> reservation_finds;
	reservation_data reservation;
	room_data room;
	string name;
	int reservation_number, input;

	// Tyhjenn‰ terminaali n‰timp‰‰ tulostusta varten
	system("cls");

	// Tulostaa Toiminnon nimen
	cout << "Muokkaa Varaus" << endl << endl;

	// Tulostetaan kysymys
	cout << "Haetko varaajan nimell‰ vai varaus numerolla : " << endl;
	cout << "[1] : Varaajan nimi" << endl;
	cout << "[2] : Varausnumero" << endl;
	cout << "Haku tyyppi. (1-2) >> ";

	// Jos k‰ytt‰j‰ hakee nimell‰ haetaan annettu nimi ja lis‰t‰‰n lˆydetyt varaukset reservation_finds vectoriin
	if (input_int(1, 2) == 1) {
		cout << "Syˆt‰ haettava nimi. >> ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		name = input_name();
		reservation_finds = find_by_name(reservations_array, name);
	}
	else { // muuten k‰ytt‰j‰ syˆtt‰‰ varaus numeron ja lis‰t‰‰n vastaavat varaukset reservation_finds vectoriin
		cout << "Syˆt‰ haettava varaus. >> ";
		reservation_number = input_int(10000, 99999);
		reservation_finds = find_by_reservation(reservations_array, reservation_number);
	}

	// Jos varauksia ei lˆytynyt tulostetaan viesti ja jatketaan
	if (reservation_finds.size() == 0) {
		cout << "Varauksia ei lˆytynyt.";
	}
	else { // Muuten tulostetaan lˆydetyt varaukset k‰ytt‰en for-looppia
		for (int i = 0; i < reservation_finds.size(); i++) {

			// Lˆydetty huone laitetaan reservation muuttujaan helppouden vuoksi
			// Varaukseen sidottu huone tallenetaan room muuttujaan
			reservation = reservation_finds[i];
			room = rooms_array[reservation.room_floor][reservation.room_number];

			// Tulostetaan kaikki varaukset
			cout << "-----------------------------------------------------------" << endl;
			cout << setw(25) << "Varaus" << ": " << i + 1 << endl << endl;
			print_reservation(reservation);
			cout << endl;
			print_room(room);
			cout << endl;
			print_bill(room, reservation);
		}

		// Jos varauksia on enemm‰n kuin yksi kysyt‰‰n mit‰ varausta halutaan muokata
		if (reservation_finds.size() > 1) {

			// esitet‰‰n kysymys ja k‰tt‰j‰ syˆtt‰‰n varauksen numeron joka haetaan
			// varauksen numerosta v‰hennet‰‰n yksi jotta se muuttuu indexiksi
			cout << endl << "Varaus jota haluat muokata. (1-" << reservation_finds.size() << ") : >> ";
			input = input_int(1, reservation_finds.size()) - 1;
			cout << endl;

			// Valittu varaus asetetaan reservation muuttujaan helpompaa k‰sittely‰ varten
			// Sidottu huone asetetaan room muuttujaan helpompaa k‰sittely‰ varten
			reservation = reservation_finds[input];
			room = rooms_array[reservation.room_floor][reservation.room_number];

			// Tulostetaan huone
			print_reservation(reservation);
			cout << endl;
			print_room(room);
			cout << endl;
			print_bill(room, reservation);
		}
		else { // Jos huoneita on yksi valitaan se
			reservation = reservation_finds[0];
			room = rooms_array[reservation.room_floor][reservation.room_number];
		}

		do { // Kysyt‰‰n mit‰ elementti‰ k‰ytt‰j‰ haluaa muokata
			cout << endl << "Mit‰ elementti‰ haluat muokata : " << endl;
			cout << "[1] : Peru Varaus" << endl;
			cout << "[2] : Huone" << endl;
			cout << "[3] : Nimi" << endl;
			cout << "[4] : Kesto" << endl;
			cout << "[0] : Poistu" << endl;
			cout << "Suoritettava teht‰v‰ >> ";

			// Otetaan int input
			input = input_int(0, 4);

			// Switch-case joka k‰y l‰pi vaihtoehdot
			// varauksen peruminen vaihtaa inputin 0 jotta se poistuu ohjelmasta, koska poistettua varausta ei voi muokata en‰‰n
			switch (input) {
			case 1: input = peru_varaus(rooms_array, reservations_array, reservation); break;
			case 2: muokkaa_huone(rooms_array, reservations_array, reservation); break;
			case 3: muokkaa_nimi(reservations_array, reservation); break;
			case 4: muokkaa_kesto(reservations_array, reservation); break;
			case 0: cout << "Poistutaan muokkaamisesta"; break;
			default: cout << "Virhetilanne";
			}

			// Jos input ei ole 0 kysyt‰‰n haluaako k‰ytt‰j‰ muokata jotain muuta osaa viel‰
			if (input > 1) {
				cout << "Haluatko muokata viel‰ jotain? (Y/N) >> ";
				if (yes_no() == false) {
					input = -1;
				}
			}
			// Poistu loopista jos syˆte on v‰hemm‰n kuin 1
		} while (input > 1);
	}
	// Paina enter jatkaaksesi
	enter();
}

// tulosta_kaikki_varaukset
// Tulostaa kaikkia varaukset
void tulosta_kaikki_varaukset(vector<vector<room_data>> rooms_array, vector<reservation_data> reservations_array) {

	// Alustetaan muuttujat
	reservation_data reservation;
	room_data room;

	// Tyhjenn‰ terminaali n‰timp‰‰ tulostusta varten
	system("cls");

	// Tulostaa Toiminnon nimen
	cout << "Kaikki Varaukset" << endl << endl;

	// For-loop joka k‰ky kaikki varaukset l‰pi
	for (int i = 0; i < reservations_array.size(); i++) {
		// Valittu varaus asetetaan reservation muuttujaan helpompaa k‰sittely‰ varten
		// Sidottu huone asetetaan room muuttujaan helpompaa k‰sittely‰ varten
		reservation = reservations_array[i];
		room = rooms_array[reservation.room_floor][reservation.room_number];

		// Tulostetaan varaus
		cout << "-----------------------------------------------------------" << endl;
		cout << setw(25) << "Varaus" << ": " << i + 1 << endl << endl;
		print_reservation(reservation);
		cout << endl;
		print_room(room);
		cout << endl;
		print_bill(room, reservation);
	}
	// Paina enter jatkaaksesi
	enter();
}

// preu_varaus
// Poistaa annetun varauksen
int peru_varaus(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array, reservation_data reservation) {

	// Alustetaan muuttujat, success on vain iso arvo joka voisi olla jopa 1
	int success = 999999;

	// Kysyt‰‰n haluaako k‰ytt‰ varmasti perua varauksen
	// Jos kyll‰ niin poistetaan huone
	cout << endl << "Oletko varma, ett‰ haluat perua varauksen? (Y/N) >>";
	if (yes_no() == true) {

		// Varaus poistetaan reservations_arraysta ja varattu huone vapautuu
		rooms_array[reservation.room_floor][reservation.room_number].reserved = false;
		reservations_array.erase(reservations_array.begin() + reservation.index);
		
		// Tulostetaan viesti ja asetetaan success 0 jotta voimme poistua loopista
		cout << "Varaus Peruutettu.";
		success = 0;
	}
	// Palautetaan success muuttuja
	return success;
}

// muokkaa_nimi
// Muokkaa varauksen nimi
void muokkaa_nimi(vector<reservation_data>& reservations_array, reservation_data reservation) {

	// Alustetaan muuttujat
	string name;

	// do-while loop joka pyˆrii kunnes k‰ytt‰j‰ hyv‰ksyy uuden nimen
	do {

		// Pyydet‰‰n uutta nime‰ varaukselle
		// T‰t‰ varten t‰ytyy clearaa ja ignoraa cin ensin
		cout << "Syˆt‰ uusi nimi. >> ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		name = input_name();

		// Kysyt‰‰n onko syˆte oikein
		cout << "Onko t‰m‰ oikein : " << name << " (Y/N) >> ";

		// Poistu Loopista kun k‰ytt‰j‰ on tyytyv‰inen nimeen
	} while (yes_no() == false);

	// P‰ivitet‰‰n nimi
	reservations_array[reservation.index].name = name;
}

// muokkaa_kesto
// Muokkaa varauksen kestoa
void muokkaa_kesto(vector<reservation_data>& reservations_array, reservation_data reservation) {

	// Alustetaan muuttujat
	int stay;

	// Do-while loop joka loppuu kun k‰ytt‰j‰ hyv‰ksyy uuden ajan
	do {

		// Pyydet‰‰n uutta kestoa varaukselle
		cout << "Syˆt‰ uusi keston pituus. >> ";
		stay = input_int(1, 999999);

		// Kysyt‰‰n onko aika oikein
		cout << "Onko t‰m‰ oikein : " << stay << " p‰iv‰‰ (Y/N) >> ";

		// Loop loppuu kun k‰ytt‰j‰ on tyytyv‰inen
	} while (yes_no() == false);

	// Tallenetaan uusi aika
	reservations_array[reservation.index].stay = stay;
}

// muokkaa_huone
// Muokataan huoneen 
void muokkaa_huone(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array, reservation_data reservation) {

	// Alustetaan muuttujat
	vector<int> hotel_size = define_hotel_size();
	vector<int> index = { -1, -1 };
	vector<room_data> room_list;
	int floor = -1, number = -1, type, low, high;
	string name;

	// Tarkista onko hotellissa yht‰‰n tilaa
	// Jos ei pahoittele k‰ytt‰j‰‰ ja pakota poistumaan
	// Jos on jatka prosessia
	if (any_free_rooms(rooms_array) == true) {

		// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako he varata huoneen itse vai ei
		cout << "Haluatko valita huoneen itse. (Y/N) >> ";

		// Jos kyll‰ jatka prosessia siten, ett‰ k‰ytt‰j‰ itse valitsee huoneen
		if (yes_no() == true) {

			// Do-while loop joka
			do {
				// Tyhjenn‰ huone lista jos toiminto ajetaan uudestaan
				room_list.clear();

				// Kysyt‰‰n ottaako k‰ytt‰j‰ yhden vai kahden hengen huoneen
				// Tallenetaan huoneen tyyppi type muuttujaan input_intill‰
				cout << "Otatteko yhden vai kahden hengen huoneen? (1-2) >> ";
				type = input_int(1, 2);

				// Jos hotellissa on enemm‰n kuin 1 kerros kysyt‰‰n kerroksesta
				// Muuten asetetaan toivottu kerros automaattisesti
				if (hotel_size[0] == 1) {
					floor = 0;
				}
				else {
					// K‰ytt‰j‰lt‰ kysyt‰‰n mihin kerrokseen h‰n haluaa
					// Tallenetaan kerros floor muuttujaan input_intill‰
					cout << "Mihin kerrokseen haluat huoneen? (1-" << hotel_size[0] << ") >> ";
					floor = input_int(1, hotel_size[0]);

					// Jos kerroksessa ei ole yht‰‰n vapaata huonetta muuta kerros -1
					if (free_rooms(rooms_array, floor, type, -1) == false) {
						floor = -1;
					}

					// Jos floor = -1 niin siirryy while looppiin joka pyyt‰‰ uutta kerrosta
					// Jos kerros on yh‰ varattu pysy loopissa
					while (floor == -1) {
						cout << "Kerroksessa ei ole vapaita t‰m‰n kokoisia huoneita. Yrit‰ uudestaan. >> ";
						floor = input_int(1, hotel_size[0]) - 1;
						if (free_rooms(rooms_array, floor, type, -1) == false) {
							floor = -1;
						}
					}
				}

				// Ker‰‰ huoneita oikealta kerrokselta ja tyypilt‰
				room_list = collect_rooms(rooms_array, floor, type, -1);

				// Asetetaan low ja high arvoihin listan ensimm‰inen ja viimeinen esine
				// Tulostetaan viesti joka pyyt‰‰ huone numeroa
				low = output_room_number(room_list[0].floor, room_list[0].number);
				high = output_room_number(room_list[room_list.size() - 1].floor, room_list[room_list.size() - 1].number);
				cout << "Valitse huone. (" << low << "-" << high << ") >> ";

				// do-while loop joka kiert‰‰ kunnes k‰ytt‰j‰ lˆyt‰‰ vapaan huoneen
				do {
					// K‰ytt‰j‰ inputtaa huoneen numeron joka muunnetaan indexiksi
					number = input_int(low, high);
					index = index_from_number(number);

					// If lauseke joka tarkistaa onko huone vapaa vai varattu
					// Jos huone on varattu aseta number -1 jotta voimme pysy‰ loopissa
					if (rooms_array[index[0]][index[1]].reserved == true) {
						cout << "Huone on varattu. Valitse uusi huone. >> ";
						number = -1;
					}
				} while (number == -1);

				// Tulostetaan huoneen informaato
				cout << endl;
				print_room(rooms_array[index[0]][index[1]]);

				// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako h‰n k‰ytt‰‰ t‰t‰ huonetta
				cout << endl << "Hyv‰ksytkˆ huoneen? (Y/N) >> ";
			} while (yes_no() == false);
		} // Jos k‰ytt‰j‰ ei halua valita huonetta itse valitaan se auttomaattisesti
		else {
			// Do-while loop joka kiert‰‰ kunnes k‰ytt‰j‰ hyv‰ksyy huoneen
			do {
				// Tyhjenn‰ huone lista jos toiminto ajetaan uudestaan
				room_list.clear();

				// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako h‰n 1 vai 2 hengen huoneen
				cout << "Otatteko yhden vai kahden hengen huoneen? (1-2) >> ";
				type = input_int(1, 2);
				cout << endl;

				// Ker‰t‰‰n halutun tyypisi‰ huoneita
				// Haetaan satunnainen index listasta
				room_list = collect_rooms(rooms_array, -1, type, -1);
				index = random_from_list(room_list);

				// Tulostetaan huoneen informaatio
				print_room(rooms_array[index[0]][index[1]]);

				// Kysyt‰‰n k‰ytt‰j‰lt‰ haluaako h‰n k‰ytt‰‰ t‰t‰ huonetta
				cout << endl << "Hyv‰ksytkˆ huoneen. (Y/N) >> ";
			} while (yes_no() == false);
		}

		// Uusi huone varataan ja vanha vapautuu
		rooms_array[index[0]][index[1]].reserved = true;
		rooms_array[reservation.room_floor][reservation.room_number].reserved = false;

		// Varauksen huone indexit ladataan
		reservations_array[reservation.index].room_floor = index[0];
		reservations_array[reservation.index].room_number = index[1];

		// Tulostetaan huoneen data
		print_reservation(reservations_array[reservation.index]);
		cout << endl;
		print_room(rooms_array[index[0]][index[1]]);
		cout << endl;
		print_bill(rooms_array[index[0]][index[1]], reservations_array[reservation.index]);
	}
	else {
		// Jos huoneita ei ole 
		cout << "Olemme pahoilamme, mutta vapaita huoneita ei ole";
	}

	// Paina enter jatkaaksesi
	enter();
}

// uusi_hotelli
// Luo uuden hotellin tarvittaessa
void uusi_hotelli() {

	// Tyhjenn‰ terminaali n‰timp‰‰ tulostusta varten
	system("cls");

	// Tulostaa Toiminnon nimen
	cout << "Luo uusi hotelli! TƒMƒ POISTAA KAIKKI TIEDOT" << endl;

	// Alustaa muuttujat
	vector<int> hotel_plan = { -1, -1,};

	// Kysyy k‰ytt‰j‰lt‰ haluaako h‰n itse luoda hotellin uudet arvot
	cout << "Haluatko itse luoda uuden hotelli datan? (Y/N) >> ";
	if (yes_no() == true) {

		// Jos kyll‰ Kysyt‰‰n montako kerrosta uudessa hotellissa on
		// Testi tarkoituksista hotellissa voi olla max 10 kerrosta
		cout << "Montako kerrosta uudessa hotelissa on? (1-10) >> ";
		hotel_plan[0] = input_int(1, 10);

		// Kysyt‰‰n k‰ytt‰j‰lt‰ parillista m‰‰r‰‰ huoneita per kerros v‰lilt‰ 20-80
		cout << "Montako huonetta uudessa hotelissa on? syˆt‰ parillinen m‰‰r‰ (20-80) >> ";

		// Jos cin ei saa hyv‰ksytt‰v‰‰ arvoa, syˆte on liian pieni, iso tai ei parillinen ignoraa se ja pyyd‰ uutta arvoa
		while (!(cin >> hotel_plan[1]) || hotel_plan[1] < 20 || hotel_plan[1] > 80 || hotel_plan[1] % 2 != 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Huono syˆte, yrit‰ uudelleen. >> ";
		}

		// Luo uusi hotelli t‰ll‰ pohjalla
		create_hotel_size_input(hotel_plan[0], hotel_plan[1]);
	}
	else { // Muuten luo satunnainen hotelli koko
		create_hotel_size_random();
	}

	// Alustetaan hotellin uusi koko ja sit‰ mukaa uusi huone data
	vector<int> hotel = define_hotel_size();
	vector<vector<room_data>> new_hotel(hotel[0], vector<room_data>(hotel[1]));

	// Generoidaan uusi huone data k‰ytt‰en uutta kokoa
	// Tallenetaan uudet tiedot
	generate_room_data(new_hotel);
	save_room_data(new_hotel);

	// Luodaan uusi tyhj‰ varaus tiedosto
	empty_reservation_data();

	// Varoitetaan k‰ytt‰j‰‰ sulkeutuvasta ohjelmasta ja lopetetaan ohjelma
	cout << "Ohjelma sulkeutuu t‰m‰n j‰lkeen";
	enter();
	exit(0);
}