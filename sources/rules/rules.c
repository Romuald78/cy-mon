#include <stdio.h>
#include <stdlib.h>

#include "rules.h"

int canPickUp(CellType itemType){
    return ( (itemType>=START_PICK_UP) && (itemType<=END_PICK_UP) );
}

Moves playerCanMove(Player* pPlayer, Map* pMap, float deltaTime){
    CellType ctx;
    CellType cty;
    float dx;
    float dy;
    Moves movesRes = MOVES_NONE; 
    // check parameters
    if(pPlayer==NULL || pMap==NULL){
        RAGE_QUIT("Rules player move NULL parameters");        
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

void pickUpItem(Player* pPlayer, Map* pMap, Backpack* pBk){
    // Variables
    int x;
    int y;
    CellType itemType;
    // check parameters
    if(pPlayer==NULL || pMap==NULL ||pBk==NULL){
        RAGE_QUIT("Rules pickup item NULL parameters");        
    }
    // Check if the grid under the player position contains an item
    x = (int)(pPlayer->x);
    y = (int)(pPlayer->y);
    itemType = readMap(pMap, x, y);
    // Check if item can be put into the backpack
    if( canPickUp(itemType) ){
        // Put item in backpack (if enough remaining space)
        if( addItem(pBk, itemType) ){
            // Remove item from map
            writeMap(pMap, x, y, GRASS);
        } 
    }       
}



