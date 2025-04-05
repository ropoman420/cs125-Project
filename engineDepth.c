#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD 10

//recursively analyzes best move
// this function is very slow and will be replaced, but works quickly up to a depth of 2 moves into the future

int engineRecursion(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int board3[BOARD][BOARD], int turn, int depth, int castleRights[2][2])
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
  
  int castleRightsCopy[2][2];
  castleRightsCopy[0][0] = castleRights[0][0];
  castleRightsCopy[0][1] = castleRights[0][1];
  castleRightsCopy[1][0] = castleRights[1][0];
  castleRightsCopy[1][1] = castleRights[1][1];
  
  srand(time(NULL));
  int randomNum;
  
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
  int checkCoords[2] = {0, 0};
  int kingCoords[2] = {0, 0};
  
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
  moves(board, boardMove, moveList, turn, castleRights);
  
  int offset;
  
  // ensures final engine calculation is on opponents turn
  if(depth % 2 == 0)
  {
    offset = 0;
  }
  else
  {
    offset = 1;
  }

  // run every possible move
  int tempMove = 0;
  i=0;
  while(moveList[i] !=0)
  {
      tempMove = moveList[i];
      intToMove(tempMove, loopPos, loopMove);
      
      updateBoard(boardMove, board);
      
      makeMoveTest(boardMove, loopPos, loopMove, castleRightsCopy);
      moveScore = 0;
      
      //execute best moves at current depth -1 and chose the one with the best outcome

      for(a=0; a<=depth+offset; a++)
      {
        if(depth == 0)
        {
          engineVal = bestPieceMove(boardMove, board3, board4, (turn+a+1), castleRightsCopy);
        }
        else
        {
          engineVal = engineRecursion(boardMove, board3, board4, (turn+a+1), (depth-1), castleRightsCopy);
        }
        
        check = testCheck(boardMove, kingCoords, checkCoords, (turn+a+1));
        if(engineVal == 0)
        {
          
          if((a % 2 == 0) && check == 1)
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
          makeMoveTest(boardMove, currPos, currMove, castleRightsCopy);
        }
      }
      
      // if no checkmate, evaluate based on point differential
      if(moveScore == 0)
      {
        moveScore = 10*scoreDif(boardMove, board3, turn);
      }
      
      randomNum = (rand() % 100);
      
      // determine of move is best
      if(moveScore > scoreMax)
      {
        scoreMax = moveScore;
        moveMax = moveToInt(loopPos, loopMove);
      }
      
      // makes random move only if it has same value as previous best move
      if((moveScore == scoreMax) && (randomNum > 50))
      {
        scoreMax = moveScore;
        moveMax = moveToInt(loopPos, loopMove);
      }
      i++;
    }

  return moveMax;
}