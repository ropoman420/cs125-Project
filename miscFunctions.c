

#include "Chess.h"

/*
  This program contains ungrouped useful functions
  that are used throughout multiple compilable programs
  Programmed by Ellis, Caleb, and Roman
  Comments by Caleb Groover
*/


/*This function makes a pieces value positive so that there
are no negative numbers when handling coordinate data*/
int makePos(int value)
{
  if(value < 0)
  {
    return value * -1;
  }
  else
  {
    return value;
  }

}


//This function checks the possible movement for a knight
int rayKnight(int board[BOARD][BOARD], int coordStart[2], int coordEnd[2], int direction)
{
  int di = 0;
  int dj = 0;
  switch(direction)
  {
    int add;
    case 1:
      di = 1;
      dj = 2;
      break;
    case 2:
      di = 2;
      dj = 1;
      break;
    case 3:
      di = 2;
      dj = -1;
      break;
    case 4:
      di = 1;
      dj = -2;
      break;
    case 5:
      di = -1;
      dj = 2;
      break;
    case 6:
      di = -2;
      dj = -1;
      break;
    case 7:
      di = -2;
      dj = 1;
      break;
    case 8:
      di = -1;
      dj = -2;
      break;
    default:
      //printf("Invalid Knight Movement");
      break;
  }
  
  int currPiece = 0;
  int row = coordStart[1];
  int col = coordStart[0];
  int y = row + dj;
  int x = col + di;
    
  if( (y > 8) || (y < 1) || (x > 8) || (x < 1) )
  {
    //The move is out of bounds
  }
  else 
  {
    coordEnd[0] = x;
    coordEnd[1] = y;
    currPiece = board[y][x];
  }
  return currPiece;
}


//This function tests if a piece is within a line of sight of another piece
int rayLos(int board[BOARD][BOARD], int coordStart[2], int coordEnd[2], int direction, int cmp)
{
  /*Passed variables include input board, start coordnate, 
  desired/output coordnates, direction, and if you are comparing coordinates
  If cmp = 1 function returns 1 only if coordEnd is within ray*/
  int di;
  int dj;
  int oneSquare = 0;
  
  //If direction is negative, function only checks one square in direction
  if(direction < 0)
  {
    direction = direction * -1;
    oneSquare = 1;
  }
  
  switch(direction)  //Switch statement to check each radius surrounding a piece
  {
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
      printf("Invalid LOS direction");
      break;
      
  }
  
  int currPiece = 0;
  int row = coordStart[1];
  int col = coordStart[0];
  int match = 0;
  
  while((currPiece == 0) || (currPiece == 4) || (currPiece == -4))
  {
    row += di;
    col += dj;
    
    currPiece = board[row][col];
    
    if((coordEnd[0]==col) && (coordEnd[1]==row))
    {
      match = 1;
    }
    
    if(oneSquare == 1)
    {
      break;
    }
  }

  if(cmp == 1)
  {
    return match;
  }
  else
  {
    coordEnd[0] = col;
    coordEnd[1] = row;
    return currPiece;
  }
}


//Given 2 positions on board, this function returns which direction is needed to get from one to the other
int testDirection(int pos1[2], int pos2[2])
{
  int direction = 0;
  int slope = 10;
  
  int difY = pos2[1] - pos1[1];
  int difX = pos2[0] - pos1[0];
  
  if(difX == 0)
  {
    if(difY > 0)
    {
      direction = 1;
    }
    else
    {
      direction = 5;
    }
  }
  else if(difY == 0)
  {
    if(difX > 0)
    {
      direction = 3;
    }
    else
    {
      direction = 7;
    }
  }
  else
  { 
    if(makePos(difY) == makePos(difX))
    {
      slope = difY / difX;
    }
    
    if(slope == 1)
    {
      if(difY > 0)
      {
        direction = 2;
      }
      else
      {
        direction = 6;
      }
    }
    else if(slope == -1)
    {
      if(difY > 0)
      {
        direction = 8;
      }
      else
      {
        direction = 4;
      }
    }
  }
  
  
  return direction;
}




