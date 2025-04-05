#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD 10

/*
  Programmed by Ellis
  This program tests to see if the King is in check from various locations
  Comments and cleanup by Caleb Groover
*/



//This function makes a matrix of zeroes for the necessary calculations
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


//This functions determines the location of the King
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


//This function finds which squares are threatening the King (in check)
void getCheckSquares(int board[BOARD][BOARD], int kingPos[2], int checker[2], int output[BOARD][BOARD])
{
  //Ensures output board starts as 0
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
  
  int di;  //The positional difference along the x-axis
  int dj;  //The positional difference along the y-axis

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



/*This function uses a different line of sight function to find which 
pieces are threatening the King and where from*/
int testCheck(int board[BOARD][BOARD], int kingCoord[2], int checkCoord[2], int turn)
{
  checkCoord[0] = 0;
  checkCoord[1] = 0;
  
  int type;
  int piece;
  int piece1;
  int piecePos[2];
  int piecePos1[2];
  int piecePos2[2];
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
  
  //Finding king
  findKing(board, type, kingPos);
  
  kingCoord[0] = kingPos[0];
  kingCoord[1] = kingPos[1];
  
  int pieceKnight = 0;
  
  //Test for check
  for(i=1; i<=8; i++)
  {
    //Uses rayLos at king position to search for checking pieces
    piece = rayLos(board, kingPos, piecePos, i, 0);
    piece1 = rayLos(board, kingPos, piecePos1, (i * -1), 0);
    
    //Knight checking piece
    pieceKnight = rayKnight(board, kingPos, piecePos2, i, 0);

    if(pieceKnight == -2 * type)
    {
      check = 1;
      checkCoord[0] = piecePos2[0];
      checkCoord[1] = piecePos2[1];
    }
    
    //Bishop or queen (x movement)
    if(((i % 2) == 0) && ((piece == (-3 * type)) || (piece == (-6 * type))))
    {
      check = 1;
      checkCoord[0] = piecePos[0];
      checkCoord[1] = piecePos[1];
    }
    
    //Queen or rook (+ movement)
    if(((i % 2) == 1) && ((piece == (-5 * type)) || (piece == (-6 * type))))
    {
      check = 1;
      checkCoord[0] = piecePos[0];
      checkCoord[1] = piecePos[1];
    }
    
    //Checks if the Kings are adjacent
    if(piece1 == (-7 * type))
    {
      check = 1;
      checkCoord[0] = piecePos1[0];
      checkCoord[1] = piecePos1[1];
    }
    
    //Pawns
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
    
    
  }
  
  return check;
}

//This function sets the first input equal to second so as to update the board
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

