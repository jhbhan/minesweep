#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "board_print.h"

void printboard(Board minesweeper) {
	
	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k ++) {
			if (k == 0){
				printf("%d %c",minesweeper.row-(i+1),minesweeper.board[i][k]);
			}
			else{
				printf(" ");
				printf("%c",minesweeper.board[i][k]);
			}
		}
		printf("\n");
	}
	
	for (int i = 0; i <= minesweeper.column; i++) {
		if (i == 0){
			printf("  ");
		}
		else {
			printf("%d ",i-1);
		}
			
	}
	printf("\n");
	return;
}

void printloseboard(Board minesweeper,int** board){

	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k ++) {
			if (board[i][k] >= 9) {
				minesweeper.board[i][k] = '*';
			}
			else if (board[i][k] == 0) {
				minesweeper.board[i][k] = '0';
			}
			else if (board[i][k] == 1) {
				minesweeper.board[i][k] = '1';
			}
			else if (board[i][k] == 2) {
				minesweeper.board[i][k] = '2';
			}
			else if (board[i][k] == 3) {
				minesweeper.board[i][k] = '3';
			}
			else if (board[i][k] == 4) {
				minesweeper.board[i][k] = '4';
			}
			else if (board[i][k] == 5) {
				minesweeper.board[i][k] = '5';
			}
			else if (board[i][k] == 6) {
				minesweeper.board[i][k] = '6';
			}
			else if (board[i][k] == 7) {
				minesweeper.board[i][k] = '7';
			}
			else if (board[i][k] == 8) {
				minesweeper.board[i][k] = '8';
			}
		}
	}

	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k ++) {
			if (k == 0){
				printf("%d %c",minesweeper.row-(i+1),minesweeper.board[i][k]);
			}
			else{
				printf(" ");
				printf("%c",minesweeper.board[i][k]);
			}
		}
		printf("\n");
	}
	
	for (int i = 0; i <= minesweeper.column; i++) {
		if (i == 0){
			printf("  ");
		}
		else {
			printf("%d ",i-1);
		}
			
	}
	printf("\n");
	return;
}

void printnumboard(int** board,Board minesweeper) {
	for (int i = 0; i < minesweeper.row; i++) {
		for (int k = 0; k < minesweeper.column; k ++) {
			if (k == 0){
				printf("%d %c",minesweeper.row-(i+1),minesweeper.board[i][k]);
			}
			else{
				printf(" ");
				printf("%d",board[i][k]);
			}
		}
		printf("\n");
	}
	
	for (int i = 0; i <= minesweeper.column; i++) {
		if (i == 0){
			printf("  ");
		}
		else {
			printf("%d ",i-1);
		}
			
	}
	printf("\n");
	return;
}