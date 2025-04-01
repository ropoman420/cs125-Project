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
  int moveList[250];
  
  for(i=0; i<250; i++)
  {
    moveList[i] = 0;
  }
  
  updateBoard(boardMove, board);
  //printf("1\n");
  moves(board, boardMove, moveList, turn);
  //printf("2\n");
  /*
  j=0;
      while(moveList[j] != 0)
      {
        printf("%d\n", moveList[j]);
        j++;
      }
  printf("----------\n");
  */
  // run every possible move
  int tempMove = 0;
  i=0;
  while(moveList[i] !=0)
  {
      tempMove = moveList[i];
      intToMove(tempMove, loopPos, loopMove);
      
      updateBoard(boardMove, board);
      
      makeMoveTest(boardMove, loopPos, loopMove);
      moveScore = 0;
      
      //execute best moves at current depth -1 and chose the one with the best outcome
      
      //printf("Current Depth: %d\n", depth);
      for(a=0; a<=depth; a++)
      {
        if(depth == 0)
        {
        //printf("1\n");
          engineVal = bestPieceMove(boardMove, board3, board4, (turn+a+1));
        //printf("2\n");
        }
        else
        {
          engineVal = engineRecursion(boardMove, board3, board4, (turn+a+1), (depth-1));
        }
        
        if(engineVal == 0)
        {
          //printf("Future game end: %d\n", a);
          //printBoardChar(boardMove);
          
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
      i++;
    }

  return moveMax;
}