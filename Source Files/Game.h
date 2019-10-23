#pragma once
#include "Header.h"

class Game {
private:
	const int Sprites[256][2] {
		000,000, // Empty					// 000
		//////////////////////////////////////////
		 16,000, // Gray Tile				// 001
		144,000, // Sudo-transparent Tile	// 002
		032,000, // Red Tile				// 003
		 48,000, // Cyan Tile				// 004
		064,000, // Orange Tile				// 005
		 80,000, // Blue Tile				// 006
		 96,000, // Pink Tile				// 007
		112,000, // Green Tile				// 008
		128,000, // Yellow Tile				// 009
		//////////////////////////////////////////
		160,000, // #0						// 010
		176,000, // #1						// 011
		192,000, // #2						// 012
		208,000, // #3						// 013
		224,000, // #4						// 014
		240,000, // #5						// 015
		000, 16, // #6						// 016
		 16, 16, // #7						// 017
		 32, 16, // #8						// 018
		 48, 16, // #9						// 019
		//////////////////////////////////////////
		 64, 16, // A						// 020
		 80, 16, // B						// 021
		 96, 16, // C						// 022
		112, 16, // D						// 023
		128, 16, // E						// 024
		144, 16, // F						// 025
		160, 16, // G						// 026
		176, 16, // H						// 027
		192, 16, // I						// 028
		208, 16, // J						// 029
		224, 16, // K						// 030
		240, 16, // L						// 031
		000, 32, // M						// 032
		 16, 32, // N						// 033
		 32, 32, // O						// 034
		 48, 32, // P						// 035
		 64, 32, // Q						// 036
		 80, 32, // R						// 037
		 96, 32, // S						// 038
		112, 32, // T						// 039
		128, 32, // U						// 040
		144, 32, // V						// 041
		160, 32, // W						// 042
		176, 32, // X						// 043
		192, 32, // Y						// 044
		208, 32, // Z						// 045
		//////////////////////////////////////////
		240, 32, // :						// 046
		 16, 48, // ?						// 047
		000, 48, // !						// 048
		 48, 48, // .						// 049
		224, 32, // -						// 050
		 32, 48, // "						// 051
		//////////////////////////////////////////
		 64, 48, // O Preview				// 052
		 80, 48, // T Preview				// 053
		 96, 48, // I Preview				// 054
		112, 48, // L Preview				// 055
		128, 48, // J Preview				// 056
		144, 48, // S Preview				// 057
		160, 48, // Z Preview				// 058

	};
	int Level; // Current Level

	int X, Y; // Axis coordinates

	Direction pInput;
	GameState State;

	int Board[WH][WW] = {
		01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,01,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,01,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,01,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,01,
		01,00,00,00,00,00,00,00,00,00,00,01,01,01,01,01,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,00,00,00,00,00,00,00,00,00,00,01,00,00,00,00,
		01,01,01,01,01,01,01,01,01,01,01,01,00,00,00,00,
		31,24,41,24,31,46,00,00,00,00,00,00,00,00,00,00,
		31,28,33,24,38,46,00,00,00,00,00,00,00,00,00,00,
	};
public:
	void DrawSprite(int spriteID, int x, int y) const; // Uses the index of sprites and active bitmap to output a sprite of the current global sprite size
	void DrawBoard() const; // Outputs Board[][] using DrawSprite
	void SetAxis(int x, int y);

	/* Logic functions for main loop*/
	void Draw() const;
	void Input();
	void Logic();

	/* Definitions of constructors and destructors may be changed later */
	Game() { State = BEFORE; pInput = NONE; X = 5, Y = 10; };
	Game(int L) :Level(L) { State = BEFORE; pInput = NONE; X = 5, Y = 10; };
	~Game() { };
};
