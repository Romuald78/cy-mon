// TODO
// add a way to get any data using GenericRead callbacks (pDat pointer could be the solution)
// add a way to get system time for the game (may be using getTimeMs function from the API : to check)
// this way we could add some blinking operations or anything related to time


#ifndef GAME_H
    #define GAME_H
    #include "errors.h"
    #include "map.h"
    #include "camera.h"
    #include "player.h"
    #include "backpack.h"
    #include "menus.h"


    // --------------------------------
    // USER DATA STRUCTURE
    // --------------------------------
    typedef struct{
        Map      map;
        Camera   cam;
        Player   player;
        Backpack backpack;
        Menu     itemMenu;
        char*    celltypes[NB_CELL_TYPES]; 
    } UserData;


    // --------------------------------
    // GAME CALLBACKS
    // --------------------------------
    void init  (void* pUserData, Pencil* pPencil);
    void event (void* pUserData, Event* pEv);
    int  update(void* pUserData, Pencil* pPencil, double deltaTime);
    void draw  (void* pUserData, Pencil* pPencil);
    void finish(void* pUserData);
    

    
#endif
