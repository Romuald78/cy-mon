#ifndef PLAYER_H
    #define PLAYER_H
    
    #include "../errors/errors.h"
    #include "../moves/moves.h"
    
    #define PLAYER_INIT_SPEED 7.5

    typedef struct {
        float x;
        float y;
        float speed;
        char* display;
        int   move;
        int   pickingUp;    // player trying to pick up an object. Set on event. Reset after update.
    } Player;
    
    // functions
    void initPlayer(Player* p, float x, float y, float speed, char* disp);
    void updatePlayer(Player* p, float deltaTime, Moves* pMoveLimit);    
#endif
