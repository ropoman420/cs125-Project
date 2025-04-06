/* 

  Chess Header File
  File: Chess.h
  
  How to Play:
  
  In our chess game there are 3 game modes to choose from 1.Player vs. Player
  2.Player vs. Engine, and 3.Engine vs. Engine.
  
  If you as the user would like to play someone else sitting at the same 
  computer, you can do so by selecting the first game mode. The way the game
  starts is by first letting the green pieces move and then the red. 
  
  The way you move your pieces is this:
    1. First input the column that the piece you want to move is in.
       The way the board is set up, you select a column A-H, which is 
       represented using corresponding numbers 1-8. A=1, B=2, C=3, ect.
       
    2. The next input is the row that the piece you want to move is on. 
       The rows range from 1-8, so you need to input accordingly.
    
    3. The program now knows what piece you would like to move. Next you
       will input the column (A-H) and row (1-9) you would like to move
       your previously selected piece too. 
    
    4. After the first player completes their move the chess board will
       flip around and allow the next user to input their move the same way
  
  If you select 2.Player vs. Engine you as the user will be playing against
  the chess engine we have designed to scan the board and make the best move
  possible according to the available pieces to be taken. 
  
  You as the user will be prompted to input the column and row as in the other
  game mode, however the board will nor flip around, the chess engine will
  make its move automatically. 
  
  If you would like to see the chess engine play itself, you can do so by 
  selecting game mode 3.Engine vs. Engine. You will then be prompted to select
  the difficulty on a scale from 0-2. This will tell the engine the 'depth' 
  of searching it will do for each move. The depth refers to how many move
  iterations the engine will scan for before making the most appropriate move. 

  This depth is capped at 2 because the time it takes in between moves grows 
  exponentially. A game played at a depth of 1 will take less than 30 seconds,
  where a game played at a depth of 2 will take more than 30 minutes.
  
  There are multiple ways the game will end:
    1. Check Mate is detected
    2. 3 Move Repetition
    3. Draw
  
*/


#ifndef CHESS_H      // Guard to prevent multiple includes
#define CHESS_H

// Including libraries used throughout the program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Defining macros
#define BOARD 10

#endif               // End CHESS_H
