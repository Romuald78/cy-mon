#include <stdio.h>
#include <stdlib.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "./inc/main.h"
#include "./inc/moves.h"


void event(void* pUserData, Event* pEv){
    // Cast the user data correctly 
    UserData* pDat = (UserData*)pUserData;
    if(!pDat || !pEv){
        RAGE_QUIT("EVENT NULL params");
    }
    int type  = pEv->type;
    int code  = pEv->code;
    int value = pEv->value;

    if(type == EV_KEY){
        Moves camo = MOVES_NONE;
        if(code==KEY_LEFT){
            camo |= MOVES_LEFT;
        }
        else if(code==KEY_RIGHT){
            camo |= MOVES_RIGHT;
        }
        else if(code==KEY_UP){
            camo |= MOVES_UP;
        }
        else if(code==KEY_DOWN){
            camo |= MOVES_DOWN;
        }
        if(camo != MOVES_NONE){
            if(value==0x01){
                pDat->player.move |= camo;
            }
            else if(value==0x00){
                pDat->player.move &= (~camo);
            }
        }
        
        if(code==KEY_SPACE && value==0x01){
            int x = rand()%(pDat->map.W-pDat->cam.W);
            int y = rand()%(pDat->map.H-pDat->cam.H);
            moveCameraTo( &(pDat->cam), x, y);
        }
    }

}

