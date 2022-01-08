#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "./inc/main.h"

void init(void* pUserData, Pencil* pPencil){
    int mapW, mapH;
    // Cast the user data correctly 
    UserData* pDat = (UserData*)pUserData;
    if(!pDat || !pPencil){
        RAGE_QUIT("INIT NULL parameters !");
    }
    
    // Init map
    mapW = pPencil->width *2;
    mapH = pPencil->height*2;
    createMap( &(pDat->map), mapW, mapH );
    
    // init camera
    initCamera( &(pDat->cam),
                0,0,//(mapW-pPencil->width )/2,
                    //(mapH-pPencil->height)/2,
                pPencil->width,
                pPencil->height,
                CAMERA_SPEED_INIT );                
    //moveCameraTo( &(pDat->cam), mapW-pPencil->width, 0);
    
    // Init player
    initPlayer( &(pDat->player), mapW/2.0, mapH/2.0, PLAYER_INIT_SPEED, EMOT_RABBIT);
    
    // Create an axe on the map
    writeMap(&(pDat->map), (mapW/2)-5, (mapH/2)+2, AXE);        
}

