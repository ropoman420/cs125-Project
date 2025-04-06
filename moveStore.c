

#include "Chess.h"
#define MOVES 12

int moveStore(int userSelect, int movesMade[], int move, int playerInput, int botMove2)
{
  int i = MOVES;                       // Initializing Index to be the same length as the move array
  movesMade[MOVES];                    // Initializing move array size
  
  if(userSelect == 1)                  // If statement based on user gamemode selection
  {
  
    for(i= MOVES - 1; i>=2; i--)       // For loop traverses throug array to create 2 spaces
    {
      movesMade[i] = movesMade[i-2];   // Indexes out 2 spaces for new movement values
    }
  
    movesMade[0] = move;               // Makes index 1 of array the users's move
    movesMade[1] = botMove2;           // Makes index 2 of array the engine's move
  }  
  
  else if(userSelect == 2)             // else if statement for 2nd gamemode
  {
    for(i= MOVES - 1; i >= 0; i--)     // For loop traverses throug array to create 1 space
    {  
      movesMade[i] = movesMade[i-1];   // Indexes out 1 space for new movement value
    }

    movesMade[0] = botMove2;           // Makes index 1 of array the engine's move
  }
   
   
  if(movesMade[3] == movesMade[7] == movesMade[11])        // If statement to check is there is 3-fold repitition
  {
    printf("Three-Fold Repirition Found");
    return 1;            
  }
  else if(movesMade[1] == movesMade[5] == movesMade[9])
  {
    printf("Three-Fold Repirition Found");
    return 1; 
  }
  else if(movesMade[2] == movesMade[6] == movesMade[10])
  {
    printf("Three-Fold Repirition Found");
    return 1; 
  }
  else if(movesMade[0] == movesMade[4] == movesMade[8])
  {
    printf("Three-Fold Repirition Found");
    return 1; 
  }
  else
  {
    return 0; 
  }
}