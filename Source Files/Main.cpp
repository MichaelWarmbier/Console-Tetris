#include "Functions.h"
int main() {
	SetupTetris();
	while (!EXIT_TETRIS && (timer += (dt = FPS + Wait(FPS)))) {
		DrawTetris();
		InputTetris();
		LogicTetris();
	}
	return EXIT_SUCCESS;
}
