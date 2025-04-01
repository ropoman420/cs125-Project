//This function will check the legality of a player's desired move. 
//RETURN 1 means that the move IS legal. RETURN 0 means the move is NOT legal

#define BOARD 10

int legalMove(int i, int j, int newX, int newY, int turn, int board[BOARD][BOARD], /*Are these necessary?*/int board2[BOARD][BOARD], int coord[2], int newCoord[2], );
{  
  int pieceVal;

  int x1 = coord[0]; //What were these four lines of code from???
  int y1 = coord[1];
  
  int x2 = newCoord[0];
  int y2 = newCoord[1];
  
  if (newX >= 9 || newY >= 9 || newX <= 0 || newY <= 0)
  {
    printf("This is beyond the constraints of the board. Please try again.\n");
    return 0;
  }
  else
  {
    pieceVal = board[i][j];
  }
  
  /*
  if(turn % 2 == 0)
  {
    type = -1;
  }
  else
  {
    type = 1;
  }
  
  
  
  Do we have to  check for whose turn it is or will pieceMove only play when it's the user's turn?
  */
    
    
  switch(pieceValue)
  {
    case (1 /*pawn*/):
      if (newX == (j+1) && (newY == i+1) && board[newX][newY] < 0)
      {
        /*replace enemy piece with pawn*/
        printf("You captured a piece with your pawn!\n");
        return 1;
      }
      else if (newX == (j-1) && newY == (i+1) && board[newX][newY] < 0)
      {
        /*replace enemy piece with pawn*/
        printf("You captured a piece with your pawn!\n");
        return 1;
      }
      else if (newX == j && newY == (i+1) && board[newX][newY] == 0)
      {
        /*Returns positive check since space in front of pawn is empty*/
        return 1;
      }
      else if (newX == j && i == 2 && board[newX][newY] == 0 && newY == i+2)
      {
        /*Returns positive check if space in front of pawn in empty and on initial row*/
        return 1;
      }
      else
      {
        return 0; //bad check. Move not valid
      }
   
    case (2 /*knight*/):
      
    
    
    case (3 /*bishop*/):
      if (newX == (j+1) && (newY == i+1) && board[newX][newY] < 0)
      {
        printf("You captured a piece with your pawn!\n");
        return 1;
      }
      else if (newX == (j-1) && newY == (i+1) && board[newX][newY] < 0)
      {
        printf("You captured a piece with your pawn!\n");
        return 1;
      }
      else if (newX == j && newY == (i+1) && board[newX][newY] == 0)
      {
        return 1;
      }
      else if (newX == j && i == 2 && board[newX][newY] == 0 && newY == i+2)
      {
      
      }
      else
      {
        return 0; //bad check. Move not valid
      }
    
    
    case (5 /*rook*/):
      for (i = 0; i < 8; i + 2)
      {
        
      }
      
    
      if ()
      {
        return 1;
      }
      else if ()
      {
        return 1;
      }
      else
      {
        return 0; //bad check. Move not valid
      }
    
    
    
    case (6 /*queen*/): 
     for (i = 0; i =< 8; i++)
      {
        /*run the line of sight function to check for a piece at the spot and in that row*/
      }
      
    
      if ()
      {
        return 1;
      }
      else if ()
      {
        return 1;
      }
      else
      {
        return 0; //bad check. Move not valid
      }
    case (7 /*king*/):
      if
      {
        // Ellis here, im writing a function specifically for testing the king and will just call that here
      }
      else if (type < 0 && /*los == queen*/, /*add checks for validity of taking pieces*/)
      {
          /*Kings cannot place themselves in check*/
          printf("You cannot place yourself in check.\n");
          return 0;
      }
      else if (newX == /*old input + 1*/ && newY == /*old input + 1*/ && type == -1)
      {
        
      }
      else
      {
          return 0; //bad check. Move not valid
      }
    
    
    default:
      printf("Please make a valid piece selection.\n");
      return 0;
  }

}     