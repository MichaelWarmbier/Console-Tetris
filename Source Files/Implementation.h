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
input player_menu_input = NONE;
int color_change_counter = 0;
int menu_main_option_selected = 1;
int color_value = 0;
bool menu_egg = false;
bool draw_HTP = false;

// Tetris Variables
input player_tetris_input = NONE;
state game_state = BEFORE;
char next_block = '?';
char current_block = '?';
int score = 0;
int lines_cleared = 0;
int level = 1;
int o_count = 0;
int i_count = 0;
int t_count = 0;
int l_count = 0;
int j_count = 0;
int s_count = 0;
int z_count = 0;

int ref_y = 1;
int ref_x = 6;

////////////////////////////
// Main Routines - Main Menu
////////////////////////////
void MainMenuSetup() {
	ShowConsoleCursor(false); 
	system("MODE 42, 25");
}
void MainMenuDraw() {
	drawLogo(10, 3);
	indent(14);
	OutputOption(1, "Play Tetris");
	indent(14);
	OutputOption(2, "Options");
	indent(14);
	OutputOption(3, "How To Play");
	indent(14);
	OutputOption(4, "Exit Game");
	if (draw_HTP)
		DrawHowToPlay();

}
void MainMenuInput() {
	player_menu_input = NONE;
	if (KeyIsDown('W', true, false))
		player_menu_input = UP;
	if (KeyIsDown('S', true, false))
		player_menu_input = DOWN;
	if (KeyIsDown('A', true, false))
		player_menu_input = LEFT;
	if (KeyIsDown('D', true, false))
		player_menu_input = RIGHT;
	if (KeyIsDown(13, true, false))
		player_menu_input = ENTER;
	if (KeyIsDown('*', true, false)) {
		menu_egg = true;
		system("CLS");
		cout << "\a";
	}
}
void MainMenuLogic() {
	switch (player_menu_input) {
	case UP:
		menu_main_option_selected--;
		break;
	case DOWN:
		menu_main_option_selected++;
		break;
	case ENTER:
		switch (menu_main_option_selected) {
		case 1:
			EXIT_MENU = true;
			EXIT_TETRIS = false;
			break;
		case 2:
			// TBA
			break;
		case 3:
			system("CLS");
			draw_HTP = !draw_HTP;
			if (draw_HTP)
				system("MODE 120, 25");
			else
				system("MODE 42, 25");
			break;
		case 4:
			EXIT_PROGRAM = true;
			EXIT_MENU = true;
			break;
		}
		break;
	}
	SetMenuBounds();
}

/////////////////////////
// Main Routines - Tetris
/////////////////////////
void TetrisSetup() {
	system("CLS");
	system("MODE 47, 25");
	if (KeyIsDown(13, true, false))
		true;
}
void TetrisDraw() {
	DrawBoard(4, 2);
	DrawStatistics(26, 2);
}
void TetrisInput() {
	player_tetris_input = NONE;
	if (KeyIsDown(13, true, false))
		player_tetris_input = ENTER;
	if (player_tetris_input == ENTER)
		switch (game_state) {
		case BEFORE:
			game_state = DURING;
			break;
		case DURING:
			game_state = LIMBO;
			break;
		case AFTER:
			break;
		case LIMBO:
			game_state = DURING;
			break;
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
	if (game_state == BEFORE)
		cout << "PRESS ENTER TO START";
	else if (game_state == LIMBO)
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
