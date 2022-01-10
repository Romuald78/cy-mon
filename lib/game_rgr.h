#ifndef GAME_RGR_H
    #define GAME_RGR_H

    // Includes
    #include <linux/input.h>
    
    // Error types
    #define ERR_MALLOC      (-1)
    #define ERR_NULL        (-2)
    #define ERR_DIMENSIONS  (-3)
    #define ERR_DEVICE      (-4)
    #define ERR_PARAMS      (-5)
    #define ERR_IMPOSSIBLE  (-6)
    #define ERR_GAMESTATE   (-7)
    
    // Structures
    typedef struct input_event Event;

    // Graphic structure
    typedef struct {
        int   x;
        int   y;
        int   width;
        int   height;
        char* screenBuffer;
        int   scrBuffIndex;
        int   lastFontClr;
        int   lastBgClr;
    } Pencil;

    // Game Callbacks
    typedef void (*InitCallback  )(void* pData, Pencil* p);
    typedef void (*EventCallback )(void* pData, Event*  pEv);
    typedef int  (*UpdateCallback)(void* pData, Pencil* p, double deltaTime);
    typedef void (*DrawCallback  )(void* pData, Pencil* p);
    typedef void (*FinishCallback)(void* pData);

    // Game structure
    typedef struct{
        // Events
        int            fdEventK;
        int            fdEventM;
        // FPS display
        int            maxFPS;
        int            curFPS;
        int            showFPS;
        // Drawing structure
        Pencil*        pPencil;
        // User data
        void*          pData;
        // User callbacks
        InitCallback   cbInit;        
        EventCallback  cbEvent;        
        UpdateCallback cbUpdate;
        DrawCallback   cbDraw;
        FinishCallback cbFinish;
    } Game;    

    // Game interface
    Game* createGame(int W, int H, int maxFPS, int showFPS,
                     char* devK,
                     char* devM,
                     void* pData,
                     InitCallback   cbInit,
                     EventCallback  cbEvt,
                     UpdateCallback cbUpd,
                     DrawCallback   cbDrw,
                     FinishCallback cbFinish  );               
    void   gameLoop (Game* pGame);
    void   playSound(char* filePath);
    double getTimeMs();

    // Graphic interface
    void    displayChar    (Pencil* p, char* str);
    void    displayCharAt  (Pencil* p, int x, int y, char* str);
    void    setPosition    (Pencil* p, int x, int y);
    void    clearLineBefore(Pencil* p);
    void    clearLineAfter (Pencil* p);
    void    clearLineFull  (Pencil* p);
    void    setBgColor     (Pencil* p, int RGB, int bright);
    void    setFontColor   (Pencil* p, int RGB, int bright); 
    void    resetBgColor   (Pencil* p);
    void    resetFontColor (Pencil* p); 
    void    setNormalColor (Pencil* p);

#endif
