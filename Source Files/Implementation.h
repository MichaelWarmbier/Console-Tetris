#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>
#include <chrono>
#include <random>
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
bool on_options = false;
input player_menu_input = NONE;
int color_change_counter = 0;
int menu_option_selected = 1;
int color_value = 0;
bool menu_egg = false;
bool draw_HTP = false;
// Variables Set On Menu
bool movement_delay = false;
bool music = true;
bool sounds = true;

// Tetris Variables
input player_tetris_input = NONE;
state game_state = BEFORE;
int block_position = 1;
bool may_move = true;
bool halt_a_frame = false;
int game_frames = 0;
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
int frame_cap = 40;

////////////////////////////
// Routines - Main Menu
////////////////////////////
void MainMenuSetup() {
	EXIT_MENU = false;
	menu_option_selected = 1;
	menu_egg = false;
	draw_HTP = false;
	color_value = 0;
	player_menu_input = NONE;
	ShowConsoleCursor(false); 
	system("MODE 42, 25");
	if (KeyIsDown('W', true, false))
		true;
	if (KeyIsDown('S', true, false))
		true;
	if (KeyIsDown('A', true, false))
		true;
	if (KeyIsDown('D', true, false))
		true;
	if (KeyIsDown(13, true, false))
		true;
}
void MainMenuDraw() {
	drawLogo(10, 3);
	indent(14);
	OutputOption(1, "Play Tetris", "WHITE");
	indent(14);
	OutputOption(2, "Options", "WHITE");
	if (on_options) {
		indent(16);
		if (movement_delay)
			OutputOption(5, "Movement Delay", "GREEN");
		else
			OutputOption(5, "Movement Delay", "RED");
		indent(16);
		if (music)
			OutputOption(6, "Music", "GREEN");
		else
			OutputOption(6, "Music", "RED");
		indent(16);
		if (sounds)
			OutputOption(7, "Sounds", "GREEN");
		else
			OutputOption(7, "Sounds", "RED");
	}
	indent(14);
	OutputOption(3, "How To Play", "WHITE");
	indent(14);
	OutputOption(4, "Exit Game", "WHITE");
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
	if (KeyIsDown(8, true, false) || KeyIsDown(27, true, false))
		player_menu_input = BACK;
	if (KeyIsDown('*', true, false)) {
		menu_egg = true;
		system("CLS");
		cout << "\a";
	}
}
void MainMenuLogic() {
	switch (player_menu_input) {
	case UP:
		menu_option_selected--;
		break;
	case DOWN:
		menu_option_selected++;
		break;
	case ENTER:
		switch (menu_option_selected) {
		case 1:
			EXIT_MENU = true;
			EXIT_TETRIS = false;
			break;
		case 2:
			on_options = true;
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
		// Options
		case 5:
			movement_delay = !movement_delay;
			break;
		case 6:
			music = !music;
			break;
		case 7:
			sounds = !sounds;
			break;
		}
		break;
	case BACK:
		if (on_options) {
			on_options = false;
			menu_option_selected = 2;
			system("CLS");
		}
		break;
	}
	SetMenuBounds();
}

/////////////////////////
// Routines - Tetris
/////////////////////////
void TetrisSetup() {
	system("CLS");
	system("MODE 47, 25");
	if (KeyIsDown(13, true, false))
		true;
	game_state = BEFORE;
	player_tetris_input = NONE;
	block_position = 1;
	may_move = true;
	halt_a_frame = false;
	game_frames = 0;
	next_block = '?';
	current_block = '?';
	score = 0;
	lines_cleared = 0;
	level = 1;
	o_count = 0;
	i_count = 0;
	t_count = 0;
	l_count = 0;
	j_count = 0;
	s_count = 0;
	z_count = 0;
	ref_y = 1;
	ref_x = 6;
	SetupBoard();
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
		case LIMBO:
			game_state = DURING;
			break;
		}
	if (game_state == DURING) {
		if (KeyIsDown('A', true, !movement_delay))
			player_tetris_input = LEFT;
		if (KeyIsDown('D', true, !movement_delay))
			player_tetris_input = RIGHT;
		if (KeyIsDown('S', true, true))
			player_tetris_input = DOWN;
		if (KeyIsDown('Q', true, false))
			player_tetris_input = RL;
		if (KeyIsDown('E', true, false))
			player_tetris_input = RR;
	}
}
void TetrisLogic() {
	may_move = true;
	CheckHorizontalCollision();
	if (RotationCheck()) {
		switch (player_tetris_input) {
		case RR:
			block_position++;
			break;
		case RL:
			block_position--;
			break;
		}
	}
	if (block_position > 4)
		block_position = 1;
	else if (block_position < 1)
		block_position = 4;
	if (may_move) {
		switch (player_tetris_input) {
		case LEFT:
			ref_x--;
			break;
		case RIGHT:
			ref_x++;
			break;
		}
	}
	if (CheckVerticalCollision() && player_tetris_input != DOWN) {
		if (game_frames > frame_cap) {
			SetBlock();
			ResetBlock();
			game_frames = 0;
		}
		else
			halt_a_frame = true;
	}
	else if (CheckVerticalCollision() && player_tetris_input == DOWN) {
		SetBlock();
		ResetBlock();
		game_frames = 0;
	}
	else if (player_tetris_input == DOWN)
		IncrementY();
	else if (game_frames > frame_cap && !halt_a_frame) {
		if (level < 10)
			frame_cap -= (level - 1) * 2;
		game_frames = 0;
		IncrementY();
	}
	if (CheckVerticalCollision())
		halt_a_frame = false;
	if (current_block == '?') {
		if (next_block == '?')
			current_block = SetRandomBlock();
		else
			current_block = next_block;
		next_block = SetRandomBlock();
		IncrementBlockCounter();
	}
	CheckForLines();
	ResetBoard();
	DrawBlock();
	CheckForLoss();
	game_frames++;
	level = (lines_cleared / 5) + 1;
}

/////////////////////
// Functions - Tetris
/////////////////////
void SetLevelColor() {
	switch (level % 3 + 1) {
	case 1:
		SetColor("LIGHTBLUE");
		break;
	case 2:
		SetColor("LIGHTRED");
		break;
	case 3:
		SetColor("LIGHTGREEN");
		break;
	default:
		SetColor("WHITE");
		break;
	}
}
void CheckForLoss() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 21; j++) {
			if (tetris_board[i][j] == '@' && tetris_board_copy[i][j] == '#' && game_state != AFTER)
				GameOver();
		}
	}
}
void GameOver() {
	game_state = AFTER;
	coordinates.X = 4;
	coordinates.Y = 3;
	SetConsoleCursorPosition(console_handle, coordinates);
	for (int i = 1; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			SetRandomColor();
			cout << trans_block;
			Sleep(20);
		}
		cout << endl;
		indent(4);
	}
	coordinates.X = 10;
	coordinates.Y = 9;
	SetConsoleCursorPosition(console_handle, coordinates);
	SetColor("RED");
	cout << "GAME OVER";
	Sleep(5000);
	EXIT_TETRIS = true;
	EXIT_MENU = false;
	system("CLS");
}
void SetupBoard() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 20; j++) {
			tetris_board_copy[i][j] = tetris_template[i][j];
			tetris_board[i][j] = tetris_template[i][j];
		}
	}
}
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
			if (tetris_board[y][x] == '#' && ((y <= 0 || y >= 19) || (x <= 0 || x >= 11))) {
				SetLevelColor();
				cout << solid_block;
			}
			else if (tetris_board[y][x] == '#') {
				if (level % 3 == 0)
					SetColor("BLUE");
				if (level % 3 == 1)
					SetColor("RED");
				if (level % 3 == 2)
					SetColor("GREEN");
				cout << solid_block;
				SetColor("GRAY");
			}
			else if (tetris_board[y][x] == '*') {
				SetLevelColor();
				cout << solid_block;
			}
			else if (tetris_board[y][x] == '@' && y != 0) {
				SetBlockColor();
				cout << solid_block;
				SetColor("GRAY");
			}
			else if (tetris_board[y][x] == '@' && y == 0)
				cout << solid_block;
			else if (((tetris_board[y][x] > 64 && tetris_board[y][x] < 123) || (tetris_board[y][x] == ':')) && tetris_board[y][x] != 'b')
				cout << tetris_board[y][x];
			else if (tetris_board[y][x] == 'b')
				cout << static_cast<char>(toupper(next_block));
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
	cout << "I Blocks: " << i_count;
	newLine(x, 2);
	cout << "T Blocks: " << t_count;
	newLine(x, 2);
	cout << "L Blocks: " << l_count;
	newLine(x, 2);
	cout << "J Blocks: " << j_count;
	newLine(x, 2);
	cout << "S Blocks: " << s_count;
	newLine(x, 2);
	cout << "Z Blocks: " << z_count;
	newLine(x, 2);

}
void CheckForLines() {
	int total_lines = 0;
	int bottom_line = -1;
	for (int i = 1; i < 19; i++) {
		int blocks_found = 0;
		for (int j = 1; j < 11; j++) {
			if (tetris_board[i][j] == '#')
				blocks_found++;
		}
		if (blocks_found == 10) {
			total_lines++;
			bottom_line = i;
		}
	}
	if (total_lines > 0 && bottom_line != -1)
		ClearLines(total_lines, bottom_line);
}
void ClearLines(int number, int bottom) {
	score += static_cast<int>(200 * pow(number, 2));
	lines_cleared += number;
	for (int i = bottom; i > bottom - number; i--) {
		for (int j = 1; j < 11; j++) {
			tetris_board[i][j] = tetris_board[i - 1][j];
		}
	}
	for (int i = bottom; i > 1; i--) {
		for (int j = 1; j < 11; j++) {
			if (tetris_board[i - number][j] != '*') {
				tetris_board[i][j] = tetris_board[i - number][j];
				tetris_board_copy[i][j] = tetris_board_copy[i - number][j];
			}
		}
	}
}
void ResetBlock() {
	ref_y = 2;
	ref_x = 6;
	current_block = '?';
	block_position = 1;
}
void IncrementY() {
	ref_y++;
}
void ResetBoard() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 21; j++) {
			tetris_board[i][j] = tetris_board_copy[i][j];
		}
	}
}
void SetBlock() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 21; j++) {
			if (tetris_board[i][j] == '@') {
				tetris_board[i][j] = '#';
				tetris_board_copy[i][j] = '#';
			}
		}
	}
}
void SetRandomColor() {
	random_device generator;
	uniform_int_distribution<int> distribution(1, 7);
	switch (distribution(generator)) {
	case 1:
		SetColor("YELLOW");
		break;
	case 2:
		SetColor("CYAN");
		break;
	case 3:
		SetColor("PURPLE");
		break;
	case 4:
		SetColor("ORANGE");
		break;
	case 5:
		SetColor("BLUE");
		break;
	case 6:
		SetColor("LIGHTGREEN");
		break;
	case 7:
		SetColor("RED");
		break;
	}
}
char SetRandomBlock() {
	random_device generator;
	uniform_int_distribution<int> distribution(1, 7);
	switch (distribution(generator)) {
	case 1:
		return 'o';
		break;
	case 2:
		return 'i';
		break;
	case 3:
		return 't';
		break;
	case 4:
		return 'l';
		break;
	case 5:
		return 'j';
		break;
	case 6:
		return 's';
		break;
	case 7:
		return 'z';
		break;
	default:
		return '?';
		break;
	}
}
void IncrementBlockCounter() {
	switch (current_block) {
	case 'o':
		o_count++;
		break;
	case 'i':
		i_count++;
		break;
	case 't':
		t_count++;
		break;
	case 'l':
		l_count++;
		break;
	case 'j':
		j_count++;
		break;
	case 's':
		s_count++;
		break;
	case 'z':
		z_count++;
		break;
	}
}
void DrawBlock() {
	switch (current_block) {
	case 'o':
		tetris_board[ref_y][ref_x] = '@';
		tetris_board[ref_y][ref_x + 1] = '@';
		tetris_board[ref_y + 1][ref_x + 1] = '@';
		tetris_board[ref_y + 1][ref_x] = '@';
		break;
	case 'i':
		switch (block_position) {
		case 1:
		case 3:
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y + 2][ref_x] = '@';
			break;
		case 2:
		case 4:
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x + 2] = '@';
			break;
		}
		break;
	case 't':
		switch (block_position) {
		case 1:
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y + 1][ref_x] = '@';
			break;
		case 2:
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y][ref_x + 1] = '@';
			break;
		case 3:
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x + 1] = '@';
			break;
		case 4:
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y][ref_x - 1] = '@';
			break;
		}
		break;
	case 'l':
		switch (block_position) {
		case 1:
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y + 1][ref_x + 1] = '@';
			break;
		case 2:
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y - 1][ref_x + 1] = '@';
			break;
		case 3:
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x - 1] = '@';
			break;
		case 4:
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y + 1][ref_x - 1] = '@';
			break;
		}
		break;
	case 'j':
		switch (block_position) {
		case 1:
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y + 1][ref_x - 1] = '@';
			break;
		case 2:
			tetris_board[ref_y + 1][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x + 1] = '@';
			break;
		case 3:
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x + 1] = '@';
			break;
		case 4:
			tetris_board[ref_y - 1][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x + 1] = '@';
			break;
		}
		break;
	case 's':
		switch (block_position) {
		case 1:
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		case 2:
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y + 1][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		case 3:
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y + 1][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		case 4:
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y - 1][ref_x - 1] = '@';
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		}
		break;
	case 'z':
		switch (block_position) {
		case 1:
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		case 2:
			tetris_board[ref_y][ref_x + 1] = '@';
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y - 1][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		case 3:
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y + 1][ref_x] = '@';
			tetris_board[ref_y + 1][ref_x + 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		case 4:
			tetris_board[ref_y][ref_x - 1] = '@';
			tetris_board[ref_y - 1][ref_x] = '@';
			tetris_board[ref_y + 1][ref_x - 1] = '@';
			tetris_board[ref_y][ref_x] = '@';
			break;
		}
		break;
	}
}
void CheckHorizontalCollision() {
	DrawBlock();
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 21; j++) {
			if (tetris_board[i][j] == '@' && player_tetris_input == LEFT) {
				if (tetris_board[i][j - 1] == '#')
					may_move = false;
			}
			else if (tetris_board[i][j] == '@' && player_tetris_input == RIGHT) {
				if (tetris_board[i][j + 1] == '#')
					may_move = false;
			}
		}
	}
}
bool CheckVerticalCollision() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 21; j++) {
			if (tetris_board[i][j] == '@' && tetris_board[i + 1][j] == '#')
				return true;
		}
	}
	return false;
}
void SetBlockColor() {
	switch (current_block) {
	case 'o':
		SetColor("YELLOW");
		break;
	case 'i':
		SetColor("CYAN");
		break;
	case 't':
		SetColor("PURPLE");
		break;
	case 'l':
		SetColor("ORANGE");
		break;
	case 'j':
		SetColor("BLUE");
		break;
	case 's':
		SetColor("LIGHTGREEN");
		break;
	case 'z':
		SetColor("RED");
		break;
	default:
		SetColor("WHITE");
		break;
	}
}
bool RotationCheck() {
	switch (player_tetris_input) {
	case RR:
		switch (current_block) {
		case 'o':
			return true;
			break;
		case 'i':
			switch (block_position) {
			case 1:
			case 3:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x + 2] == '#')
					return false;
				break;
			case 2:
			case 4:
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 2][ref_x] == '#')
					return false;
				break;
			}
			break;
		case 't':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				break;
			}
			break;
		case 'l':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				break;
			}
			break;
		case 'j':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				break;
			}
			break;
		case 's':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				break;
			}
			break;
		case 'z':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				break;
			}
			break;
		}
		break;
	case RL:
		switch (current_block) {
		case 'o':
			return true;
			break;
		case 'i':
			switch (block_position) {
			case 1:
			case 3:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x + 2] == '#')
					return false;
				break;
			case 2:
			case 4:
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 2][ref_x] == '#')
					return false;
				break;
			}
			break;
		case 't':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				break;
			}
			break;
		case 'l':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
			case 2:
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				break;
			}
			break;
		case 'j':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				break;
			}
			break;
		case 's':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				break;
			}
			break;
		case 'z':
			switch (block_position) {
			case 1:
				if (tetris_board[ref_y][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x - 1] == '#')
					return false;
				break;
			case 2:
				if (tetris_board[ref_y - 1][ref_x - 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x] == '#')
					return false;
				break;
			case 3:
				if (tetris_board[ref_y][ref_x + 1] == '#')
					return false;
				if (tetris_board[ref_y - 1][ref_x + 1] == '#')
					return false;
				break;
			case 4:
				if (tetris_board[ref_y + 1][ref_x] == '#')
					return false;
				if (tetris_board[ref_y + 1][ref_x + 1] == '#')
					return false;
				break;
			}
			break;
		}
		break;
	}
	return true;
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
	// Set menu_option_selected bounds
	if (!on_options) {
		if (menu_option_selected < 1)
			menu_option_selected = 1;
		if (menu_option_selected > 4)
			menu_option_selected = 4;
	}
	else {
		if (menu_option_selected < 5)
			menu_option_selected = 5;
		if (menu_option_selected > 7)
			menu_option_selected = 7;
	}
}
void OutputOption(int option, const char option_name[10], const char color[10]) {
	if (!menu_egg)
		SetColor("LIGHTGREEN");
	else
		SetColor("RED");
	cout << list_dot;
	SetColor(color);
	cout << " " << option_name;
	if (menu_option_selected == option) {
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
	else if (color == "GRAY")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	else if (color == "WHITE")
		SetConsoleTextAttribute(console_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else if (color == "DARKGRAY")
		SetConsoleTextAttribute(console_handle, 8);

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
