// Eetu Parén

// Harjoitustyö - Hotellivaraus systeemi

# include "hotel_system.h"


// Generoi random numer väliltä min - max ---------------------------------------------------------
void varaa_huone(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	system("cls");

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

		print_reservation(reservations_array[0]);

	}
	else {
		cout << "Olemme pahoilamme, mutta vapaita huoneita ei ole";
	}

	enter();

}

void tulosta_varaus(vector<vector<room_data>>& rooms_array, vector<reservation_data>& reservations_array) {

	system("cls");

	reservation_data latest_reservation = reservations_array[0];

	room_data reserved_room = rooms_array[latest_reservation.room_floor][latest_reservation.room_number];

	cout << "Viimeisin Varaus" << endl << endl;
	print_reservation(latest_reservation);
	cout << endl;
	print_room(reserved_room);

	enter();

}