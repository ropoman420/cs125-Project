

#include "Chess.h"

/*
  This code was programmed by Caleb before
  it was moved elsewhere. We are 99% sure that
  this is derelict and non-functional, 
  but we are too scared to remove it.
  Comments and code by Caleb Groover.
*/

void pieceMove(int i, int j, int pieceVal, int turn, int board[BOARD][BOARD], int moveFrom[2], int moveTo[2])
{
  int newX = 0;  /*new x position from user input*/
  int newY = 0;  /*new y position from user input*/
  int validMove = 0;  //return value from legalMove.c program
    
  printf("What column would you like your new piece to be in (A for 1, B for 2, etc.)?: \n");
  scanf("%d", &newX);
  printf("What row would you like your new piece to be in?: \n");
  scanf("%d", &newY);

  validMove = legalMove(i, j, newX, newY, turn, board, moveFrom, moveTo);
  
  while(validMove == 0)
  {
    printf("This is not a legal move. Please try again.\n");
    validMove = legalMove(i, j, newX, newY, turn, board, moveFrom, moveTo);  //repeats the legalMove function until a legal input is made
  }
  

  board[i][j] = 0;    //Alter the previously occupied space to become empty
  board[newX][newY] = pieceVal; //Alters the newly occupied space to reflect the piece's value
    
  /*printBoard function to display new board (since function returns void otherwise*/ //I DON'T THINK THIS IS NECESSARY WILL DELETE IF ALL IN AGREEMENT

  
}