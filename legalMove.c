//This function will check the legality of a player's desired move

int legalMove(newX, newY, board[][], /*what other variables?*/);
{  

  which piece? check
  
  if (newX == 9 && newY == 9)
  {
    printf("This is beyond the constraints of the board. Please try again\n");
    return 0;
  }
  else
  {
    printf("");
  }
    
    
  switch(piece number)
  {
    case (pawn):
      if (newX == /*old input*/ && newY == /*old input + 1*/ && type == -1)
      {
        /*replace enemy piece with desired piece*/
      }
      else if (newX == /*old input*/ && newY == /*old input + 1*/ && type == -1)
      {
        
      }
      else
      {
        return 0; //bad check. Move not valid
      }
    case (bishop):
    
    case (rook):
      
    case (king):
    
    case (queen): 
   
    case (knight):
     
    default:


}     