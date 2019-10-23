#pragma once
#include "Game.h"

void Game::DrawSprite(int spriteID, int x, int y) const {
	SelectObject(hdc, bmap); // Get bitmap..
	BitBlt(console, x, y, GSS, GSS, hdc, Sprites[spriteID][0], Sprites[spriteID][1], SRCCOPY); // Draw on screen..
	DeleteObject(bmap); // Delete bitmap..
}

void Game::DrawBoard() const {
	/* Go through each index of the matrix and draw a sprite accordingly */
	for (int y = 0; y < WH; y++) {
		for (int x = 0; x < WW; x++) {
			DrawSprite(Board[y][x], x * GSS, y * GSS);
		}
	}
}

void Game::Draw() const {
	DrawBoard();
}

void Game::Input() {
	pInput = NONE;
	// Note: Add secondary arrow-key controls
	if (KeyIsDown('W', true, false) || KeyIsDown(38, true, false))
		pInput = UP;
	else if (KeyIsDown('S', true, false) || KeyIsDown(40, true, false))
		pInput = DOWN;
	else if (KeyIsDown('A', true, false) || KeyIsDown(37, true, false))
		pInput = LEFT;
	else if (KeyIsDown('D', true, false) || KeyIsDown(39, true, false))
		pInput = RIGHT;
}

void Game::Logic() {
}

void Game::SetAxis(int x, int y) {
	Board[Y][X] = 0;
	X = x, Y = y;
	Board[y][x] = 1; // Note: TBC
}
