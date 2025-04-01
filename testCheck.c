#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD 10
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

void findKing(int board[BOARD][BOARD], int type, int kingPos[2])
{
  int i;
  int j;
  
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
}

void getCheckSquares(int board[BOARD][BOARD], int kingPos[2], int checker[2], int output[BOARD][BOARD])
{
  // ensures output board starts as 0
  makeZero(output);
  
  int direction = 0;
  int inCheck = 1;
  
  int kingX = kingPos[0];
  int kingY = kingPos[1];
  
  int checkX = checker[0];
  int checkY = checker[1];
  
  if((board[checkY][checkX] == 2) || (board[checkY][checkX] == -2))
  {
    output[checkY][checkX] = 1;
  }
  else
  {
    direction = testDirection(kingPos, checker);
  }
  
  int di;
  int dj;

  switch(direction)
  {
    case 0:
      inCheck = 0;
      break;
    case 1:
      di = 1;
      dj = 0;
      break;
    case 2:
      di = 1;
      dj = 1;
      break;
    case 3:
      di = 0;
      dj = 1;
      break;
    case 4:
      di = -1;
      dj = 1;
      break;
    case 5:
      di = -1;
      dj = 0;
      break;
    case 6:
      di = -1;
      dj = -1;
      break;
    case 7:
      di = 0;
      dj = -1;
      break;
    case 8:
      di = 1;
      dj = -1;
      break;
    default:
      if((board[checkY][checkX] != 2) || (board[checkY][checkX] != -2))
      {
        printf("Error getting direction\n");
      }
      break;
  }
  
  while((inCheck == 1) && (direction != 0) && ((kingX != checkX) || (kingY != checkY)))
  {
    kingX += dj;
    kingY += di;
    
    output[kingY][kingX] = 1;
  }
  
  output[checkY][checkX] = 2;

}


int testCheck(int board[BOARD][BOARD], int kingCoord[2], int checkCoord[2], int turn)
{
  checkCoord[0] = 0;
  checkCoord[1] = 0;
  
  int type;
  int piece;
  int piece1;
  int piecePos[2];
  int piecePos1[2];
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
  findKing(board, type, kingPos);
  
  kingCoord[0] = kingPos[0];
  kingCoord[1] = kingPos[1];
  
  int pieceKnight = 0;
  
  // test for check
  for(i=1; i<=8; i++)
  {
    // uses rayLos at king position to search for checking pieces
    piece = rayLos(board, kingPos, piecePos, i, 0);
    piece1 = rayLos(board, kingPos, piecePos1, (i * -1), 0);
    
    // knight checking piece?
    
    pieceKnight = rayKnight(board, kingPos, piecePos, i, 0);
    
    if(pieceKnight == -2 * type)
    {
      check = 1;
      checkCoord[0] = piecePos[0];
      checkCoord[1] = piecePos[1];
    }
    
    // rayKnight functionality will be added here
    
    // bishop or queen
    if(((i % 2) == 0) && ((piece == (-3 * type)) || (piece == (-6 * type))))
    {
      check = 1;
      checkCoord[0] = piecePos[0];
      checkCoord[1] = piecePos[1];
    }
    
    // queen or rook
    if(((i % 2) == 1) && ((piece == (-5 * type)) || (piece == (-6 * type))))
    {
      check = 1;
      checkCoord[0] = piecePos[0];
      checkCoord[1] = piecePos[1];
    }
    
    // kings touching?
    if(piece1 == (-7 * type))
    {
      check = 1;
      checkCoord[0] = piecePos1[0];
      checkCoord[1] = piecePos1[1];
    }
    
    // pawns
    if((piece1 == 1) && (type == -1) && ((i == 6) || (i == 4)))
    {
      check = 1;
      checkCoord[0] = piecePos1[0];
      checkCoord[1] = piecePos1[1];
    }
    if((piece1 == -1) && (type == 1) && ((i == 8) || (i == 2)))
    {
      check = 1;
      checkCoord[0] = piecePos1[0];
      checkCoord[1] = piecePos1[1];
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

