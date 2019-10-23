#pragma once
#include <iostream>
#include <windows.h>
#include <chrono>
#include <tchar.h>
using namespace std;
using namespace chrono;

/* Exit Flags */
static bool EXIT_GAME_F = false;
static bool EXIT_PROGRAM_F = false;

typedef unsigned char byteint; // Integer with range of one byte

const HDC console = GetDC(GetConsoleWindow()); // Handle for device context specifically targeted at the console window.
const HDC hdc = CreateCompatibleDC(NULL); // Handle for device context for bitmap
const HBITMAP bmap = (HBITMAP)LoadImage(NULL, _T("ConsoleTetrisSpriteSheet.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // Bitmap image data

enum GameState {BEFORE, DURING, LIMBO, WIN, LOSS};
enum Direction {UP, DOWN, LEFT, RIGHT, NONE};

const int GSS = 16; // Global Sprite Size
const int BH = 20, BW = 10, WH = 24, WW = 16; // Dimension Variables (Board and Window)

bool KeyIsDown(char key, bool pressed, bool held); // Returns true if passed key is pressed or held
