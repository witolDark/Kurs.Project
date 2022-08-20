#define _CRT_SECURE_NO_WARNINGS

//include of headers
#include "Source.h"
#include "Workless.h"
#include "Work.h"
#include "Menu.h"

//Name of files
const string Workless_Base = "Workless Base";
const string Work_Base = "Work Base";

//Main
int main() {
	fullscr(); //Full screen function
	SetConsoleTitle(L"Witold"); //Set console title to Witold
	system("CLS"); // Clearscreen
	system("mode con cols=300 lines=100"); // Defining the size of console
	ConsoleCursorVisible(false, 100); // Invisible cursor
	Menu menu; // Main menu object
	while (true) { // Endless cicle
		system("CLS"); 
		ConsoleCursorVisible(false, 100); // Invisible cursor
		switch (menu.doMenu()) { 
		case 0: system("CLS");  menu.new_record(0, Workless_Base); break; //New workless
		case 1: system("CLS");  menu.edit_base(0, Workless_Base); break; // Edit workless
		case 2: system("CLS");  menu.show_base(0, Workless_Base); break; // Show workless
		case 3: system("CLS");  menu.new_record(1, Work_Base); break; // New work
		case 4: system("CLS");  menu.edit_base(1, Work_Base); break; // Edit work
		case 5: system("CLS");  menu.show_base(1, Work_Base); break; // Show work
		case 6: system("CLS");  menu.delete_DB(Workless_Base); break; // Delete workless
		case 7: system("CLS");  menu.delete_DB(Work_Base); break; // Delete work
		}
	}
}

