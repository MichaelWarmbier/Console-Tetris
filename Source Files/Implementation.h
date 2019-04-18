#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#include "DataStructure.h"

// Characters
const char solid_block = 219, empty_space = 32, list_dot = 254, selection_arrow = 174;

// Exit Conditions
bool EXIT_PROGRAM = false, EXIT_MENU = false, EXIT_TETRIS = true;

// Counters
int color_change_counter = 0;
int menu_main_option_selected = 1;

// Misc
int color_value = 0;

// Main Routines - Main Menu
void MainMenuSetup() {
	ShowConsoleCursor(false);

}
void MainMenuDraw() {
	drawLogo(20, 3);
	indent(24); cout << list_dot;
	cout << " Play Tetris!";
	OutputSelectionArrow(1);
	indent(24); cout << list_dot;
	cout << " Options";
	OutputSelectionArrow(2);
	indent(24); cout << list_dot;
	cout << " How To Play";
	OutputSelectionArrow(3);
	indent(24); cout << list_dot;
	cout << " Exit Game";
	OutputSelectionArrow(4);
	
}
void MainMenuInput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			menu_main_option_selected--;
			break;
		case 's':
			menu_main_option_selected++;
			break;
		}
	}
}
void MainMenuLogic() {
	SetMenuBounds();

}
// Lesser Routines
void SetMenuBounds() {
	// Color visual logic
	color_change_counter++;
	if (color_change_counter > 20) {
		color_change_counter = 0;
		color_value++;
	}
	// Set menu_main_option_selected bounds
	if (menu_main_option_selected < 1)
		menu_main_option_selected = 1;
	if (menu_main_option_selected > 4)
		menu_main_option_selected = 4;
}
void OutputSelectionArrow(int option) {
	if (menu_main_option_selected == option)
		cout << " " << selection_arrow;
	else
		cout << "  ";
	cout << endl;
}

// Main Routines - Tetris


// Functions - Main Menu
void drawLogo(int x, int y) {
	COORD coordinates;
	coordinates.X = x; coordinates.Y = y;
	SetConsoleCursorPosition(console_handle, coordinates);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 22; j++) {
			if (logo[i][j] == getColor(color_value)) {
				SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN);
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 1)) {
				SetConsoleTextAttribute(console_handle, FOREGROUND_BLUE);
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 2)) {
				SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE);
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 3)) {
				SetConsoleTextAttribute(console_handle, FOREGROUND_RED);
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 4)) {
				SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 5)) {
				SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_RED);
				cout << solid_block;
			}
			else
				cout << empty_space;
		}
		cout << endl;
		indent(x);
	}
	cout << endl;
	SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
}
char getColor(int color_value_param) {
	switch ((color_value_param + 1) % 6) {
	case 0:
		return 't';
		break;
	case 1:
		return 'e';
		break;
	case 2:
		return 'T';
		break;
	case 3:
		return 'r';
		break;
	case 4:
		return 'i';
		break;
	case 5:
		return 's';
		break;
	default:
		return ' ';
		break;
	}
}
void ShowConsoleCursor(bool flag) {
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(console_handle, &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(console_handle, &cursorInfo);
}
void indent(int i) {
	for (int dent = 0; dent < i; dent++)
		cout << " ";
}
