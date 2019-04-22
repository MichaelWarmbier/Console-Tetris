// Functions - CamelCase
// Variables - scored_ 

// Routine Prototypes
void MainMenuSetup();
void MainMenuDraw();
void MainMenuInput();
void MainMenuLogic();

void TetrisSetup();
void TetrisDraw();
void TetrisInput();
void TetrisLogic();

// Function Prototypes
void drawLogo(int, int); // Draws logo at position x,y, based off argument
void indent(int); // Indents based off argument
char getColor(int); // Returns a character based off an argument, for updating logo colors
void ShowConsoleCursor(bool); // Shows or hides cursor based off bool
void DrawHowToPlay(); // Draws How To Play portion of screen
void newLine(int, int); // Resets cursor position to X argument, and adds Y argument
void SetMenuBounds(); // Logic function reserved for mainly bounds
void OutputOption(int, const char[10]); // Outputs selection arrow with proper formating with argument of menu position and option name

void DrawBoard(int, int);
void DrawStatistics(int, int);

#include "Implementation.h"

int main() {
	do { // Program Loop
		MainMenuSetup();
		do { // Menu Loop
			MainMenuDraw();
			MainMenuInput();
			MainMenuLogic();
		} while (!EXIT_MENU);
		if (!EXIT_TETRIS)
			TetrisSetup();
		while (!EXIT_TETRIS) { // Tetris Loop
			TetrisDraw();
			TetrisInput();
			if (!pause && game_start)
				TetrisLogic();
		}
	} while (!EXIT_PROGRAM);
	return 0;
}
