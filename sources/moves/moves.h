#ifndef MOVES_H
    #define MOVES_H
    
    typedef enum{
        MOVES_NONE  = 0,
        MOVES_LEFT  = 1,
        MOVES_RIGHT = 2,
        MOVES_UP    = 4,
        MOVES_DOWN  = 8,
        MOVES_HORIZ = MOVES_LEFT  | MOVES_RIGHT,
        MOVES_VERTI = MOVES_UP    | MOVES_DOWN,
        MOVES_ALL   = MOVES_HORIZ | MOVES_VERTI 
    } Moves;

    float absf(float v);
    void move(int move, float speed, float deltaTime, float* pDX, float* pDY);

#endif
