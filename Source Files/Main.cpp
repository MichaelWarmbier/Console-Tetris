#include "Function.h"
int main() {
	while (!EXIT_PROGRAM) {
		MenuSetup();
		do {
			MenuDraw();
			MenuInput();
			MenuLogic();
			while (GetConsoleWindow() != GetForegroundWindow()) {}
		} while (!EXIT_MENU);
		GameSetup();
		while (!EXIT_GAME) {
			GameDraw();
			GameInput();
			GameLogic();
			while (GetConsoleWindow() != GetForegroundWindow()) {}
		};
	}
	return EXIT_SUCCESS;
}
