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

	bool free_rooms = any_free_rooms(rooms_array);

	if (free_rooms == true) {
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
					floor = input_int(1, hotel_size[0]) - 1;
					if (free_rooms_type_floor(rooms_array, type, floor) == false) {
						floor = -1;
					}

					while (floor == -1) {
						cout << "Kerroksessa ei ole vapaita tämän kokoisia huoneita. Yritä uudestaan. >> ";
						floor = input_int(1, hotel_size[0]) - 1;
						if (free_rooms_type_floor(rooms_array, type, floor) != true) {
							floor = -1;
						}
					}
				}

				room_list = collect_rooms_type_floor(rooms_array, type, floor);

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

				for (int i = 0; i <= hotel_size[0] - 1; i++) {
					room_list = collect_rooms(rooms_array, type);
				}

				index = random_from_list(room_list);

				/*
				index = find_free_room(rooms_array);

				print_room(rooms_array[index]);

				cout << endl << "Hyväksytkö huoneen. (Y/N) >> ";
				*/

			} while (yes_no() == false);

		}
		/*
		cout << "Syötä varauksen nimi. >> ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		name = input_name();

		cout << "Montako vuorokautta aiotte pysyä. >> ";
		stay = input_int(1, 999999);

		reservation = create_reservation_number(reservations_array);

		input_room(index, rooms_array, reservation, name, stay);

		print_reservation(rooms_array[index]);
		*/
	}
	else {
		cout << "Olemme pahoilamme, mutta vapaita huoneita ei ole";
	}

	enter();

}