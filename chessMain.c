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
*/

//Primary "chessMain.c" contributors include Caleb Groover and Roman Warder


int main()
{
  //Program initializes user gameplay selections and establishes an error check variable
  int userSelect = 0;
  int errCheck = 1;  
  int newX;  /*new x position from user input*/
  int newY;  /*new y position from user input*/
  int oldX;  /*old x position from user input*/
  int oldY;   /*old y position from user input*/
  int legal;
  int mate = 0;
  
  
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
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        
        //Initialize board
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
        
    
       
       
        //This conditional sets every position value to 0 so as to initialize the board
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
        
        //List of all legal moves
        int moveList[250];
        for(i=0; i<250; i++)
        {
          moveList[i] = 0;
        }
       
      
        
      	makeBoard(board);
        updateBoard(boardMove, board);
        
        
        turn = 1;
        
        
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
        
        //Engine testing
        
        int score = scoreDif(board, boardMove, turn);
        printf("Points: %d\n", score);
  
        
        int botMove2 = 1;
  
      
        printBoardChar(board, turn);
        
        int currPos[2];
        int currMove[2];
        int playerInput;
        
      
        int input = 1;
        
        
        while ((botMove2 != 0) && (turn < 350))  //THIS WHILE LOOP WAS EDITED TO SEE IF THE ROBOT WOULD PLAY AS BLACK
        {
          botMove2 = engineRecursion(board, boardMove, board3, turn, 1);
          
          if(botMove2 > 0)
          {
          
            currPos[0] = 0;
            currPos[1] = 0;
            currMove[0] = 0;
            currMove[1] = 0;
            
            if((turn % 2 == 0) || (input == 0))
            {
              intToMove(botMove2, currPos, currMove);
            }
            else    ///////////////////////////////////////////THIS IS ALL OF THE CODE THAT TAKES USER INPUT. IT DOES NOT RETURN A POSITIVE LEGAL CHECK//////////////////////////////////////
            {
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

              legal = checkLegalTest(board, boardMove, moveFrom, moveTo, turn);  ///////////////////////////////////////////LEGAL DOES NOT RETURN 1 EVER
              
              
              if (legal == 1)
              {
                makeMoveTest(board, moveFrom, moveTo);
              }
              else   ///////////////////////////////////////////THIS IS ALL OF THE CODE THAT TAKES USER INPUT. IT DOES NOT RETURN A POSITIVE LEGAL CHECK//////////////////////////////////////
              {
                printf("Please make a legal move and try again\n");
                while (legal != 1)
                {
                  printf("What column is your old piece in (1 for A, 2 for B, etc.)?: \n");
                  scanf("%d", &oldX);
                  printf("What row is your old piece in?: \n");
                  scanf("%d", &oldY);
                  
                  printf("What column would you like your new piece to be in (A for 1, B for 2, etc.)?: \n");
                  scanf("%d", &newX);
                  printf("What row would you like your new piece to be in?: \n");
                  scanf("%d", &newY);
                  
                  moveTo[0] = newX;
                  moveTo[1] = newX;
                  
                  moveFrom[0] = oldX;
                  moveFrom[1] = oldY;
              
                  legal = checkLegalTest(board, boardMove, moveFrom, moveTo, turn);
                  printf("%d\n", legal);
                }
              }
              //Take user input
            }
            
            makeMoveTest(board, currPos, currMove);
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
        

        check = testCheck(board, kingCoords, checkCoords, turn); 
        
        printf("In check? %d\nCheck from: %d, %d\n", check, checkCoords[0], checkCoords[1]);
        printf("King Coords: %d, %d\n", kingCoords[0], kingCoords[1]);
        
        dir = testDirection(kingCoords, checkCoords);
        printf("Direction: %d\n", dir);
        
        getCheckSquares(board, kingCoords, checkCoords, checkSquares);
        
        mate = testMate(board, boardMove, checkSquares, turn);
        
        printf("Mate? %d\n", mate);
        
        //Engine testing
        
        score = scoreDif(board, boardMove, turn);
        printf("Points: %d\n", score);
      

      
      //Asks the user for another game or end program
      printf("Shall we play again (1 for y, 2 for EvE, 3 or 4 for n)?\n");
      errCheck = scanf("%d", &userSelect);
      
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
    
    
    
    ///////////////////////\SEPARATION OF BOT V. BOT AND USER V. BOT/\//////////////////////////////////////// 
    
    
    
    
    while (userSelect == 2)
    {
    //Engine running against itself. Will run in a while loop, but instantly wins. I assume that the actual board is not getting reset
    {
      clock_t start, end;
      double cpu_time_used;
      start = clock();
    
      //initialize board
      
    	int board[BOARD][BOARD];
      int boardMove[BOARD][BOARD];
      int board3[BOARD][BOARD];
      int checkSquares[BOARD][BOARD];
    	int i;
    	int j;	
      int turn = 1;	 
    
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
      
      // list of all legal moves
      int moveList[250];
      for(i=0; i<250; i++)
      {
        moveList[i] = 0;
      }
    
    	makeBoard(board);
      updateBoard(boardMove, board);
      
      turn = 1;
      
    
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
      
      //engine testing
      
      int score = scoreDif(board, boardMove, turn);
      printf("Points: %d\n", score);
      
      
      int botMove2 = 1;
    
      printBoardChar(board, turn);
      
      //engine playing itself
      
      int currPos[2];
      int currMove[2];
      int playerInput;
      
      //if input is made 0, engine plays itself
      int input = 0;
      
    
      
      
      
      while((botMove2 != 0) && (turn < 350))
      {
        botMove2 = engineRecursion(board, boardMove, board3, turn, 1);
        
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
          
          makeMoveTest(board, currPos, currMove);
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
      
      //Asks the user for another game or end program.
      printf("Shall I play again (4 for n, 2 for y)?\n");
      errCheck = scanf("%d", &userSelect);
      }

    }
    
    }
  	return 0;
}