#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "./inc/main.h"


void draw(void* pUserData, Pencil* pPencil){
    // Cast the user data correctly 
    UserData* pDat = (UserData*)pUserData;
    if(!pDat ||!pPencil){
        RAGE_QUIT("DRAW NULL parameters !");
    }

    // Display only the part of the grid under the camera 
    for(int y=0;y<pPencil->height;y++){
        setPosition(pPencil, 0, y);
        clearLineFull(pPencil);
        for(int x=0;x<pPencil->width;x++){
            // add camera offset
            int X2 = x + (int)(pDat->cam.x);
            int Y2 = y + (int)(pDat->cam.y);
            if(X2>=0 && Y2>=0 && X2<pDat->map.W && Y2<pDat->map.H){
                // read cell type from the map
                CellType ct = readMap(&(pDat->map), X2, Y2);
                // Get blocking info
                CellType block = ct & BLOCKING;
                // Keep only the display value
                ct = ct & (~BLOCKING);
                // Check if the current cell is the player position
                if( X2==(int)(pDat->player.x) && Y2==(int)(pDat->player.y) ){
                    displayChar(pPencil, pDat->player.display);
                }
                else{
                    displayChar(pPencil, pDat->map.celltypes[ct]);
                }
            }
            else{
                displayChar(pPencil, EMOT_BLANK);
            }            
        }        
    }
}

