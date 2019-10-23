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

void Game::Draw() {
	DrawBoard();
	DrawBlock();
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
	if (ForceSpriteTest)
		BlockTest();
}

void Game::SetAxis(int x, int y) {
	Board[Y][X] = 0;
	X = x, Y = y;
	Board[y][x] = 1; // Note: TBC
}

void Game::CopyBoard() {
	for (int y = 0; y < WH; y++) {
		for (int x = 0; x < WW; x++) {
			BoardCopy[y][x] = Board[y][x];
		}
	}
}

bool Game::IsBlockData(int data) const {
	for (int i = 1; i < 10; i++) {
		if (i == 2)
			continue;
		if (data == i)
			return true;
	}
	return false;
}

void Game::DrawBlock() {
	switch (CurrBlck) {
	case bX:
	default:
		// continue;
		break;
	case bO:
		SetTile(X, Y, 9);
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + O.Limbs[i][0], Y + O.Limbs[i][1], 9);
		break;
	case bI:
		SetTile(X, Y, 4);
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + I.Limbs[i][0], Y + I.Limbs[i][1], 4);
		break;
	case bT:
		SetTile(X, Y, 7);
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + T.Limbs[i][0], Y + T.Limbs[i][1], 7);
		break;
	case bL:
		SetTile(X, Y, 5);
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + L.Limbs[i][0], Y + L.Limbs[i][1], 5);
		break;
	case bJ:
		SetTile(X, Y, 6);
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + J.Limbs[i][0], Y + J.Limbs[i][1], 6);
		break;
	case bS:
		SetTile(X, Y, 8);
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + S.Limbs[i][0], Y + S.Limbs[i][1], 8);
		break;
	case bZ:
		SetTile(X, Y, 3);
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + Z.Limbs[i][0], Y + Z.Limbs[i][1], 3);
		break;
	}
}

void Game::ClearBlock(int arr[WH][WW]) {
	switch (CurrBlck) {
	case bX:
	default:
		// continue;
		break;
	case bO:
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			arr[Y + O.Limbs[i][1], 0][X + O.Limbs[i][0]] = 0;
		break;
	case bI:
		
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			arr[Y + I.Limbs[i][1], 0][X + I.Limbs[i][0]] = 0;
		break;
	case bT:
		
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			arr[Y + T.Limbs[i][1], 0][X + T.Limbs[i][0]] = 0;
		break;
	case bL:
		
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			arr[Y + L.Limbs[i][1], 0][X + L.Limbs[i][0]] = 0;
		break;
	case bJ:
		
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			arr[Y + J.Limbs[i][1], 0][X + J.Limbs[i][0]] = 0;
		break;
	case bS:
		
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			arr[Y + S.Limbs[i][1], 0][X + S.Limbs[i][0]] = 0;
		break;
	case bZ:
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			arr[Y + Z.Limbs[i][1], 0][X + Z.Limbs[i][0]] = 0;
		break;
	}
	SetTile(X, Y, 0);
}

void Game::SetTile(int x, int y, int ID) {
	Board[y][x] = ID;
}

void Game::BlockTest() {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			ClearBlock(Board);
			CurrBlck = (BlockType)i;
			Rot = j;
			DrawBlock();
			DrawBoard();
			Wait(1);
		}
	}
}

void Game::ClearBoard() {
	for (int y = 0; y < BH; y++) {
		for (int x = 0; x < BW; x++) {
			SetTile(x + 1, y + 1, 0);
		}
	}
}

void Game::SetBlock() {
	/* This function is purely visual */
	DrawBlock();
}
