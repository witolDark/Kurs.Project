#pragma once
//Source header file 
//includes
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

//defines
#define Up 72
#define Down 80
#define Enter 13
#define Esc 27
#define xpos 80
#define ypos 12

using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Get console discriptor

void GoToXY(short x, short y) { // Movenment cursor function
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size) { // Setting cursor parameters function
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void fullscr() { // Full screen function
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}


