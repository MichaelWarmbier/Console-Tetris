#pragma once
#include "Game.h"

/* Main */

int main() {
	do {
		Game * Tetris = new Game;
		while (!EXIT_GAME_F) {
			Tetris->Draw();
			Tetris->Input();
			Tetris->Logic();
		}
		delete Tetris;
	} while (!EXIT_PROGRAM_F);
	return 0;
}

/* Non Specific Function definitions */
bool KeyIsDown(char key, bool pressed, bool held) {
	int keyState = GetAsyncKeyState(static_cast<int>(key));
	return (pressed && (keyState & 1)) || (held && (keyState & 0xA000));
}
