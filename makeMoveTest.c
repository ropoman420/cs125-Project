#include <stdio.h>
#include <stdlib.h>

#define BOARD 10

// rudimentary move piece function

void removePassant(int board[BOARD][BOARD], int type)
{
  int i, j;
  
  for(i=1; i<9; i++)
  {
    for(j=1; j<9; j++)
    {
      if(board[i][j] == (type * 4))
      {
        board[i][j] = 0;
      }
    }
  }
}

void makeMoveTest(int board[BOARD][BOARD], int moveFrom[2], int moveTo[2])
{
  int x1 = moveFrom[0];
  int y1 = moveFrom[1];
  
  int x2 = moveTo[0];
  int y2 = moveTo[1];
  
  int piece = board[y1][x1];
  int type = piece / makePos(piece);
  
  // ensures en passant is not possible 1+ moves after pawn was moved
  removePassant(board, type);
  
  if((board[y2][x2] != 7) && board[y2][x2] != -7)
  {
    // removing en passant - captured pawn
    if((board[y2][x2] == (-4*type)) && (board[y1][x1] == type))
    {
      board[y1][x2] = 0;
    }
  
    // piece placed in second position
    board[y2][x2] = board[y1][x1];
    
    // pawn promotion
    if(((y2 == 8) || (y2 == 1)) && ((board[y2][x2] == 1) || (board[y2][x2] == -1)))
    {
      board[y2][x2] *= 6;
    }
    
    // adds 4 to represent capturable pawn via en passant, if a pawn moves 2 spaces
    if(((board[y2][x2] == 1) || (board[y2][x2] == -1)) && (makePos(y2-y1) == 2))
    {
      board[y2-board[y2][x2]][x2] = board[y2][x2] * 4;
    }
    
    //piece removed from first position
    board[y1][x1] = 0;
  }
}

int checkLegalTest(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int moveFrom[2], int moveTo[2], int turn)
{
  updateBoard(boardMove, board);

  int legal = 0;
  int basicLegal = basicMoveCheck(board, moveFrom, moveTo, turn);
  int i;
  int dummyRay;
  int type;
  
  int x = moveFrom[0];
  int y = moveFrom[1];
  
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  // check variables
  int check = 0;
  int kingCoords[2];
  int checkCoords[2];
  kingCoords[0] = 0;
  kingCoords[1] = 0;
  checkCoords[0] = 0;
  checkCoords[1] = 0;
  
  int pieceOfInterest = board[y][x];
  pieceOfInterest = makePos(pieceOfInterest);
  
  int disx;
  int disy;
  
  //printf("piece: %d\n", pieceOfInterest);
  
  if(basicLegal == 1)
  {
    switch(pieceOfInterest)
    {
      case 7:
        // kings (and knights temporarily)
        for(i=-8; i<=-1; i++)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1);
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
        }
        break;
      case 6:
        for(i=1; i<=8; i++)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1);
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
        }
        break;
      case 5:
        for(i=1; i<=8; i+=2)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1);
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
        }
        break;
      case 3:
        for(i=2; i<8; i+=2)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1);
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
        }
        break;
      case 2:
        //int disx;
        //int disy;
        disx = makePos((moveTo[0] - x));
        disy = makePos((moveTo[1] - y));
        
        if(((disx == 2) && (disy == 1)) || ((disx == 1) && (disy == 2)))
        {
          legal = 1;
        }
        break;
      case 1:
        // forward 1
        if((board[y+type][x] == 0) && (y+type == moveTo[1]) && (x == moveTo[0]))
        {
          legal = 1;
          //printf("pawn can go 1 forward\n");
        }
        
        // forward 2
        if((board[y+type][x] == 0) && (board[y+(2*type)][x] == 0) && (y+(2*type) == moveTo[1]) && (x == moveTo[0]))
        {
          if((type == 1) && (y == 2))
          {
            legal = 1;
            //printf("pawn can go 2 forward\n");
          }
          
          if((type == -1) && (y == 7))
          {
            legal = 1;
            //printf("pawn can go 2 forward\n");
          }
        }
        
        // diagonal capture
        int distanceX = moveTo[0] - x;
        
        if((board[y+type][x+distanceX] * type < 0) && (y+type == moveTo[1]) && (makePos(distanceX) == 1))
        {
          legal = 1;
          //printf("pawn can capture\n");
        }
        break;
    }
    
    // testing if this move will put king in check
    makeMoveTest(boardMove, moveFrom, moveTo);
    
    check = testCheck(boardMove, kingCoords, checkCoords, turn);
    
    if(check == 1)
    {
      legal = 0;
    }
    
  }
  updateBoard(boardMove, board);
  
  return legal;
}