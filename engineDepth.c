#include <stdio.h>
#include <stdlib.h>

#define BOARD 10

//recursively analyzes best move
// this function is very slow and will be replaced, but works quickly up to a depth of 2 moves into the future

int engineRecursion(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int board3[BOARD][BOARD], int turn, int depth)
{
  int engineDepthMove = 0;
  int i, j, k, l, a;
  int currPos[2];
  int currMove[2];
  int loopPos[2];
  int loopMove[2];
  int engineVal;
  int moveScore;
  int type;
  int legal;
  
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  // 4th board copy
  int board4[BOARD][BOARD];
  
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      board4[i][j] = 0;
    }
  }
  
  // checkmate variables
  int checkCoords[2];
  int kingCoords[2];
  
  int check;
  int mate;
  
  int checkSquares[BOARD][BOARD];
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      checkSquares[i][j] = 0;
    }
  }
  
  int scoreMax = -10000;
  int moveMax = 0;
  
  // run every possible move
  for(i=1; i<9; i++)
  {
    for(j=1; j<9; j++)
    {
      if((board[i][j] * type > 0)  && ((board[i][j] != 4) || (board[i][j] != -4)))
      {
        loopPos[0] = j;
        loopPos[1] = i;
        
        for(k=1; k<9; k++)
        {
          for(l=1; l<9; l++)
          {
            loopMove[0] = l;
            loopMove[1] = k;
            
            legal = checkLegalTest(board, boardMove, loopPos, loopMove, turn);
          
            if(legal == 1)
            {
              updateBoard(boardMove, board);
              
              makeMoveTest(boardMove, loopPos, loopMove);
              moveScore = 0;
              
              //execute best moves at current depth -1 and chose the one with the best outcome
              for(a=0; a<=depth; a++)
              {
                if(depth == 0)
                {
                  engineVal = bestMove(boardMove, board3, board4, (turn+a+1));
                }
                else
                {
                  engineVal = engineRecursion(boardMove, board3, board4, (turn+a+1), (depth-1));
                }
                
                if(engineVal == 0)
                {
                  //printf("Future game end: %d\n", a);
                  if(a % 2 == 0)
                  {
                    moveScore = (depth-a+1) * 1000;
                    break;
                  }
                  else
                  {
                    moveScore = (depth-a+1) * -1000;
                    break;
                  }
                }
                else
                {
                  intToMove(engineVal, currPos, currMove);
                  makeMoveTest(boardMove, currPos, currMove);
                  //printBoardChar(boardMove, turn);
                }
              }
              
              // if no checkmate, evaluate based on point differential
              if(moveScore == 0)
              {
                moveScore = scoreDif(boardMove, board3, turn);
              }
              
              // determine of move is best
              if(moveScore >= scoreMax)
              {
                scoreMax = moveScore;
                moveMax = moveToInt(loopPos, loopMove);
                
                //printf("new Best Move! %d, %d\n", moveMax, scoreMax);
                
                //printBoardChar(boardMove, turn);
              }
            }
          }
        }
      }
    }
  }
  return moveMax;
}