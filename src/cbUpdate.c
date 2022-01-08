#include <stdio.h>
#include <stdlib.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "./inc/main.h"
#include "./inc/rules.h"


int update(void* pUserData, Pencil* pPencil, double deltaTime){
    int leave = 0;
    float camX;
    float camY;
    Moves moveRes = MOVES_NONE;
    // printf("UPDATE %.2f \n", deltaTime);       
    // Cast the user data correctly 
    UserData* pDat = (UserData*)pUserData;
    if(!pDat || !pPencil){
        exit(ERR_NULL);
    }
    // Check if the player can move (according to blocking cells)
    moveRes = playerCanMove(&(pDat->player), &(pDat->map), deltaTime);
    // Update player position
    updatePlayer( &(pDat->player), deltaTime, &moveRes);        
    // Set camera center to player position
    camX = pDat->player.x - (pPencil->width /2);
    camY = pDat->player.y - (pPencil->height/2);
    setCameraTo( &(pDat->cam), camX, camY);
    // Make the camera does not goes out of the grid,
    // even if the player is on the edge
    saturateCamera( &(pDat->cam), 0, 0,
                    pDat->map.W-pDat->cam.W,
                    pDat->map.H-pDat->cam.H );
                    
    // Return boolean to indicate if we have to leave the game or not
    return leave;    
}

