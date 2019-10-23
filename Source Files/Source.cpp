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
