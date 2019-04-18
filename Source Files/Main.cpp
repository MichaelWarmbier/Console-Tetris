// Functions - CamelCase
// Variables - scored_ 

// Routine Prototypes
void MainMenuSetup();
void MainMenuDraw();
void MainMenuInput();
void MainMenuLogic();

// Function Prototypes
void drawLogo(int, int);

#include "Implementation.h"

int main() {
	do { // Program Loop
		MainMenuSetup();
		do { // Menu Loop
			MainMenuDraw();
			MainMenuInput();
			MainMenuLogic();
		} while (!EXIT_MENU);
		while (!EXIT_TETRIS) { // Tetris Loop

		}
	} while (!EXIT_PROGRAM);
	return 0;
}
