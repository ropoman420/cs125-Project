#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD 10


/*
  This program was primarily written by Roman and Ellis
  Debugging by Ellis and Roman
  Comments by Caleb Groover
  
  This program finds a legal move set for the King to make
  in order to get out of an existing check
*/


//This function finds a legal move set for the King to make in order to get out of an existing check
int findMoves(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int moves[BOARD][BOARD], int moveList[], int turn)
{
  int type;
  
  //Turn is -1 for black, 1 for white
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  //Variable initialization
  int canMove = 0;
  int pinned;
  int i;
  int j;
  int k;
  int squareAttacked;
  int currCoord[2];
  int defender[2] = {0, 0};
  
  //This function requires a second copy of the board (generated here)
  int board3[BOARD][BOARD];
  
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      board3[i][j] = 0;
    }
  }
  
  //This sets the board copy equal to current board
  updateBoard(board3, board);
  updateBoard(boardMove, board);
  
  int enemyKing[2];
  int king[2];
  
  findKing(board, (type*-1), enemyKing);
  findKing(board, type, king);
  
  int kingX = enemyKing[0];
  int kingY = enemyKing[1];
  
  int kingX2 = king[0];
  int kingY2 = king[1];
  
  int dummy[2] = {0, 0};
  int dummyKing[2] = {0, 0};
  
  int movingTo[2] = {0, 0};
  
  int breakCondition = 0;
  
  for(i=1; i<9; i++)
  {
    if(breakCondition == 1)
    {
      break;
    }
    
    for(j=1; j<9; j++)
    {
      if(breakCondition == 1)
      {
        break;
      }
      
      movingTo[0] = j;
      movingTo[1] = i;
      
      if(moves[i][j] != 0)
      {
        //This moves the enemy king to a check square to see if pieces can capture it, blocking check
        updateBoard(boardMove, board);
        boardMove[kingY][kingX] = 0;
        boardMove[i][j] = -7 * type;
        
        
        /*There can be up to 8 pieces that could block the check, but are pinned, all must be checked.
        Each piece that can block check but is pinned is converted to a 9, so the next piece can be found*/
        for(k=0; k<8; k++)
        {
          //This ensures that the King is not considered for blocking check
          boardMove[kingY2][kingX2] = 9;
          
          squareAttacked = testCheck(boardMove, dummyKing, defender, (turn+1));
          
          if(moves[i][j] == 1)
          {
            //This eliminates diagonal pawn moves that are not captures from blocking check
            if((boardMove[defender[1]][defender[0]] == type) && (board[i][j] != (type*-4)))
            {
              boardMove[defender[1]][defender[0]] = 9;
              defender[1] = 0;
              defender[0] = 0;
            }
            
            //This checks if a pawn can block 1 forward
            if(boardMove[i + (type*-1)][j] == type)
            {
              defender[1] = i + (type*-1);
              defender[0] = j;
            }
            
            //This checks if a pawn can block 2 forward
            if((i == 4) || (i == 5))
            {
              if((boardMove[i + (type*-2)][j] == type) && (boardMove[i + (type*-1)][j] == 0))
              {
                defender[1] = i + (type*-2);
                defender[0] = j;
              }
            }
          }
          
          //This checks to see if a piece is stuck adjacent to the King and not allowed to move
          if(defender[0] != 0)
          {
            
            boardMove[kingY2][kingX2] = type * 7;
            pinned = testPin(boardMove, board3, defender, dummyKing);
            
            if(pinned == 0)
            {
              canMove++;
              
              addToList(moveList, moveToInt(defender, movingTo));
              
              boardMove[defender[1]][defender[0]] = 9;
            }
            else
            {
              boardMove[defender[1]][defender[0]] = 9;
            }
          }
        }
        
        boardMove[i][j] = 0;
      }
    }
  }
  

  return canMove; /*Function/program return the validity of whether a King can move to a tile or not*/
}
