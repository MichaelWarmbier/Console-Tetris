#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#include "DataStructure.h"

// Characters
const char solid_block = 219, empty_space = 32;

// Exit Conditions
bool EXIT_PROGRAM = false, EXIT_MENU = false, EXIT_TETRIS = true;

// Main Routines - Main Menu
void MainMenuSetup() {
	drawLogo(20, 3);
}
void MainMenuDraw() {


}
void MainMenuInput() {


}
void MainMenuLogic() {

}

// Main Routines - Tetris


// Functions - Main Menu
void drawLogo(int x, int y) {
	COORD coordinates;
	coordinates.X = x; coordinates.Y = y;
	SetConsoleCursorPosition(console_handle, coordinates);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 22; j++) {
			if (logo[i][j] == 't' && j < 5) {
				SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN);
				cout << solid_block;
			}
			else if (logo[i][j] == 'e') {
				SetConsoleTextAttribute(console_handle, FOREGROUND_BLUE);
				cout << solid_block;
			}
			else if (logo[i][j] == 't') {
				SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE);
				cout << solid_block;
			}
			else if (logo[i][j] == 'r') {
				SetConsoleTextAttribute(console_handle, FOREGROUND_RED);
				cout << solid_block;
			}
			else if (logo[i][j] == 'i') {
				SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_BLUE);
				cout << solid_block;
			}
			else if (logo[i][j] == 's') {
				SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_RED);
				cout << solid_block;
			}
			else
				cout << empty_space;
		}
		cout << endl;
		for (int indent = 0; indent < x; indent++)
			cout << " ";
	}
	
}
