// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

# include "hotel_system.h"


// Generoi random numer väliltä min - max ---------------------------------------------------------
void varaa_huone(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	system("cls");

	cout << "Varaa Huone" << endl << endl;

	vector<int> hotel_size = define_hotel_size();
	vector<int> index = { -1, -1 };
	vector<room_data> room_list;
	int floor = -1, number = -1, reservation, stay, type, low, high;
	string name;

	if (any_free_rooms(rooms_array) == true) {
		cout << "Haluatko valita huoneen itse. (Y/N) >> ";

		if (yes_no() == true) {

			do {
				room_list.clear();

				cout << "Otatteko yhden vai kahden hengen huoneen? (1-2) >> ";
				type = input_int(1, 2);

				if (hotel_size[0] == 1) {
					floor = 0;
				}
				else {
					cout << "Mihin kerrokseen haluat huoneen? (1-" << hotel_size[0] << ") >> ";
					floor = input_int(1, hotel_size[0]);

					if (free_rooms(rooms_array, floor, type, -1) == false) {
						floor = -1;
					}

					while (floor == -1) {
						cout << "Kerroksessa ei ole vapaita tämän kokoisia huoneita. Yritä uudestaan. >> ";
						floor = input_int(1, hotel_size[0]) - 1;
						if (free_rooms(rooms_array, floor, type, -1) == false) {
							floor = -1;
						}
					}
				}

				room_list = collect_rooms(rooms_array, floor, type, -1);

				low = output_room_number(room_list[0].floor, room_list[0].number);
				high = output_room_number(room_list[room_list.size() - 1].floor, room_list[room_list.size() - 1].number);

				cout << "Valitse huone. (" << low << "-" << high << ") >> ";

				do {
					number = input_int(low, high);

					index = index_from_number(number);

					if (rooms_array[index[0]][index[1]].reserved == true) {
						cout << "Huone on varattu. Valitse uusi huone. >> ";
						number = -1;
					}
				} while (number == -1);

				cout << endl;
				print_room(rooms_array[index[0]][index[1]]);

				cout << endl << "Hyväksytkö huoneen? (Y/N) >> ";
			} while (yes_no() == false);

		}
		else {
			do {
				room_list.clear();

				cout << "Otatteko yhden vai kahden hengen huoneen? (1-2) >> ";
				type = input_int(1, 2);
				cout << endl;

				room_list = collect_rooms(rooms_array, -1, type, -1);

				index = random_from_list(room_list);

				print_room(rooms_array[index[0]][index[1]]);

				cout << endl << "Hyväksytkö huoneen. (Y/N) >> ";

			} while (yes_no() == false);

		}

		cout << endl << "Syötä nimesi. >> ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		name = input_name();

		cout << "Montako vuorokautta aiotte pysyä. >> ";
		stay = input_int(1, 999999);
		cout << endl;

		create_reservation(reservations_array, index[0], index[1], name, stay);

		rooms_array[index[0]][index[1]].reserved = true;

		print_reservation(reservations_array[0]);

		if (rooms_array[index[0]][index[1]].coupon != 0) {
			cout << "Huoneessa on " << rooms_array[index[0]][index[1]].coupon << "% alennus." << endl;
		}

		cout << endl;

		print_bill(rooms_array[index[0]][index[1]], reservations_array[0]);

	}
	else {
		cout << "Olemme pahoilamme, mutta vapaita huoneita ei ole";
	}

	enter();

}

void tulosta_varaus(vector<vector<room_data>> rooms_array, vector<reservation_data> reservations_array) {

	system("cls");

	cout << "Viimeisin Varaus" << endl << endl;

	reservation_data latest_reservation = reservations_array[0];

	room_data reserved_room = rooms_array[latest_reservation.room_floor][latest_reservation.room_number];
	print_reservation(latest_reservation);
	cout << endl;
	print_room(reserved_room);
	cout << endl;
	print_bill(reserved_room, latest_reservation);

	enter();

}

void etsi_varaus(vector<vector<room_data>> rooms_array, vector<reservation_data> reservations_array) {

	vector<reservation_data> reservation_finds;
	reservation_data reservation;
	room_data room;
	string name;
	int reservation_number;

	system("cls");

	cout << "Hae Varaus" << endl << endl;

	cout << "Haetko varaajan nimellä vai varaus numerolla : " << endl;
	cout << "[1] : Varaajan nimi" << endl;
	cout << "[2] : Varausnumero" << endl;
	cout << "Haku tyyppi. (1-2) >> ";

	if (input_int(1, 2) == 1) {
		cout << "Syötä haettava nimi. >> ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		name = input_name();
		reservation_finds = find_by_name(reservations_array, name);
	}
	else {

		cout << "Syötä haettava varaus. >> ";
		reservation_number = input_int(10000, 99999);
		reservation_finds = find_by_reservation(reservations_array, reservation_number);
	}

	if (reservation_finds.size() == 0) {
		cout << "Varauksia ei löytynyt.";
	}
	else {
		for (int i = 0; i < reservation_finds.size(); i++) {
			reservation = reservation_finds[i];

			room = rooms_array[reservation.room_floor][reservation.room_number];

			cout << "-----------------------------------------------------------" << endl;
			cout << "Varaus \t\t\t: " << i + 1 << endl << endl;
			print_reservation(reservation);
			cout << endl;
			print_room(room);
			cout << endl;
			print_bill(room, reservation);

		}

	}

	enter();

}

void muokkaa_varaus(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	vector<reservation_data> reservation_finds;
	reservation_data reservation;
	room_data room;
	string name;
	int reservation_number, input;

	system("cls");

	cout << "Muokkaa Varaus" << endl << endl;

	cout << "Haetko varaajan nimellä vai varaus numerolla : " << endl;
	cout << "[1] : Varaajan nimi" << endl;
	cout << "[2] : Varausnumero" << endl;
	cout << "Haku tyyppi. (1-2) >> ";

	if (input_int(1, 2) == 1) {
		cout << "Syötä haettava nimi. >> ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		name = input_name();
		reservation_finds = find_by_name(reservations_array, name);
	}
	else {

		cout << "Syötä haettava varaus. >> ";
		reservation_number = input_int(10000, 99999);
		reservation_finds = find_by_reservation(reservations_array, reservation_number);
	}

	if (reservation_finds.size() == 0) {
		cout << "Varauksia ei löytynyt.";
	}
	else {
		for (int i = 0; i < reservation_finds.size(); i++) {
			reservation = reservation_finds[i];

			room = rooms_array[reservation.room_floor][reservation.room_number];

			cout << "-----------------------------------------------------------" << endl;
			cout << "Varaus \t\t\t: " << i + 1 << endl << endl;
			print_reservation(reservation);
			cout << endl;
			print_room(room);
			cout << endl;
			print_bill(room, reservation);

		}

		if (reservation_finds.size() > 1) {

			cout << endl << "Varaus jota haluat muokata. (1-" << reservation_finds.size() << ") : >> ";
			input = input_int(1, reservation_finds.size()) - 1;
			cout << endl;

			reservation = reservation_finds[input];

			room = rooms_array[reservation.room_floor][reservation.room_number];

			print_reservation(reservation);
			cout << endl;
			print_room(room);
			cout << endl;
			print_bill(room, reservation);
		}
		else {

			reservation = reservation_finds[0];

			room = rooms_array[reservation.room_floor][reservation.room_number];

		}

		do {
			cout << endl << "Mitä elementtiä haluat muokata : " << endl;
			cout << "[1] : Peru Varaus" << endl;
			cout << "[2] : Huone" << endl;
			cout << "[3] : Nimi" << endl;
			cout << "[4] : Kesto" << endl;
			cout << "[0] : Takaisin" << endl;
			cout << "Suoritettava tehtävä >> ";
			input = input_int(0, 4);

			switch (input) {
			case 1: input = peru_varaus(rooms_array, reservations_array, reservation); break;
			case 2: cout << "2"; break;
			case 3: muokkaa_nimi(reservations_array, reservation); break;
			case 4: cout << "4"; break;
			case 0: cout << "0"; break;
			default: cout << "Virhetilanne";
			}

			if (input > 1) {
				cout << "Haluatko muokata vielä jotain? (Y/N) >> ";
				if (yes_no() == false) {
					input = -1;
				}
			}
		} while (input > 1);

	}


	enter();

}

void tulosta_kaikki_varaukset(vector<vector<room_data>> rooms_array, vector<reservation_data> reservations_array) {

	system("cls");
	
	cout << "Kaikki Varaukset" << endl << endl;

	reservation_data reservation;
	room_data room;

	for (int i = 0; i < reservations_array.size(); i++) {
		reservation = reservations_array[i];

		room = rooms_array[reservation.room_floor][reservation.room_number];

		cout << "-----------------------------------------------------------" << endl;
		cout << "Varaus \t\t\t: " << i + 1 << endl << endl;
		print_reservation(reservation);
		cout << endl;
		print_room(room);
		cout << endl;
		print_bill(room, reservation);
	}

	enter();

}

int peru_varaus(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array, reservation_data reservation) {

	int success = 999999;
	cout << endl << "Oletko varma, että haluat perua varauksen? (Y/N) >>";

	if (yes_no() == true) {

		rooms_array[reservation.room_floor][reservation.room_number].reserved = false;

		reservations_array.erase(reservations_array.begin() + reservation.index);

		cout << "Varaus Peruutettu.";

		success = 0;
	}

	return success;
}

void muokkaa_nimi(vector<reservation_data>& reservations_array, reservation_data reservation) {

	string name;

	do {

		cout << "Syötä uusi nimi. >> ";

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		name = input_name();

		cout << "Onko tämä oikein : " << name;

	} while (yes_no() == false);

	reservations_array[reservation.index].name = name;

}