#pragma once
#include "Game.h"

void Game::DrawSprite(int spriteID, int x, int y) const {
	if (spriteID < 0)
		return;
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
	DrawBlock(true);
	DrawNextBlock();
	DrawInteger(8, 22, 3, Level - 1);
	DrawInteger(8, 23, 3, LinesC);
	for (int i = 0; i < 7; i++)
		DrawInteger(13, 7 + (2 * i), 2, BlockNums[i]);
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
	else if (KeyIsDown('Q', true, false))
		pInput = RL;
	else if (KeyIsDown('E', true, false))
		pInput = RR;
}

void Game::Logic() {
	if (ForceSpriteTest)
		BlockTest();
	else {
		if (CurrBlck == bX) {
			CurrBlck = NxtBlck;
			NxtBlck = GetRandomBlock();
			BlockNums[(int)CurrBlck]++;
		}
		else {
			ApplyInput();
			if (!IsSolid(DOWN) && DecrementBlock()) {
				DecrementBlock();
				ClearBoard();
				DrawBlock(true);
			}
			else if (IsSolid(DOWN) && DecrementBlock()) {
				DrawBlock(0);
				ResetBlock();
				CurrBlck = bX;
			}
		}
	}
	LineClear();
	ClearBoard();
	DrawBlock(true);
}

void Game::ResetBlock() {
	X = 5;
	Y = 3;
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
		if (data == i)
			return true;
	}
	return false;
}

void Game::DrawBlock(bool SolidFlag) {
	switch (CurrBlck) {
	case bO:
		SetTile(X, Y, pow(9, SolidFlag));
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + O.Limbs[i][0], Y + O.Limbs[i][1], pow(9, SolidFlag));
		break;
	case bI:
		SetTile(X, Y, pow(4, SolidFlag));
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + I.Limbs[i][0], Y + I.Limbs[i][1], pow(4, SolidFlag));
		break;
	case bT:
		SetTile(X, Y, pow(7, SolidFlag));
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + T.Limbs[i][0], Y + T.Limbs[i][1], pow(7, SolidFlag));
		break;
	case bL:
		SetTile(X, Y, pow(5, SolidFlag));
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + L.Limbs[i][0], Y + L.Limbs[i][1], pow(5, SolidFlag));
		break;
	case bJ:
		SetTile(X, Y, pow(6, SolidFlag));
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + J.Limbs[i][0], Y + J.Limbs[i][1], pow(6, SolidFlag));
		break;
	case bS:
		SetTile(X, Y, pow(8, SolidFlag));
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + S.Limbs[i][0], Y + S.Limbs[i][1], pow(8, SolidFlag));
		break;
	case bZ:
		SetTile(X, Y, pow(3, SolidFlag));
		for (int i = 0 + (Rot * 3); i < 3 + (Rot * 3); i++)
			SetTile(X + Z.Limbs[i][0], Y + Z.Limbs[i][1], pow(3, SolidFlag));
		break;
	}
}

void Game::SetTile(int x, int y, int ID) {
	Board[y][x] = ID;
}

void Game::BlockTest() {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			ClearBoard();
			CurrBlck = (BlockType)i;
			Rot = j;
			DrawBlock(true);
			DrawBoard();
			Wait(1);
		}
	}
}

void Game::ClearBoardCopy() {
	for (int y = 0; y < BH; y++) {
		for (int x = 0; x < BW; x++) {
			BoardCopy[y + 1][x + 1] = 0;
		}
	}
}

void Game::ClearBoard() {
	for (int y = 0; y < BH; y++) {
		for (int x = 0; x < BW; x++) {
			if (Board[y + 1][x + 1] != 1)
				SetTile(x + 1, y + 1, 0);
		}
	}
}

void Game::LineClear() {
	for (int y = 0 + 1; y < BH + 1; y++) {
		int SolidBlocks = 0;
		for (int x = 0 + 1; x < BW + 1; x++) {
			if (Board[y][x] == 1)
				SolidBlocks++;
		}
		if (SolidBlocks == 10) {
			LinesC++;
			for (int i = 0; i < 5; i++) {
				for (int j = 0 + 1; j < BW + 1; j++) {
					Board[y][j] = !Board[y][j];
				}
				Wait(.05);
				DrawBoard();
			}
			for (int i = y - 1; i > 0; i--) {
				for (int j = 0 + 1; j < BW + 1; j++) {
					if (Board[i][j] == 1) {
						Board[i][j] = 0;
						Board[i + 1][j] = 1;
					}
				}
			}
		}
	}
}

BlockType Game::GetRandomBlock() const {
	return (BlockType)distribution(generator);
}

void Game::DrawNextBlock() {
	if (NxtBlck == bX)
	SetTile(13, 2, 47);
	else
		SetTile(13, 2, 52 + (int)NxtBlck);

}

bool Game::DecrementBlock() {
	if ((GetTimeSince(_DropTS) > WaitTime || SpeedUp)) {
		if (!IsSolid(DOWN))
			Y++;
		_DropTS = GetTime();
		SpeedUp = false;
		return true;
	}
	return false;
}

bool Game::IsSolid(Direction Dir) {
	int adjX = 0, adjY = 0, adjR = Rot;
	switch (Dir) {
	case NONE:
	case RL:
		adjR = Rot - 1;
		break;
	case RR:
		adjR = Rot + 1;
		break;
	case UP:
		adjY--;
		break;
	case DOWN:
		adjY++;
		break;
	case LEFT:
		adjX--;
		break;
	case RIGHT:
		adjX++;
		break;
	}
	if (adjR < 0)
		adjR = 3;
	else if (adjR > 3)
		adjR = 0;
	ClearBoard();
	CopyBoard();
	DrawBlock(true);
	if (IsBlockData(BoardCopy[Y + adjY][X + adjX]))
		return true;
	switch (CurrBlck) {
	case bO:
		for (int i = 0 + (adjR * 3); i < 3 + (adjR * 3); i++)
			if (IsBlockData(BoardCopy[Y + adjY + O.Limbs[i][1]][X + adjX + O.Limbs[i][0]]))
					return true;
		break;
	case bI:
		for (int i = 0 + (adjR * 3); i < 3 + (adjR * 3); i++)
			if (IsBlockData(BoardCopy[Y + adjY + I.Limbs[i][1]][X + adjX + I.Limbs[i][0]]))
					return true;
		break;
	case bT:
		for (int i = 0 + (adjR * 3); i < 3 + (adjR * 3); i++)
			if (IsBlockData(BoardCopy[Y + adjY + T.Limbs[i][1]][X + adjX + T.Limbs[i][0]]))
					return true;
		break;
	case bL:
		for (int i = 0 + (adjR * 3); i < 3 + (adjR * 3); i++)
			if (IsBlockData(BoardCopy[Y + adjY + L.Limbs[i][1]][X + adjX + L.Limbs[i][0]]))
					return true;
		break;
	case bJ:
		for (int i = 0 + (adjR * 3); i < 3 + (adjR * 3); i++)
			if (IsBlockData(BoardCopy[Y + adjY + J.Limbs[i][1]][X + adjX + J.Limbs[i][0]]))
					return true;
		break;
	case bS:
		for (int i = 0 + (adjR * 3); i < 3 + (adjR * 3); i++)
			if (IsBlockData(BoardCopy[Y + adjY + S.Limbs[i][1]][X + adjX + S.Limbs[i][0]]))
					return true;
		break;
	case bZ:
		for (int i = 0 + (adjR * 3); i < 3 + (adjR * 3); i++)
			if (IsBlockData(BoardCopy[Y + adjY + Z.Limbs[i][1]][X + adjX + Z.Limbs[i][0]]))
					return true;
		break;
	}
 	return false;
}

void Game::ApplyInput() {
	switch (pInput) {
	case RL:
		if (!IsSolid(RL))
			Rot--;
		break;
	case RR:
		if (!IsSolid(RR))
			Rot++;
		break;
	case DOWN:
		SpeedUp = true;
		break;
	case LEFT:
		if (!IsSolid(LEFT))
			X--;
		break;
	case RIGHT:
		if (!IsSolid(RIGHT))
			X++;
		break;
	}
	if (Rot < 0)
		Rot = 3;
	else if (Rot > 3)
		Rot = 0;
}

void Game::DrawPause() {
	DrawSprite(35, 3 * 16, 8 * 16);
	DrawSprite(20, 4 * 16, 8 * 16);
	DrawSprite(40, 5 * 16, 8 * 16);
	DrawSprite(38, 6 * 16, 8 * 16);
	DrawSprite(24, 7 * 16, 8 * 16);
	DrawSprite(23, 8 * 16, 8 * 16);
}

void Game::DrawInteger(int x, int y, int size, int value) {
	if (size != 3 && size != 2)
		size = 2;
	if (value > 999 && size == 3)
		value = 999;
	else if (value > 99)
		value = 99;
	int Digits[3] = { value / 100, (value % 100) / 10 , value % 10 };
	for (int i = 0; i < size; i++)
		SetTile(x + (2 - i), y, Digits[2 - i] + 10);
}
