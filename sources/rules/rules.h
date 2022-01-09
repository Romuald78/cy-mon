#ifndef RULES_H
    #define RULES_H

    #include "errors.h"
    #include "player.h"
    #include "moves.h"
    #include "map.h"
    #include "backpack.h"
    
    Moves playerCanMove(Player* pPlayer, Map* pMap, float deltaTime);
    void  pickUpItem   (Player* pPlayer, Map* pMap, Backpack* pBk  );
    
#endif
