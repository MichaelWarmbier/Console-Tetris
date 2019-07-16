#pragma once

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <chrono>

using namespace std;
using namespace chrono;

bool EXIT_PROGRAM = false;
bool EXIT_GAME = false;
bool EXIT_MENU = false;
bool ON_OPTIONS = false;

const unsigned int CSS = 16;
unsigned int MenuOptionSelected = 1;

bool MUSIC = true;
bool SOUND = true;

const unsigned int MapWidth = 16;
const unsigned int MapHeight = 25;

unsigned int Score = 0;
unsigned int Lines = 0;

HDC console = GetDC(GetConsoleWindow());
HDC hdc = CreateCompatibleDC(NULL);
HBITMAP bmap = (HBITMAP)LoadImage(NULL, _T("ConsoleTetrisSpriteSheet.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

enum input { UP, DOWN, LEFT, RIGHT, ENTER, NONE, BACK };
enum state { BEFORE, DURING, AFTER, LIMBO};
input PlayerInput = NONE;

void MenuSetup();
void MenuDraw();
void MenuInput();
void MenuLogic();

void GameSetup();
void GameDraw();
void GameInput();
void GameLogic();

void DrawMap(int, int);
void DrawInteger(int, int, int);
int NumberToSpriteIndex(int);
void DrawString(const char[30], int, int);
void ClearMenuStyle(int, int);
void DrawMenuStyle(int, int);
int GetCharSpriteID(char);
void DrawLogo(int, int);
void DrawSprite(int, int, int, int, int);
bool KeyIsDown(char, bool, bool);
double GetTime();
double GetTimeSince(double);
double Wait(double);
void ShowConsoleCursor(bool);

int Map[MapHeight][MapWidth] = {
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,
	36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,36,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,36,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,36,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,36,00,
	36,28,28,28,28,28,28,28,28,28,36,36,36,36,36,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,28,28,28,28,28,28,28,28,28,36,00,00,00,00,00,
	36,36,36,36,36,36,36,36,36,36,36,00,00,00,00,00,
};

const int SpritePositions[56][2]{
	160,0, // Logo - 1
	00,32, // A - 2
	16,32, // B - 3
	32,32, // C - 4
	48,32, // D - 5
	64,32, // E - 6
	80,32, // F - 7
	96,32, // G - 8
	112,32, // H - 9
	128,32, // I - 10
	00,48, // J - 11
	16,48, // K - 12
	32,48, // L - 13
	48,48, // M - 14
	64,48, // N - 15
	80,48, // O - 16
	96,48, // P - 17
	112,48, // Q - 18
	128,48, // R - 19
	00,64, // S - 20
	16,64, // T - 21
	32,64, // U - 22
	48,64, // V - 23
	64,64, // W - 24
	80,64, // X - 25
	96,64, // Y - 26
	112,64, // Z - 27
	144,00, // ' ' - 28
	00,80, // '-' - 29
	16,80, // ':' - 30
	32,80, // '!' - 31
	48,80, // '?' - 32
	64,80, // '"' - 33
	80,80, // '.' - 34
	128,64, // Arrow - 35
	00,00, // Gray block - 36
	16,00, // Red block - 37
	32,00, // Cyan block - 38
	48,00, // Orange block - 39
	64,00, // Blue block - 40
	80,00, // Purple block - 41
	96,00, // Green block - 42
	112,0, // Yellow block - 43
	128,0, // Transparent block - 44
	00,16, // #0 - 45
	16,16, // #1 - 46
	32,16, // #2 - 47
	48,16, // #3 - 48
	64,16, // #4 - 49
	80,16, // #5 - 50
	96,16, // #6 - 51
	112,16, // #7 - 52
	128,16, // #8 - 53
	144,16, // #9 - 54
	97,80, // ON - 55
	113,80, // OF - 56
};
