#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>
#include <chrono>
using namespace std;
using namespace chrono;
HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#include "DataStructure.h"
COORD coordinates;

// Global Variables
const unsigned char solid_block = 219, empty_space = 32, list_dot = 254, selection_arrow = 174, trans_block = 176;
bool EXIT_PROGRAM = false, EXIT_MENU = false, EXIT_TETRIS = true;
double FPS = 1.0 / 90.0;
double timer = 0, dt = 0;

// Menu Variables
int color_change_counter = 0;
int menu_main_option_selected = 1;
int color_value = 0;
bool menu_egg = false;
bool draw_HTP = false;

// Tetris Variables
char next_block = '?';
char current_block = '?';
bool pause = false;
bool game_start = false;
bool score = 0;
bool lines_cleared = 0;
bool level = 1;
bool o_count = 0;
bool i_count = 0;
bool t_count = 0;
bool l_count = 0;
bool j_count = 0;
bool s_count = 0;
bool z_count = 0;

int ref_y = 1;
int ref_x = 6;

////////////////////////////
// Main Routines - Main Menu
////////////////////////////
void MainMenuSetup() {
	ShowConsoleCursor(false);

}
void MainMenuDraw() {
	drawLogo(20, 3);
	indent(24);
	OutputOption(1, "Play Tetris");
	indent(24);
	OutputOption(2, "Options");
	indent(24);
	OutputOption(3, "How To Play");
	indent(24);
	OutputOption(4, "Exit Game");
	DrawHowToPlay();

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
		case 13:
			if (menu_main_option_selected == 4) {
				EXIT_PROGRAM = true;
				EXIT_MENU = true;
			}
			else if (menu_main_option_selected == 3) {
				draw_HTP = !draw_HTP;
			}
			else if (menu_main_option_selected == 1) {
				EXIT_MENU = true;
				EXIT_TETRIS = false;
			}
			break;
		case '*':
			menu_egg = true;
			system("CLS");
			cout << "\a";
			break;
		}
	}
}
void MainMenuLogic() {
	SetMenuBounds();
}

/////////////////////////
// Main Routines - Tetris
/////////////////////////
void TetrisSetup() {
	system("CLS");
	system("MODE 47, 25");
}
void TetrisDraw() {
	DrawBoard(4, 2);
	DrawStatistics(26, 2);
}
void TetrisInput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 13:
			if (pause)
				pause = false;
			else if (game_start)
				pause = true;
			else if (!game_start)
				game_start = true;
			break;
		case 'a':
			ref_x--;
			break;
		case 'd':
			ref_x++;
			break;
		}
	}
}
void TetrisLogic() {

}

/////////////////////
// Functions - Tetris
/////////////////////
void DrawBoard(int x, int y) {
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(console_handle, coordinates);
	SetColor("WHITE");
	cout << "Score: " << score;
	SetColor("GRAY");
	newLine(x, 1);
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			if (tetris_board[y][x] == '#')
				cout << solid_block;
			else if (((tetris_board[y][x] > 64 && tetris_board[y][x] < 123) || (tetris_board[y][x] == ':')) && tetris_board[y][x] != 'b')
				cout << tetris_board[y][x];
			else if (tetris_board[y][x] == 'b')
				cout << next_block;
			else
				cout << empty_space;
		}
		cout << endl;
		indent(x);
	}
	cout << "\r";
	indent(x);
	if (!game_start)
		cout << "PRESS ENTER TO START";
	else if (pause)
		cout << "GAME IS PAUSED";
	else
		cout << "                     ";
}
void DrawStatistics(int x, int y) {
	coordinates.X = x;
	coordinates.Y = y;
	newLine(x, 0);
	SetColor("WHITE");
	indent(4);
	cout << "Statistics";
	newLine(x, 2);
	cout << "Cleared Lines: " << lines_cleared;
	newLine(x, 2);
	cout << "Level: " << level;
	newLine(x, 2);
	cout << "O Blocks: " << o_count;
	newLine(x, 2);
	cout << "I Blocks: " << i_count;;
	newLine(x, 2);
	cout << "T Blocks: " << t_count;;
	newLine(x, 2);
	cout << "L Blocks: " << l_count;;
	newLine(x, 2);
	cout << "J Blocks: " << j_count;;
	newLine(x, 2);
	cout << "S Blocks: " << s_count;;
	newLine(x, 2);
	cout << "Z Blocks: " << z_count;;

}

////////////////////////
// Functions - Main Menu
////////////////////////
void DrawHowToPlay() {
	coordinates.X = 45; coordinates.Y = 5;
	SetConsoleCursorPosition(console_handle, coordinates);
	if (draw_HTP) {
		SetColor("BLUE");
		cout << "How To Play";
		SetColor("LIGHTBLUE");
		newLine(45, 2);
		cout << "Stack the blocks. Every line you make gets cleared and earns you points!";
		newLine(45, 2);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << empty_space << solid_block;
		newLine(45, 1);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << empty_space << solid_block << " " << selection_arrow << " There are seven kinds of blocks!";
		newLine(45, 1);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << solid_block << solid_block;
		newLine(45, 2);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << "If you stack all the way to the ceiling, you lose!";
		newLine(45, 2);
		SetConsoleCursorPosition(console_handle, coordinates);
		SetColor("BLUE");
		cout << "Controls";
		SetColor("LIGHTBLUE");
		newLine(45, 2);
		cout << "ENTER ---------- Pauses Game";
		newLine(45, 1);
		cout << "SPACE ----------- Drops Block";
		newLine(45, 1);
		cout << "WASD / ARROWS -- Movement Controls";
		newLine(45, 1);
		cout << "Q -------------- Rotate Left";
		newLine(45, 1);
		cout << "E -------------- Rotate Right";
	}
	else {
		cout << "           ";
		newLine(45, 2);
		cout << "                                                                         ";
		newLine(45, 2);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << "  ";
		newLine(45, 1);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << "                                     ";
		newLine(45, 1);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << "  ";
		newLine(45, 2);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << "                                                  ";
		newLine(45, 2);
		SetConsoleCursorPosition(console_handle, coordinates);
		cout << "        ";
		newLine(45, 2);
		cout << "                                    ";
		newLine(45, 1);
		cout << "                                            ";
		newLine(45, 1);
		cout << "                                                 ";
		newLine(45, 1);
		cout << "                                    ";
		newLine(45, 1);
		cout << "                                    ";
	}
}
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
void OutputOption(int option, const char option_name[10]) {
	if (!menu_egg)
		SetColor("LIGHTGREEN");
	else
		SetColor("RED");
	cout << list_dot;
	SetColor("WHITE");
	cout << " " << option_name;
	if (menu_main_option_selected == option) {
		if (!menu_egg)
			SetColor("LIGHTGREEN");
		else
			SetColor("RED");
		cout << " " << selection_arrow;
		SetColor("WHITE");
	}
	else
		cout << "  ";
	cout << endl;
}
void drawLogo(int x, int y) {
	coordinates.X = x; coordinates.Y = y;
	SetConsoleCursorPosition(console_handle, coordinates);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 22; j++) {
			if (logo[i][j] == getColor(color_value)) {
				if (!menu_egg)
					SetColor("GREEN");
				else
					SetColor("RED");
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 1)) {
				if (!menu_egg)
					SetColor("BLUE");
				else
					SetColor("RED");
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 2)) {
				if (!menu_egg)
					SetColor("PURPLE");
				else
					SetColor("RED");
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 3)) {
				if (!menu_egg)
					SetColor("RED");
				else
					SetColor("YELLOW");
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 4)) {
				if (!menu_egg)
					SetColor("CYAN");
				else
					SetColor("RED");
				cout << solid_block;
			}
			else if (logo[i][j] == getColor(color_value + 5)) {
				if (!menu_egg)
					SetColor("YELLOW");
				else
					SetColor("RED");
				cout << solid_block;
			}
			else
				cout << empty_space;
		}
		cout << endl;
		indent(x);
	}
	SetColor("PINK");
	if (menu_egg) {
		cout << " The Soviet Mind Game" << endl;
	}
	cout << endl;
	SetColor("WHITE");
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

///////////////////
// Global Functions
///////////////////
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
void newLine(int x, int y) {
	coordinates.X = x;
	coordinates.Y += y;
	SetConsoleCursorPosition(console_handle, coordinates);
}
void SetColor(const char color[15]) {
	if (color == "RED")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED);
	else if (color == "BLUE")
		SetConsoleTextAttribute(console_handle, FOREGROUND_BLUE);
	else if (color == "GREEN")
		SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN);
	else if (color == "PURPLE")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE);
	else if (color == "MAGENTA")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	else if (color == "YELLOW")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_GREEN);
	else if (color == "CYAN")
		SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_BLUE);
	else if (color == "ORANGE")
		SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	else if (color == "LIGHTBLUE")
		SetConsoleTextAttribute(console_handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	else if (color == "LIGHTGREEN")
		SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else if (color == "PINK" || color == "LIGHTRED")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
	else if (color == "WHITE")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	else if (color == "GRAY")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

}

/////////////////////
// Borrowed Functions
/////////////////////
bool KeyIsDown(char key, bool pressed, bool held) {
	int keyState = GetAsyncKeyState(static_cast<int>(key));
	return (pressed && (keyState & 1)) || (held && (keyState & 0xA000));
}
double getTime() {
	return time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count() / 1e9;
}
double getTimeSince(double startTime) {
	return time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count() / 1e9 - startTime;
}
double wait(double waitTime) {
	double startTime = getTime();

	while (waitTime > getTimeSince(startTime)) {}

	return getTimeSince(startTime + waitTime);
}
