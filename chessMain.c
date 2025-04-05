#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD 10

/*
	Authors: Caleb Groover, Ellis Garrett, Roman Warder
	Class: CS125
	Assignment: Final Project
	Date: 3/31/2025
 
 
  Notes: Programmed by Caleb Groover, debugged by Ellis,
  comments by Caleb Groover.
  
  This program handles the multitude of functionality that
  the user can input in order to play the game. It handles
  multiple instances of error-checking, gameplay options, and
  allows for a difficulty selection as well. Enjoy!
*/


int main()
{
  //Program initializes user gameplay selections and establishes an error check variable
  int userSelect = 0;
  int errCheck = 1;  
  int newX;  /*new x position from user input*/
  int newY;  /*new y position from user input*/
  int oldX;  /*old x position from user input*/
  int oldY;   /*old y position from user input*/
  int legal;   /*The value used to determine a legal move*/
  int mate = 0;  /*The value used to determine if checkmate has occurred or not*/
  int difficulty = 1;  
  int difficulty2 = 1;  /*These two variables set the "depth" of the engine*/
  
  
  //User decides what kind of game they would like to play
  printf("Shall we play a game (1 for PvE, 2 for EvE)?\n");
  errCheck = scanf("%d", &userSelect);
  
  if (errCheck != 1)
    {
      printf("Please enter a valid input and try again\n");
    }
    
    
  else //Else statement added for error-checking. Runs if scanf above completes successfully
    {
      
    
      if (userSelect < 1 || userSelect > 4)
      {
        printf("Please enter a valid integer and try again\n");
      }
      else
      {
        printf("");
      }
      
      
        
        //This is where the actual engine running starts
        while (userSelect == 1 && mate == 0)
        {
        
          printf("What difficulty would you like to play (Options of 0-2)?: \n");
          errCheck = scanf("%d", &difficulty);
      
          if (errCheck != 1 || difficulty > 2 || difficulty < 0)
          {
            printf("Please enter a valid input and try again\n");
          }
          else
          {
          
          clock_t start, end;
          double cpu_time_used;
          start = clock();
          
          //Initializes board variables
        	int board[BOARD][BOARD];
          int boardMove[BOARD][BOARD];
          int board3[BOARD][BOARD];
          int checkSquares[BOARD][BOARD];
        	int i;
        	int j;
          int moveTo[2];
          int moveFrom[2];
          int turn = 1;
          int pieceVal;
          int castleRights[2][2] = {{1, 1}, {1, 1}};
          
      
         
         
          //This conditional sets every position value to 0 so as to initialize the background board
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
          
          //List of all legal moves is generated for first moveset
          int moveList[250];
          for(i=0; i<250; i++)
          {
            moveList[i] = 0;
          }
         
        
          
        	makeBoard(board);
          updateBoard(boardMove, board);
          
          
          turn = 1; //Turn set to "1" to track number of turns in a game
          
          
          //Initial check testing
          int checkCoords[2];
          checkCoords[0] = 0;
          checkCoords[1] = 0;
          
          int kingCoords[2];
          kingCoords[0] = 0;
          kingCoords[1] = 0;
          
          int check = testCheck(board, kingCoords, checkCoords, turn); 
          
          printf("In check? %d\nCheck from: %d, %d\n", check, checkCoords[0], checkCoords[1]);
          printf("King Coords: %d, %d\n", kingCoords[0], kingCoords[1]);
          
          int dir = testDirection(kingCoords, checkCoords);
          printf("Direction: %d\n", dir);
          
          getCheckSquares(board, kingCoords, checkCoords, checkSquares);
          
          int mate = testMate(board, boardMove, checkSquares, turn);
          
          printf("Mate? %d\n", mate);
          

          int score = scoreDif(board, boardMove, turn);
          printf("Points: %d\n", score);
    
          
          int botMove2 = 1;
    
        
          printBoardChar(board, turn);
          
          int currPos[2];
          int currMove[2];
          int playerInput;
          
        
          int input = 1;
          
          
          while ((botMove2 != 0) && (turn < 350))  //This while loop handles the user input and turn inputs
          {
            botMove2 = engineRecursion(board, boardMove, board3, turn, difficulty);
            
            if(botMove2 > 0)
            {
            
              currPos[0] = 0;
              currPos[1] = 0;
              currMove[0] = 0;
              currMove[1] = 0;
              
              if((turn % 2 == 0) || (input == 0))
              {
                //This portion of the conditional handles engine/bot movement
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
                
                
                if (legal == 1)
                {
                  makeMoveTest(board, moveFrom, moveTo, castleRights); //Makes a move if it is legal
                }
                else  //If the move is not legal, the following occurs
                {
                  while (legal != 1)
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
              
              printBoardChar(board, 1);
              turn++; //Increments turn count
            }
          }
          
          int pos[2];
          int pos2[2];
        
          pos[0] = 5;
          pos[1] = 2;
          
        
          end = clock();
          cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
          printf("Time taken: %f seconds\n", cpu_time_used);
          
  
          check = testCheck(board, kingCoords, checkCoords, turn); 
          
          printf("In check? %d\nCheck from: %d, %d\n", check, checkCoords[0], checkCoords[1]);
          printf("King Coords: %d, %d\n", kingCoords[0], kingCoords[1]);
          
          dir = testDirection(kingCoords, checkCoords);
          printf("Direction: %d\n", dir);
          
          getCheckSquares(board, kingCoords, checkCoords, checkSquares);
          
          mate = testMate(board, boardMove, checkSquares, turn);
          
          printf("Mate? %d\n", mate);
          
          score = scoreDif(board, boardMove, turn);
          printf("Points: %d\n", score);
        
  
        
        //Asks the user for another game or end program
        printf("Shall we play again (1 for y, 2 for EvE, 3 or 4 for n)?\n");
        errCheck = scanf("%d", &userSelect);
        
        
        //Error checking
        if ((userSelect == 1 || userSelect == 2) && errCheck == 1)
        {
          
          printf("");
        }
        else if ((userSelect == 1 || userSelect == 2) && errCheck != 1)
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
    
    {
      clock_t start, end;
      double cpu_time_used;
      start = clock();
    
      //initialize board variables
      
    	int board[BOARD][BOARD];
      int boardMove[BOARD][BOARD];
      int board3[BOARD][BOARD];
      int checkSquares[BOARD][BOARD];
    	int i;
    	int j;	
      int turn = 1;	 
      int castleRights[2][2] = {{1, 1}, {1, 1}};
    
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
      
      //List of all legal moves is generated for first moveset
      int moveList[250];
      for(i=0; i<250; i++)
      {
        moveList[i] = 0;
      }
    
    	makeBoard(board);
      updateBoard(boardMove, board);
      
      turn = 1;
      
      //This takes user input for the engine's difficulty
      printf("What difficulty would you like to play (Options of 0-2)?: \n");
      errCheck = scanf("%d", &difficulty2);
      
      
      if (errCheck != 1 || difficulty2 > 2 || difficulty2 < 0)
      {
        printf("Please enter a valid input and try again\n");
        return 0;
      }
      else
      {
        int checkCoords[2];
        checkCoords[0] = 0;
        checkCoords[1] = 0;
        
        int kingCoords[2];
        kingCoords[0] = 0;
        kingCoords[1] = 0;
        
        int check = testCheck(board, kingCoords, checkCoords, turn);
        
        printf("In check? %d\nCheck from: %d, %d\n", check, checkCoords[0], checkCoords[1]);
        printf("King Coords: %d, %d\n", kingCoords[0], kingCoords[1]);
        
        int dir = testDirection(kingCoords, checkCoords);
        printf("Direction: %d\n", dir);
        
        getCheckSquares(board, kingCoords, checkCoords, checkSquares);
        
        int mate = testMate(board, boardMove, checkSquares, turn);
        
        printf("Mate? %d\n", mate);
      
        
        int score = scoreDif(board, boardMove, turn);
        printf("Points: %d\n", score);
        
        
        int botMove2 = 1;
      
        printBoardChar(board, turn);
         
        int currPos[2];
        int currMove[2];
        int playerInput;
        
        
        
        //If the input is made 0, the engine plays itself
        int input = 0;
          
          //This while loop handles the majority of the bot's logic and moves, which are turn dependent
          while((botMove2 != 0) && (turn < 350))
          {
            botMove2 = engineRecursion(board, boardMove, board3, turn, difficulty2);
            
            if(botMove2 > 0)
            {
            
              currPos[0] = 0;
              currPos[1] = 0;
              currMove[0] = 0;
              currMove[1] = 0;
              
              if((turn % 2 == 1) || (input == 0))
              {
                intToMove(botMove2, currPos, currMove);
              }
              else
              {
                scanf("%d", &playerInput);
                intToMove(playerInput, currPos, currMove);
              }
              
              makeMoveTest(board, currPos, currMove, castleRights);
              printf("Bot Move (recursion): %d\n", botMove2);
              
              printBoardChar(board, 1);
              turn++;
            }
          }
          
          int pos[2];
          int pos2[2];
        
          pos[0] = 5;
          pos[1] = 2;
          
         
          
        
          end = clock();
          cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
          printf("Time taken: %f seconds\n", cpu_time_used);
          
          //Asks the user for another game or end program
          printf("Shall I play again (4 for n, 2 for y)?\n");
          errCheck = scanf("%d", &userSelect);
          }
        
        }
      }
    }
  	return 0;
}