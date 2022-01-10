#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/game_rgr.h"
#include "lib/emoticons.h"
#include "main.h"

void init(void* pUserData, Pencil* pPencil){
    int mapW, mapH;
    // Cast the user data correctly 
    UserData* pDat = (UserData*)pUserData;
    if(!pDat || !pPencil){
        RAGE_QUIT("INIT NULL parameters !");
    }
    
    // Init cell types
    initCellTypes(pDat->celltypes);
    
    fprintf(stderr, "@");
    
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
    createItemMenu( &(pDat->itemMenu), pPencil->width-6, 1, 6, 3);
    
    // Add layers to camera (background layer is the map)
    // Upper layers could be game windows, etc...
    // TODO : give pDat as data pointer to have access to all information instead of specific info ???
    addLayer( &(pDat->cam), readMap     , &(pDat->map     ) ); 
    addLayer( &(pDat->cam), readItemMenu, &(pDat->itemMenu) );    
    
    // Init player
    initPlayer( &(pDat->player), mapW/2.0, mapH/2.0, PLAYER_INIT_SPEED, EMOT_RABBIT);

    // Init backpack
    initBackpack( &(pDat->backpack), MAX_NB_ITEMS );
        
        
        
        
    // [TESTS] Create an axe on the map
    writeMap(&(pDat->map), (mapW/2)- 5, (mapH/2)+2, AXE);        
    writeMap(&(pDat->map), (mapW/2)- 6, (mapH/2)+2, HAMMER);        
    writeMap(&(pDat->map), (mapW/2)- 7, (mapH/2)+2, WRENCH);        
    writeMap(&(pDat->map), (mapW/2)- 8, (mapH/2)+2, LOCK1);        
    writeMap(&(pDat->map), (mapW/2)- 9, (mapH/2)+2, LOCK2);        
    writeMap(&(pDat->map), (mapW/2)-10, (mapH/2)+2, KEY);        
    writeMap(&(pDat->map), (mapW/2)-11, (mapH/2)+2, TOOLBOX);        
    writeMap(&(pDat->map), (mapW/2)-12, (mapH/2)+2, MAGNET);        
   
}

