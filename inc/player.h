#ifndef PLAYER_H
    #define PLAYER_H
    
    #include "./inc/errors.h"
    #include "./inc/moves.h"
    
    #define PLAYER_INIT_SPEED 7.5

    typedef struct {
        float x;
        float y;
        float speed;
        char* display;
        int   move;
    } Player;
    
    // functions
    void initPlayer(Player* p, float x, float y, float speed, char* disp);
    void updatePlayer(Player* p, float deltaTime, Moves* pMoveLimit);    
#endif
