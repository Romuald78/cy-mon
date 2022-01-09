#ifndef GAME_H
    #define GAME_H
    #include "errors.h"
    #include "map.h"
    #include "camera.h"
    #include "player.h"

    // --------------------------------
    // USER DATA STRUCTURE
    // --------------------------------
    typedef struct{
        Map    map;
        Camera cam;
        Player player;
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