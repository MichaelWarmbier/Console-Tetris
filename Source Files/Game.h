#pragma once
#include "Header.h"

class Game {
private:
	const int Sprites[256][2] {
		000,000, // Background				// 000
		//////////////////////////////////////////
		 16,000, // Dark Gray Tile			// 001
		144,000, // Light Gray Tile			// 002
		 32,000, // Red Tile				// 003
		 48,000, // Cyan Tile				// 004
		 64,000, // Orange Tile				// 005
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
		176, 48, // =						// 059
		192, 48, // NE						// 060
		208, 48, // XT						// 061
		224, 48, // Empty					// 062
	};

	int BlockNums[7] = { 0,0,0,0,0,0,0 }; // Number of times each block has fallen

	int Level; // Current Level
	int LinesC; // Lines Cleared
	int X, Y; // Axis coordinates
	int Rot; // Current rotation 
	double _DropTS; // Time stamp for decrementing block
	double WaitTime; // Variable for game speed
	bool SpeedUp; // Flag for increasing speed
	int MenuSel; // Menu selection

	Direction pInput; // User Input
	
	BlockType CurrBlck; // Current falling block
	BlockType NxtBlck; // Next block to fall

	int Board[WH][WW] = {
		02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,60,61,46,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,00,00,00,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,00,00,00,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,52,02,10,10,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,53,02,10,10,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,54,02,10,10,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,55,02,10,10,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,56,02,10,10,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,57,02,10,10,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,00,00,00,00,00,00,00,00,00,00,02,58,02,10,10,02,
		02,00,00,00,00,00,00,00,00,00,00,02,02,02,02,02,02,
		02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,02,
		02,31,24,41,24,31,46,02,10,10,10,02,02,02,02,02,02,
		02,31,28,33,24,38,46,02,10,10,10,02,02,02,02,02,02,
	};
	int BoardCopy[WH][WW]; // Copy of Board[][] used for comparison when detecting collision
	/* Block Data -- Temporary, may combine */
	const struct B1 {
	public:
		int Limbs[12][2]{
		/*  X,Y   */
		//////////// - Rotation 1
			1,0,
			1,1,
			0,1,
		//////////// - Rotation 2
			1,0,
			1,1,
			0,1,
		//////////// - Rotation 3
			1,0,
			1,1,
			0,1,
		//////////// - Rotation 4
			1,0,
			1,1,
			0,1,
		};
	}; B1 O; // O Block Data
	const struct B2{
		public:
		int Limbs[12][2]{
		/*  X,Y   */
		//////////// - Rotation 1
			0,-1,
			0,1,
			0,2,
		//////////// - Rotation 2
			-1,0,
			1,0,
			2,0,
		//////////// - Rotation 3
			0,-1,
			0,1,
			0,2,
		//////////// - Rotation 4
			-1,0,
			1,0,
			2,0,
		};
	}; B2 I; // I Block Data
	const struct B3 {
		public:
		int Limbs[12][2]{
		/*  X,Y   */
		//////////// - Rotation 1
			-1,0,
			1,0,
			0,1,
		//////////// - Rotation 2
			-1,0,
			0,-1,
			0,1,
		//////////// - Rotation 3
			-1,0,
			1,0,
			0,-1,
		//////////// - Rotation 4
			1,0,
			0,-1,
			0,1,
		};
	}; B3 T; // T Block Data
	const struct B4 {
	public:
		int Limbs[12][2]{
		/*  X,Y   */
		//////////// - Rotation 1
			0,-1,
			0,1,
			1,1,
		//////////// - Rotation 2
			-1,0,
			1,0,
			1,-1,
		//////////// - Rotation 3
			0,-1,
			0,1,
			-1,-1,
		//////////// - Rotation 4
			-1,0,
			1,0,
			-1,1,
		};
	}; B4 L; // L Block Data
	const struct B5 {
		public:
		int Limbs[12][2]{
		/*  X,Y   */
		//////////// - Rotation 1
			0,-1,
			0,1,
			1,-1,
		//////////// - Rotation 2
			-1,0,
			1,0,
			-1,-1,
		//////////// - Rotation 3
			0,-1,
			0,1,
			-1,1,
		//////////// - Rotation 4
			-1,0,
			1,0,
			1,1,
		};
	}; B5 J; // J Block Data
	const struct B6 {
		public:
		int Limbs[12][2]{
		/*  X,Y   */
		//////////// - Rotation 1
			0,1,
			1,0,
			-1,1,
		//////////// - Rotation 2
			-1,0,
			-1,-1,
			0,1,
		//////////// - Rotation 3
			-1,0,
			0,-1,
			1,-1,
		//////////// - Rotation 4
			0,-1,
			1,0,
			1,1,
		};
	}; B6 S; // S Block Data
	const struct B7 {
		public:
		int Limbs[12][2]{
		/*  X,Y   */
		//////////// - Rotation 1
			-1,0,
			0,1,
			1,1,
		//////////// - Rotation 2
			0,-1,
			-1,0,
			-1,1,
		//////////// - Rotation 3
			0,-1,
			-1,-1,
			1,0,
		//////////// - Rotation 4
			1,0,
			1,-1,
			0,1,
		};
	}; B7 Z; // Z Block Data

public:
	bool EXIT_G, EXIT_P; // Exit conditions before being transfered
	GameState State; // State of the game
	bool Pause; // Pause flag

	void DrawSprite(int spriteID, int x, int y) const; // Uses the index of sprites and active bitmap to output a sprite of the current global sprite size
	void DrawBoard() const; // Outputs Board[][] using DrawSprite
	void SetAxis(int x, int y); // Sets the given coordinate to the current axis
	void CopyBoard(); // Copies data of Board to BoardCopy
	bool IsBlockData(const int data) const; // Returns true if given data is associated with block sprites
	void DrawBlock(bool SolidFlag); // Draws CurrBlck at axis
	void ClearBoardCopy(); // Clears inside of the board copy
	void ClearBoard(); // Clears inside of the board
	void SetTile(int x, int y, int ID); // Sets a Board[][] index to given ID
	void BlockTest(); // Tests block drawing
	void DrawNextBlock(); // Draws icon for upcoming block
	void ApplyInput(); // Applies input specifically in logic
	BlockType GetRandomBlock() const; // Returns random BlockType
	bool DecrementBlock(); // Y++
	void DrawPause(); // Draws "Pause" string
	bool IsSolid(Direction Dir); // Collision Check
	void ResetBlock(); // Resets block position to top
	void DrawInteger(int x, int y, int size, int value); // Draw integer of two or three digits at a position
	void LineClear(); // Returns true and clears a line if it can be
	void DrawMenu(); // Draws details for menu
	void SetTileS(int x, int y, const char str[10]); // Sets a string of text as tiles
	void GameOver(); // Begins game over sequence if game has been lost

	/* Logic functions for main loop*/
	void Draw();
	void Input();
	void Logic();

	/* Definitions of constructors and destructors may be changed later */
	Game() { 
		MenuSel = 1;
		State = BEFORE; 
		pInput = NONE;
		X = 5, Y = 2;
		CurrBlck = bX;
		NxtBlck = bX;
		Rot = 0; 
		Level = 1;
		Pause = false;
		LinesC = 0;
		_DropTS = GetTime();
		WaitTime = 1.5;
		SpeedUp = false;
		EXIT_G = false;
		EXIT_P = false;
	};
	~Game() { };
};
