

#include "Chess.h"

/*
  This program was primarily coded by Caleb and Ellis
  Comments by Caleb Groover
  EnPassant and castling functionality by Ellis
  
  This program handles various movements and their legality therein
  Moves such as en passant and castling are verified through here
  as well as whether or not an overall move is legal. Were it not for
  main, this would be the most complicated program on file.
*/


//This program removes a potential enPassant move from the move set
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


//This function executes a particular move, altering the board values
void makeMoveTest(int board[BOARD][BOARD], int moveFrom[2], int moveTo[2], int castleRights[2][2])
{
  //These declarations initialize the matrix position values
  int x1 = moveFrom[0];
  int y1 = moveFrom[1];
  
  int x2 = moveTo[0];
  int y2 = moveTo[1];
  
  int piece = board[y1][x1];
  int type = piece / makePos(piece);
  
  //Ensures en passant is not possible 1+ moves after pawn was moved
  removePassant(board, type);
  
  if((board[y2][x2] != 7) && board[y2][x2] != -7)
  {
    //Removing en passant due to captured pawn
    if((board[y2][x2] == (-4*type)) && (board[y1][x1] == type))
    {
      board[y1][x2] = 0;
    }
  
    //Piece placed in second position
    board[y2][x2] = board[y1][x1];
    
    //Pawn promotion
    if(((y2 == 8) || (y2 == 1)) && ((board[y2][x2] == 1) || (board[y2][x2] == -1)))
    {
      board[y2][x2] *= 6;
    }
    
    //Adds 4 to represent capturable pawn via en passant, if a pawn moves 2 spaces
    if(((board[y2][x2] == 1) || (board[y2][x2] == -1)) && (makePos(y2-y1) == 2))
    {
      board[y2-board[y2][x2]][x2] = board[y2][x2] * 4;
    }
    
    //Piece removed from first position
    board[y1][x1] = 0;
    
    //Completing castle move
    if((board[y2][x2] == 7*type) && (makePos(x2-x1) == 2))
    {
      int castleDirection = (x2 - x1) / 2;

      int rookCoordX = x2+castleDirection;
      
      //If queenside castle, rook is 1 space farther away from king
      if(board[y2][x2+castleDirection] == 0)
      {
        rookCoordX += castleDirection;
      }
      
      board[y2][rookCoordX] = 0;
      board[y2][x2-castleDirection] = 5*type;
    }
    
    
    //Updating castling rights
    
    //Kings
    if(x1 == 5)
    {
      //White king
      if(y1 == 1)
      {
        castleRights[0][0] = 0;
        castleRights[0][1] = 0;
      }
      
      //Black king
      if(y1 == 8)
      {
        castleRights[1][0] = 0;
        castleRights[1][1] = 0;
      }
    }
    
    //Rooks
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


//This function tests to see if a particular move is legal or not
int checkLegalTest(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int moveFrom[2], int moveTo[2], int turn, int castleRights[2][2])
{
  updateBoard(boardMove, board);

  int legal = 0; //This is the return value. "1" means the move is legal, "0" means it is not
  int basicLegal = basicMoveCheck(board, moveFrom, moveTo, turn);
  int i;
  int dummyRay;
  int type;
  int rookFound;
  int castleType;
  
  int x = moveFrom[0];
  int y = moveFrom[1];
  
  /*This conditional sets a pieces value as positive
  or negative to determine piece side (black or white)*/
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  //Creates a copy of castleRights, so it is not altered when checking legality of a move
  int castleRightsCopy[2][2];
  castleRightsCopy[0][0] = castleRights[0][0];
  castleRightsCopy[0][1] = castleRights[0][1];
  castleRightsCopy[1][0] = castleRights[1][0];
  castleRightsCopy[1][1] = castleRights[1][1];
  
  //Check variables
  int check = 0;
  int kingCoords[2] = {0, 0};
  int checkCoords[2] = {0, 0};
  
  int pieceOfInterest = board[y][x];
  pieceOfInterest = makePos(pieceOfInterest); //Here lies the functionality to make an absolute value of a piece for universal operation
  
  int disx;
  int disy;
  
  int kingRight = 0;
  int kingLeft = 0;
  
  int posDummy1[2] = {0, 0};
  int posDummy2[2] = {0, 0};
  

  if(basicLegal == 1)
  {
    switch(pieceOfInterest) //This switch picks a particular piece by value to validate
    {
      case 7:
        //King's legal move set
        for(i=-8; i<=-1; i++)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1);
          
          if(dummyRay == 1)
          {
            legal = 1;
          }     
        }
        
        //Castling legality  
        //Converts type from -1=black, 1=white --> 0=white, 1=black, for use as castleRights matrix index
        
        
        castleType = (type-1)/-2;
        check = testCheck(board, kingCoords, checkCoords, turn);
        int distance = moveTo[0] - moveFrom[0];
        
        //Can't castle out of check
        if(check == 0)
        {
          //Castle right
          if(distance == 2)
          {
            rookFound = rayLos(board, kingCoords, posDummy2, 3, 0);
            
            if((rookFound == 5*type) && (castleRightsCopy[castleType][1] == 1))
            {
              legal = 1;
            }
          }
          
          //Castle left
          if(distance == -2)
          {
            rookFound = rayLos(board, kingCoords, posDummy2, 7, 0);
            
            if((rookFound == 5*type) && (castleRightsCopy[castleType][0] == 1))
            {
              legal = 1;
            }
          }
          
          //Moving king 1 square in direction of castle to check if castle is across check
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
        //Queen move set
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
        //Rook moveset
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
        //Bishop moveset 
        for(i=2; i<=8; i+=2)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1);
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
        }
        break;
      case 2:
        //Knight move set
        disx = makePos((moveTo[0] - x));
        disy = makePos((moveTo[1] - y));
        
        if(((disx == 2) && (disy == 1)) || ((disx == 1) && (disy == 2)))
        {
          legal = 1;
        }
        break;
      case 1:
        //Pawn move set
        
        //Forward 1
        if((board[y+type][x] == 0) && (y+type == moveTo[1]) && (x == moveTo[0]))
        {
          legal = 1;
        }
        
        //Forward 2 if on first row/rank
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
        
        //Diagonal capture
        int distanceX = moveTo[0] - x;
        
        if((board[y+type][x+distanceX] * type < 0) && (y+type == moveTo[1]) && (makePos(distanceX) == 1))
        {
          legal = 1;
        }
        break;
    }
    
    //Testing if a move will put king in check
    makeMoveTest(boardMove, moveFrom, moveTo, castleRightsCopy);
    
    int check3 = testCheck(boardMove, kingCoords, checkCoords, turn);
    
    if(check3 == 1)
    {
      legal = 0;
    }
    
  }
  updateBoard(boardMove, board);  //Updates the values of the board (not displayed)
  
  return legal;  //Returns the legality of the desired input move
}