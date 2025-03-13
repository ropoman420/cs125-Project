void pieceMove(i, j, board[][], /*whatother variables?*/)
{
  int maxSize = 10;
  int validMove = 0;
  board[i][j] = 0; //Alter the previously occupied space to become empty
    
  printf("What column would you like your new piece to be in?: \n");
  scanf("%c", &newX);
  printf("What row would you like your new piece to be in?: \n");
  scanf("%d", &newY);
  validMove = legalMove(newX, newY, board[][], /*what other variables?*/);
  
  while(validMove == 0)
  {
    printf("This is not a legal move. Please try again.\n");
    validMove = legalMove(newX, newY, board[][], /*what other variables?*/);
  }
  
  newX = /*new x position from user input*/;
  newY = /*new y position from user input*/;

  board[newX][newY] = /*Piece's value*/; //Alters the newly occupied space to reflect the piece's value
    
  /*printBoard function to display new board (since function returns void otherwise*/

  
}