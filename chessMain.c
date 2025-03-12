#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD 10

/*
	Authors:
	Class: CS125
	Assignment: Final Project
	Date:
*/

int main()
{
  //initialize board
  
	int board[BOARD][BOARD];5
  int boardMove[BOARD][BOARD];
  int checkSquares[BOARD][BOARD];
	int i;
	int j;	

	for(i=0; i<BOARD; i++)
	{
		for(j=0; j<BOARD; j++)
		{
			board[i][j] = 0;
      boardMove[i][j] = 0;
      checkSquares[i][j] = 0;
		}
	}

	makeBoard(board);
  updateBoard(boardMove, board);
  
  int turn = 1;
 
  //main loop
  board[8][5] = 0;
  board[5][8] = -7;

	printBoardChar(board, turn);
  
  
  /* Example use-case of rayLos
  int coord1[2];
  int coord2[2];
  
  coord1[0] = 1;
  coord1[1] = 2;
  
  int pieceHit = rayLos(board, coord1, coord2, 2, 0);
  
  printf("Peice: %d found at %d, %d.\n", pieceHit, coord2[0], coord2[1]);
  
  coord2[0] = 3;
  coord2[1] = 4;
  
  int legalCheck = rayLos(board, coord1, coord2, 2, 1);
  
  printf("piece found? %d\n", legalCheck);
  */
  
  int check = testCheck(board, turn);
  
  printf("In check? %d\n", check);
  
  // testing direction function
  int pos1[2];
  int pos2[2];
  
  pos1[0] = 8;
  pos1[1] = 8;
  
  pos2[0] = 1;
  pos2[1] = 2;
  
  int dir = testDirection(pos1, pos2);
  printf("Direction: %d\n", dir);

	return 0;
}
