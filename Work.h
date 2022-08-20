#pragma once

class Work { // Vacancy class
private:
	string organisation, position, require, salary, avalaible, holder; // Vacancy variables
	bool avalaible_virtual; 
public:
	friend istream& operator >> (istream& in, Work& work); // Friend input operator overload

	void insert_DB(ofstream& file) { // Insert data in file
		file << organisation << '\t' << position << '\t' << require << '\t' << salary <<  '\t' << avalaible_virtual << '\t' << holder << endl;
	}
	Work extract_DB(ifstream& file) { // Extract data from file
		getline(file, organisation, '\t');
		getline(file, position, '\t');
		getline(file, require, '\t');
		getline(file, salary, '\t');
		getline(file, avalaible, '\t');
		getline(file, holder, '\n');
		return *this;
	}

	void create_work() { cin >> *this; } // Entering data
	void show_data(); // Showing data
	
	Work() { // Constructor
		organisation = "", position = "", require = "", salary = "";
		avalaible_virtual = true;
		holder = "FREE";
	}

	friend class Menu; // Defining Menu class as friendly

	~Work() {} // Destructor
};

void Work::show_data() {
	cout << organisation << '\t' << '\t' << '\t' << position << '\t' << '\t' << require << '\t' << salary + "$" << '\t' << '\t';
	if (avalaible == "1") cout << "Yes" << '\t' << '\t';
	else cout << "No" << '\t' << '\t';
	cout << holder << endl;
}

istream& operator >> (istream& in, Work& work) {
	int x = xpos, y = 5;
	GoToXY(x, y);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "Vacancy" << endl;
	GoToXY(x, ++y);
	cout << "Name of organisation: "; getline(in, work.organisation);
	GoToXY(x, ++y);
	cout << "Position: "; getline(in, work.position);
	GoToXY(x, ++y);
	cout << "Requirments: "; getline(in, work.require);
	GoToXY(x, ++y);
	cout << "Salary: "; getline(in, work.salary);
	work.avalaible_virtual = false;
	return in;;
}


