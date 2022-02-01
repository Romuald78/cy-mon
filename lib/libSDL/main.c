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
    unsigned int backColor  = 0xFF804040;
    unsigned int cellColor  = 0xFF707070;
    UserData* pData = (UserData*)(pUserData);

    int T = 500;
    unsigned short alpha = 255*((int)pData->time % (2*T))/T;
    if (alpha>=255){
        alpha = 510-alpha;
    }
    
    drawEmoji(pGfx, 0, 0, EMOT_RABBIT       , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 1, 0, EMOT_SNAKE        , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 2, 0, EMOT_SHEEP        , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 3, 0, EMOT_GOAT         , frontColor, backColor, cellColor);
    
    drawEmoji(pGfx, 0, 1, EMOT_WRENCH       , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 1, 1, EMOT_HAMMER       , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 2, 1, EMOT_AXE          , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 3, 1, EMOT_TOOLBOX      , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 4, 1, EMOT_MAGNET       , frontColor, backColor, cellColor);
    
    drawEmoji(pGfx, 0, 2, EMOT_KEY          , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 1, 2, EMOT_LOCK_CLOSED  , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 2, 2, EMOT_LOCK_OPEN    , frontColor, backColor, cellColor);

    drawEmoji(pGfx, 0, 3, EMOT_GEM          , 0x00FFFF00 | ((alpha&0xFF)<<24), backColor, cellColor);
    drawEmoji(pGfx, 1, 3, EMOT_MONEYBAG     , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 2, 3, EMOT_BANKNOTE     , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 3, 3, EMOT_CROWN        , frontColor, backColor, cellColor);
    drawEmoji(pGfx, 4, 3, EMOT_RING         , frontColor, backColor, cellColor);

/*
    // Loop through the grid cells
    double t = ((UserData*)pUserData)->time/2;
    srand(0);
    for(int x=0; x<pCanvas->nbCharX; x++){
        for(int y=0; y<pCanvas->nbCharY; y++){
            int R = (int)(512*(x+t)/pCanvas->nbCharX)%512; 
            int G = (int)(512*(y+t)/pCanvas->nbCharY)%512;
            int B = 128;
            int A = 255;
            int color = (A<<24)+(R<<16)+(G<<8)+B;
            if (R>=256){
                R = 511-R;
            } 
            if (G>=256){
                G = 511-G;
            } 
            //drawEmptyRect(pGfx, x, y, color);
            int r = rand()%101;
            if(r <= 5){
                drawText(pGfx, EMOT_TREE, x, y, 0xFF80FF80);
            }
            else if(r <= 10){
                drawText(pGfx, EMOT_CACTUS, x, y, 0xFF00FF00);
            }
            else if(r <= 15){
                drawText(pGfx, EMOT_PINE, x, y, 0xFF00A000);
            }
            else if(r <= 20){
                drawText(pGfx, EMOT_PINE, x, y, 0xFF00A000);
            }
            else if(r <= 25){
                drawText(pGfx, EMOT_ROCK, x, y, 0xFF808080);
            }
            else if(r <= 30){
                drawText(pGfx, EMOT_PALMTREE, x, y, 0xFF90FF00);
            }
            else if(r <= 35){
                drawText(pGfx, EMOT_CLOVER, x, y, 0xFF008000);
            }
            else if(r <= 40){
                drawText(pGfx, EMOT_HERB, x, y, 0xFFA0F0A0);
            }
            else if(r <= 45){
                drawText(pGfx, EMOT_TULIP, x, y, 0xFFFF4020);
            }
            else if(r <= 50){
                drawText(pGfx, EMOT_FLOWER, x, y, 0xFFFF8080);
            }
            else if(r <= 55){
                drawText(pGfx, EMOT_MONEYBAG, x, y, 0xFFFFFF80);
            }
            else if(r <= 60){
                drawText(pGfx, EMOT_GEM, x, y, color);
            }
            else if(r <= 65){
                drawText(pGfx, EMOT_BEE, x, y, 0xFFF0F080);
            }
            else if(r <= 70){
                drawText(pGfx, EMOT_RABBIT, x, y, 0xFFFFFFFF);
            }

        }
    }

//*/
    
/* -----------------------------------------------------------------------------------

        // TODO here we have to call the user callback instead (draw)
        // DEBUG
        // Draw a 10x10 grid, with 32x32 cells
        // Prepare a text (use tmp memory for surface and texture)
        SDL_Color    color1  = { 0, 0, 0 };
        SDL_Color    color2  = { 0, 0, 0 };
        SDL_Surface* fntSurf;
	    SDL_Texture* fntText;;
        for(int i=0;i<nbCharY;i++){
            for(int j=0;j<nbCharX;j++){
                SDL_Rect rect;
                rect.x = charW*j;
                rect.y = charH*i;
                rect.w = charW;
                rect.h = charH;
                SDL_SetRenderDrawColor(renderer, (255*i)/nbCharY, (255*j)/nbCharX, 128, 255);
                // Render background
                SDL_RenderFillRect(renderer, &rect);
                // Render text
                fntSurf = TTF_RenderUTF8_Blended(font, "😄", color1); 
//              fntSurf = TTF_RenderGlyph32_Blended(font, "😄", color1); 
//                fntSurf = TTF_RenderUTF8_Shaded(font, "😄", color1, color2); 
                fntText = SDL_CreateTextureFromSurface(renderer, fntSurf);
                SDL_RenderCopy(renderer, fntText, NULL, &rect);
                // Remove font tmp memory
                SDL_DestroyTexture(fntText);
                SDL_FreeSurface   (fntSurf);
            }
        }
//*///-------------------------------------------------------------------------------
    
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



