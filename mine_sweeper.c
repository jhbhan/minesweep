#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "board_print.h"
#include "mine_sweeper.h"

int main(int argc,char* argv[]) {

	if (argc > 5) {
		printf("Too many arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])");
		exit(0);
	}
	else if (argc < 5) {
		printf("Not enough arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])");
		exit(0);
	}

	Board minesweeper;
	minesweeper.board = NULL;
	Userinput user;
	int** board = NULL;
	int action;

	sscanf(argv[1],"%d",&minesweeper.row);
	sscanf(argv[2],"%d",&minesweeper.column);
	sscanf(argv[3],"%d",&minesweeper.numofmines);
	sscanf(argv[4],"%d",&minesweeper.randomnum);
 	
 	int* row = NULL;
 	int* col = NULL;

 	row = (int*)malloc(minesweeper.numofmines+1*sizeof(int));
 	col = (int*)malloc(minesweeper.numofmines+1*sizeof(int));

 	for (int i = 0; i < minesweeper.numofmines; i++) {
 		row[i] = minesweeper.row;
 	}

 	for (int k = 0; k < minesweeper.numofmines; k++) {
 		col[k] = minesweeper.column;
 	}

	makeboard(&minesweeper);
	makesecondboard(&board,minesweeper);

	setmines(&minesweeper,row,col);
	board_set(board,minesweeper,row,col);
	minedetect(minesweeper);
	printboard(minesweeper);

	while(gameover(minesweeper,board) != 0 && gameover(minesweeper,board) != 1) {
		userinput(minesweeper,&user);
		if (actiondetect(minesweeper,user) == 0){ 
			useractioninput(&action,minesweeper,user);
			action_execute(action,minesweeper,board,user,row,col);
			if (action == 0 && minesweeper.board[user.userrow][user.usercolumn] == '*') {
				break;
			}
			else if (gameover(minesweeper,board) == 1) {
				break;
			}
			else {
				minedetect(minesweeper);
				printboard(minesweeper);
			}
		}
		else if (actiondetect(minesweeper,user) == 1) {

			if (questionmarkoption(minesweeper,user) == 1) {
				minedetect(minesweeper);
				printboard(minesweeper);
			}
			
		}
		else if (actiondetect(minesweeper,user) == 2) {

			if (markoption(minesweeper,user) == 1) {
				minedetect(minesweeper);
				printboard(minesweeper);
			}

		}
		else if (actiondetect(minesweeper,user) == 3) {
			printf("This tile is already revealed.\n");
		}
		
	} 

	if (gameover(minesweeper,board) == 0) {	
		printloseboard(minesweeper,board);
		printf("You Lost :(");
	}
	else if(gameover(minesweeper,board) == 1) {
		printloseboard(minesweeper,board);
		printf("You Won!!");
	}

	freeboard(&minesweeper);
	freenumboard(&board,minesweeper);
	
	return 0;
}

void freeboard(Board* minesweeper) {

	for (int i = 0; i < minesweeper->row; i++) {
		free(minesweeper->board[i]);
	}
	free(minesweeper->board);

	return;
}

void freenumboard(int*** board,Board minesweeper) {

	for (int i = 0; i < minesweeper.row; i++) {
		free((*board)[i]); 
	}
	free(*board);

	return;
}
void userinput(Board minesweeper,Userinput* user) {

	int argumentget;

	do {
	printf("Enter row a row between 0-%d and a column between 0-%d: ",minesweeper.row-1,minesweeper.column-1);
	argumentget = scanf("%d %d",&user->userrow,&user->usercolumn);
	} while(!validMove(2,argumentget,minesweeper,user));
	user->userrow = abs(user->userrow-(minesweeper.row-1));

	return;
}

bool validMove(int argumentneed, int argumentget,Board minesweeper,Userinput* user) {

	char lastchar;
	bool validinput;

	do {
		scanf("%c",&lastchar);
		if (!isspace(lastchar)) {
			validinput = false;
		}
	} while(lastchar != '\n');

	if (argumentneed != argumentget) {
		validinput = false;
	}

	else if(user->userrow <= minesweeper.row - 1 && user->userrow >= 0 && user->usercolumn <= minesweeper.column-1 && user->usercolumn >= 0 ) {
		validinput = true;
	}

	else {
		validinput = false;
	}

	return validinput;
}

void useractioninput(int* action,Board minesweeper,Userinput user){

	int argumentget;

	printf("Enter Action\n");
	printf("0. Reveal\n");
	printf("1. Question\n");
	printf("2. Mark\n");
	printf("3. Cancel\n");
	printf("Action: ");
	argumentget = scanf("%d",action);
	
	if (!validAction(1,argumentget,*action)) {
		userinput(minesweeper,&user);
		useractioninput(action,minesweeper,user);
	}

	return;
}

bool validAction(int argumentneed,int argumentget,int action) {
	
	char lastchar;
	bool validinput = true;

	do {
		scanf("%c",&lastchar);
		if (!isspace(lastchar)) {
			validinput = false;
		}
	} while(lastchar != '\n');

		if (argumentneed != argumentget) {
			validinput = false;
		}

		else if(action != 0 && action != 1 && action != 2 && action != 3) {
			validinput = false;
		}

		else {
			validinput = true;
		
	}
	

	return validinput;
}

int actiondetect(Board minesweeper,Userinput user) {

	if (minesweeper.board[user.userrow][user.usercolumn] == '#') {
		return 0;
	}
	else if (minesweeper.board[user.userrow][user.usercolumn] == '?') {
		return 1;
	}
	else if (minesweeper.board[user.userrow][user.usercolumn] == '!') {
		return 2;
	}
	else {
		return 3;
	}

	return 0;
}


int questionmarkoption(Board minesweeper,Userinput user) {

	int action;
	int argumentget;

	do {
		printf("Enter Action\n");
		printf("0. UnQuestion\n");
		printf("1. Cancel\n");
		printf("Action: ");
		argumentget = scanf("%d",&action);
	} while (validsideAction(1,argumentget,action) == false);
	

	if (action == 0) {
		minesweeper.board[user.userrow][user.usercolumn] = '#';
		return 1;
	}
	else if (action == 1) {
		return 0;
	}

	return 0;
}

bool validsideAction(int argumentneed,int argumentget,int action) {
	
	char lastchar;
	bool validinput;

	do {
		scanf("%c",&lastchar);
		if (!isspace(lastchar)) {
			validinput = false;
		}
	} while(lastchar != '\n');

	if (argumentneed != argumentget) {
		validinput = false;
	}

	else if(action != 0 && action != 1) {
		validinput = false;
	}

	else {
		validinput = true;
	}

	return validinput;
}

int markoption(Board minesweeper,Userinput user) {

	int action;
	int argumentget;

	do {
		printf("Enter Action\n");
		printf("0. UnMark\n");
		printf("1. Cancel\n");
		printf("Action: ");
		argumentget = scanf("%d",&action);
	} while (validsideAction(1,argumentget,action) == false);
	

	if (action == 0) {
		minesweeper.board[user.userrow][user.usercolumn] = '#';
		return 1;
	}
	else if (action == 1) {
		return 0;
	}

	return 0;
}


int gameover(Board minesweeper,int** board) {

	int n = 0;

	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k++) {
			if (minesweeper.board[i][k] == '*') {
				return 0;
			}
		}
	}

	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k++) {
			if ((minesweeper.board[i][k] == '!' && board[i][k] >= 9)) {
				n = n + 1;
			} 
			else if (minesweeper.board[i][k] == '#' || minesweeper.board[i][k] == '?' || minesweeper.board[i][k] == '!') {
				return 2;
			}
		}
	}

	if (n == minesweeper.numofmines) {
		return 1;
	}

	return 2;
}

void board_set(int** board,Board minesweeper,int* row,int* col) {

	for (int i = 0; i < minesweeper.row;i++) {
		for (int k = 0; k < minesweeper.column;k++) {
			for (int g = 0; g < minesweeper.numofmines; g++) {
				if (minesweeper.row == 1 && k != 0 && k!= minesweeper.column-1 && i == row[g] && k == col[g]) {
					board[i][k] = 9;
					board[i][k-1] = board[i][k-1] + 1;
					board[i][k+1] = board[i][k+1] + 1;
				}
				else if (minesweeper.row == 1 && k == 0 && i == row[g] && k == col[g]) {
					board[i][k] = 9;
					board[i][k+1] = board[i][k+1] + 1;
				}
				else if (minesweeper.row == 1 && k == minesweeper.column-1 && i == row[g] && k == col[g]) {
					board[i][k] = 9;
					board[i][k-1] = board[i][k-1] + 1;
				}
				else if (i == row[g] && k == col[g] && k != 0 && k!= minesweeper.column-1 && i!= 0 && i!= minesweeper.row-1 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i+1][k] =  board[i+1][k] + 1;
					board[i+1][k - 1] =  board[i+1][k - 1] + 1;
					board[i+1][k + 1] =  board[i+1][k + 1] + 1;
					board[i][k - 1] =  board[i][k - 1] + 1;
					board[i][k + 1] =  board[i][k + 1] + 1;
					board[i-1][k] =  board[i-1][k] + 1;
					board[i-1][k - 1] =  board[i-1][k - 1] + 1;
					board[i-1][k + 1] =  board[i-1][k + 1] + 1;
				}
				else if (i == row[g] && k == col[g] && k == 0 && i != 0 && i != minesweeper.row-1 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i+1][k] =  board[i+1][k] + 1;
					board[i+1][k + 1] =  board[i+1][k + 1] + 1;
					board[i][k + 1] =  board[i][k + 1] + 1;
					board[i-1][k] =  board[i-1][k] + 1;
					board[i-1][k + 1] =  board[i-1][k + 1] + 1;
				}
				else if (i == row[g] && k == col[g] && k == minesweeper.column-1 && i != 0 && i != minesweeper.row-1 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i+1][k] =  board[i+1][k] + 1;
					board[i+1][k - 1] =  board[i+1][k - 1] + 1;
					board[i][k - 1] =  board[i][k - 1] + 1;
					board[i-1][k] =  board[i-1][k] + 1;
					board[i-1][k - 1] =  board[i-1][k - 1] + 1;
				}
				else if (i == row[g] && k == col[g] && i == 0 && k != 0 && k != minesweeper.column-1 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i+1][k] =  board[i+1][k] + 1;
					board[i+1][k - 1] =  board[i+1][k - 1] + 1;
					board[i+1][k + 1] =  board[i+1][k + 1] + 1;
					board[i][k - 1] =  board[i][k - 1] + 1;
					board[i][k + 1] =  board[i][k + 1] + 1;
				}
				else if (i == row[g] && k == col[g] && i == minesweeper.row-1 && k != 0 && k != minesweeper.column-1 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i][k - 1] =  board[i][k - 1] + 1;
					board[i][k + 1] =  board[i][k + 1] + 1;
					board[i-1][k] =  board[i-1][k] + 1;
					board[i-1][k - 1] =  board[i-1][k - 1] + 1;
					board[i-1][k + 1] =  board[i-1][k + 1] + 1;
				}
				else if (i == row[g] && k == col[g] && i == 0 && k == 0 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i+1][k] =  board[i+1][k] + 1;
					board[i+1][k + 1] =  board[i+1][k + 1] + 1;
					board[i][k + 1] =  board[i][k + 1] + 1;
				}
				else if (i == row[g] && k == col[g] && i == minesweeper.row-1 && k == 0 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i-1][k] =  board[i-1][k] + 1;
					board[i-1][k + 1] =  board[i-1][k + 1] + 1;
					board[i][k + 1] =  board[i][k + 1] + 1;
				}
				else if (i == row[g] && k == col[g] && i == 0 && k == minesweeper.column-1 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i+1][k] =  board[i+1][k] + 1;
					board[i+1][k-1] =  board[i+1][k-1] + 1;
					board[i][k-1] =  board[i][k-1] + 1;
				}
				else if (i == row[g] && k == col[g] && i == minesweeper.row-1 && k == minesweeper.column-1 && minesweeper.row > 1) {
					board[i][k] = 9;
					board[i][k-1] =  board[i][k-1] + 1;
					board[i-1][k-1] =  board[i-1][k-1] + 1;
					board[i-1][k] =  board[i-1][k] + 1;
				}

			}
		}
	}

	return;
}

void board_play(Board* minesweeper,int** board,int rowx,int coly) {

	if (rowx < 0 || rowx > minesweeper->row-1 || coly < 0 || coly > minesweeper->column-1) {
		return;
	}
	if (board[rowx][coly] != 0 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
		if (board[rowx][coly] == 1) {
			minesweeper->board[rowx][coly] = '1';
			return;
		}
		else if (board[rowx][coly] == 2 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
			minesweeper->board[rowx][coly] = '2';
			return;
		}
		else if (board[rowx][coly] == 3 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
			minesweeper->board[rowx][coly] = '3';
			return;
		}
		else if (board[rowx][coly] == 4 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
			minesweeper->board[rowx][coly] = '4';
			return;
		}
		else if (board[rowx][coly] == 5 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
			minesweeper->board[rowx][coly] = '5';
			return;
		}
		else if (board[rowx][coly] == 6 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
			minesweeper->board[rowx][coly] = '6';
			return;
		}
		else if (board[rowx][coly] == 7 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
			minesweeper->board[rowx][coly] = '7';
			return;
		}
		else if (board[rowx][coly] == 8 && minesweeper->board[rowx][coly] != '?' && minesweeper->board[rowx][coly] != '!') {
			minesweeper->board[rowx][coly] = '8';
			return;
		}	
	}
	else if (board[rowx][coly] == 0 && minesweeper->board[rowx][coly] == '#') {
		minesweeper->board[rowx][coly] = '0';
		board_play(minesweeper,board,rowx-1,coly);
		board_play(minesweeper,board,rowx,coly-1);
		board_play(minesweeper,board,rowx-1,coly-1);
		board_play(minesweeper,board,rowx-1,coly+1);
		board_play(minesweeper,board,rowx+1,coly-1);
		board_play(minesweeper,board,rowx+1,coly+1);
		board_play(minesweeper,board,rowx+1,coly);
		board_play(minesweeper,board,rowx,coly+1);
	}

	return;
} 

void action_execute(int action,Board minesweeper,int** board,Userinput user,int* row,int* col) {

	if (action == 0) {
		reveal(&minesweeper,board,user,row,col);
	}
	else if (action == 1) {
		questionplacer(&minesweeper,user);
	}
	else if (action == 2) {
		markplacer(&minesweeper,user);
	}
	else if (action == 3) {
		return;
	}

	return;
}


void reveal(Board* minesweeper,int** board, Userinput user,int* row,int* col) {

	int rowx = user.userrow;
	int coly = user.usercolumn;

	for (int i = 0; i < minesweeper->row; i++) {
		for (int k = 0; k < minesweeper->column; k++) {
			if (i == user.userrow && k == user.usercolumn) {

				if (ismine(minesweeper,user,row,col)) {
					minesweeper->board[i][k] = '*';
				}
				else {
					board_play(minesweeper,board,rowx,coly);
				}

			}
		}
	}

	return;
}

bool ismine(Board* minesweeper,Userinput user,int* row,int* col) {

	for (int i = 0; i < minesweeper->numofmines; i++) {
		if (user.userrow == row[i] && user.usercolumn == col[i]) {
			return true;
		}
	}

	return false;
}

void minedetect(Board minesweeper) {

	int n = 0;

	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k++) {
			if (minesweeper.board[i][k] == '!') {
				n++;
			}
		}
	}

	printf("There are %d mines left\n",minesweeper.numofmines - n);

	return;
}

void questionplacer(Board* minesweeper,Userinput user) {
	for (int i = 0; i < minesweeper->row; i++) {
		for (int k = 0; k < minesweeper->column; k++) {
			if (i == user.userrow && k == user.usercolumn) {
				minesweeper->board[i][k] = '?';
			}
		}
	}

	return;
}

void markplacer(Board* minesweeper,Userinput user) {
	for (int i = 0; i < minesweeper->row; i++) {
		for (int k = 0; k < minesweeper->column; k++) {
			if (i == user.userrow && k == user.usercolumn) {
				minesweeper->board[i][k] = '!';
			}
		}
	}

	return;
}

void makeboard(Board* minesweeper) {

	minesweeper->board = (char**)malloc(minesweeper->row*sizeof(char*));

	for (int i = 0; i< minesweeper->row; i++) {
		minesweeper->board[i] = (char*)malloc(minesweeper->column*sizeof(char));
	}
	
	for (int i = 0; i < minesweeper->row; i++) {
		for (int k = 0; k < minesweeper->column; k ++) {
				minesweeper->board[i][k] = '#';
			}
		}

	return;
}

void makesecondboard(int*** board,Board minesweeper) {

	*board = (int**)malloc(minesweeper.row*sizeof(int*));

	for (int i = 0; i< minesweeper.row; i++) {
		(*board)[i] = (int*)malloc(minesweeper.column*sizeof(int));
	}
	
	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k ++) {
				(*board)[i][k] = 0;
			}
		}

	return;
}




void setmines(Board* minesweeper,int* row,int* col) {

	srand(minesweeper->randomnum);
	int rownum;
	int colnum;

	for (int k = 0; k < minesweeper->numofmines; k++) {
		do {
			rownum = rand()%(minesweeper->row);
			colnum = rand()%(minesweeper->column);
		} while(samepoints(minesweeper,rownum,colnum,row,col) == false);
		printf("Placing mine at %d, %d\n",rownum,colnum);
		row[k] = rownum;
		col[k] = colnum;
		
	}
	
	for (int i = 0; i < minesweeper->numofmines; i++) {
		row[i] = abs(row[i]-(minesweeper->row-1));
	}
			

	return;
}

bool samepoints(Board* minesweeper,int rownum,int colnum,int*row,int*col) {
	for (int i = 0; i < minesweeper->numofmines; i++) {
			if (row[i] == rownum && col[i] == colnum) {
				return false;
			}
		}

	return true;
} 	