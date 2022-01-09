#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "main.h"

int main(int argc, char** argv){
    // Local variables
    int   W = -1;
    int   H = -1;
    int   maxFPS  = 60;
    int   showFPS = 0;
    char* devK;
    char* devM;
    Game* pGame;
    // Create user data
    UserData userData;
         
    // Check parameter presence    
    if(argc < 5){
        exit(ERR_PARAMS);
    }
    if(argc >= 6){
        maxFPS = atoi(argv[5]);
    }
    if(argc >= 7){
        showFPS = atoi(argv[6]);
    }
    // Retrieve parameters
    W    = atoi(argv[1]);
    H    = atoi(argv[2]);
    devK = argv[3];
    devM = argv[4];
    // Check parameter values
    if(W <= 0 || H <= 0){
        exit(ERR_DIMENSIONS);
    }
        
    // Create game structure
    pGame = createGame(W, H, maxFPS, showFPS,
                       devK, devM,
                       &userData,
                       init, event, update, draw, finish);
    if(!pGame){
        exit(ERR_NULL);
    }
    // Call the game loop (infinite loop) until ESC key is pressed
    gameLoop(pGame);
    // End of program
    return 0;
}

