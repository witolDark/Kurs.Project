#pragma once

class Workless { // Basic workless class
protected:
	string code, name, surname, age, phone_number, pass_data, education, instituion, qualification, address, childs; // Basic variables
	bool child;
public:
	friend istream& operator >> (istream& in, Workless& work); // Friend input operator overload
	friend ostream& operator << (ostream& out, Workless& work); // Friend output operator overload

	virtual void insert_DB(ofstream& file) { // Insert data in file 
		file << code << '\t' << name << " " << surname << '\t' << age << '\t' << phone_number << '\t' <<
			pass_data << '\t' << education << '\t' << instituion << '\t' << qualification << '\t' << address << '\t' << child << '\t';
	} 
	Workless extract_DB(ifstream& file) { // Extract data from file
		getline(file, code, '\t');
		getline(file, name, ' ');
		getline(file, surname, '\t');
		getline(file, age, '\t');
		getline(file, phone_number, '\t');
		getline(file, pass_data, '\t');
		getline(file, education, '\t');
		getline(file, instituion, '\t');
		getline(file, qualification, '\t');
		getline(file, address, '\t');
		getline(file, childs, '\t');
		return *this;
	}

	virtual void create_worker() { cin >> *this; } // Entering data
	virtual void show_worker() { cout << *this; } // Showing data
	virtual void show_own_data(); // Show short data

	Workless() { // Constructor
		code = "", name = ""; surname = ""; phone_number = ""; age = ""; pass_data = "", education = "", instituion = "",
			qualification = "", address = "", child = NULL;
	}

	friend class Menu; // Defining Menu class as friendly

	~Workless() {} // Destructor
};

istream& operator >> (istream& in, Workless& work) { 
	int x = xpos, y = 5;
	GoToXY(x, y);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Personal data" << endl;
	GoToXY(x, ++y);
	cout << "ID(13): "; in >> work.code;
	GoToXY(x, ++y);
	cout << "Name Surname: "; in >> work.name >> work.surname;
	GoToXY(x, ++y);
	cout << "Age: "; in >> work.age;
	GoToXY(x, ++y);
	cout << "Phone number: "; cout << "+"; in >> work.phone_number;
	work.phone_number = "+" + work.phone_number;
	GoToXY(x, ++y);
	cout << "Passport#: "; in >> work.pass_data;
	cin.ignore();
	GoToXY(x, ++y);
	cout << "Education: "; getline(in, work.education);
	GoToXY(x, ++y);
	cout << "Education instituion: "; getline(in, work.instituion);
	GoToXY(x, ++y);
	cout << "Qualification (years): "; getline(in, work.qualification);
	GoToXY(x, ++y);
	cout << "Live address: "; getline(in, work.address);
restart:
	GoToXY(x, ++y);
	cout << "Children (y/n)" << endl;
	if (_getch() == 'y') work.child = true;
	else if (_getch() == 'n') work.child = false;
	else goto restart;
	return in;
}

ostream& operator << (ostream& out, Workless& work) {
	int x = xpos - 75, y = ypos - 5;
	system("CLS");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	GoToXY(x, y);
	out << "Full data" << endl;
	GoToXY(x, ++y);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	out << "Code: " << work.code << endl;
	GoToXY(x, ++y);
	out << "Name Surname: " << work.name << " " << work.surname << endl;
	GoToXY(x, ++y);
	out << "Age: " << work.age << endl;
	GoToXY(x, ++y);
	out << "Phone number: " << work.phone_number << endl;
	GoToXY(x, ++y);
	out << "Passport code: " << work.pass_data << endl;
	GoToXY(x, ++y);
	out << "Education: " << work.education << endl;
	GoToXY(x, ++y);
	out << "Education institution: " << work.instituion << endl;
	GoToXY(x, ++y);
	out << "Qualification (year): " << work.qualification << endl;
	GoToXY(x, ++y);
	out << "Home address: " << work.address << endl;
	GoToXY(x, ++y);
	out << "Childrens (yes/no): ";
	if (work.childs == "1") cout << "yes" << endl;
	else cout << "No" << endl;
	return out;
}

void Workless::show_own_data() {
	cout << code << '\t' << name << " " << surname << '\t' << age << '\t' << pass_data << '\t' << '\t' << phone_number << endl;
}

class Past_Work : public Workless { // Child class
protected:
	string organisation, position, experience, date_employment, date_release, release_reason; // Class variables
public:
	friend istream& operator >> (istream& in, Past_Work& work); // Overloaded input operator
	friend ostream& operator << (ostream& out, Past_Work& work); // Overloaded output operator

	virtual void insert_DB(ofstream& file) { // Insert data in file
		Workless::insert_DB(file);
		file << organisation << '\t' << position << '\t' << experience << '\t' << date_employment 
			<< '\t' << date_release << '\t' << release_reason << endl;
	}
	Past_Work extract_DB(ifstream& file) { // Extract data from file
		Workless::extract_DB(file);
		getline(file, organisation, '\t');
		getline(file, position, '\t');
		getline(file, experience, '\t');
		getline(file, date_employment, '\t');
		getline(file, date_release, '\t');
		getline(file, release_reason, '\n');
		return *this;
	}

	virtual void create_worker() { cin >> *this; } // Entering data
	virtual void show_worker() { cout << *this; } // Showing data

	Past_Work() : Workless() { // Constructor
		organisation = "", position = "", experience = ""
			, date_employment = "", date_release = "", release_reason = "";
	}

	friend class Menu; // Defining Menu class as friendly
	friend class Work; // Defining Work class as friendly

	~Past_Work() {} // Destructor
};

istream& operator >> (istream& in, Past_Work& work) {
	int x = xpos, y = 5;
	GoToXY(x, y);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "Personal data" << endl;
	GoToXY(x, ++y);
	cout << "ID(13): "; in >> work.code;
	GoToXY(x, ++y);
	cout << "Name Surname: "; in >> work.name >> work.surname;
	GoToXY(x, ++y);
	cout << "Age: "; in >> work.age;
	GoToXY(x, ++y);
	cout << "Phone number: "; cout << "+"; in >> work.phone_number;
	work.phone_number = "+" + work.phone_number;
	GoToXY(x, ++y);
	cout << "Passport#: "; in >> work.pass_data;
	cin.ignore();
	GoToXY(x, ++y);
	cout << "Education: "; getline(in, work.education);
	GoToXY(x, ++y);
	cout << "Education instituion: "; getline(in, work.instituion);
	GoToXY(x, ++y);
	cout << "Qualification (years): "; getline(in, work.qualification);
	GoToXY(x, ++y);
	cout << "Live address: "; getline(in, work.address);
restart:
	GoToXY(x, ++y);
	cout << "Children (y/n)" << endl;
	if (_getch() == 'y') work.child = true;
	else if (_getch() == 'n') work.child = false;
	else goto restart;
	system("CLS");
	x = xpos, y = 5;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	GoToXY(x, y);
	cout << "Past work data" << endl;
	GoToXY(x, ++y);
	cout << "Organisation: "; getline(in, work.organisation);
	GoToXY(x, ++y);
	cout << "Position: "; getline(in, work.position);
	GoToXY(x, ++y);
	cout << "Experience: "; getline(in, work.experience);
	GoToXY(x, ++y);
	cout << "Date of employement (dd.mm.yyyy): "; getline(in, work.date_employment);
	GoToXY(x, ++y);
	cout << "Date of release (dd.mm.yyyy): "; getline(in, work.date_release);
	GoToXY(x, ++y);
	cout << "Release reason: "; getline(in, work.release_reason);
	system("CLS");
	return in;
}

ostream& operator << (ostream& out, Past_Work& work) {
	int x = xpos - 75, y = ypos - 5;
	system("CLS");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	GoToXY(x, y);
	out << "Full data" << endl;
	GoToXY(x, ++y);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	out << "Code: " << work.code << endl;
	GoToXY(x, ++y);
	out << "Name Surname: " << work.name << " " << work.surname << endl;
	GoToXY(x, ++y);
	out << "Age: " << work.age << endl;
	GoToXY(x, ++y);
	out << "Phone number: " << work.phone_number << endl;
	GoToXY(x, ++y);
	out << "Passport code: " << work.pass_data << endl;
	GoToXY(x, ++y);
	out << "Education: " << work.education << endl;
	GoToXY(x, ++y);
	out << "Education institution: " << work.instituion << endl;
	GoToXY(x, ++y);
	out << "Qualification (year): " << work.qualification << endl;
	GoToXY(x, ++y);
	out << "Home address: " << work.address << endl;
	GoToXY(x, ++y);
	out << "Childrens (yes/no): ";
	if (work.childs == "1") cout << "yes" << endl;
	else cout << "No" << endl;
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	GoToXY(x, ++y);
	out << "Past Work data" << endl;
	GoToXY(x, ++y);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
	out << "Organisation: " << work.organisation << endl;
	GoToXY(x, ++y);
	out << "Position: " << work.position << endl;
	GoToXY(x, ++y);
	out << "Experience: " << work.experience << endl;
	GoToXY(x, ++y);
	out << "Date of employment: " << work.date_employment << endl;
	GoToXY(x, ++y);
	out << "Date of release: " << work.date_release << endl;
	GoToXY(x, ++y);
	out << "Release reason: " << work.release_reason << endl;
	return out;
}