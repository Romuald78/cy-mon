#include <stdio.h>
#include <stdlib.h>
#include "libGameRGR.h"

#define RGB(r,g,b) ((r<<16)|(g<<8)|(b))

typedef struct {
    double time;
} UserData;

void init(void* pUSerData, Canvas* pCanvas){
    printf("[INIT]\n");
}

void event(void* pUserData, Canvas* pCanvas, Event* pEvt){
    //printf("[EVENT]>\n");
    if(pEvt==NULL){
        rageQuit(3000, "EVENT : Event pointer is NULL !");
    }
    if(pEvt->keyCode == KEY_LEFT && pEvt->keyState == KEY_PRESSED){
        printf("LEFT\n");
    }
}

int  update(void* pUserData, Canvas* pCanvas, double deltaTime){
    //printf("[UPDATE]\n");
    // TODO test params
    //
    UserData* pData = (UserData*)pUserData;    
    pData->time += deltaTime;
    
    
    return 0;
}

void draw(void* pUserData, Canvas* pCanvas, GFX* pGfx){
    //printf("[DRAW]\n");
    // Variables
    
    // Check parameters
    if(pUserData==NULL){
        rageQuit(1000, "DRAW : User Data pointer is NULL !");
    }
    if(pCanvas==NULL){
        rageQuit(1001, "DRAW : Canvas pointer is NULL !");
    }
    if(pGfx==NULL){
        rageQuit(1002, "DRAW : GFX pointer is NULL !");
    }
   
    UserData* pData = (UserData*)(pUserData);

    int T = 2000;
    unsigned short v = 255*((int)pData->time % (2*T))/T;
    if (v>=255){
        v = 510-v;
    }

    for(int y=0;y<pCanvas->nbCharY;y++){
        for(int x=0;x<pCanvas->nbCharX;x++){    
            // Draw emojis with full opaque + lightning background
            //drawEmoji(pGfx, x, y, y*255 + x, 0xFF000000 + RGB(v,v,v), COLOR_WHITE);
            // Draw emojis with changing opacity + fixed gray background
            //drawEmoji(pGfx, x, y, y*255 + x, 0xFF808080, RGB( (255*x)/pCanvas->nbCharX, (255*y)/pCanvas->nbCharY, 0xFF) + (v<<24));
            
            // Draw emojis with gradient background + fixed white filter color
            drawEmoji(pGfx, x, y, y*255 + x, 0xFF000000 + RGB((255*x)/pCanvas->nbCharX,(255*y)/pCanvas->nbCharY,0x00), COLOR_WHITE);              
        }
    }
}

void finish(void* pUserData){
    printf("[FINISH]\n");
}


int main(int argc, char** argv){

    // Input Variables
    int nbCharX = -1;
    int nbCharY = -1;
    int charW   = -1;
    int charH   = -1;
    int showFPS =  0;
    int result  = -1;
    // Callbacks
    Callbacks cbStruct;
    cbStruct.cbInit   = init;
    cbStruct.cbEvent  = event;
    cbStruct.cbUpdate = update;
    cbStruct.cbDraw   = draw;
    cbStruct.cbFinish = finish;
    // User data
    UserData userDat;
    // Game data pointer
    GameData* pGame;
        
    // ---------------------------------------------
    // CHECK PARAMETERS
    // ---------------------------------------------    
    // Check number of arguments
    if(argc != 5){
        rageQuit(10, "Incorrect number of arguments !");
    }
    // Retrieve numbers of characters along X and Y axis
    result = sscanf(argv[1], "%d", &nbCharX);
    if(result != 1){
        rageQuit(11, "Incorrect value for number of characters along X-axis (not a number) !");
    }
    result = sscanf(argv[2], "%d", &nbCharY);
    if(result != 1){
        rageQuit(12, "Incorrect value for number of characters along Y-axis (not a number) !");
    }
    // Check values of numbers of characters
    if(nbCharX <= 0){
        rageQuit(13, "Incorrect value for number of characters along X-axis (negative or zero value) !");
    }
    if(nbCharX <= 0){
        rageQuit(14, "Incorrect value for number of characters along Y-axis (negative or zero value) !");
    }
    // Retrieve dimensions of characters
    result = sscanf(argv[3], "%d", &charW);
    if(result != 1){
        rageQuit(15, "Incorrect value for character width (not a number) !");
    }
    result = sscanf(argv[4], "%d", &charH);
    if(result != 1){
        rageQuit(16, "Incorrect value for character height (not a number) !");
    }
    // Check values for character dimensions
    if(charW <= 0){
        rageQuit(17, "Incorrect value for character width (negative or zero value) !");
    }
    if(charH <= 0){
        rageQuit(18, "Incorrect value for character height (negative or zero value) !");
    }

    // Create game 
    pGame = createGame(nbCharX, nbCharY, charW, charH, &userDat, &cbStruct);
    printf("GAME=%p\n", pGame);

    // Launch game (infinite loop)
    gameLoop(pGame);
    
    return 0;
}



