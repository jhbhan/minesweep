#ifndef BOARD_PRINT_H
	#define BOARD_PRINT_H

	typedef struct Board_struct{
		int row;
		int column;
		int numofmines;
		int randomnum;
		char** board;
	} Board;

	typedef struct Userinput_struct {
		int userrow;
		int usercolumn;
	} Userinput;
	
	void printboard(Board minesweeper);
	void printnumboard(int** board,Board minesweeper);
	void printloseboard(Board minesweeper,int** board);

#endif