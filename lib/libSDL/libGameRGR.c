#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libGameRGR.h"
#include "SDL.h"
#include "SDL_ttf.h"


void rageQuit(int errorCode, const char* format, ...){
    // List of arguments
    va_list args;  
    // Start retrieving arguments
    va_start(args, format );
    fprintf (stderr, "[ERROR] ");
    vfprintf(stderr, format, args );
    fprintf (stderr, "\nProgram exited with code (%d).\n", errorCode);
    // Clean up list
    va_end  (args);
    exit(errorCode);
}

Canvas* _newCanvas(int nbCharX, int nbCharY, int charW, int charH){
    // Variables
    Canvas* canvas;
    // check parameters
    if(nbCharX<1 || nbCharY<1){
        rageQuit(10, "Canvas size is not correct (nbX=%d/nbY=%d) !", nbCharX, nbCharY);
    }
    if(charW<1 || charH<1){
        rageQuit(11, "Canvas size is not correct (W=%d/H=%d) !", charW, charH);
    }   
    // Memory Allocation
    canvas = malloc(sizeof(Canvas));
    // Check Allocation
    if(canvas==NULL){
        rageQuit(15, "Canvas allocation failed !");
    }
    // Fill canvas
    canvas->nbCharX = nbCharX;
    canvas->nbCharY = nbCharY;
    canvas->charW   = charW;
    canvas->charH   = charH;
    // Return structure address
    return canvas;    
}

GFX* _newGFX(void* pWindow, void* pFont, void* pRenderer, Canvas* pCanvas){
    // Variables
    GFX* pGfx;
    // Check parameters
    if(pWindow==NULL || pFont==NULL || pRenderer==NULL || pCanvas==NULL){
        rageQuit(20, "CreateGFX null parameters !\n"
                     "pWindow  =%p\n"
                     "pFont    =%p\n"
                     "pRenderer=%p\n"
                     "pCanvas  =%p", pWindow, pFont, pRenderer, pCanvas);        
    }
    // Allocate structure
    // Memory Allocation
    pGfx = malloc(sizeof(GFX));
    // Check Allocation
    if(pGfx==NULL){
        rageQuit(25, "GFX allocation failed !");
    }
    // Fill structure
    pGfx->pWindow   = pWindow;
    pGfx->pFont     = pFont;
    pGfx->pRenderer = pRenderer;
    pGfx->pCanvas   = pCanvas;
    // Return structure address
    return pGfx;        
}

/*
Callbacks* _Callbacks( InitCallback init,
                            EventCallback event,
                            UpdateCallback update,
                            DrawCallback draw,
                            FinishCallback finish ){
    // Variables
    Callbacks* pCb;
    // Check parameters
    if(init==NULL || event==NULL || update==NULL || draw==NULL || finish==NULL){
        rageQuit(30, "Create Callbacks null parameters !\n"
                     "init  =%p\n"
                     "event =%p\n"
                     "update=%p\n"
                     "draw  =%p\n"
                     "finish=%p", init, event, update, draw, finish );
    }
    // Memory Allocation
    pCb = malloc(sizeof(Callbacks));
    if(pGfx==NULL){
        rageQuit(35, "Callbacks allocation failed !");
    }
    // Fill structure
    pCb->cbInit   = init;
    pCb->cbEvent  = event;
    pCb->cbUpdate = update;
    pCb->cbDraw   = draw;
    pCb->cbFinish = finish;
    // Return structure address
    return pCb;
}
//*/

GameData* _newGame(GFX* pGfx, Callbacks* pCb, void* pUserData, int displayFPS){
    // Variables
    GameData* pGame;
    // Check parameters
    if(pGfx==NULL || pCb==NULL || pUserData==NULL){
        rageQuit(40, "CreateGFX null parameters !\n"
                     "pGfx       =%p\n"
                     "pCallbacks =%p\n"
                     "pUserData  =%p\n"
                     "pCanvas    =%p", pGfx, pCb, pUserData);        
    }
    // Memory Allocation
    pGame = malloc(sizeof(GameData));
    if(pGame==NULL){
        rageQuit(45, "GameData allocation failed !");
    }
    // Fill structure
    pGame->pGfx           = pGfx;
    pGame->pUserCallbacks = pCb;
    pGame->pUserData      = pUserData;
    // Return structure address
    return pGame;
}

GameData* createGame(int nbCharX, int nbCharY, int charW, int charH, void* pUserData, Callbacks* pCb){    
    // Variables
    SDL_Window*   pWindow;
    TTF_Font*     pFont;    
    SDL_Renderer* pRenderer;
    Canvas*       pCanvas;
    GFX*          pGfx;
    GameData*     pGame; 
    // Do not check parameters as we are checking them when creating the different structures
    // First create Canvas
    pCanvas = _newCanvas(nbCharX, nbCharY, charW, charH);
    //Initialize SDL and TTF
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        rageQuit(100, "SDL Init failed !");
    }
    if( TTF_Init() < 0 )
    {
        rageQuit(105, "TTF Init failed !");
    }
    // Init SDL Window, and Renderer (window dimensions are given by nbCharX/Y * charW/H)
    if( SDL_CreateWindowAndRenderer(nbCharX*charW, nbCharY*charH, 0, &pWindow, &pRenderer) < 0){
        rageQuit(110, "Creation of Window and Renderer failed !");
    }
    // Load emoji font (do not test result, we will when creating GFX struct)
    pFont = TTF_OpenFont("GameRGR/fonts/NotoColorEmoji.ttf", 32);
    // Create GFX structure
    pGfx = _newGFX(pWindow, pFont, pRenderer, pCanvas);
    // Create game structure
    pGame = _newGame(pGfx, pCb, pUserData, 0);
    // Return Game structure
    return pGame;
}

void gameLoop(GameData* pGame){
    // Variables
    SDL_Event sdlEvt;
    SDL_Rect  rect;
    int quit = 0;
    // Check the whole structure before starting
    // TODO
    // Game loop (infinite)
    while(!quit){
        // Get events
        while( SDL_PollEvent( &sdlEvt ) != 0 ){
            
            // User requests quit
            if( sdlEvt.type == SDL_QUIT ){
                quit = 1;
            }
            // User releases a key
            else if( sdlEvt.type == SDL_KEYUP ){
                printf("UP");
                if(sdlEvt.key.keysym.sym == KEY_ESCAPE){
                    quit = 1;
                }
            }
            else if( sdlEvt.type == SDL_KEYDOWN){
                printf("DOWN");
            }
        }
        // Update model

                
        // Draw frame
        
        SDL_SetRenderDrawColor(pGame->pGfx->pRenderer, 0,0,0, 255);
        SDL_RenderClear(pGame->pGfx->pRenderer);
        
        // Fill rect        
        rect.x = 0;
        rect.y = 0;
        rect.w = 256;
        rect.h = 128;
        SDL_SetRenderDrawColor(pGame->pGfx->pRenderer, 255,255,255, 255);
        SDL_RenderFillRect(pGame->pGfx->pRenderer, &rect);                

        SDL_Color fg = {255,255,255,255};
        SDL_Color bg = {0,128,64, 255};
        // TODO ???? Blended / Shaded ???
        SDL_Surface* pSurf = TTF_RenderUTF8_Blended(pGame->pGfx->pFont, "🥞"EMOT_RABBIT, fg);
        SDL_Texture* pTex  = SDL_CreateTextureFromSurface(pGame->pGfx->pRenderer, pSurf);
        rect.x = 64;
        rect.y = 64;
        rect.w = rect.x+64*2;
        rect.h = 128;
        SDL_RenderCopy(pGame->pGfx->pRenderer, pTex, NULL, &rect);

        SDL_RenderPresent(pGame->pGfx->pRenderer);
        
        // Wait for next frame
        SDL_Delay(17);
    }
}

void closeGame(GameData* pGame){
    // All free
    // TTF quit
    // SDL quit
    /*
        Game Data
            pGfx (GFX)
                pWindow (void*)
                pFont (void*)
                pRenderer (void*)
                pCanvas (Canvas* )
                    int x4     
            pUserCallbacks (Callbacks)
                InitCallback   cbInit;        
                EventCallback  cbEvent;        
                UpdateCallback cbUpdate;
                DrawCallback   cbDraw;
                FinishCallback cbFinish; 
            pUserData (void*)
            displayFPS (int)
    */
}


