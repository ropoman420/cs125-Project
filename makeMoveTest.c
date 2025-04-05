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

void makeMoveTest(int board[BOARD][BOARD], int moveFrom[2], int moveTo[2], int castleRights[2][2])
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
    
    // piece removed from first position
    board[y1][x1] = 0;
    
    // completing castle move
    
    if((board[y2][x2] == 7*type) && (makePos(x2-x1) == 2))
    {
      int castleDirection = (x2 - x1) / 2;

      int rookCoordX = x2+castleDirection;
      
      // if queenside castle, rook is 1 space farther away from king
      if(board[y2][x2+castleDirection] == 0)
      {
        rookCoordX += castleDirection;
      }
      
      board[y2][rookCoordX] = 0;
      board[y2][x2-castleDirection] = 5*type;
    }
    
    
    // updating castling rights
    
    // kings
    if(x1 == 5)
    {
      // white king
      if(y1 == 1)
      {
        castleRights[0][0] = 0;
        castleRights[0][1] = 0;
      }
      
      // black king
      if(y1 == 8)
      {
        castleRights[1][0] = 0;
        castleRights[1][1] = 0;
      }
    }
    
    // rooks
    if((x1 == 1) && (y1 == 1))
    {
      castleRights[0][0] = 0;
    }
    if((x1 == 8) && (y1 == 1))
    {
      castleRights[0][1] = 0;
    }
    if((x1 == 1) && (y1 == 8))
    {
      castleRights[1][0] = 0;
    }
    if((x1 == 8) && (y1 == 8))
    {
      castleRights[1][1] = 0;
    }
    
  }
}

int checkLegalTest(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int moveFrom[2], int moveTo[2], int turn, int castleRights[2][2])
{
  updateBoard(boardMove, board);

  int legal = 0;
  int basicLegal = basicMoveCheck(board, moveFrom, moveTo, turn);
  int i;
  int dummyRay;
  int type;
  int rookFound;
  int castleType;
  
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
  
  // copy of castleRights, so it is not altered when checking legality of a move
  int castleRightsCopy[2][2];
  castleRightsCopy[0][0] = castleRights[0][0];
  castleRightsCopy[0][1] = castleRights[0][1];
  castleRightsCopy[1][0] = castleRights[1][0];
  castleRightsCopy[1][1] = castleRights[1][1];
  
  // check variables
  int check = 0;
  int kingCoords[2] = {0, 0};
  int checkCoords[2] = {0, 0};
  
  int pieceOfInterest = board[y][x];
  pieceOfInterest = makePos(pieceOfInterest);
  
  int disx;
  int disy;
  
  int kingRight = 0;
  int kingLeft = 0;
  
  int posDummy1[2] = {0, 0};
  int posDummy2[2] = {0, 0};
  
  //printf("piece: %d\n", pieceOfInterest);
  
  if(basicLegal == 1)
  {
    switch(pieceOfInterest)
    {
      case 7:
        // kings
        for(i=-8; i<=-1; i++)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1);
          
          if(dummyRay == 1)
          {
            legal = 1;
          }     
        }
        
        // castling legality
            
        // converts type from -1=black, 1=white --> 0=white, 1=black, for use as castleRights matrix index
        
        
        castleType = (type-1)/-2;
        check = testCheck(board, kingCoords, checkCoords, turn);
        int distance = moveTo[0] - moveFrom[0];
        
        // cant castle out of check
        if(check == 0)
        {
          // castle right
          if(distance == 2)
          {
            rookFound = rayLos(board, kingCoords, posDummy2, 3, 0);
            
            if((rookFound == 5*type) && (castleRightsCopy[castleType][1] == 1))
            {
              legal = 1;
            }
          }
          
          // castle left
          if(distance == -2)
          {
            rookFound = rayLos(board, kingCoords, posDummy2, 7, 0);
            
            if((rookFound == 5*type) && (castleRightsCopy[castleType][0] == 1))
            {
              legal = 1;
            }
          }
          
          // moving king 1 square in direction of castle to check if castle is across check
          posDummy1[0] = moveTo[0] + (distance/2);
          posDummy1[1] = moveTo[0];
          updateBoard(boardMove, board);
          
          makeMoveTest(boardMove, moveFrom, posDummy1, castleRightsCopy);
          int check2 = testCheck(boardMove, kingCoords, checkCoords, turn);
          
          updateBoard(boardMove, board);

          if(check == 1)
          {
            legal = 0;
          }
        }
        break;
      case 6:
        // queen moves
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
        // rook moves
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
        // bishop moves
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
        // knight moves
        disx = makePos((moveTo[0] - x));
        disy = makePos((moveTo[1] - y));
        
        if(((disx == 2) && (disy == 1)) || ((disx == 1) && (disy == 2)))
        {
          legal = 1;
        }
        break;
      case 1:
        // pawn moves
        // forward 1
        if((board[y+type][x] == 0) && (y+type == moveTo[1]) && (x == moveTo[0]))
        {
          legal = 1;
        }
        
        // forward 2
        if((board[y+type][x] == 0) && (board[y+(2*type)][x] == 0) && (y+(2*type) == moveTo[1]) && (x == moveTo[0]))
        {
          if((type == 1) && (y == 2))
          {
            legal = 1;
          }
          
          if((type == -1) && (y == 7))
          {
            legal = 1;
          }
        }
        
        // diagonal capture
        int distanceX = moveTo[0] - x;
        
        if((board[y+type][x+distanceX] * type < 0) && (y+type == moveTo[1]) && (makePos(distanceX) == 1))
        {
          legal = 1;
        }
        break;
    }
    
    // testing if this move will put king in check
    makeMoveTest(boardMove, moveFrom, moveTo, castleRightsCopy);
    
    check = testCheck(boardMove, kingCoords, checkCoords, turn);
    
    if(check == 1)
    {
      legal = 0;
    }
    
  }
  updateBoard(boardMove, board);
  
  return legal;
}