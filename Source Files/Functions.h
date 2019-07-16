#pragma once

#include "Info.h"

///////////////////////////////////////// - Menu loop
void MenuSetup() {
	system("MODE 58, 25");
	ShowConsoleCursor(false);
}
void MenuDraw() {
	DrawLogo(16, 25);
	DrawMenuStyle(8, 12);
	if (!ON_OPTIONS) {
		DrawString("Main Menu   \0", 8, 11);
		DrawString("Play Game\0", 9, 13);
		if (MenuOptionSelected == 1)
			DrawSprite(35, 20 * CSS, 13 * CSS, CSS, CSS);
		else
			DrawSprite(28, 20 * CSS, 13 * CSS, CSS, CSS);
		DrawString("Options\0", 9, 15);
		if (MenuOptionSelected == 2)
			DrawSprite(35, 20 * CSS, 15 * CSS, CSS, CSS);
		else
			DrawSprite(28, 20 * CSS, 15 * CSS, CSS, CSS);
		DrawString("Exit\0", 9, 17);
		if (MenuOptionSelected == 3)
			DrawSprite(35, 20 * CSS, 17 * CSS, CSS, CSS);
		else
			DrawSprite(28, 20 * CSS, 17 * CSS, CSS, CSS);
	}
	else {
		DrawString("Options Menu\0", 8, 11);
		DrawString("Sound: \0", 9, 13);
		if (MenuOptionSelected == 4)
			DrawSprite(35, 20 * CSS, 13 * CSS, CSS, CSS);
		else
			DrawSprite(28, 20 * CSS, 13 * CSS, CSS, CSS);
		if (SOUND)
			DrawString("On ", 16, 13);
		else
			DrawString("Off", 16, 13);
		DrawString("Music: \0", 9, 15);
		if (MenuOptionSelected == 5)
			DrawSprite(35, 20 * CSS, 15 * CSS, CSS, CSS);
		else
			DrawSprite(28, 20 * CSS, 15 * CSS, CSS, CSS);
		if (MUSIC)
			DrawString("On ", 16, 15);
		else
			DrawString("Off", 16, 15);
		DrawString("Clear Save\0", 9, 17);
		if (MenuOptionSelected == 6)
			DrawSprite(35, 20 * CSS, 17 * CSS, CSS, CSS);
		else
			DrawSprite(28, 20 * CSS, 17 * CSS, CSS, CSS);
	}
}

void MenuInput() {
	PlayerInput = NONE;
	if (KeyIsDown('W', true, false))
		PlayerInput = UP;
	else if (KeyIsDown('S', true, false))
		PlayerInput = DOWN;
	else if (KeyIsDown('A', true, false))
		PlayerInput = LEFT;
	else if (KeyIsDown('D', true, false))
		PlayerInput = RIGHT;
	else if (KeyIsDown(13, true, false))
		PlayerInput = ENTER;
	else if (KeyIsDown(8, true, false) || KeyIsDown(27, true, false))
		PlayerInput = BACK;
}
void MenuLogic() {
	if (PlayerInput == UP)
		MenuOptionSelected--;
	else if (PlayerInput == DOWN)
		MenuOptionSelected++;
	if (!ON_OPTIONS) {
		if (MenuOptionSelected < 1)
			MenuOptionSelected = 1;
		else if (MenuOptionSelected > 3)
			MenuOptionSelected = 3;
	}
	else {
		if (MenuOptionSelected < 4)
			MenuOptionSelected = 4;
		else if (MenuOptionSelected > 6)
			MenuOptionSelected = 6;
	}
	if (PlayerInput == ENTER)
		switch (MenuOptionSelected) {
		case 1:
			EXIT_GAME = false;
			EXIT_MENU = true;
			break;
		case 2:
			ON_OPTIONS = true;
			ClearMenuStyle(12, 12);
			break;
		case 3:
			EXIT_PROGRAM = true;
			EXIT_GAME = true;
			EXIT_MENU = true;
			break;
		case 4:
			SOUND = !SOUND;
			break;
		case 5:
			MUSIC = !MUSIC;
			break;
		case 6:
			// TBA: SAVE CLEAR
			break;
		}
	if (PlayerInput == BACK && ON_OPTIONS) {
		ClearMenuStyle(12, 12);
		ON_OPTIONS = false;
		MenuOptionSelected = 2;
	}
}

///////////////////////////////////////// - Game loop
void GameSetup() {
	system("CLS");
}
void GameDraw() {
	DrawMap(0, 0);
}
void GameInput() {

}
void GameLogic() {

}

//////////////////////////////////////////////////////////////////////////////////
void ClearMenuStyle(int x, int y) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			DrawSprite(28, (x + j) * CSS, (y + i) * CSS, CSS, CSS);
		}
	}

}
void DrawString(const char text[30], int x, int y) {
	for (int i = 0;; i++) {
		if (text[i] == '\0')
			break;
		tolower(text[i]);
		DrawSprite(GetCharSpriteID(text[i]), (x + i) * CSS, y * CSS, CSS, CSS);
	}
}
void DrawMap(int x_offset, int y_offset) {
	DrawString("Score: ", 0, 0); DrawInteger(Score, 7, 0);
	DrawString("Lines: ", 0, 1); DrawInteger(Lines, 7, 1);
	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++) {
			if (Map[y][x] == 00)
				continue;
			else
				DrawSprite(Map[y][x], (x_offset + x) * CSS, (y_offset + y) * CSS, CSS, CSS);
		}
	}
}
void DrawInteger(int value, int x_pos, int y_pos) {
	int ZeroOffset = 0;
	bool FirstNumber = false;
	if (value > 9999999)
		value = 9999999;
	int Digits[7] = { 0,0,0,0,0,0,0 };
	for (int i = 6; i >= 0; i--) {
		Digits[i] = value % 10;
		value /= 10;
	}
	for (int i = 0; i < 7; i++) {
		if (Digits[i] > 0 && !FirstNumber)
			FirstNumber = true;
		if (Digits[i] == 0 && !FirstNumber && i != 6) {
			ZeroOffset++;
			continue;
		}
		Map[y_pos][x_pos + i - ZeroOffset] = NumberToSpriteIndex(Digits[i]);
	}
}
int NumberToSpriteIndex(int number) {
	if (number > 9 || number < 0)
		return 40;
	else {
		switch (number) {
		case 0:
			return 45;
		case 1:
			return 46;
		case 2:
			return 47;
		case 3:
			return 48;
		case 4:
			return 49;
		case 5:
			return 50;
		case 6:
			return 51;
		case 7:
			return 52;
		case 8:
			return 53;
		case 9:
			return 54;
		}
	}
}
void DrawMenuStyle(int x, int y) {
	bool F = false;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 14; j++) {
			if (i == 0)
				F = true;
			if (i == 6)
				F = true;
			if (i % 2 == 0 && j == 12)
				F = true;
			if (j == 0)
				F = true;
			if (j == 13)
				F = true;
			if (j == 11)
				F = true;
			if (F) {
				DrawSprite(36, (j + x) * CSS, (i + y) * CSS, CSS, CSS);
				F = false;
			}
		}
	}
}
int GetCharSpriteID(char character) {
	if (character == ' ')
		return 28;
	else if (character == '-')
		return 29;
	else if (character == ':')
		return 30;
	else if (character == '!')
		return 31;
	else if (character == '?')
		return 32;
	else if (character == '"')
		return 33;
	else if (character == '.')
		return 34;
	else if (character >= 48 && character <= 57)
		return character - 3;
	character = tolower(character);
	return static_cast<int>(character) - 95;
}
void DrawLogo(int x, int y) {
	DrawSprite(1, x, y, 432, 111);
}
void DrawSprite(int ArrPos, int x, int y, int s_x, int s_y) {
	SelectObject(hdc, bmap);
	BitBlt(console, x, y, s_x, s_y, hdc, SpritePositions[ArrPos - 1][0], SpritePositions[ArrPos - 1][1], SRCCOPY);
	DeleteObject(bmap);
}
bool KeyIsDown(char key, bool pressed, bool held) {
	int keyState = GetAsyncKeyState(static_cast<int>(key));
	return (pressed && (keyState & 1)) || (held && (keyState & 0xA000));
}
double GetTime() {
	return time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count() / 1e9;
}
double GetTimeSince(double startTime) {
	return time_point_cast<nanoseconds>(high_resolution_clock::now()).time_since_epoch().count() / 1e9 - startTime;
}
double Wait(double waitTime) {
	double startTime = GetTime();
	while (waitTime > GetTimeSince(startTime)) {}
	return GetTimeSince(startTime + waitTime);
}
void ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
