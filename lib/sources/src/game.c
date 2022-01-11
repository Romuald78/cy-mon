#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <unistd.h>
#include <time.h>
#include "game_rgr.h"
#include "game.h"
#include "gui.h"


float minFPS = 10000000.0;

int eventMouse(Game* pGame){
    // Local variables
    ssize_t n=0;
    char    buffer[3];
    int     res=0;
    Event   ev;
    
    static int leftButton   = 0;
    static int rightButton  = 0;
    static int middleButton = 0;
    static int coordX       = 0;
    static int coordY       = 0;
    
    // Check parameters
    if(pGame==NULL){
        exit(ERR_NULL);
    }
    // Consume all events from the last time
    while(n != (ssize_t)-1){
        //printf("x=%5d / y=%5d \r", coordX, coordY);
        // Read events
        n = read(pGame->fdEventM, buffer, sizeof(buffer));
        if (n == (ssize_t)-1) {
            if (errno == EINTR){
                fprintf(stderr, "[EVENT ERROR #04] \n");
                exit(-4);
            }
            else{
                // No key has been pressed or released
                // Just do nothing 
            }
        }
        else if(n != 3){
            fprintf(stderr, "[EVENT ERROR #06] \n");
            exit(-6);
        }
        else{
        /* // TODO
            char left   = buffer[0] & 0x01;
            char right  = buffer[0] & 0x02;
            char middle = buffer[0] & 0x04;
            char moveX  = buffer[1];
            char moveY  = buffer[2];

            // check if we have to generate an event for buttons
            if(left != leftButton){
                ev.type    = EV_KEY;
                ev.code    = BTN_LEFT;
                ev.value   = left;
                leftButton = left;
                pGame->cbEvent(pGame->pData, &ev);
            }
            if(right != rightButton){
                ev.type     = EV_KEY;
                ev.code     = BTN_RIGHT;
                ev.value    = right;                
                rightButton = right;
                pGame->cbEvent(pGame->pData, &ev);
            }
            if(middle != middleButton){
                ev.type      = EV_KEY;
                ev.code      = BTN_MIDDLE;
                ev.value     = middle;                
                middleButton = middle;
                pGame->cbEvent(pGame->pData, &ev);
            }
            // Check if there is a move (X or Y)
            if(moveX){
                ev.type  = EV_REL;
                ev.code  = REL_X;
                ev.value = moveX;
                pGame->cbEvent(pGame->pData, &ev);
                coordX  += moveX;
                ev.type  = EV_ABS;
                ev.code  = ABS_X;
                ev.value = coordX;
                pGame->cbEvent(pGame->pData, &ev);
            }
            if(moveY){
                ev.type  = EV_REL;
                ev.code  = REL_Y;
                ev.value = moveY;
                pGame->cbEvent(pGame->pData, &ev);
                coordY  += moveY;
                ev.type  = EV_ABS;
                ev.code  = ABS_Y;
                ev.value = coordY;
                pGame->cbEvent(pGame->pData, &ev);
            }
        //*/
        }
    }
    return res;
}

int eventKeyboard(Game* pGame){
    // Local variables
    ssize_t n=0;
    Event   ev;
    int     res=0;
    // Check parameters
    if(pGame==NULL){
        exit(ERR_NULL);
    }
    // Consume all events from the last time
    while(n != (ssize_t)-1){
        // Flush events with value=0x02
        do{
            n = read(pGame->fdEventK, &ev, sizeof(ev));
        } while( (n==sizeof(ev))&&(ev.value==0x02) );
        //printf("read n=%ld \n", n);        
        if (n == (ssize_t)-1) {
            if (errno == EINTR){
                fprintf(stderr, "[EVENT ERROR #01] \n");
                exit(-1);
            }
            else{
                // No key has been pressed or released
                // Just do nothing
            }
        }
        else if (n != sizeof(ev)) {
            fprintf(stderr, "[EVENT ERROR #03] \n");
            exit(-3);
        }
        else{
            if(ev.type == EV_KEY){
                // If ESCAPE key is released : just exit
                if(ev.code==KEY_ESC && ev.value==0x00){
                    res = -1;
                }
                else{
                    // Call the user callback
                    pGame->cbEvent(pGame->pData, &ev);
                }
            }
        }
    }
    return res;
}

int eventPolling(Game* pGame){
    int res = 0;
    res = eventKeyboard(pGame);
    if(res >= 0){
        res = eventMouse(pGame);    
    }    
    return res;
}

Game* createGame(int W, int H, int maxFPS, int showFPS,
                 char* devK,
                 char* devM,
                 void* pData,
                 InitCallback   cbInit,
                 EventCallback  cbEvt,
                 UpdateCallback cbUpd,
                 DrawCallback   cbDrw,
                 FinishCallback cbFinish     ){
    // Local variables
    Game*   pGame;
    Pencil* pPen;
    int     fdK;        
    int     fdM;        
    // Check input pointers (init and finish callbacks can be NULL)
    if(cbEvt==NULL || cbUpd==NULL || cbDrw==NULL || devK==NULL || devM==NULL){
        exit(ERR_NULL);
    }
    // Check input dimensions
    if(W<=0 || H<=0){
        exit(ERR_DIMENSIONS);
    }
    // Create game structure
    pGame = malloc(sizeof(Game));
    if(pGame==NULL){
        exit(ERR_MALLOC);
    }
    // Create GUI structure 
    pPen = createCanvas(W, H);
    if(pPen==NULL){
        exit(ERR_MALLOC);
    }
    // Open device (non blocking read to let the game loop flow)
    fdK = open(devK, O_RDONLY|O_NONBLOCK);
    if (fdK == -1) {
        exit(ERR_DEVICE);
    }
    // Open device (non blocking read to let the game loop flow)
    fdM = open(devM, O_RDONLY|O_NONBLOCK);
    if (fdM == -1) {
        exit(ERR_DEVICE);
    }
    // Store callbacks
    pGame->cbInit   = cbInit;
    pGame->cbEvent  = cbEvt; 
    pGame->cbUpdate = cbUpd; 
    pGame->cbDraw   = cbDrw;     
    pGame->cbFinish = cbFinish;
    // Store gui
    pGame->pPencil  = pPen;
    // Store file descriptors
    pGame->fdEventK = fdK;
    pGame->fdEventM = fdM;
    // Store user data
    pGame->pData    = pData; 
    // Store max FPS value
    pGame->curFPS   = maxFPS;
    pGame->maxFPS   = maxFPS;
    pGame->showFPS  = showFPS;
    // Return  
    return pGame;
}

void closeGame(Game* pGame){
    char c;
    int  n;
    if(pGame==NULL){
        exit(ERR_NULL);
    }
    // Call user exit callback
    if(pGame->cbFinish){
        pGame->cbFinish(pGame->pData);
    }
    // Close events
    close(pGame->fdEventM);
    close(pGame->fdEventK);
    // Close pencil
    closeCanvas(pGame->pPencil);
    // Free game structure
    free(pGame);
}

void gameLoop(Game* pGame){
    // Local variables
    double timeStart = getTimeMs();
    double timeEnd   = timeStart;
    double timeDiff  = timeEnd - timeStart;
    int    res       = 0;
    char   buffFPS[32];
    int    count     = 0;
    // Check parameters
    if(pGame==NULL){
        exit(ERR_NULL);
    }
    // Call init function before starting the game loop
    if(pGame->cbInit){
        pGame->cbInit(pGame->pData, pGame->pPencil);
    }
    // Infinite loop
    while(res==0){
        // Start time measurment 
        timeStart = getTimeMs();
 
        //----------------------------
        // INPUT event check
        //----------------------------
        res |= eventPolling(pGame); 

        //----------------------------
        // UPDATE 
        //----------------------------
        res |= pGame->cbUpdate(pGame->pData, pGame->pPencil, timeDiff);        

        //----------------------------
        // DRAW
        //----------------------------
        // init screen buffer and clear screen
        startScreenDraw(pGame->pPencil);
        clearScreen  (pGame->pPencil);
        // User draw
        pGame->cbDraw(pGame->pData, pGame->pPencil);
        // display FPS if requested
        if(pGame->showFPS){
            sprintf(buffFPS, "FPS=%.1f \n", 1000.0/timeDiff);
            displayCharAt(pGame->pPencil, 0, 0, buffFPS);
        }
        // Flush screen buffer (send to stdout)
        flushScreenDraw(pGame->pPencil);
        
        // Wait for the FPS time
        count = 0;
        do{
            // End of time measurment
            timeEnd = getTimeMs();
            // Compute time diff
            timeDiff = timeEnd-timeStart;
            // Increase wait counter
            count++;            
        } while(timeDiff <= 1000.0/pGame->curFPS);
/*
        // Auto adapt FPS (TODO)
        if (count <= 2){
            pGame->curFPS /= 2;
        }
        else{
            pGame->curFPS += 1;
            if(pGame->curFPS>pGame->maxFPS){
                pGame->curFPS = pGame->maxFPS;
            }
        }
//*/
    }
    // Close game (free all resources)
    closeGame(pGame);    
}

double getTimeMs(){
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time);
    double result = (1000*time.tv_sec) + (time.tv_nsec/1000000.0);
    return result;   
}

void playSound(char* filePath){
    char cmd[128];
    sprintf(cmd, "aplay 2>&1 %s | grep XXX &", filePath);
    system(cmd);
}


