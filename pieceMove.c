#define BOARD 10

void pieceMove(int i, int j, int newX, int newY, int turn, int board[BOARD][BOARD], /*whatother variables?*/)
{
  int newX = 0;  /*new x position from user input*/
  int newY = 0;  /*new y position from user input*/
  int validMove = 0;  //return value from legalMove.c program
    
  printf("What column would you like your new piece to be in (A for 1, B for 2, etc.)?: \n");
  scanf("%d", &newX);
  printf("What row would you like your new piece to be in?: \n");
  scanf("%d", &newY);

  validMove = legalMove(i, j, newX, newY, turn, board[][], /*what other variables?*/);
  
  while(validMove == 0)
  {
    printf("This is not a legal move. Please try again.\n");
    validMove = legalMove(i, j, newX, newY, turn, board[][], /*what other variables?*/);
  }
  

  board[i][j] = 0;    //Alter the previously occupied space to become empty
  board[newX][newY] = piece; //Alters the newly occupied space to reflect the piece's value
    
  /*printBoard function to display new board (since function returns void otherwise*/

  
}