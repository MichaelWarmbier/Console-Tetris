#pragma once

#include <iostream>
#include <windows.h>
#include <random>
#include <chrono>

#include "Info.h"

void SetupTetris();
void DrawTetris();
void InputTetris();
void LogicTetris();

void DrawSpriteData(const int[GlobalSpriteSize][GlobalSpriteSize], int, int, COLORREF);
void DrawSquareSprite(const int[GlobalSpriteSize][GlobalSpriteSize], int, int, COLORREF);
void DrawLineSprite(const int[GlobalSpriteSize][GlobalSpriteSize], int, int, COLORREF);
void DrawMapData(int, int);
void CopyMapData();

void ResetShape();
void DisplayNextShape();
int GetRandomShape();
bool CheckVerticalCollision();
bool CheckHorizontalCollision();
bool CheckRotationCollision();
bool CheckPositions(int, int, int, int, int, int, int, int);
void ConvertTiles();
void DrawShape();
void ResetShapePosition();
void ClearShape();
void ClearPosition(int, int, int, int, int, int);
void DrawPosition(int, int, int, int, int, int, int);
void Movement();
void SetCeiling();
void LowerShape();

bool KeyIsDown(char, bool, bool);
double GetTime();
double Wait(double);
double GetTimeSince(double);
void HideCursor();
void FrameCounter();

//// Main Functions ///

void SetupTetris() {
	CopyMapData();
	system("MODE 40,25");
	HideCursor();
	ResetShapePosition();
}

void DrawTetris() {
	DrawMapData(MapShift, MapShift);
}

void InputTetris() {
	PlayerInput = NONE;
	if (KeyIsDown('A', true, false))
		PlayerInput = LEFT;
	if (KeyIsDown('D', true, false))
		PlayerInput = RIGHT;
	if (KeyIsDown('S', true, true))
		PlayerInput = DOWN;
	if (KeyIsDown('Q', true, false))
		PlayerInput = LB;
	if (KeyIsDown('E', true, false))
		PlayerInput = RB;
}

void LogicTetris() {
	if ((CheckVerticalCollision() && GetTimeSince(TimeSinceDrop) > DropTime) || CurrentShape == 0) {
		ResetShape();
		DisplayNextShape();
	}
	LowerShape();
	Movement();
	DrawShape();
	SetCeiling();
}
//// Secondary Functions ////
void DisplayNextShape() {
	for (int y = 6; y < 11; y++) {
		for (int x = 12; x < 17; x++) {
			ActiveMap[y][x] = 99;
		}
	}
	switch (NextShape) {
	case 1:
		ActiveMap[7][13] = 13;
		ActiveMap[7][14] = 13;
		ActiveMap[8][13] = 13;
		ActiveMap[8][14] = 13;
		break;
	case 2:
		ActiveMap[8][12] = 14;
		ActiveMap[8][13] = 14;
		ActiveMap[8][14] = 14;
		ActiveMap[8][15] = 14;
		break;
	case 3:
		ActiveMap[7][13] = 15;
		ActiveMap[7][14] = 15;
		ActiveMap[7][15] = 15;
		ActiveMap[8][14] = 15;
		break;
	case 4:
		ActiveMap[7][13] = 16;
		ActiveMap[8][13] = 16;
		ActiveMap[9][13] = 16;
		ActiveMap[9][14] = 16;
		break;
	case 5:
		ActiveMap[7][14] = 17;
		ActiveMap[8][14] = 17;
		ActiveMap[9][14] = 17;
		ActiveMap[7][13] = 17;
		break;
	case 6:
		ActiveMap[7][13] = 18;
		ActiveMap[8][13] = 18;
		ActiveMap[7][14] = 18;
		ActiveMap[8][12] = 18;
		break;
	case 7:
		ActiveMap[7][14] = 19;
		ActiveMap[8][14] = 19;
		ActiveMap[7][13] = 19;
		ActiveMap[8][15] = 19;
		break;
	}
}
void SetCeiling() {
	for (int i = 1; i < 11; i++)
		ActiveMap[3][i] = 03;
}
void Movement() {
	if (PlayerInput == RB)
		if (CheckRotationCollision()) {
			ClearShape();
			RotationPosition++;
		}
	if (PlayerInput == LB)
		if (CheckRotationCollision()) {
			ClearShape();
			RotationPosition--;
		}
	if (RotationPosition > 4)
		RotationPosition = 1;
	else if (RotationPosition < 1)
		RotationPosition = 4;
	if (!CheckHorizontalCollision()) {
		switch (PlayerInput) {
		case LEFT:
			ClearShape();
			rX--;
			break;
		case RIGHT:
			ClearShape();
			rX++;
			break;
		}
	}
	if (MayDrop) {
		ClearShape();
		rY++;
	}
}
void LowerShape() {
	MayDrop = false;
	if (PlayerInput == DOWN)
		DropTime = .1;
	else
		DropTime = .8;
	if (GetTimeSince(TimeSinceDrop) > DropTime) {
		MayDrop = true;
		TimeSinceDrop = GetTime();
		ClearShape();
		DrawShape();
	}
}
bool CheckHorizontalCollision() {
	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++) {
			if (ActiveMap[y][x] > 05 && ActiveMap[y][x] < 13) {
				switch (PlayerInput) {
				case LEFT:
					if ((ActiveMap[y][x - 1] < 06 || ActiveMap[y][x - 1] > 12) && ActiveMap[y][x - 1] != 0)
						return true;
					break;
				case RIGHT:
					if ((ActiveMap[y][x + 1] < 06 || ActiveMap[y][x + 1] > 12) && ActiveMap[y][x + 1] != 0)
						return true;
				}
			}
		}
	}
	return false;
}
void CopyMapData() {
	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++) {
			ActiveMap[y][x] = InactiveMap[y][x];
		}
	}
}
void DrawSquareSprite(const int sprite[GlobalSpriteSize][GlobalSpriteSize], int Xpos, int Ypos, COLORREF Color) {
	HPEN Rect_Pen = CreatePen(PS_SOLID, 1, Color);
	SelectObject(hdc, Rect_Pen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	for (int y = 0; y < GlobalSpriteSize; y++) {
		for (int x = 0; x < GlobalSpriteSize; x++) {
			if (sprite[y][x] == 1) {
				x1 = x;
				y1 = y;
			}
			else if (sprite[y][x] == 2) {
				x2 = x;
				y2 = y;
			}
		}
	}
	RoundRect(hdc, Xpos + x1, Ypos + y1, Xpos + x2, Ypos + y2, 4, 4);
	DeleteObject(Rect_Pen);
	DeleteObject(GetStockObject(NULL_BRUSH));
}
void DrawLineSprite(const int sprite[GlobalSpriteSize][GlobalSpriteSize], int Xpos, int Ypos, COLORREF Color) {
	HPEN Line_Pen = CreatePen(PS_SOLID, 1, Color);
	SelectObject(hdc, Line_Pen);
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int x3 = 0;
	int y3 = 0;
	bool thirdPoint = false;
	for (int y = 0; y < GlobalSpriteSize; y++) {
		for (int x = 0; x < GlobalSpriteSize; x++) {
			if (sprite[y][x] == 1) {
				x1 = x;
				y1 = y;
			}
			else if (sprite[y][x] == 2) {
				x2 = x;
				y2 = y;
			}
			else if (sprite[y][x] == 3) {
				thirdPoint = true;
				x3 = x;
				y3 = y;
			}
		}
	}
	if (x1 == x2)
		y2--;
	if (y1 == y2)
		x2++;
	MoveToEx(hdc, Xpos + x1, Ypos + y1, NULL);
	LineTo(hdc, Xpos + x2, Ypos + y2);
	if (x1 == x2)
		y2++;
	if (thirdPoint) {
		MoveToEx(hdc, Xpos + x2, Ypos + y2, NULL);
		LineTo(hdc, Xpos + x3 + 1, Ypos + y3);
	}
	DeleteObject(Line_Pen);

}
void DrawSpriteData(const int sprite[GlobalSpriteSize][GlobalSpriteSize], int Xpos, int Ypos, COLORREF Color) {
	for (int y = 0; y < GlobalSpriteSize; y++) {
		for (int x = 0; x < GlobalSpriteSize; x++) {
			switch (sprite[y][x]) {
			case 0:
				continue;
			case 1:
				SetPixelV(hdc, Xpos + x, Ypos + y, Color);
				break;
			default:
				SetPixelV(hdc, Xpos + x, Ypos + y, RGB(234, 14, 139));
			}
		}
	}
}
void ResetShape() {
	ConvertTiles();
	if (CurrentShape == 0) {
		ResetShapePosition();
		NextShape = GetRandomShape();
		CurrentShape = GetRandomShape();
		// Decide Current Block
	}
	else {
		ResetShapePosition();
		CurrentShape = NextShape;
		NextShape = GetRandomShape();
	}
}
int GetRandomShape() {
	std::uniform_int_distribution<int> distribution(1, 7);
	return distribution(generator);
}
void DrawShape() {
	switch (CurrentShape) {
	case 0:
		break;
	case 1:
		DrawPosition(rX, rY + 1, rX + 1, rY, rX + 1, rY + 1, 06);
		break;
	case 2:
		DrawPosition(rX, rY - 1, rX, rY + 1, rX, rY + 2, 07);
		break;
	case 3:
		DrawPosition(rX - 1, rY, rX + 1, rY, rX, rY + 1,  8);
		break;
	case 4:
		DrawPosition(rX, rY - 1, rX, rY + 1, rX + 1, rY + 1, 9);
		break;
	case 5:
		DrawPosition(rX, rY - 1, rX, rY + 1, rX - 1, rY - 1, 10);
		break;
	case 6:
		DrawPosition(rX, rY - 1, rX - 1, rY, rX + 1, rY - 1, 11);
		break;
	case 7:
		DrawPosition(rX, rY - 1, rX - 1, rY - 1, rX + 1, rY, 12);
		break;
	}
}
bool CheckVerticalCollision() {
	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++) {
			if (ActiveMap[y][x] > 05 && ActiveMap[y][x] < 13) {
				if (ActiveMap[y + 1][x] != 00 && ActiveMap[y + 1][x] != ActiveMap[y][x])
					return true;
			}
		}
	}
	return false;
}
void ResetShapePosition() {
	rX = 5;
	rY = 4;
	TimeSinceDrop = GetTime();
}
void ConvertTiles() {
	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++) {
			switch (ActiveMap[y][x]) {
			case 06:
				ActiveMap[y][x] = 13;
				break;
			case 07:
				ActiveMap[y][x] = 14;
				break;
			case  8:
				ActiveMap[y][x] = 15;
				break;
			case  9:
				ActiveMap[y][x] = 16;
				break;
			case 10:
				ActiveMap[y][x] = 17;
				break;
			case 11:
				ActiveMap[y][x] = 18;
				break;
			case 12:
				ActiveMap[y][x] = 19;
				break;
			}
		}
	}
}
void ClearShape() {
	switch (CurrentShape) {
	case 1:
		ClearPosition(rX + 1, rY, rX + 1, rY + 1, rX, rY + 1);
		break;
	case 2:
		ClearPosition(rX, rY - 1, rX, rY + 1, rX, rY + 2);
		break;
	case 3:
		ClearPosition(rX - 1, rY, rX + 1, rY, rX, rY + 1);
		break;
	case 4:
		ClearPosition(rX, rY - 1, rX, rY + 1, rX + 1, rY + 1);
		break;
	case 5:
		ClearPosition(rX, rY - 1, rX, rY + 1, rX - 1, rY - 1);
		break;
	case 6:
		ClearPosition(rX, rY - 1, rX - 1, rY, rX + 1, rY - 1);
		break;
	case 7:
		ClearPosition(rX, rY - 1, rX - 1, rY - 1, rX + 1, rY);
		break;
	}
}

void ClearPosition(int x2, int y2, int x3, int y3, int x4, int y4) {
	DrawSquareSprite(SolidBlock, (MapShift + rX) * GlobalSpriteSize, (MapShift + rY) * GlobalSpriteSize, RGB(12, 12, 12));
	DrawSquareSprite(SolidBlock, (MapShift + x2) * GlobalSpriteSize, (MapShift + y2) * GlobalSpriteSize, RGB(12, 12, 12));
	DrawSquareSprite(SolidBlock, (MapShift + x3) * GlobalSpriteSize, (MapShift + y3) * GlobalSpriteSize, RGB(12, 12, 12));
	DrawSquareSprite(SolidBlock, (MapShift + x4) * GlobalSpriteSize, (MapShift + y4) * GlobalSpriteSize, RGB(12, 12, 12));

	ActiveMap[rY][rX] = 0;
	ActiveMap[y2][x2] = 0;
	ActiveMap[y3][x3] = 0;
	ActiveMap[y4][x4] = 0;
}

void DrawPosition(int x2, int y2, int x3, int y3, int x4, int y4, int value) {
	ActiveMap[rY][rX] = value;
	ActiveMap[y2][x2] = value;
	ActiveMap[y3][x3] = value;
	ActiveMap[y4][x4] = value;
}

bool KeyIsDown(char key, bool pressed, bool held) {
	int keyState = GetAsyncKeyState(static_cast<int>(key));
	return (pressed && (keyState & 1)) || (held && (keyState & 0xA000));
}
double GetTime() {
	return std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1e9;
}
double GetTimeSince(double startTime) {
	return std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1e9 - startTime;
}
double Wait(double waitTime) {
	double startTime = GetTime();

	while (waitTime > GetTimeSince(startTime)) {}

	return GetTimeSince(startTime + waitTime);
}
void HideCursor() {
	CONSOLE_CURSOR_INFO     CursorInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}
void DrawMapData(int xShift, int yShift) {
	int Xpos = 0; int Ypos = 0;
	for (int y = 0; y < MapHeight; y++) {
		for (int x = 0; x < MapWidth; x++) {
			Xpos = (xShift + x) * GlobalSpriteSize;
			Ypos = (yShift + y) * GlobalSpriteSize;
			switch (ActiveMap[y][x]) {
			case 00:
				continue;
				// Tiles
			case 01:
				DrawLineSprite(LeftWall, Xpos, Ypos, RGB(0, 92, 104));
				break;
			case 02:
				DrawLineSprite(Floor, Xpos, Ypos, RGB(0, 92, 104));
				break;
			case 03:
				DrawLineSprite(Ceiling, Xpos, Ypos, RGB(0, 92, 104));
				break;
			case 04:
				DrawLineSprite(RightWall, Xpos, Ypos, RGB(0, 92, 104));
				break;
			case 05:
				DrawLineSprite(Cross, Xpos, Ypos, RGB(0, 92, 104));
				break;
			case 06:
			case 13:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(255, 255, 0));
				break;
			case 14:
			case 07:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(0, 255, 255));
				break;
			case  8:
			case 15:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(170, 0, 255));
				break;
			case  9:
			case 16:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(255, 165, 0));
				break;
			case 10:
			case 17:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(0, 0, 255));
				break;
			case 11:
			case 18:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(0, 255, 0));
				break;
			case 12:
			case 19:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(255, 0, 0));
				break;
				// Characters
			case 22:
				DrawSpriteData(C, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 24:
				DrawSpriteData(E, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 31:
				DrawSpriteData(L, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 33:
				DrawSpriteData(N, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 34:
				DrawSpriteData(O, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 37:
				DrawSpriteData(R, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 38:
				DrawSpriteData(S, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 39:
				DrawSpriteData(T, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 41:
				DrawSpriteData(V, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 43:
				DrawSpriteData(X, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 46:
				DrawSpriteData(COLON, Xpos, Ypos, RGB(255, 255, 255));
				break;
			case 99:
				DrawSquareSprite(SolidBlock, Xpos, Ypos, RGB(12, 12, 12));
				break;
			}
		}
	}
}
bool CheckPositions(int x2, int y2, int x3, int y3, int x4, int y4, int value1, int value2) {
	if (ActiveMap[y2][x2] != value1 && ActiveMap[y2][x2] != value2)
		return true;
	if (ActiveMap[y3][x3] != value1 && ActiveMap[y3][x3] != value2)
		return true;
	if (ActiveMap[y4][x4] != value1 && ActiveMap[y4][x4] != value2)
		return true;
	return false;
}
bool CheckRotationCollision() {
	return false;
}
