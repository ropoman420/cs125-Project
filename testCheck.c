#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD 10

int testCheck(int board[BOARD][BOARD], int turn)
{
  
  int type;
  int piece;
  int piece1;
  int piecePos[2];
  int check = 0;
  int kingPos[2];
  
  if((turn % 2) == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  int i;
  int j;
  
  //finding king
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      if(board[i][j] == (type * 7))
      {
        kingPos[0] = j;
        kingPos[1] = i;
      }
    }
  }
  
  // test for check
  for(i=1; i<=8; i++)
  {
    piece = rayLos(board, kingPos, piecePos, i, 0);
    piece1 = rayLos(board, kingPos, piecePos, (i * -1), 0);
    
    // bishop or queen
    if(((i % 2) == 0) && ((piece == (-3 * type)) || (piece == (-6 * type))))
    {
      check = 1;
    }
    
    // queen or rook
    if(((i % 2) == 1) && ((piece == (-5 * type)) || (piece == (-6 * type))))
    {
      check = 1;
    }
    
    // kings touching?
    if(piece1 == (-7 * type))
    {
      check = 1;
    }
    
    // pawns
    if((piece1 == 1) && (type == -1) && ((i == 6) || (i == 4)))
    {
      check = 1;
    }
    if((piece1 == -1) && (type == 1) && ((i == 8) || (i == 2)))
    {
      check = 1;
    }
    
    // knights
    
    
  }
  
  return check;
}

// sets first input equal to second
void updateBoard(int b1[BOARD][BOARD], int b2[BOARD][BOARD])
{
  int i;
  int j;
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      b1[i][j] = b2[i][j];
    }
  }
}

// makes matrix zeros
void makeZero(int board[BOARD][BOARD])
{
  int i;
  int j;
  for(i=0; i<BOARD; i++)
  {
    for(j=0; j<BOARD; j++)
    {
      board[i][j] = 0;
    }
  }
}
