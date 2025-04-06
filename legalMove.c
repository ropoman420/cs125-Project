

#include "Chess.h"

/*
  Similar to pieceMove.c, this function is not called in "main,"
  though it was implemented for a while during the genesis of the
  project. We are too afraid to delete it, though it served as a basis
  for checkLegalTest function used later in "main."
  Programmed by Caleb
  Debugged by Ellis
  Comments by Caleb Groover
*/

int legalMove(int i, int j, int newX, int newY, int turn, int board[BOARD][BOARD], int moveFrom[2], int moveTo[2])
{  
  int pieceVal;  //This is the piece's value that is passed in initially into the function
  int legal = 0;
  int type;
  
  
  //These four values build the matrix to store positional data for when it is passed into the LoS function
  int x1 = newX;
  int y1 = newY;
  
  int x2 = newX;
  int y2 = newY;
  int dummyRay;
  
  //This conditional ensures that the King piece cannot be captured
  if((board[y2][x2] != 7) && board[y2][x2] != -7)
  {
    board[y2][x2] = board[y1][x1];
    board[y1][x1] = 0;
  }
  
  
  if (newX >= 9 || newY >= 9 || newX <= 0 || newY <= 0)
  {
    printf("This is beyond the constraints of the board. Please try again.\n");
    return 0;
    //If the user enters a coordinate outside of the board contstraints, the legal check will fail
  }
  else
  {
    pieceVal = makePos(board[i][j]);  //This takes the piece value and makes it positive to ensure operation in the switch statement
  }
  
  
  int x = moveFrom[0];
  int y = moveFrom[1];
  
  
  //This conditional sets whose turn it is and gets used for the technicalities of piece movement during the large switch statement
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  int pieceOfInterest = board[y][x];
  pieceOfInterest = makePos(pieceOfInterest);
  
  int disx;
  int disy;
  
    
  //The switch statement selects a case determined by piece value (depending on which piece is selected)
  switch(pieceVal) 
    {
      case 7 /*King movement*/:
        for(i=-8; i<=-1; i++)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1); //Returns 1 if coordinates are within a move set, returns 0 if coordinates entered are outside of the move set
          
          if(dummyRay == 1)
          {
            legal = 1; //If legal = 1, then the movement in legal
          }
          else
          {
            legal - 0; //If legal = 0, then the movement is not legal. Rather than printing an illegal move statement repeatedly, only the value is changed
          }
        }
        break;
        
        
      case 6 /*Queen movement*/:
        for(i=1; i<=8; i++)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1); //Returns 1 if coordinates are within a move set, returns 0 if coordinates entered are outside of the move set
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
          else
          {
            legal - 0;
          }
        }
        break;
        
        
      case 5 /*Rook movement*/:
        for(i=1; i<=8; i+=2)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1); //Returns 1 if coordinates are within a move set, returns 0 if coordinates entered are outside of the move set
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
          else
          {
            legal - 0;
          }
        }
        break;
        
        
      case 3 /*Bishop movement*/:
        for(i=2; i<8; i+=2)
        {
          dummyRay = rayLos(board, moveFrom, moveTo, i, 1); //Returns 1 if coordinates are within a move set, returns 0 if coordinates entered are outside of the move set
          
          if(dummyRay == 1)
          {
            legal = 1;
          }
          else
          {
            legal - 0;
          }
        }
        break;
        
        
      case 2 /*Knight movement*/:
        disx = makePos((newX - x));      //These two lines have been altered and unverified
        disy = makePos((newY - y));
        
        if(((disx == 2) && (disy == 1)) || ((disx == 1) && (disy == 2)))
        {
          legal = 1;
        }
        else
        {
          legal - 0;
        }
        break;
        
        
      case 1 /*Pawn movement*/:
        //Forward 1
        if((board[y+type][x] == 0) && (y+type == newY) && (x == newX))
        {
          legal = 1;
        }
        else
        {
          legal - 0;
        }
        
        //Forward 2 check for pawn
        if((board[y+type][x] == 0) && (board[y+(2*type)][x] == 0) && (y+(2*type) == newY) && (x == newX))
        {
          if((type == 1) && (y == 2))
          {
            legal = 1;
            //Pawns can go 2 spaces forward if on their home row
          }
          else
          {
            legal - 0;
          }
          
          if((type == -1) && (y == 7))
          {
            legal = 1;
            //Pawns can go 2 spaces forward if on their home row
          }
          else
          {
            legal = 0;
          }
        }
        
        //Diagonal capture for pawns
        int distanceX = moveTo[0] - x;
        
        if((board[y+type][x+distanceX] * type < 0) && (y+type == newY) && (makePos(distanceX) == 1))
        {
          legal = 1;
          printf("Your pawn captured a piece!\n");
        }        
        else
        {
          legal = 0;
        }
        
        break;
        
return legal;
  }
}     