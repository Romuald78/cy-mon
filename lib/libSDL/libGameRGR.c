#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libGameRGR.h"

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
                     "pCanvas    =%p", pGfx, pCb, pUSerData);        
    }
    // Memory Allocation
    pGame = malloc(sizeof(GameData)){
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
    Canvas*   pCanvas;
    GFX*      pGfx;
    GameData* pGame;
    
    // Init SDL Window, Font and Renderer
    // TODO
    ...
    ...
     
    // Do not check parameters as we are checking them when creating the different structures
    pCanvas = _newCanvas(nbCharX, nbCharY, charW, charH);
    pGfx    = _newGFX
    
    


    
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

void closeGame(GameData* pGame){

}

int main(){
    

    return 0;
}

