#pragma once

class Menu // Main menu class
{
private:
	const string menu[8]{ "New  workless", "Edit workless", "Show workless",
		" New  work", " Edit work", " Show/Occupy work", "DELETE WORKLESS", "DELETE WORK"}; // Main menu buttons
	const string edit[2]{ "Edit record","Delete record" }; // Edit base buttons
	const string confirm[2]{ "OK", "CANCEL" }; // Confirm buttons
public:
	int doMenu(); // Creating menu
	int new_record(bool what, string file_name); // New record 
	int edit_base(bool what, string file_name); // Edit record
	int show_base(bool what, string file_name); // Show Base
	int delete_DB(string file_name); // Delete Base
	int reserve_Work(vector <Work>& work, int index); // Reserving record method

	int del_rec_workless(vector<Past_Work>& vec, string file_name, int index); // Delete workless record method
	int edt_rec_workless(vector<Past_Work>& vec, string file_name, int index); // Edit workless record method
	int del_rec_work(vector<Work>& vec, string file_name, int index); // Delete vacancy record method
	int edt_rec_work(vector<Work>& vec, string file_name, int index); // Edit vacancy record method
};

int Menu::doMenu() {
	int active_menu = 0;
	char key;
	while (true) {
		if (active_menu > 7) active_menu = 0;
		if (active_menu < 0) active_menu = 7;
		int x = xpos, y = ypos;
		GoToXY(x, y);

		for (int i = 0; i < size(menu); i++)
		{
			if (i <= 2) {
				if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				else SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}
			else if (i > 2 && i <= 5) {
				if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				else SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
			}
			else if (i > 5 && i <= 7) {
				if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
				else SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
			}

			GoToXY(x, y++);
			cout << menu[i] << endl;
			if (i == 2 || i == 5) {
				cout << endl;
				GoToXY(x, y++);
			}
		}

		key = _getch();
		if (key == -32) key = _getch();
		switch (key) {
		case Up: active_menu--;
			break;
		case Down: active_menu++;
			break;
		case Esc: exit(0);
		case Enter: switch (active_menu) {
		case 0: return 0; break;
		case 1: return 1; break;
		case 2: return 2; break;
		case 3: return 3; break;
		case 4: return 4; break;
		case 5: return 5; break;
		case 6: return 6; break;
		case 7: return 7; break;
		}
		}
	}
}

int Menu::new_record(bool what, string file_name) {
	int active_menu = 0;
	char key;
	ofstream file(file_name, fstream::app);
	if (file.is_open()) {
		another_one_record:
			Past_Work work{};
			Work workl{};
			if (!what) {
				work.create_worker();
				workl.~Work();
			}
			else {
				workl.create_work();
				work.~Past_Work();
			}
			system("CLS");
			while (true) {
				if (active_menu > 1) active_menu = 0;
				if (active_menu < 0) active_menu = 1;
				int confirm_x = xpos, confirm_y = ypos;

				for (int i = 0; i < size(confirm); i++) {
					GoToXY(confirm_x, confirm_y);
					if (i == active_menu) SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					else     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
					if (i == 0) GoToXY(confirm_x + 2, confirm_y++);
					else GoToXY(confirm_x, confirm_y++);
					cout << confirm[i] << endl;
				}

				key = _getch();
				if (key == -32) key = _getch();
				switch (key) {
				case Up: active_menu--;
					break;
				case Down: active_menu++;
					break;
				case Esc: file.close();  return 0;
				case Enter: switch (active_menu) {
				case 0:
					if (!what) work.insert_DB(file);
					else workl.insert_DB(file);
					file.close();
					return 0;
				case 1:
					system("cls"); goto another_one_record;
				}
				}
			}
		file.close();
	}
	return 0;
}

int Menu::del_rec_workless(vector<Past_Work>& vec, string file_name, int index) {
	ofstream file(file_name);
	if (file.is_open()) {
		auto iter = vec.begin();
		vec.erase(iter + index);
		for (int i = 0; i < vec.size(); i++) { vec[i].insert_DB(file); }
		file.close();
	}
	return 0;
}

int Menu::edt_rec_workless(vector<Past_Work>& vec, string file_name, int index) {
	ofstream file(file_name);
	if (file.is_open()) {
		Past_Work temp{};
		system("CLS");
		cin >> temp;
		vec[index] = temp;
		for (int i = 0; i < vec.size(); i++) { vec[i].insert_DB(file); }
		file.close();
	}
	return 0;
}

int Menu::del_rec_work(vector<Work>& vec, string file_name, int index) {
	ofstream file(file_name);
	if (file.is_open()) {
		auto iter = vec.begin();
		vec.erase(iter + index);
		for (int i = 0; i < vec.size(); i++) { vec[i].insert_DB(file); }
		file.close();
	}
	return 0;
}

int Menu::edt_rec_work(vector<Work>& vec, string file_name, int index) {
	ofstream file(file_name);
	if (file.is_open()) {
		Work temp{};
		system("CLS");
		cin >> temp;
		vec[index] = temp;
		for (int i = 0; i < vec.size(); i++) { vec[i].insert_DB(file); }
		file.close();
	}
	return 0;
}

int Menu::edit_base(bool what ,string file_name) {
	vector<Past_Work> humans;
	vector<Work> work;
	ifstream file(file_name);
	if (file.is_open()) {
		while (!file.eof()) {
			if (!what) {
				Past_Work temp{};
				humans.push_back(temp.extract_DB(file));
				temp.~Past_Work();
			}
			else {
				Work temp{};
				work.push_back(temp.extract_DB(file));
				temp.~Work();
			}
		}
		int temp_size;
		if (humans.size() > work.size()) temp_size = humans.size();
		else temp_size = work.size();
	 	const int sizev = temp_size;
		//////////////////////////////
		int active_record = 0;
		char key;
		while (true) {
			int x = xpos - 75, y = ypos - 5;
			if (active_record < 0) active_record = sizev - 1;
			if (active_record > sizev - 1) active_record = 0;
			GoToXY(x, y);
			for (int i = 0; i < sizev; i++) {
				if (!what) {
					if (i == active_record)     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					else     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

					if (i != sizev) {
						GoToXY(x, y++);
						humans[i].show_own_data();
					}
				}
				else {
					if (i == active_record)     SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					else     SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);

					if (i != sizev - 1) {
						GoToXY(x, y++);
						work[i].show_data();
					}
				}
			}
			key = _getch();
			if (key == -32) key = _getch();
			switch (key) {
			case Up: active_record--;
				break;
			case Down: active_record++;
				break;
			case Esc:
				humans.clear();
				work.clear();
				file.close(); 
				return 0;
			case Enter:
				system("CLS");
				GoToXY(xpos - 75, ypos - 5);
				if (!what) {
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					cout << humans[active_record];
				}
				else {
					SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					work[active_record].show_data();
				}
				int active_index = active_record;
				active_record = 0;
				while (true) {
					if (active_record < 0) active_record = size(edit) - 1;
					if (active_record > size(edit) - 1) active_record = 0;
					x = xpos; y = ypos + 1;
					GoToXY(x, y);
					for (int i = 0; i < size(edit); i++) {
						if (i == active_record)     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						else     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

						GoToXY(x, ++y);
						cout << edit[i] << endl;
					}
					key = _getch();
					if (key == -32) key = _getch();
					switch (key) {
					case Up: active_record--;
						break;
					case Down: active_record++;
						break;
					case Esc: 
						humans.clear();
						work.clear();
						file.close();
						return 0;
					case Enter: switch (active_record) {
					case 0: file.close(); 
						if (!what) edt_rec_workless(humans, file_name, active_index);
						else edt_rec_work(work, file_name, active_index);
						return 0;
					case 1: file.close();
						if (!what) del_rec_workless(humans, file_name, active_index);
						else del_rec_work(work, file_name, active_index);
						
						return 0;
					}
					}
				}
				system("CLS");
			}
		}
	}
	humans.clear();
	file.close();
	return 0;
} 

int Menu::show_base(bool what, string file_name) {
	system("CLS");
	vector<Past_Work> workers1;
	vector<Work> workers2;
again:
	ifstream file(file_name);
	if (file.is_open()) {
		while (!file.eof()) {
			if (!what) {
				Past_Work work{};
				workers1.push_back(work.extract_DB(file));
				work.~Past_Work();
			}
			else {
				Work work{};
				workers2.push_back(work.extract_DB(file));
				work.~Work();
			}
		}
		int temp_size;
		if (workers1.size() > workers2.size()) temp_size = workers1.size();
		else temp_size = workers2.size();
		const int sizev = temp_size;
		//////////////////////
		int active_record = 0;
		char key;
		while (true) {
			system("CLS");
			int x = xpos - 75, y = ypos - 5;
			GoToXY(x, y);
			if (!what) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "Workless Data Base" << endl;
				GoToXY(x, ++y);
				cout << "#" << '\t' << "Code" << '\t' << "	NAME SURNAME" << '\t' << "AGE" << '\t' << "Pass code" << '\t' << "Phone number" << endl;
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "Vacancy Data Base" << endl;
				GoToXY(x, ++y);
				cout << "#" << '\t' << "Organisation" << '\t' << "	Position" << '\t' << "Requirments" << '\t' << '\t' << '\t' << "Salary $" << '\t' << "Avalaible" << '\t' << "Holder" << endl;
				SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
			}
			int count = 0;
			////////////////////////////////////
			if (active_record < 0) active_record = sizev - 2;
			if (active_record > sizev - 2) active_record = 0;
			for (int i = 0; i < sizev; i++) {
				if (!what) {
					if (i == active_record)     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					else     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

					if (i != sizev - 1) {
						GoToXY(x, ++y);
						cout << ++count << '\t';
						workers1[i].show_own_data();
					}
				}
				else {
					if (i == active_record)     SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					else     SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);

					if (i != sizev - 1) {
							GoToXY(x, ++y);
							cout << ++count << '\t';
							workers2[i].show_data();
					}
				}
			}
			key = _getch();
			if (key == -32) key = _getch();
			switch (key) {
			case Up: active_record--;
				break;
			case Down: active_record++;
				break;
			case Esc: file.close(); 
				workers1.clear(); 
				workers1.clear(); 
				return 0; 
			case Enter:
			here:
				if (!what) {
					cout << workers1[active_record];
					if (_getch() == Esc) {
						break;
						system("CLS");
						show_base(what, file_name);
					}
				}
				else {
					if (workers2[active_record].avalaible == "0") reserve_Work(workers2, active_record);
					break;
					system("CLS");
					show_base(what, file_name);
				}
				if (_getch() != Esc) goto here;
				else { system("CLS"); goto again; }
			}
			/////////////////////////
		}
	}
	return 0;
}

int Menu::delete_DB(string file_name) {
	ofstream file(file_name);
	if (file.is_open()) file.close();
	GoToXY(xpos, ypos);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "Deleted" << endl;
	for (int i = 3; i > 0; i--) {
		GoToXY(xpos, ypos);
		cout << "Deleted" << endl;
		GoToXY(xpos, ypos + 1);
		cout << "Return at " << i << "...";
		Sleep(1000);
		system("CLS");
	}
	return 0;
}

int Menu::reserve_Work(vector <Work>& work, int index) {
	ifstream file("Workless Base");
	if (file.is_open()) {
		vector <Past_Work> temp;
		while (!file.eof()) {
			Past_Work temp_worker{};
			temp.push_back(temp_worker.extract_DB(file));
			temp_worker.~Past_Work();
		}
		int sizev = temp.size();
		int active_record = 0;
		char key;
		while (true) {
			if (active_record < 0) active_record = sizev - 1;
			if (active_record > sizev - 1) active_record = 0;
			system("CLS");
			int x = xpos - 75, y = ypos - 5;
			GoToXY(x, y);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "#" << '\t' << "Code" << '\t' << "	NAME SURNAME" << '\t' << "AGE" << '\t' << "Pass code" << '\t' << "Phone number" << endl;
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			int count = 0;
			for (int i = 0; i < sizev; i++) {
				if (i == active_record)     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				else     SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

				if (i != sizev - 1) {
					GoToXY(x, ++y);
					cout << ++count << '\t';
					temp[i].show_own_data();
				}
			}
			key = _getch();
			if (key == -32) key = _getch();
			switch (key) {
			case Up: active_record--;
				break;
			case Down: active_record++;
				break;
			case Esc: temp.clear(); return 0;
			case Enter:
				work[index].avalaible_virtual = false;
				work[index].holder = temp[active_record].name + " " + temp[active_record].surname;
				ofstream file("Work Base");
				for (int i = 0; i < work.size() - 1; i++) {
					if (work[i].organisation != "")
						work[i].insert_DB(file);
				}
				file.close();
				temp.clear(); 
				return 0;
			}
		}
	}
	return 0;
}