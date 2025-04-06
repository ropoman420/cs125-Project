#include <stdio.h>

#define BOARD 10

// this function determines if the board has insufficient material for a forced win
int insufficientMaterial(int board[BOARD][BOARD], int boardMove[BOARD][BOARD])
{
  int type;
  int material;
  int sideMaterial = 0;
  int insufficient = 0;
  
  int i, j;
  
  // runs material score for both sides
  for(type=1; type<=2; type++)
  {
    material = score(board, boardMove, type);
    
    // if material is less than or equal to 13, this means a side has only a king and pawns, a knight, or bishop
    if(material <= 13)
    {
      sideMaterial += 1;
    }
  }
  
  // ensures both sides habe insufficient material for checkmate
  if(sideMaterial == 2)
  {
    insufficient = 1;
  }
  
  // ensuring no pawns on board
  for(i=1; i<9; i++)
  {
    for(j=1; j<9; j++)
    {
      // if pawn found, there is not insufficient material
      if((board[i][j] == 1) || (board[i][j] == -1))
      {
        insufficient = 0;
      }
    }
  }
  
  return insufficient;
}

// this function determines a draw has been reached when 50 moves have passed between the last pawn move or piece capture
int move50(int board[BOARD][BOARD], int moveFrom[2], int moveTo[2], int* turnsSince)
{ 
  // set equal to 1 if pawn move is made or piece captured
  int reset = 0;
  
  // determining if turnsSince should be reset
  
  int x1 = moveFrom[0];
  int y1 = moveFrom[1];
  
  int x2 = moveTo[0];
  int y2 = moveTo[1];
  
  // if pawn move
  if((board[y1][x1] == 1) || (board[y1][x1] == -1))
  {
    reset = 1;
  }
  
  // if capture
  if((board[y2][x2] != 0) && (board[y2][x2] != 4) && (board[y2][x2] != -4))
  {
    reset = 1;
  }
  
  // resets or incriments turnsSince
  if(reset == 1)
  {
    *turnsSince = 0;
  }
  else
  {
    turnsSince++;
  }
  
  // determining and returning draw condition
  int draw = 0;
  if(*turnsSince >= 50)
  {
    draw = 1;
  }
  
  return draw;
}