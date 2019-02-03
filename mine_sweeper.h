#ifndef MINESWEEPER_H
	#define MINESWEEPER_H

	void makeboard(Board* minesweeper);
	void makesecondboard(int*** board,Board minesweeper);
	void freeboard(Board* minesweeper);
	void freenumboard(int*** board,Board minesweeper);
	void userinput(Board minesweeper,Userinput* user);
	void useractioninput(int* action,Board minesweeper,Userinput user);
	int actiondetect(Board minesweeper,Userinput user);
	int questionmarkoption(Board minesweeper,Userinput user);
	int markoption(Board minesweeper,Userinput user);
	int gameover(Board minesweeper,int** board);
	void setmines(Board* minesweeper,int* row,int* col);
	void minedetect(Board minesweeper);
	void board_set(int** board,Board minesweeper,int* row,int* col);
	void board_play(Board* minesweeper,int** board,int rowx,int coly);
	bool samepoints(Board* minesweeper,int rownum,int colnum,int*row,int*col);
	void action_execute(int action,Board minesweeper,int** board,Userinput user,int* row,int* col);
	bool ismine(Board* minesweeper,Userinput user,int* row,int* col);
	void questionplacer(Board* minesweeper,Userinput user);
	void markplacer(Board* minesweeper,Userinput user);
	void reveal(Board* minesweeper,int** board, Userinput user,int* row,int* col);
	bool validAction(int argumentneed,int argumentget,int action);
	bool validsideAction(int argumentneed,int argumentget,int action);
	bool validMove(int argumentneed, int argumentget,Board minesweeper,Userinput* user);

#endif