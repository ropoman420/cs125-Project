#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BOARD 10


/*
  Primary contributions by Ellis Garrett and Roman Warder
  This program checks various win conditions according to Chess rulebook
  Comments by Caleb Groover
*/


/*This function will check a basic moveset such 
as exceeding the board or selecting the wrong piece*/
int basicMoveCheck(int board[BOARD][BOARD], int pos1[2], int pos2[2], int turn)
{
  int type;  //Type represents a pieces side (black or white)
  int legal = 1; //This function assumes that a move is legal until proven otherwise
  
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }

  int x1 = pos1[0];
  int y1 = pos1[1];
  
  int x2 = pos2[0];
  int y2 = pos2[1];
  
  if((x1 > 8) || (x2 > 8) || (y1 > 8) || (y2 > 8))
  {
    legal = 0;
    //Index excedes board bounds
  }
  
  if((x1 < 1) || (x2 < 1) || (y1 < 1) || (y2 < 1))
  {
    legal = 0;
    //Index excedes board bounds
  }
  
  if(board[y2][x2] * type > 0)
  {
    legal = 0;
    //cannot take own piece
  }
  
  if((board[y1][x1] * type < 0) || (board[y1][x1] == 0))
  {
    legal = 0;
    //this is not your piece
  }
  
  return legal;
  
}


/*This function will return 1 if a selected piece is stuck 
to the King (as self-check is not allowed). It will return 0 otherwise*/
int testPin(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int pos[2], int pos2[2])
{
  updateBoard(boardMove, board);
  int mate = 0;
  
  int x1 = pos[0];
  int y1 = pos[1];
  
  int x2 = pos2[0];
  int y2 = pos2[1];
  
  int turn;
  int pinnedPiece = board[y1][x1];
  
  if(pinnedPiece > 0)
  {
    turn = 1;
  }
  else if(pinnedPiece < 0)
  {
    turn = 2;
  }
  
  int posCpy[2] = {0, 0};
  int pos1Cpy[2] = {0, 0};
  
  boardMove[y1][x1] = 0;
  boardMove[y2][x2] = pinnedPiece;
  
  int pinned = testCheck(boardMove, pos1Cpy, posCpy, turn);
  
  return pinned;
}



//This function will output 1 if a checkmate is on the board for the indicated turn
int testMate(int board[BOARD][BOARD], int board2[BOARD][BOARD], int checkSquares[BOARD][BOARD], int turn)
{ 

  int mate = 0;

  updateBoard(board2, board);
  
  int checkCoords[2] = {0, 0};
  int kingCoords[2] = {0, 0};
  
  int check = testCheck(board, kingCoords, checkCoords, turn);

  getCheckSquares(board, kingCoords, checkCoords, checkSquares);

  int checkX = checkCoords[0];
  int checkY = checkCoords[1];
  
  board2[checkY][checkX] = 0;
  
  int dummyCoords[2] = {0, 0};
  int dummyCoords2[2] = {0, 0};

  
  //Asks, "is the King in check with first checking piece removed?"
  int doubleCheck = testCheck(board2, dummyCoords, dummyCoords2, turn);
  
  if(doubleCheck == 1)
  {
    makeZero(checkSquares);
  }

  
  //Generates a list of legal King moves
  int kingMoves = 0;
  int piece;
  int piecePos[2];
  int legal;
  int pin;
  int i;
  int j;
   
  for(i=-1; i<=1; i++)
  {
    for(j=-1; j<=1; j++)
    {
      piecePos[0] = kingCoords[0] + j;
      piecePos[1] = kingCoords[1] + i;
  
      legal = basicMoveCheck(board, kingCoords, piecePos, turn);
      pin = testPin(board, board2, kingCoords, piecePos);
      
      if((legal == 1) && (pin == 0))
      {
        kingMoves++;
      }
    }
  }
  //If king is in check from 2 pieces it must move, assuming no pieces can block
  
  if((doubleCheck == 1) && (kingMoves == 0))
  {
    mate = 1;
  }
  
  int blockCheck = 0;
  //This if loop tests to see if any pieces can prevent check
  if((doubleCheck == 0) && (kingMoves == 0) && (check == 1))
  {
    int moveList[250];
    
    for(i=0; i<250; i++)
    {
      moveList[i] = 0;
    }
    
    blockCheck = findMoves(board, board2, checkSquares, moveList, turn);
    
    if(blockCheck == 0)
    {
      mate = 1;
    }
  }

  return mate; //Returns a final value if a King is in checkmate
}

