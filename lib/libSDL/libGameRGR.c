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

#define ALPHA(i)        ((i>>24)&0xFF)
#define RED(i)          ((i>>16)&0xFF)
#define GREEN(i)        ((i>> 8)&0xFF)
#define BLUE(i)         ((i    )&0xFF)
#define COLOR(r,g,b,a)  (((a&0xFF)<<24)+((r&0xFF)<<16)+((g&0xFF)<<8)+(b&0xFF))
#define INT2COLOR(i)    {RED(i),GREEN(i),BLUE(i),ALPHA(i)}
void drawEmoji(GFX* pGfx, int x, int y, char* emoji, int color, int color2){
        SDL_Rect  rect;
        SDL_Color fg = INT2COLOR(color);
        SDL_Color bg = INT2COLOR(color2);
        unsigned char r;
        unsigned char g;
        unsigned char b;
        // TODO check params
  
  
        
        r = RED(color2);
        g = GREEN(color2);
        b = BLUE(color2);
        SDL_Surface* pSurfShaded = TTF_RenderUTF8_Shaded(pGfx->pFont, emoji, fg, bg);
        SDL_SetSurfaceBlendMode(pSurfShaded, SDL_BLENDMODE_BLEND);
        SDL_SetColorKey(pSurfShaded, SDL_TRUE, SDL_MapRGB(pSurfShaded->format, r, g, b));
        SDL_Texture* pTex  = SDL_CreateTextureFromSurface(pGfx->pRenderer, pSurfShaded);
        rect.x = x*pGfx->pCanvas->charW;
        rect.y = y*pGfx->pCanvas->charH;
        rect.w = pGfx->pCanvas->charW;
        rect.h = pGfx->pCanvas->charH;
        SDL_RenderCopy(pGfx->pRenderer, pTex, NULL, &rect);


        SDL_Surface* pSurfBlended = TTF_RenderUTF8_Blended(pGfx->pFont, emoji, fg);
        SDL_SetSurfaceBlendMode(pSurfBlended, SDL_BLENDMODE_BLEND);
        pTex  = SDL_CreateTextureFromSurface(pGfx->pRenderer, pSurfBlended);
        rect.x += pGfx->pCanvas->charW;
        SDL_RenderCopy(pGfx->pRenderer, pTex, NULL, &rect);


        SDL_Surface* pSurfSolid = TTF_RenderUTF8_Solid(pGfx->pFont, emoji, fg);
        SDL_SetSurfaceBlendMode(pSurfSolid, SDL_BLENDMODE_BLEND);
        pTex  = SDL_CreateTextureFromSurface(pGfx->pRenderer, pSurfSolid);
        rect.x += pGfx->pCanvas->charW;
        SDL_RenderCopy(pGfx->pRenderer, pTex, NULL, &rect);

//----------------------------------------------
/*
        if( SDL_BlitSurface(pSurfBlended, NULL, pSurfShaded, NULL) != 0){
            rageQuit(900, SDL_GetError());
        }
        pTex  = SDL_CreateTextureFromSurface(pGfx->pRenderer, pSurfShaded);
        rect.x += pGfx->pCanvas->charW;
        SDL_RenderCopy(pGfx->pRenderer, pTex, NULL, &rect);
//*/
//----------------------------------------------
/*
        SDL_SetSurfaceBlendMode(pSurfShaded, SDL_BLENDMODE_ADD);
        if( SDL_BlitSurface(pSurfShaded, NULL, pSurfBlended, NULL) != 0){
            rageQuit(900, SDL_GetError());
        }
        pTex  = SDL_CreateTextureFromSurface(pGfx->pRenderer, pSurfBlended);
        rect.x += pGfx->pCanvas->charW;
        SDL_RenderCopy(pGfx->pRenderer, pTex, NULL, &rect);
//*/
//----------------------------------------------


        SDL_DestroyTexture(pTex);
//        SDL_FreeSurface(pSurf);
}


      
/*
        // Fill rect        
        rect.x = 64;
        rect.y = 64;
        rect.w = 64;
        rect.h = 64;
        SDL_SetRenderDrawColor(pGame->pGfx->pRenderer, 255,0,0, 200);
        SDL_RenderFillRect(pGame->pGfx->pRenderer, &rect);                
//*/



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
    SDL_Rect  rect = {0};
    int quit = 0;
    // Check the whole structure before starting
    // TODO
    // Game loop (infinite)
    while(!quit){
        // Get events
        while( SDL_PollEvent(&sdlEvt) ){
            
            // User requests quit
            if( sdlEvt.type == SDL_QUIT ){
                quit = 1;
            }
            // User releases a key
            else if( sdlEvt.type == SDL_KEYUP ){
                printf("UP\n");
                if(sdlEvt.key.keysym.sym == KEY_ESCAPE){
                    quit = 1;
                }
            }
            else if( sdlEvt.type == SDL_KEYDOWN && sdlEvt.key.repeat == 0 ){
                printf("DOWN\n");
            }
        }
        // Update model
        
                
        // Draw frame        
        SDL_SetRenderDrawColor(pGame->pGfx->pRenderer, 120,120,0, 255);
        SDL_RenderClear(pGame->pGfx->pRenderer);

        drawEmoji(pGame->pGfx, 0, 0, EMOT_RABBIT, 0xFF0000FF, 0xFFFF0000);
        drawEmoji(pGame->pGfx, 1, 1, EMOT_SNAKE, 0xFF0000FF,0xFFFF0000);
        drawEmoji(pGame->pGfx, 2, 2, EMOT_SHEEP, 0xFF0000FF,0xFFFF0000);
        drawEmoji(pGame->pGfx, 3, 3, EMOT_GOAT, 0xFF0000FF,0xFFFF0000);
        
        
        SDL_RenderPresent(pGame->pGfx->pRenderer);
        
        // Wait for next frame
        SDL_Delay(17);
    }
    // Close game and free all resources
    
}

void closeGame(GameData* pGame){
    // All free (font, window, renderer, canvas, ...
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


