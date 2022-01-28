#ifndef LIBGAMERGR_H
    #define LIBGAMERGR_H

    // Includes
    #include "keys.h"
    #include "emoticons.h"
       
    typedef enum{
        KEY_RELEASED = 0,
        KEY_PRESSED
    } KeyState;   

    // Canvas Structure
    typedef struct {
        int nbCharX;    // number of characters along X-axis
        int nbCharY;    // number of characters along Y-axis
        int charW;      // nbPixels for one character width
        int charH;      // nbPixels for one character height
    } Canvas;
       
    // GFX Structure
    typedef struct{
        void*   pWindow;      // store application window address
        void*   pFont;        // store user font address
        void*   pRenderer;    // store gfx renderer address 
        Canvas* pCanvas;   
    } GFX;

    // Event structure
    typedef struct {
        KeyState keyState;   // KEY_PRESSED or KEY_RELEASED
        KeyRGR   keyCode;    // TODO : remove direct link to SDL (?)  
    } Event;
    
    // User Callback Functions
    typedef void (*InitCallback  )(void* pUSerData, Canvas* pCanvas);
    typedef void (*EventCallback )(void* pUserData, Canvas* pCanvas, Event* pEvt);
    typedef int  (*UpdateCallback)(void* pUserData, Canvas* pCanvas, double deltaTime);
    typedef void (*DrawCallback  )(void* pUSerData, Canvas* pCanvas, GFX* pGfx);
    typedef void (*FinishCallback)(void* pUserData);

    // Callback structure
    typedef struct{
        InitCallback   cbInit;        
        EventCallback  cbEvent;        
        UpdateCallback cbUpdate;
        DrawCallback   cbDraw;
        FinishCallback cbFinish;        
    } Callbacks;
    
    // Full game structure
    typedef struct{
        GFX*       pGfx;
        void*      pUserData;
        Callbacks* pUserCallbacks; 
        int        displayFPS;       
    } GameData;
    
    // Errors
    void rageQuit(int errorCode, const char* format, ...);
    // Game functions
    GameData* createGame(int nbCharX, int nbCharY, int charW, int charH,   void* pUserData, Callbacks* pCb);
    void gameLoop(GameData* pGame);
    // Draw API
    void drawEmptyRect(GFX* pGfx, int x, int y, int color);
    void drawText(GFX* pGfx, char* text, int x, int y, int color);
    
#endif
