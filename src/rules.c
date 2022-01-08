#include <stdio.h>
#include <stdlib.h>

#include "./inc/errors.h"
#include "./inc/player.h"
#include "./inc/moves.h"
#include "./inc/map.h"


Moves playerCanMove(Player* pPlayer, Map* pMap, float deltaTime){
    CellType ctx;
    CellType cty;
    float dx;
    float dy;
    Moves movesRes = MOVES_NONE; 
    // check parameters
    if(pPlayer==NULL || pMap==NULL){
        RAGE_QUIT("Player move NULL parameters");        
    }
    // Store result equal to player requested movement
    movesRes = pPlayer->move;
    // Compute the movement    
    move(pPlayer->move, pPlayer->speed, deltaTime, &dx, &dy);
    // Read grid on both axis
    ctx = readMap(pMap, (int)(dx+pPlayer->x), (int)(   pPlayer->y) );
    cty = readMap(pMap, (int)(   pPlayer->x), (int)(dy+pPlayer->y) );
    // Check if we can move on both axis
    if( ctx & BLOCKING ){
        // Force the move on X to NONE
        movesRes &= ~MOVES_HORIZ;        
    }
    if( cty & BLOCKING ){
        // Force the move on Y to NONE
        movesRes &= ~MOVES_VERTI;        
    }
    // Check if the remaining moves is allowed too (e.g. if moving in diagonal)
    ctx = readMap(pMap, (int)(dx+pPlayer->x), (int)(dy+pPlayer->y) );
    if( ctx & BLOCKING ){
        // Remove one of the remaining axis in case thare are both remaining
        if(movesRes & MOVES_HORIZ){
            // Force the move on Y to NONE (if not already the case)
            movesRes &= ~MOVES_VERTI;        
        }
    }    
    // Return the remaining allowed movements
    return movesRes;
}


