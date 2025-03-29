#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD 10

int findMoves(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int moves[BOARD][BOARD], int turn)
{
  int type;
  
  // turn is -1 for black, 1 for white
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  // var initialization
  int canMove = 0;
  int pinned;
  int i;
  int j;
  int k;
  int squareAttacked;
  int currCoord[2];
  int defender[2];
  defender[0] = 0;
  defender[1] = 0;
  
  // this function requires a second copy of the board
  int board3[BOARD][BOARD];
  
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      board3[i][j] = 0;
    }
  }
  
  // sets board copys equal to current board
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
  
  int dummy[2];
  dummy[0] = 0;
  dummy[1] = 0;
  
  int dummyKing[2];
  dummyKing[0] = 0;
  dummyKing[1] = 0;
  
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
      
      if(moves[i][j] != 0)
      {
        // move enemy king to a check square to see if pieces can capture it, blocking check
        updateBoard(boardMove, board);
        boardMove[kingY][kingX] = 0;
        boardMove[i][j] = -7 * type;
        
        // there can be up to 8 pieces that could block the check, but are pinned, all must be checked
        // each piece that can block check but is pinned is converted to a 9, so the next piece can be found
        
        for(k=0; k<8; k++)
        {
          // ensure king is not considered for blocking check
          boardMove[kingY2][kingX2] = 9;
          
          squareAttacked = testCheck(boardMove, dummyKing, defender, (turn+1));
          
          if(moves[i][j] == 1)
          {
            // eliminates diagonal pawn moves that are not captures from blocking check
            if((boardMove[defender[1]][defender[0]] == type) && (board[i][j] != (type*-4)))
            {
              //printf("Pawn detected, cannot block diagonally, i: %d, j: %d\n", i, j);
              
              boardMove[defender[1]][defender[0]] = 9;
              defender[1] = 0;
              defender[0] = 0;
            }
            
            // if pawn can block 1 forward
            if(boardMove[i + (type*-1)][j] == type)
            {
              defender[1] = i + (type*-1);
              defender[0] = j;
              
              //printf("pawn can block 1\n");
            }
            
            // if pawn can block 2 forward
            if((i == 4) || (i == 5))
            {
              if((boardMove[i + (type*-2)][j] == type) && (boardMove[i + (type*-1)][j] == 0))
              {
                defender[1] = i + (type*-2);
                defender[0] = j;
                
                //printf("pawn can block 2\n");
              }
            }
          }
          
          if(defender[0] != 0)
          {
            
            boardMove[kingY2][kingX2] = type * 7;
            pinned = testPin(boardMove, board3, defender, dummyKing);
            
            if(pinned == 0)
            {
              canMove++;
              breakCondition = 1;
              //printf("Piece found, loop terminated\n");
              //printf("un-pinned piece at: %d, %d\n", defender[0], defender[1]);
              
              break;
            }
            else
            {
              boardMove[defender[1]][defender[0]] = 9;
              
              //printf("pinned piece at: %d, %d\n", defender[0], defender[1]);
            }
          }
        }
        
        boardMove[i][j] = 0;
      }
    }
  }
  

  return canMove;
}
