#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD 10
#define RED "\x1b[31m"
#define GREEN "\e[0;32m"
#define RESET "\x1b[0m"

/*
  This program was primarily written by Ellis. Debugging by
  Caleb and Roman. Comments by Caleb Groover.
  This program handles the initialization of the entire chess board,
  from setting initial space values to printing the letters and colors
  associated with said letters.
*/


//This function initializes the chess board's background values
void makeBoard(int board[BOARD][BOARD])
{
	int i;
	int j;
	
	for(i=0; i<BOARD; i++)
	{
		for(j=0; j<BOARD; j++)
		{
			if(i==2)
			{
				board[i][j] = 1;
			}

			if(i==7)
			{
				board[i][j] = -1;
			}
      
      if((i>2) && (i<7))
      {
        board[i][j] = 0;
      }

			if((i==0) || (j==0) || (i==9) || (j==9))
			{
				board[i][j] = 9;
			}
		}
	}

	// rooks
	board[1][1] = 5;
	board[1][8] = 5;
	board[8][1] = -5;
	board[8][8] = -5;
	
	// knights
	board[1][2] = 2;
	board[1][7] = 2;
	board[8][2] = -2;
	board[8][7] = -2;

	// bishops
	board[1][3] = 3;
	board[1][6] = 3;
	board[8][3] = -3;
	board[8][6] = -3;

	// queens
	board[1][4] = 6;
	board[8][4] = -6;

	// Kings
	board[1][5] = 7;
	board[8][5] = -7;

	// Pawns = 1
	// boarder = 9
	// none = 0
}


//This function prints the colors and pound signs that enclose the board
void printBoardNum(int board[BOARD][BOARD])
{
	int i;
	int j;

	for(i=0; i<BOARD; i++)
	{	
		for(j=0; j<BOARD; j++)
		{
			if(board[i][j] == 9)
			{
				printf("# ");
			}
			else if(board[i][j] < 0)
			{
				printf(RED "%d" RESET " ", (-1 * board[i][j]));
			}
			else
			{
				printf("%d ", board[i][j]);
			}
		}

		printf("\n");

	}


}


//This function prints the column footers for the board
void letterIndex(char str[5], int index)
{
  strcpy(str, "");

  switch(index)
  {
    case 1:
      strcpy(str, "A");
      break;
    case 2:
      strcpy(str, "B");
      break;
    case 3:
      strcpy(str, "C");
      break;
    case 4:
      strcpy(str, "D");
      break;
    case 5:
      strcpy(str, "E");
      break;
    case 6:
      strcpy(str, "F");
      break;
    case 7:
      strcpy(str, "G");
      break;
    case 8:
      strcpy(str, "H");
      break;
    default:
      strcpy(str, "-");
      break;
      
  }

}


//This function takes a value for a specific tile/piece and converts it to the appropriate character
void printSquare(int board[BOARD][BOARD], int i, int j)
{
  int absVal = makePos(board[i][j]);
      
  char charToPrint[5];

  switch(absVal)
  {
    case 0:
		  strcpy(charToPrint, " ");
		  break;
		case 1:
		  strcpy(charToPrint, "P");
		  break;
		case 2:
		  strcpy(charToPrint, "N");
		  break;
		case 3:
		  strcpy(charToPrint, "B");
		  break;
		case 5:
		  strcpy(charToPrint, "R");
		  break;
		case 6:
		  strcpy(charToPrint, "Q");
		  break;
		case 7:
		  strcpy(charToPrint, "K");
		  break;
		case 9:
		  strcpy(charToPrint, "#");
		  break;
		default:
		  strcpy(charToPrint, "-");
		  break;
  }
      
  if((absVal==9) && (j==0) && (i!=0) && (i!=9))
  {
    sprintf(charToPrint, "%d", i);
  }
  if((absVal==9) && (i==0) && (j!=0) && (j!=9))
  {
    letterIndex(charToPrint, j);
  }

  if(board[i][j] < 0)
  {
    printf(RED " %s " RESET "|", charToPrint);
  }
  else if((board[i][j] > 0) && (board[i][j] < 9))
  {
    printf(GREEN " %s " RESET "|", charToPrint);
  }
  else if(board[i][j] == 0)
  {
    printf(" %s |", charToPrint);
  }
  else
  {
    printf(" %s |", charToPrint);
  }
}


//This function prints the grid style applied to the entire chess board
void printBoardChar(int board[BOARD][BOARD], int turn)
{
	int i;
	int j;
  
  printf("+---+---+---+---+---+---+---+---+---+---+\n|");
  
  if((turn % 2) != 0)
  {
	  for(i=9; i>=0; i--)
	  {
		  for(j=0; j<BOARD; j++)
		  {
			  printSquare(board, i, j);
		  }

		  printf("\n+---+---+---+---+---+---+---+---+---+---+\n");
      
      if(i != 0)
      {
        printf("|");
      }
	  }
  }
  else
  {
  for(i=0; i<BOARD; i++)
	  {
		  for(j=9; j>=0; j--)
		  {
			  printSquare(board, i, j);
		  }

		  printf("\n+---+---+---+---+---+---+---+---+---+---+\n");
      
      if(i != 9)
      {
        printf("|");
      }
	  }
  }
}
