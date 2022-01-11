#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_rgr.h"
#include "gui.h"

// Functions for pencil
void checkPencil(Pencil* p){
    if(p==NULL){
        exit(ERR_NULL);
    }
}

void startScreenDraw(Pencil* p){
    checkPencil(p);
    p->scrBuffIndex    = 0;
    *(p->screenBuffer) = '\0';
    p->lastFontClr = DEFAULT_COLOR;
    p->lastBgClr   = DEFAULT_COLOR;
}
void flushScreenDraw(Pencil* p){
    checkPencil(p);
    // Set position on top left corner and send char stream
    printf("\x1B[1;1H");
    printf("%s", p->screenBuffer);
    fflush(stdout);
}

Pencil* createCanvas(int w, int h){
    Pencil* p = malloc(sizeof(Pencil));
    checkPencil(p);
    p->x      = 0;
    p->y      = h;
    p->width  = w/CHAR_SIZE;
    p->height = h;
    // Create screenbuffer
    p->screenBuffer = malloc(SCREEN_BUFFER_SIZE);
    if(p->screenBuffer==NULL){
        exit(ERR_MALLOC);
    }
    // Init screen buffer
    p->scrBuffIndex  = 0;
    *p->screenBuffer = '\0';
    // Init text/bg colors
    p->lastFontClr = DEFAULT_COLOR;
    p->lastBgClr   = DEFAULT_COLOR;
    // Return created Pencil
    return p;
}

void closeCanvas(Pencil* p){    
    checkPencil(p);
    setPosition(p, p->width, p->height);
    displayChar(p, "\n");
    clearLineAfter(p);
    printf("%s", p->screenBuffer);
    fflush(stdout);
    // Erase and free
    p->x      = 0;
    p->y      = 0;
    p->width  = 0;
    p->height = 0;
    free(p);    
}

// Position the Cursor:
void setPosition(Pencil* p, int x, int y){
    int n=0;
    checkPencil(p);
    // Write in the screen buffer
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[%d;%dH", y+1, CHAR_SIZE*x+1);
    p->scrBuffIndex += n;
    p->x = x;
    p->y = y;
}

int isValidPosition(Pencil* p, int x, int y){
    return (x>=0)&&(x<p->width)&&(y>=0)&&(y<p->height);    
}


// Clear the screen, move to (0,0)
void clearScreen(Pencil* p){
    int n = 0;
    checkPencil(p);
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[3J");
    p->scrBuffIndex += n;
    setPosition(p, 0, 0);    
/*    
    // old version that clears row by row
    for(int i=0;i<p->height;i++){
        setPosition(p, 0, i);
        clearLineFull(p);
    }
//*/    
}

// Clear the rest of the current line
void clearLineAfter(Pencil* p){
    int n=0;
    checkPencil(p);
    // Write in the screen buffer
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[0K");
    p->scrBuffIndex += n;
}

void clearLineBefore(Pencil* p){
    int n=0;
    checkPencil(p);
    // Write in the screen buffer
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[1K");
    p->scrBuffIndex += n;
}

void clearLineFull(Pencil* p){
    int n=0;
    checkPencil(p);
    // Write in the screen buffer
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[2K");
    p->scrBuffIndex += n;
}

void setFontColor(Pencil* p, int RGB, int bright){        
    int n=0;
    unsigned char r,g,b;
    checkPencil(p);
    r = (RGB >> 16) & 0xFF;
    g = (RGB >>  8) & 0xFF;
    b = (RGB      ) & 0xFF;
    // Write in the screen buffer
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[38;2;%d;%d;%d", r, g, b);
    p->scrBuffIndex += n;
    if(bright){
        n = sprintf(p->screenBuffer+p->scrBuffIndex, ";1");
        p->scrBuffIndex += n;
    }
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "m");
    p->scrBuffIndex += n;
}
void resetFontColor(Pencil* p){
    int n=0;
    checkPencil(p);
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[39m");
    p->scrBuffIndex += n;
}

void setBgColor(Pencil* p, int RGB, int bright){
    int n=0;
    unsigned char r,g,b;
    checkPencil(p);
    r = (RGB >> 16) & 0xFF;
    g = (RGB >>  8) & 0xFF;
    b = (RGB      ) & 0xFF;
    // Write in the screen buffer
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[48;2;%d;%d;%d", r, g, b);
    p->scrBuffIndex += n;
    if(bright){
        n = sprintf(p->screenBuffer+p->scrBuffIndex, ";1");
        p->scrBuffIndex += n;
    }
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "m");
    p->scrBuffIndex += n;
}
void resetBgColor(Pencil* p){
    int n=0;
    checkPencil(p);
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "\x1B[49m");
    p->scrBuffIndex += n;
}

void displayChar(Pencil* p, char* str){
    int n=0;
    checkPencil(p);
    n = sprintf(p->screenBuffer+p->scrBuffIndex, "%s", str);
    p->scrBuffIndex += n;
}

void displayCharAt(Pencil* p, int x, int y, char* str){
    int n=0;
    checkPencil(p);
    // Check position before displaying characters
    if(isValidPosition(p, x, y)){   
        setPosition(p, x, y);       
        displayChar(p,str);
    }
}

