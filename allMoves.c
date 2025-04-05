#include <stdio.h>
#include <stdlib.h>

#define BOARD 10

// adds a move to end of legal move list
void addToList(int moveList[], int move)
{
  int i = 0;
  
  while(moveList[i] != 0)
  {
    i++;
  }
  
  moveList[i] = move;
}

// similar to rayLos but only adds squares to move list, more efficient for engine use
void rayLegal(int board[BOARD][BOARD], int moveList[], int pos[2], int xdir, int ydir, int type)
{
  int curX = pos[0] + xdir;
  int curY = pos[1] + ydir;
  
  int move = 0;
  int moveTo[2];

  if((xdir != 0) || (ydir != 0))
  {
    while((board[curY][curX] == 0) || (board[curY][curX] == 4) || (board[curY][curX] == -4))
    {
      moveTo[0] = curX;
      moveTo[1] = curY;
      
      move = moveToInt(pos, moveTo);
      
      addToList(moveList, move);
      
      curX += xdir;
      curY += ydir;
    }
    
    if((board[curY][curX] * type < 1) && (board[curY][curX] != 9))
    {
      moveTo[0] = curX;
      moveTo[1] = curY;
      
      move = moveToInt(pos, moveTo);
      
      addToList(moveList, move);
    }
  }
}

// this will be the only direction a pinned piece is allowed to move
void pinDirection(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int pieceX, int pieceY, int turn, int direction[2])
{
  direction[0] = 0;
  direction[1] = 0;
  
  int kingCoords[2] = {0, 0};
  int checkCoords[2] = {0, 0};
  
  updateBoard(boardMove, board);
  
  boardMove[pieceY][pieceX] = 0;
  
  int pinned = testCheck(boardMove, kingCoords, checkCoords, turn);
  
  if(pinned == 1)
  {
    direction[0] = (checkCoords[0] - pieceX);
    direction[1] = (checkCoords[1] - pieceY);
    
    if(direction[0] != 0)
    {
      direction[0] /= makePos(checkCoords[0] - pieceX);
    }
    
    if(direction[1] != 0)
    {
      direction[1] /= makePos(checkCoords[1] - pieceY);
    }
  }
}

int moves(int board[BOARD][BOARD], int boardMove[BOARD][BOARD], int moveList[], int turn, int castleRights[2][2])
{
  int type;
  
  int posY;
  int posX;
  
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  int i = 0;
  int j, k, l;
  
  // clear list
  while(moveList[i] != 0)
  {
    moveList[i] = 0;
    i++;
  }
  
  int board3[BOARD][BOARD];
  int checkSquares[BOARD][BOARD];
  
  // add all legal moves to list
  
  // outer loops find pieces to move
  
  int piecePos[2] = {0, 0};
  
  int i2, j2, iPos, jPos;
  int positivePiece;
  int move;
  int direction[2] = {0, 0};
  
  int kingCoords[2] = {0, 0};
  int checkCoords[2] = {0, 0};
  int doubleCheckCoords[2] = {0, 0};
  int kingMove[2] = {0, 0};
  int moveTo[2] = {0, 0};
  int moveToLoc;
  
  int check = testCheck(board, kingCoords, checkCoords, turn);
  
  updateBoard(boardMove, board);

  // adding king moves to list
  for(i=-1; i<=1; i++)
  {
    for(j=-1; j<=1; j++)
    {
      kingMove[0] = kingCoords[0] + j;
      kingMove[1] = kingCoords[1] + i;
      
      if(checkLegalTest(board, boardMove, kingCoords, kingMove, turn, castleRights) == 1)
      {
        move = moveToInt(kingCoords, kingMove);
        addToList(moveList, move);
      }
    }
  }
  
  // if doublecheck, exit before checking moves for non-king pieces
  if(check == 1)
  {
    boardMove[checkCoords[1]][checkCoords[0]] = 9;
    int doublecheck = testCheck(boardMove, kingCoords, doubleCheckCoords, turn);
    
    if(doublecheck == 1)
    {
      return 0;
    }
    
    updateBoard(boardMove, board);
  }
  
  if(check == 1)
  {
    // find all moves that can block check
    
    for(i=0; i<BOARD; i++)
    {
      for(j=0; j<BOARD; j++)
      {
        checkSquares[i][j] = 0;
      }
    }
    
    getCheckSquares(board, kingCoords, checkCoords, checkSquares);
    findMoves(board, boardMove, checkSquares, moveList, turn);
  }
  else
  {
    // seach board for every piece of correct type
    i2 = 1;
    //printf("2\n");
    for(i=7; i>=0; i--)
    {
      j2 = 1;
      for(j=7; j>=0; j--)
      {
        //if movable piece at coordinates
        if(board[i2][j2] * type > 0)
        {
          //printf("%d, %d \n", j2, i2);
          
          positivePiece = board[i2][j2];
          piecePos[0] = j2;
          piecePos[1] = i2;
          //printf("%d, %d\n", j2, i2);
          if(makePos(positivePiece) != 7)
          {
            pinDirection(board, boardMove, j2, i2, turn, direction);
          }
          //printf("%d, %d\n", j2, i2);

          switch(makePos(positivePiece))
          {
            case 1:
              // pawns
              
              // moving forward
              if(((direction[0] == 0) && (direction[1] == 0)) || ((direction[1] != 0) && (direction[0] == 0)))
              {
                if(board[i2+type][j2] == 0)
                {
                  moveTo[0] = piecePos[0];
                  moveTo[1] = piecePos[1] + type;
                
                  move = moveToInt(piecePos, moveTo);
                  addToList(moveList, move);
                  
                  // moving forward 2?
                  if((board[i2-2][j2] == 0) && (type == -1) && (i2 == 7))
                  {
                    moveTo[1] -= 1;
                    move = moveToInt(piecePos, moveTo);
                    addToList(moveList, move);
                  }
                  
                  if((board[i2+2][j2] == 0) && (type == 1) && (i2 == 2))
                  {
                    moveTo[1] += 1;
                    move = moveToInt(piecePos, moveTo);
                    addToList(moveList, move);
                  }
                }
              }
              
              // capturing diagonally
              if(((direction[0] == 0) && (direction[1] == 0)) || ((direction[1] == 1) && (direction[0] == 1)) || ((direction[1] == -1) && (direction[0] == -1)))
              {
                if((board[i2+type][j2+type]*type < 0) && (board[i2+type][j2+type] != 9))
                {
                  moveTo[0] = piecePos[0] + type;
                  moveTo[1] = piecePos[1] + type;
                  move = moveToInt(piecePos, moveTo);
                  addToList(moveList, move);
                }
              }
              
              if(((direction[0] == 0) && (direction[1] == 0)) || ((direction[1] == 1) && (direction[0] == -1)) || ((direction[1] == -1) && (direction[0] == 1)))
              {
                if((board[i2+type][j2-type]*type < 0) && (board[i2+type][j2-type] != 9))
                {
                  moveTo[0] = piecePos[0] - type;
                  moveTo[1] = piecePos[1] + type;
                  move = moveToInt(piecePos, moveTo);
                  addToList(moveList, move);
                }
              }
              break;
            case 2:
              // knights 
              if((direction[0] == 0) && (direction[1] == 0))
              {
                for(k=-2; k<=2; k++)
                {
                  for(l=-2; l<=2; l++)
                  {
                    if(((makePos(k) == 1) && (makePos(l) == 2)) || ((makePos(k) == 2) && (makePos(l) == 1)))
                    {
                      moveTo[0] = piecePos[0] + k;
                      moveTo[1] = piecePos[1] + l;
                      
                      if((moveTo[0] > 8) || (moveTo[0] < 1) || (moveTo[1] > 8) || (moveTo[1] < 1))
                      {
                        continue;
                      }
                      
                      if(board[moveTo[1]][moveTo[0]]*type <= 0)
                      {
                        move = moveToInt(piecePos, moveTo);
                        addToList(moveList, move);
                      }
                    }
                  }
                }
              }
              
              break;
            case 3:
              // bishops
              posX = direction[0];
              posY = direction[1];
            
              if((direction[0] == 0) && (direction[1] == 0))
              {
                rayLegal(board, moveList, piecePos, 1, 1, type);
                rayLegal(board, moveList, piecePos, 1, -1, type);
                rayLegal(board, moveList, piecePos, -1, 1, type);
                rayLegal(board, moveList, piecePos, -1, -1, type);
                break;
              }
              
              if((makePos(posX) == 1) && (makePos(posY) == 1))
              {
                rayLegal(board, moveList, piecePos, direction[0], direction[1], type);
                rayLegal(board, moveList, piecePos, -direction[0], -direction[1], type);
              }
              break;
            case 5:
              // rooks
              if((direction[0] == 0) && (direction[1] == 0))
              {
                rayLegal(board, moveList, piecePos, 0, 1, type);
                rayLegal(board, moveList, piecePos, 1, 0, type);
                rayLegal(board, moveList, piecePos, 0, -1, type);
                rayLegal(board, moveList, piecePos, -1, 0, type);
                break;
              }
              
              if((direction[0] == 0) || (direction[1] == 0))
              {
                rayLegal(board, moveList, piecePos, direction[0], direction[1], type);
                rayLegal(board, moveList, piecePos, -direction[0], -direction[1], type);
              }
              break;
            case 6:
              // queens
              if((direction[0] == 0) && (direction[1] == 0))
              {
                for(k=-1; k<=1; k++)
                {
                  for(l=-1; l<=1; l++)
                  {
                    if((k != 0) || (l != 0))
                    {
                      rayLegal(board, moveList, piecePos, k, l, type);
                    }
                  }
                }
              }
              else
              {
                rayLegal(board, moveList, piecePos, direction[0], direction[1], type);
                rayLegal(board, moveList, piecePos, -direction[0], -direction[1], type);
              }
              break;
          }         
        }
        
        // i and j loop from board edges to the center, such that the engine while find moves playing in the center of the board first
        if(j % 2 == 0)
        {
          jPos = j * -1;
        }
        else
        {
          jPos = j;
        }
        j2 += jPos;
      }
      
      if(i % 2 == 0)
      {
        iPos = i * -1;
      }
      else
      {
        iPos = i;
      }
      i2 += iPos;
    }
  }
}
