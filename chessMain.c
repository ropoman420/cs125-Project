#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD 10

/*
	Authors:
	Class: CS125
	Assignment: Final Project
	Date:
*/

int main()
{
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  //initialize board
  
	int board[BOARD][BOARD];
  int boardMove[BOARD][BOARD];
  int board3[BOARD][BOARD];
  int checkSquares[BOARD][BOARD];
	int i;
	int j;	

	for(i=0; i<BOARD; i++)
	{
		for(j=0; j<BOARD; j++)
		{
			board[i][j] = 0;
      board3[i][j] = 0;
      boardMove[i][j] = 0;
      checkSquares[i][j] = 0;
		}
	}
  
  // list of all legal moves
  int moveList[250];
  for(i=0; i<250; i++)
  {
    moveList[i] = 0;
  }

	makeBoard(board);
  updateBoard(boardMove, board);
  
  int turn = 1;
  
  // mate in 2
  
  //clear board
  /*
  for(i=1; i<9; i++)
  {
    for(j=1; j<9; j++)
    {
      board[i][j] = 0;
    }
  }
  
  board[6][8] = -7;
  board[1][4] = 7;
  
  board[3][3] = -2;
  */
  
  /*
  board[1][2] = 5;
  board[1][6] = 3;
  board[1][7] = 2;
  board[3][2] = -1;
  board[3][5] = 7;
  board[4][1] = -5;
  board[4][2] = 1;
  board[4][3] = 1;
  board[4][7] = -1;
  board[6][1] = -3;
  board[6][2] = -1;
  board[6][8] = 5;
  board[7][4] = -7;
  board[7][5] = 1;
  board[8][8] = 3;
  */
  
	//printBoardChar(board, turn);
  
  int checkCoords[2];
  checkCoords[0] = 0;
  checkCoords[1] = 0;
  
  int kingCoords[2];
  kingCoords[0] = 0;
  kingCoords[1] = 0;
  
  int check = testCheck(board, kingCoords, checkCoords, turn);
  
  printf("In check? %d\nCheck from: %d, %d\n", check, checkCoords[0], checkCoords[1]);
  printf("King Coords: %d, %d\n", kingCoords[0], kingCoords[1]);
  
  int dir = testDirection(kingCoords, checkCoords);
  printf("Direction: %d\n", dir);
  
  getCheckSquares(board, kingCoords, checkCoords, checkSquares);
  
  int mate = testMate(board, boardMove, checkSquares, turn);
  
  printf("Mate? %d\n", mate);
  
  // engine testing
  
  int score = scoreDif(board, boardMove, turn);
  printf("Points: %d\n", score);
  
  //int botMove = bestMove(board, boardMove, board3, turn);
  //printf("Bot Move: %d\n", botMove);
  
  int botMove2; /*= engineRecursion(board, boardMove, board3, turn, 1);*/
  //printf("Bot Move (recursion): %d\n", botMove2);

  printBoardChar(board, turn);
  
  // engine playing itself
  
  int currPos[2];
  int currMove[2];
  int playerInput;
  
  // if input is made 0, engine plays itself
  int input = 0;
  
  // example of player playing engine, no error check or prompts. Example move: 1213 -> pawn A2 to A3
  //botMove2 = engineRecursion(board, boardMove, board3, turn, 2);
  /*
  moves(board, boardMove, moveList, turn);
  
  i=0;
  while(moveList[i] != 0)
  {
    printf("%d\n", moveList[i]);
    i++;
  }
  */
  //printBoardNum(board);
  
  //botMove2 = engineRecursion(board, boardMove, board3, turn+1, 0);
  
  
  
  while((botMove2 != 0) && (turn < 350))
  {
    botMove2 = engineRecursion(board, boardMove, board3, turn, 1);
    
    if(botMove2 > 0)
    {
    
      currPos[0] = 0;
      currPos[1] = 0;
      currMove[0] = 0;
      currMove[1] = 0;
      
      if((turn % 2 == 1) || (input == 0))
      {
        intToMove(botMove2, currPos, currMove);
      }
      else
      {
        scanf("%d", &playerInput);
        intToMove(playerInput, currPos, currMove);
      }
      
      makeMoveTest(board, currPos, currMove);
      printf("Bot Move (recursion): %d\n", botMove2);
      
      printBoardChar(board, 1);
      turn++;
    }
  }
  
  int pos[2];
  int pos2[2];

  pos[0] = 5;
  pos[1] = 2;
  
  /*
  pos2[0] = 5;
  pos2[1] = 3;
  int legalTest = checkLegalTest(board, boardMove, pos, pos2, turn);
  
  printf("legal? %d\n", legalTest);
  */


  
  /*
  int direction[2] = {0, 0};
  int pieceX = 5;
  int pieceY = 6;
  
  pinDirection(board, boardMove, pieceX, pieceY, turn, direction);
  
  printf("direction to pinning piece: %d, %d\n", direction[0], direction[1]);
  */
  
  //rayLegal(board, moveList, pos, 1, 1, 1);
  
  

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Time taken: %f seconds\n", cpu_time_used);

	return 0;
}
