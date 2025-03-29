#include <stdio.h>
#include <stdlib.h>

#define BOARD 10

// experimenting with chess engine

int moveToInt(int coord1[2], int coord2[2])
{
  int out = (coord1[0] * 1000) + (coord1[1] * 100) + (coord2[0] * 10) + (coord2[1]);
  return out;
}

void intToMove(int num, int coord1[2], int coord2[2])
{
  coord1[0] = (num - (num % 1000)) / 1000;
  coord1[1] = ((num % 1000) - (num % 100)) / 100;
  
  coord2[0] = ((num % 100) - (num % 10)) / 10;
  coord2[1] = num % 10;
}

int score(int board[BOARD][BOARD], int board2[BOARD][BOARD], int turn)
{
  updateBoard(board2, board);

  int i;
  int j;
  int type;
  int sideScore = 0;
  
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  int posSquare;
  
  for(i=1; i<9; i++)
  {
    for(j=1; j<9; j++)
    {
      switch(board[i][j])
      {
        case 2:
          board2[i][j] = 3;
          break;
        case 6:
          board2[i][j] = 9;
          break;
        case 7:
          board2[i][j] = 10;
          break;
        case -2:
          board2[i][j] = -3;
          break;
        case -6:
          board2[i][j] = -9;
          break;
        case -7:
          board2[i][j] = -10;
          break;
        case 4:
          board2[i][j] = 0;
          break;
        case -4:
          board2[i][j] = 0;
          break;
      }
      
      posSquare = board2[i][j];
    
      if(board[i][j] * type > 0)
      {
        sideScore += makePos(posSquare);
      }
    }
  }
  
  return sideScore;
}

int scoreDif(int board[BOARD][BOARD], int board2[BOARD][BOARD], int turn)
{
  int score1 = score(board, board2, turn);
  int score2 = score(board, board2, turn+1);
  
  int dif = score1 - score2;
  return dif;
}

int bestPieceMove(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int board3[BOARD][BOARD], int turn, int startX, int startY, int *maxVal)
{
  int i;
  int j;
  int move = 0;
  int curVal = 0;
  int type;
  int legal;
  *maxVal = -1000;
  //int legal;
  
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  int moveFrom[2];
  moveFrom[0] = startX;
  moveFrom[1] = startY;
  
  int moveTo[2];
  
  // checkmate variables
  int checkCoords[2];
  int kingCoords[2];
  
  int checkSquares[BOARD][BOARD];
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      checkSquares[i][j] = 0;
    }
  }
  
  int check = 0;
  int mate = 0;
  
  for(i=1; i<9; i++)
  {
    for(j=1; j<9; j++)
    {
      if(board[i][j] * type <= 0)
      {
        moveTo[0] = j;
        moveTo[1] = i;
        
        updateBoard(boardMove, board);

        legal = checkLegalTest(boardMove, board3, moveFrom, moveTo, turn);
        
        if(legal == 1)
        {
          //printf("legal: %d\n", legal);
          //legal = 1;
        
          // try making move
          makeMoveTest(boardMove, moveFrom, moveTo);
          //printBoardChar(boardMove);
          
          // oponent in mate?
          kingCoords[0] = 0;
          kingCoords[1] = 0;
          
          checkCoords[0] = 0;
          checkCoords[1] = 0;
          
          makeZero(checkSquares);
          
          //printf("working...%d, %d\n", i, j);
          check = testCheck(boardMove, kingCoords, checkCoords, (turn+1));
          getCheckSquares(boardMove, kingCoords, checkCoords, checkSquares);
          mate = testMate(boardMove, board3, checkSquares, (turn+1));
          
          curVal = scoreDif(boardMove, board3, turn);
          
          // ensures that a mate is valued the highest
          
          if(mate == 1)
          {
            curVal = 1000;
          }
          
          updateBoard(board3, boardMove);
          
          // updates maximum move result value
          if(curVal >= *maxVal)
          {
            *maxVal = curVal;
            move = moveToInt(moveFrom, moveTo);
          }
        }
      }
    }
  }

  return move;
}

int bestMove(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int board3[BOARD][BOARD], int turn)
{
  int type;
  
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }

  int i;
  int j;
  int move = 0;
  int curMove = 0;
  int maxVal = -1000;
  int curVal;
  int posSquare;
  
  for(i=1; i<9; i++)
  {
    for(j=1; j<9; j++)
    {
      posSquare = board[i][j];
      
      if((board[i][j] * type > 0) && (makePos(posSquare) != 4))
      {
        curVal = -10000;
        curMove = bestPieceMove(board, boardMove, board3, turn, j, i, &curVal);
        
        if(curVal >= maxVal)
        {
          maxVal = curVal;
          move = curMove;
        }
      }
    }
  }
  
  return move;
}