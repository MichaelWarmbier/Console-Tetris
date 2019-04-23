#pragma once
//////////////
// Enumerators
//////////////
enum input {RL, RR, UP, DOWN, LEFT, RIGHT, ENTER, BACK, NONE};
enum state {BEFORE, DURING, AFTER, LIMBO};

/////////
// Arrays
/////////
const char logo[5][22]{
	"ttt eee TTT rrr i sss",
	" t  e    T  r r   s  ",
	" t  eee  T  rr  i  s ",
	" t  e    T  r r i   s",
	" t  eee  T  r r i sss",
};
char tetris_board[20][21]{
	"#**********#########",
	"#          # Next: #",
	"#          #   b   #",
	"#          #########",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"############",
};
char tetris_board_copy[20][21]{
	"#**********#########",
	"#          # Next: #",
	"#          #   b   #",
	"#          #########",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"#          #",
	"############",
};
