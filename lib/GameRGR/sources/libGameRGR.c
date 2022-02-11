#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libGameRGR.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"


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
void drawEmoji(GFX* pGfx, int x, int y, unsigned short emojiCode, int backColor, int filterColor){
        SDL_Rect  textRect;
        SDL_Rect  rendRect;
        // TODO check params
        
        // TODO check all function returns (below)

        // Set position and size for texture source
        textRect.x = x*EMOJI_SIZE;
        textRect.y = y*EMOJI_SIZE;
        textRect.w =   EMOJI_SIZE;
        textRect.h =   EMOJI_SIZE;
        // Set position and size for blitting
        rendRect.x = x*pGfx->pCanvas->charW;
        rendRect.y = y*pGfx->pCanvas->charH;
        rendRect.w =   pGfx->pCanvas->charW;
        rendRect.h =   pGfx->pCanvas->charH;
        // Set color for background
        SDL_SetRenderDrawColor(pGfx->pRenderer,
                               RED(backColor),
                               GREEN(backColor),
                               BLUE(backColor),
                               ALPHA(backColor)  );
        // Draw background
        SDL_RenderFillRect(pGfx->pRenderer, &rendRect);                

        
        // Set alpha on emoji texture
        SDL_SetTextureAlphaMod(pGfx->pTexture, ALPHA(filterColor));
        // Set color modifier (filter color)
        SDL_SetTextureColorMod(pGfx->pTexture, RED(filterColor), GREEN(filterColor), BLUE(filterColor));
        // display Emoji on screen
        SDL_RenderCopy(pGfx->pRenderer, pGfx->pTexture, &textRect, &rendRect);
        
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

GFX* _newGFX(void* pWindow, void* pRenderer, Canvas* pCanvas){
    // Variables
    GFX* pGfx;
    SDL_Surface* pSurf;
    // Check parameters
    if(pWindow==NULL || pRenderer==NULL || pCanvas==NULL){
        rageQuit(20, "CreateGFX null parameters !\n"
                     "pWindow  =%p\n"
                     "pRenderer=%p\n"
                     "pCanvas  =%p", pWindow, pRenderer, pCanvas);        
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
    pGfx->pRenderer = pRenderer;
    pGfx->pCanvas   = pCanvas;
    // Create texture with all emojis from bitmap file
    pSurf = IMG_Load( "./atlas/emoji.png" );
    if(pSurf==NULL){
        rageQuit(27, "Impossible to load emoji atlas !");
    }
    // Create texture from surface
    pGfx->pTexture = SDL_CreateTextureFromSurface(pGfx->pRenderer, pSurf);
    if(pGfx->pTexture==NULL){
        rageQuit(28, "Impossible to create emoji texture from surface !");
    }
    SDL_SetTextureBlendMode(pGfx->pTexture, SDL_BLENDMODE_BLEND);        
    // Free surface
    SDL_FreeSurface(pSurf);
    // Return structure address
    return pGfx;        
}

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
    // Create GFX structure
    pGfx = _newGFX(pWindow, pRenderer, pCanvas);
    // Create game structure
    pGame = _newGame(pGfx, pCb, pUserData, 0);
    // Return Game structure
    return pGame;
}

void closeGame(GameData* pGame){
    // All free (font, window, renderer, canvas, ...
    // TODO
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

void gameLoop(GameData* pGame){
    // Variables
    GFX*          pGfx;
    Canvas*       pCanvas;
    void*         pData;
    Callbacks*    pCb; 
    int           dispFPS; 
    SDL_Event     sdlEvt;
    Event         rgrEvt;
    SDL_Rect      rect = {0};
    int           quit =  0;
    unsigned long startTime;
    unsigned long stopTime;
    unsigned long frameTime;
    // Check the whole structure before starting
    // TODO
    // Store each pointer locally
    pGfx    = pGame->pGfx;
    pCanvas = pGfx->pCanvas;
    pData   = pGame->pUserData;
    pCb     = pGame->pUserCallbacks; 
    dispFPS = pGame->displayFPS; 
    // First time measurement
    startTime = SDL_GetTicks64();        
    stopTime  = startTime;
    frameTime = 0;
    // Call INIT callback
    pCb->cbInit(pData, pCanvas);
    // Game loop (infinite)
    while(quit==0){
        // Get events
        while( SDL_PollEvent(&sdlEvt) ){            
            // User requests quit
            if( sdlEvt.type == SDL_QUIT ){
                quit |= 1;
            }
            // User releases a key
            else if( sdlEvt.type == SDL_KEYUP ){
                if(sdlEvt.key.keysym.sym == KEY_ESCAPE){
                    quit |= 1;
                }
                // Call EVENT callback
                rgrEvt.keyState = KEY_RELEASED;
                rgrEvt.keyCode  = sdlEvt.key.keysym.sym;
                pCb->cbEvent(pData, pCanvas, &rgrEvt);
            }
            else if( sdlEvt.type == SDL_KEYDOWN && sdlEvt.key.repeat == 0 ){
                // Call EVENT callback
                rgrEvt.keyState = KEY_PRESSED;
                rgrEvt.keyCode  = sdlEvt.key.keysym.sym;
                pCb->cbEvent(pData, pCanvas, &rgrEvt);
            }
        }
        // Call UPDATE callback
        quit |= pCb->cbUpdate(pData, pCanvas, frameTime);
        // Draw frame        
        SDL_SetRenderDrawColor(pGame->pGfx->pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pGame->pGfx->pRenderer);
        // Call DRAW callback
        pCb->cbDraw(pData, pCanvas, pGfx);
        // Finalize frame rendering        
        SDL_RenderPresent(pGame->pGfx->pRenderer);
        // Wait for next frame
        stopTime  = SDL_GetTicks64();
        frameTime = stopTime-startTime;
        startTime = stopTime;
        if(frameTime < 17){
            SDL_Delay(17-frameTime);        
        }       
    }
    // Call FINISH callback
    pCb->cbFinish(pData);
    // Close game and free all resources
    closeGame(pGame);   
}


