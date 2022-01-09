#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "main.h"

void init(void* pUserData, Pencil* pPencil){
    int mapW, mapH;
    // Cast the user data correctly 
    UserData* pDat = (UserData*)pUserData;
    if(!pDat || !pPencil){
        RAGE_QUIT("INIT NULL parameters !");
    }
    
    // Init map
    mapW = pPencil->width *5;
    mapH = pPencil->height*5;
    createMap( &(pDat->map), mapW, mapH );
    
    // init camera
    initCamera( &(pDat->cam),
                (mapW-pPencil->width )/2,
                (mapH-pPencil->height)/2,
                pPencil->width,
                pPencil->height,
                CAMERA_SPEED_INIT );               
    
    // Init item menu
    createItemMenu( &(pDat->itemMenu), 3, 2, 4, 5);
    
    // Add layers to camera (background layer is the map)
    // Upper layers could be game windows, etc...
    addLayer( &(pDat->cam), readMap     , &(pDat->map     ) ); 
    addLayer( &(pDat->cam), readItemMenu, &(pDat->itemMenu) ); 
        
    // Init player
    initPlayer( &(pDat->player), mapW/2.0, mapH/2.0, PLAYER_INIT_SPEED, EMOT_RABBIT);

    // Init backpack
    initBackpack( &(pDat->backpack), MAX_NB_ITEMS );
    
    
    
    // [TEST] Create an axe on the map
    writeMap(&(pDat->map), (mapW/2)-5, (mapH/2)+2, AXE);        
}

