//This function will check the legality of a player's desired move. 
//RETURN 1 means that the move IS legal. RETURN 0 means the move is NOT legal

int legalMove(newX, newY, board[][], /*what other variables?*/);
{  

  /*which piece? check
  type == */ 
  
  if (newX > 8 || newY > 8 || newX < 1 || newY < 1)
  {
    printf("This is beyond the constraints of the board. Please try again\n");
    return 0;
  }
  else
  {
    printf("");
  }
    
    
  switch(type)
  {
    case (1 /*pawn*/):
      if (newX == /*old input + 1*/ && newY == /*old input + 1*/ && type < 0)
      {
        /*replace enemy piece with pawn*/
        return 1;
      }
      else if (newX == /*old input - 1*/ && newY == /*old input + 1*/ && type < 0)
      {
        /*replace enemy piece with pawn*/
        return 1;
      }
      else if (newX == /*old input*/ && newY == /*old input + 1*/ && board[newX][newY] == 0)
      {
        return 1;
        /*Returns positive check if space in front of pawn in empty*/
      }
      else if (newX == /*initial x input*/ && /*old y input*/ == 2 && board[newX][newY] == 0 && /*new y input*/ == /*old y input + 2*/)
      {
        return 1;
        /*Returns positive check if space in front of pawn in empty and on initial row*/
      }
      else
      {
        return 0; //bad check. Move not valid
      }
   
    case (2 /*knight*/):
    
    
    
    case (3 /*bishop*/):
      for (i = 0; i =< 8; i + 2)
      {
        /*run line of sight function to check for piece*/
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