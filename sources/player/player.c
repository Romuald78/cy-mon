#include <stdio.h>
#include <math.h>
#include "player.h"

void initPlayer(Player* p, float x, float y, float speed, char* disp){
    // check parameters
    if(p == NULL){
        RAGE_QUIT("Bad player pointer !");
    }
    // Fill structure    
    p->x         = x;
    p->y         = y;
    p->speed     = speed;
    p->display   = disp;
    p->move      = MOVES_NONE;
    p->pickingUp = 0;
}

// pMoveLimit is a limitation of the allowed movement
void updatePlayer(Player* p, float deltaTime, Moves* pMoveLimit){
    float dx = 0;
    float dy = 0;
    // check parameters
    if(p == NULL){
        RAGE_QUIT("Bad player pointer !");
    }
    // Get dx dy move
    move(p->move, p->speed, deltaTime, &dx, &dy);
    if(pMoveLimit != NULL){
        if( ((*pMoveLimit) & MOVES_HORIZ) == MOVES_NONE ){
            dx = 0;
        }
        if( ((*pMoveLimit) & MOVES_VERTI) == MOVES_NONE ){
            dy = 0;
        }
    }
    // If moving in diagonal, set a coef to limit movement speed
    if( absf(absf(dx)-absf(dy)) <= 0.00001 ){
        dx /= sqrt(2);
        dy /= sqrt(2);
    }
    // Update position according to both player input AND map limitations
    p->x += dx;
    p->y += dy;
}


