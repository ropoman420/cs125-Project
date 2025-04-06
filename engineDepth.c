

#include "Chess.h"

/*
  Programmed by Ellis, Caleb, and Roman
  Debugged by Ellis
  Comments by Caleb Groover
  
  This program recursively analyzes best move and can be very slow,
  but works quickly up to a depth of 2 moves into the future. This
  functions similar to a difficulty, allowing the computer (engine)
  to determine a move based off of the next "x" moves forward.
*/

//This function recursively runs a brutal analysis of which move would be the highest value
int engineRecursion(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int board3[BOARD][BOARD], int turn, int depth, int castleRights[2][2])
{
  //Variable initializations
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
  
  //Creates a 4th board copy
  int board4[BOARD][BOARD];
  
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      board4[i][j] = 0;
    }
  }
  
  //Establishes checkmate variables
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
  
  //This ensures that the final engine calculation is on opponents turn
  if(depth % 2 == 0)
  {
    offset = 0;
  }
  else
  {
    offset = 1;
  }

  //This will run every possible move
  int tempMove = 0;
  i=0;
  while(moveList[i] !=0)
  {
      tempMove = moveList[i];
      intToMove(tempMove, loopPos, loopMove);
      
      updateBoard(boardMove, board);
      
      makeMoveTest(boardMove, loopPos, loopMove, castleRightsCopy);
      moveScore = 0;
      
      //This will execute best moves at current depth -1 and chose the one with the best outcome, prioritizing check or checkmate

      for(a=0; a<=depth+offset; a++)
      {
        if(depth == 0)
        {
          engineVal = bestPieceMove(boardMove, board3, board4, (turn+a+1), castleRightsCopy);
        }
        else
        {
          engineVal = engineRecursion(boardMove, board3, board4, (turn+a+1), (depth-1), castleRightsCopy);  //Application of recursion
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
      
      //If no checkmate is found, evaluate based on point differential
      if(moveScore == 0)
      {
        moveScore = 10*scoreDif(boardMove, board3, turn);
      }
      
      randomNum = (rand() % 100);
      
      //This will determine of move is best
      if(moveScore > scoreMax)
      {
        scoreMax = moveScore;
        moveMax = moveToInt(loopPos, loopMove);
      }
      
      //This makes a random move only if it has same value as previous best move
      if((moveScore == scoreMax) && (randomNum > 50))
      {
        scoreMax = moveScore;
        moveMax = moveToInt(loopPos, loopMove);
      }
      i++;
    }

  return moveMax;
}