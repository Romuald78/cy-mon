#include <stdio.h>
#include <stdlib.h>
#include "libGameRGR.h"


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
   
    unsigned int frontColor = 0xFFFFFF00;
    unsigned int backColor  = 0xFFA020A0;
    unsigned int cellColor  = 0xFF60A090;
    UserData* pData = (UserData*)(pUserData);

    int T = 500;
    unsigned short alpha = 255*((int)pData->time % (2*T))/T;
    if (alpha>=255){
        alpha = 510-alpha;
    }
    
    drawEmoji(pGfx, 0, 0, EMOT_RABBIT       , 0xFEFFFFFF, backColor , cellColor);
    drawEmoji(pGfx, 1, 0, EMOT_SNAKE        , 0xFFFFFF00, 0xFF008000, cellColor);
    drawEmoji(pGfx, 2, 0, EMOT_SHEEP        , 0xFF000000, 0xFF808080, cellColor);
    drawEmoji(pGfx, 3, 0, EMOT_GOAT         , 0xFF101010, 0xFF707070 , cellColor);
    drawEmoji(pGfx, 4, 0, EMOT_BEE          , 0xFEF0F000, 0xFF404000 , cellColor);
    
    drawEmoji(pGfx, 0, 1, EMOT_WRENCH       , 0xFFFFFFFF, 0xFF808080, cellColor);
    drawEmoji(pGfx, 1, 1, EMOT_HAMMER       , 0xFFFFFFFF, 0xFF808080, cellColor);
    drawEmoji(pGfx, 2, 1, EMOT_AXE          , 0xFFFFFFFF, 0xFFC08000, cellColor);
    drawEmoji(pGfx, 3, 1, EMOT_TOOLBOX      , 0xFF0000FF, 0xFF000000, cellColor);
    drawEmoji(pGfx, 4, 1, EMOT_MAGNET       , 0xFEFF0000, 0xFFA0A0A0, cellColor);
    
    drawEmoji(pGfx, 0, 2, EMOT_KEY          , 0xFFFFFF80, 0xFF808040, cellColor);
    drawEmoji(pGfx, 1, 2, EMOT_LOCK_CLOSED  , 0xFFFFFF80, 0xFF808040, cellColor);
    drawEmoji(pGfx, 2, 2, EMOT_LOCK_OPEN    , 0xFFFFFF80, 0xFF808040, cellColor);

    drawEmoji(pGfx, 0, 3, EMOT_GEM          , 0x00FFFF00 | ((alpha&0xFE)<<24), backColor, cellColor);
    drawEmoji(pGfx, 1, 3, EMOT_MONEYBAG     , 0xFFFFFF00, 0xFFA08040, cellColor);
    drawEmoji(pGfx, 2, 3, EMOT_BANKNOTE     , 0xFF40E040, 0xFF000000, cellColor);
    drawEmoji(pGfx, 3, 3, EMOT_CROWN        , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 4, 3, EMOT_RING         , frontColor, backColor, cellColor);

/*
                drawText(pGfx, EMOT_TREE, x, y, 0xFF80FF80);
                drawText(pGfx, EMOT_CACTUS, x, y, 0xFF00FF00);
                drawText(pGfx, EMOT_PINE, x, y, 0xFF00A000);
                drawText(pGfx, EMOT_ROCK, x, y, 0xFF808080);
                drawText(pGfx, EMOT_PALMTREE, x, y, 0xFF90FF00);
                drawText(pGfx, EMOT_CLOVER, x, y, 0xFF008000);
                drawText(pGfx, EMOT_HERB, x, y, 0xFFA0F0A0);

                drawText(pGfx, EMOT_TULIP, x, y, 0xFFFF4020);
                drawText(pGfx, EMOT_FLOWER, x, y, 0xFFFF8080);

                drawText(pGfx, EMOT_BEE, x, y, 0xFFF0F080);
//*/
    
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



