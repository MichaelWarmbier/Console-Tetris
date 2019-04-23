// Functions - CamelCase
// Variables - scored_ 

// Global Function Prototypes
void indent(int); // Indents based off argument
void newLine(int, int); // Resets cursor position to X argument, and adds Y argument
void SetColor(const char[15]); // Sets text color based off argument

// Main Menu Routine Prototypes
void MainMenuSetup();
void MainMenuDraw();
void MainMenuInput();
void MainMenuLogic();

// Tetris Routine Prototypes
void TetrisSetup();
void TetrisDraw();
void TetrisInput();
void TetrisLogic();

// Menu Function Prototypes
void drawLogo(int, int); // Draws logo at position x,y, based off argument
char getColor(int); // Returns a character based off an argument, for updating logo colors
void ShowConsoleCursor(bool); // Shows or hides cursor based off bool
void DrawHowToPlay(); // Draws How To Play portion of screen
void SetMenuBounds(); // Logic function reserved for mainly bounds
void OutputOption(int, const char[10], const char[10]); // Outputs selection arrow with proper formating with argument of menu position, option name and color

// Tetris Function Prototypes
void DrawBoard(int, int); // Draws Tetris board
void DrawStatistics(int, int); // Draws Tetris statistics
void ResetBlock(); // Resets reference coordinates of block
void IncrementY(); // Increments reference y value
void ResetBoard(); // Resets board using data from it's copy
void SetBlock(); // Converts falling blocks to landed blocks and copies those values to the board copy
void DrawBlock(); // Sets block to correct position based off reference coordinate
char SetRandomBlock(); // Returns the value of a character representing a block randomly
void IncrementBlockCounter(); // Increments counter associated with current block
void CheckHorizontalCollision(); // Checks for collisions horizontally
bool CheckVerticalCollision(); // Checks if block has landed
void SetBlockColor(); // Sets color based off current block
bool RotationCheck(); // Checks if rotation is possible based off current block
void CheckForLines(); // Checks to see if lines were filled
void ClearLines(int, int); // Clears lines given number and y position
void SetLevelColor(); // Sets text color based off current level
void CheckForLoss(); // Checks if game has been lost
void GameOver(); // Plays game over 'animation'
void SetRandomColor(); // Sets text color randomly
void SetupBoard(); // Copies board template onto board and board copy

// Borrowed Functions
bool KeyIsDown(char key, bool pressed = true, bool held = true);
double getTime();
double getTimeSince(double);
double wait(double);

#include "Implementation.h"

int main() {
	while (!EXIT_PROGRAM) { // Program Loop
		MainMenuSetup();
		while (!EXIT_MENU && (timer += (dt = FPS + wait(FPS)))) { // Menu Loop
			MainMenuDraw();
			MainMenuInput();
			MainMenuLogic();
		}
		if (!EXIT_TETRIS)
			TetrisSetup();
		while (!EXIT_TETRIS && (timer += (dt = FPS + wait(FPS)))) { // Tetris Loop
			TetrisDraw();
			TetrisInput();
			if (!(game_state == LIMBO || game_state == BEFORE))
				TetrisLogic();
		}
	}
	return 0;
}
