

#include "Chess.h"

/*
	Authors: Caleb Groover, Ellis Garrett, Roman Warder
	Class: CS125
	Assignment: Final Project
	Date: 4/6/2025
 
 
  Notes: Programmed by Caleb Groover, debugged by Ellis,
  comments by Caleb Groover.
  
  This program handles the multitude of functionality that
  the user can input in order to play the game. It handles
  multiple instances of error-checking, gameplay options, and
  allows for a difficulty selection as well. Enjoy!
*/


int main()
{
  // Program initializes user gameplay selections and establishes an error check variable
  int userSelect = 0;
  int errCheck = 1; 
  int errCheck2 = 1;  
  int newX;  /*new x position from user input*/
  int newY;  /*new y position from user input*/
  int oldX;  /*old x position from user input*/
  int oldY;   /*old y position from user input*/
  int legal;   /*The value used to determine a legal move*/
  int mate = 0;  /*The value used to determine if checkmate has occurred or not*/
  int check;
  int checkCoords[2];
  int kingCoords[2];
  int difficulty = 1;  
  int difficulty2 = 1;  /*These two variables set the "depth" of the engine*/
  int currPos[2];
  int currMove[2];
  int playerInput;
  int input;
  int botMove2;
  
  // variables for different draw conditions
  int draw1;
  int draw2;
  int draw3;
  
  int i, j; // loop variables
  
  // establishes and populates matricies that define board. Various board copies are passed to functions to experiment with moves
  
  int board[BOARD][BOARD];        // matrix used to represent board
  int boardMove[BOARD][BOARD];    // matrix used by functions to try moves without changing main board
  int board3[BOARD][BOARD];       // additional copy of board used in several functions 
  int checkSquares[BOARD][BOARD];	// this matrix contains squares pertaining to a check
  int turn = 1;	 
  int castleRights[2][2] = {{1, 1}, {1, 1}};
  
  // initializes matricies at zero, so they can be passed to functions without error
	for(i=0; i<BOARD; i++)
	{
		for(j=0; j<BOARD; j++)
		{
			board[i][j] = 0;
      board3[i][j] = 0;
      boardMove[i][j] = 0;
      checkSquares[i][j] = 0;
		}
	}
 
  int moveTo[2];
  int moveFrom[2];
  
  // List of all legal moves is generated for first moveset
  int moveList[250];
  for(i=0; i<250; i++)
  {
    moveList[i] = 0;
  }
  
  
  // User decides what kind of game they would like to play
  printf("Shall we play a game (1 for PvP or PvE, 2 for EvE)?\n");
  errCheck = scanf("%d", &userSelect);
  
  if(errCheck != 1)
  {
    printf("Please enter a valid input and try again\n");
  }

  else // Else statement added for error-checking. Runs if scanf above completes successfully
  {
    if(userSelect < 1 || userSelect > 4)
    {
      printf("Please enter a valid integer and try again\n");
    }
    else
    {
      printf("");
    }
      
      // This is where the actual engine running starts
      while(userSelect == 1)
      {
        difficulty = 0;
        errCheck = 1;
        input = 0;
        
        printf("Would you like to play:\n1: The chess engine\n2: A friend\n");
        errCheck = scanf("%d", &input);
        
        if(errCheck != 1 || input > 2 || input < 1)
        {
          printf("Please enter a valid input and try again\n");
          continue;
        }
        
        input-=1;
        
        if(input == 0)
        {
          printf("What difficulty would you like to play (Options of 0-2)?: \n");
          errCheck = scanf("%d", &difficulty);
        }
    
        if(errCheck != 1 || difficulty > 2 || difficulty < 0)
        {
          printf("Please enter a valid input and try again\n");
        }
        else
        {
        
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        
        // castle rights initialized as 1s
        castleRights[0][0] = 1;
        castleRights[0][1] = 1;
        castleRights[1][0] = 1;
        castleRights[1][1] = 1;
           
      	makeBoard(board);
        updateBoard(boardMove, board);
        
        // Turn set to "1" to track number of turns in a game
        turn = 1;
        
        // Initial check testing
        checkCoords[0] = 0;
        checkCoords[1] = 0;
        kingCoords[0] = 0;
        kingCoords[1] = 0;
       
        botMove2 = 1;   
        printBoardChar(board, turn);
        
        while((botMove2 != 0) && (turn < 350))  //This while loop handles the user input and turn inputs
        {
          botMove2 = engineRecursion(board, boardMove, board3, turn, 0, castleRights);
          
          if(botMove2 > 0)
          {
            currPos[0] = 0;
            currPos[1] = 0;
            currMove[0] = 0;
            currMove[1] = 0;
            
            if((turn % 2 == 0) && (input == 0))
            {
              //This portion of the conditional handles engine/bot movement
              botMove2 = engineRecursion(board, boardMove, board3, turn, difficulty, castleRights);
              intToMove(botMove2, currPos, currMove);
              makeMoveTest(board, currPos, currMove, castleRights);
            }
            else //This is all of the code that takes user input/coordinates
            {
              printf("What column is your old piece in (1 for A, 2 for B, etc.)?: \n");
              scanf("%d", &oldX);
              printf("What row is your old piece in?: \n");
              scanf("%d", &oldY);
              
              printf("What column would you like your new piece to be in (A for 1, B for 2, etc.)?: \n");
              scanf("%d", &newX);
              printf("What row would you like your new piece to be in?: \n");
              scanf("%d", &newY);
              
              moveTo[0] = newX;  //Converts user input into a matrix-style format
              moveTo[1] = newY;
              
              moveFrom[0] = oldX;
              moveFrom[1] = oldY;

              legal = checkLegalTest(board, boardMove, moveFrom, moveTo, turn, castleRights); //Ensures a legal move
              
              
              if(legal == 1)
              {
                makeMoveTest(board, moveFrom, moveTo, castleRights); //Makes a move if it is legal
              }
              else  //If the move is not legal, the following occurs
              {
                while(legal != 1)
                {
                  //This while loop will reiterate until the user inputs proper coordinates
                  printf("\nPlease make a legal move and try again\n");
                  printf("What column is your old piece in (1 for A, 2 for B, etc.)?: \n");
                  scanf("%d", &oldX);
                  printf("What row is your old piece in?: \n");
                  scanf("%d", &oldY);
                  
                  printf("What column would you like your new piece to be in (A for 1, B for 2, etc.)?: \n");
                  scanf("%d", &newX);
                  printf("What row would you like your new piece to be in?: \n");
                  scanf("%d", &newY);
                  
                  moveTo[0] = newX;
                  moveTo[1] = newY;
                  
                  moveFrom[0] = oldX;
                  moveFrom[1] = oldY;
              
                  legal = checkLegalTest(board, boardMove, moveFrom, moveTo, turn, castleRights);
                }
                
                makeMoveTest(board, moveFrom, moveTo, castleRights);
                //This will make the actual move

              }
            }
            printf("Bot Move (recursion): %d\n", botMove2);
            
            if(input == 0)
            {
              printBoardChar(board, 1);
            }
            else
            {
              printBoardChar(board, turn+1);
            }
            turn++; //Increments turn count
          }
        }
        
        check = testCheck(board, kingCoords, checkCoords, turn);       
        getCheckSquares(board, kingCoords, checkCoords, checkSquares);          
        mate = testMate(board, boardMove, checkSquares, turn);
        
        if(check == 1)
        {
          if(turn % 2 == 1)
          {
            printf("Black wins by checkmate on move %d!\n", turn);
          }
          else
          {
            printf("White wins by checkmate on move %d!\n", turn);
          }
        }
        else
        {
          printf("The game ends in a draw, after %d moves!\n", turn);
        }

        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Time taken: %f seconds\n", cpu_time_used);
      
        //Asks the user for another game or end program
        printf("Shall we play again (1 for y, 2 for EvE, 3 or 4 for n)?\n");
        errCheck = scanf("%d", &userSelect);
        
        
        //Error checking
        if((userSelect == 1 || userSelect == 2) && errCheck == 1)
        { 
          printf("");
        }
        else if((userSelect == 1 || userSelect == 2) && errCheck != 1)
        {
          printf("Please make a valid selection and try again\n");
          while (errCheck != 1)
          {
            printf("Shall we play again (1 for y, 2 for EvE, 3 or 4 for n)?\n");
            errCheck = scanf("%d", &userSelect);
          }
        }
        else
        {
          return 0;
        }
      }   
    }
    
    ///////////////////////\SEPARATION OF BOT V. BOT AND USER V. BOT/\//////////////////////////////////////// 
      
    while (userSelect == 2)
    {
      clock_t start, end;
      double cpu_time_used;
      start = clock();
	
      turn = 1;	
       
      // castle rights initialized as 1s
      castleRights[0][0] = 1;
      castleRights[0][1] = 1;
      castleRights[1][0] = 1;
      castleRights[1][1] = 1;
    
    	makeBoard(board);
      updateBoard(boardMove, board);

      //This takes user input for the engine's difficulty
      printf("What difficulty would you like for white? (Options of 0-2)?: \n");
      errCheck = scanf("%d", &difficulty2);
      
      printf("What difficulty would you like for black? (Options of 0-2)?: \n");
      errCheck2 = scanf("%d", &difficulty);
      
      if(errCheck != 1 || errCheck2 != 1 || difficulty2 > 2 || difficulty2 < 0 || difficulty > 2 || difficulty < 0)
      {
        printf("Please enter a valid input and try again\n");
        continue;
      }
      else
      {
        checkCoords[0] = 0;
        checkCoords[1] = 0;
        kingCoords[0] = 0;
        kingCoords[1] = 0;
        
        botMove2 = 1;
      
        printBoardChar(board, turn);
          
        //This while loop handles the majority of the bot's logic and moves, which are turn dependent
        while((botMove2 != 0) && (turn < 350))
        {
          if(turn % 2 == 1)
          {
            botMove2 = engineRecursion(board, boardMove, board3, turn, difficulty2, castleRights);
          }
          else
          {
            botMove2 = engineRecursion(board, boardMove, board3, turn, difficulty, castleRights);
          }
          
          if(botMove2 > 0)
          {
            currPos[0] = 0;
            currPos[1] = 0;
            currMove[0] = 0;
            currMove[1] = 0;

            intToMove(botMove2, currPos, currMove);
            
            makeMoveTest(board, currPos, currMove, castleRights);
            printf("Bot Move (recursion): %d\n", botMove2);
            
            printBoardChar(board, 1);
            turn++;
          }
        }
        
        check = testCheck(board, kingCoords, checkCoords, turn);
        getCheckSquares(board, kingCoords, checkCoords, checkSquares);
        mate = testMate(board, boardMove, checkSquares, turn);
        
        if(check == 1)
        {
          if(turn % 2 == 1)
          {
            printf("Black wins by checkmate on move %d!\n", turn);
          }
          else
          {
            printf("White wins by checkmate on move %d!\n", turn);
          }
        }
        else
        {
          printf("The game ends in a draw, after %d moves!\n", turn);
        }
        
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Time taken: %f seconds\n", cpu_time_used);
        
        //Asks the user for another game or end program
        printf("Shall I play again (4 for n, 2 for y)?\n");
        errCheck = scanf("%d", &userSelect);     
      }      
    }
  }
	return 0;
}