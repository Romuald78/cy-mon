#include <stdio.h>
#include "./inc/moves.h"

float absf(float v){
    if(v<0.0){
        v = -v;
    }
    return v;
}

void move(int move, float speed, float deltaTime, float* pDX, float* pDY){
    // Variables
    int   dirX = 0;
    int   dirY = 0;
    *pDX = 0.0;
    *pDY = 0.0;
    // If we have something to move
    if( (move & MOVES_ALL) != MOVES_NONE){
        // now check direction
        if( (move & MOVES_HORIZ) == MOVES_LEFT){
            dirX = -1;
        }
        if( (move & MOVES_HORIZ) == MOVES_RIGHT){
            dirX = 1;
        }
        if( (move & MOVES_VERTI) == MOVES_UP){
            dirY = -1;
        }
        if( (move & MOVES_VERTI) == MOVES_DOWN){
            dirY = 1;
        }
    }
    // Move the object if needed
    *pDX = (dirX*speed*deltaTime)/1000.0;
    *pDY = (dirY*speed*deltaTime)/1000.0;
}
