#ifndef GUI_H
    #define GUI_H

    // Used for emoticons with double size
    #define CHAR_SIZE 2
    
    // Screen buffer
    #define SCREEN_BUFFER_SIZE 5*1024*1024

    // Default colors for Font and Background
    #define DEFAULT_COLOR (-1)

    #include "game_rgr.h"

    // Functions
    Pencil* createCanvas(int w, int h);
    void    debugPencil (Pencil* p);
    void    clearScreen (Pencil* p);
    void    closeCanvas (Pencil* p);
    
    void    startScreenDraw(Pencil* p);
    void    flushScreenDraw(Pencil* p);
        
    

           
#endif
