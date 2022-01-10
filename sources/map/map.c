#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lib/game_rgr.h"
#include "lib/emoticons.h"
#include "map.h"

//-------------------------------------------------
// LOCAL functions
//-------------------------------------------------
void _initMap(Map* pMap){
    // check parameters
    if(pMap == NULL){
        RAGE_QUIT("Bad map pointer !");
    }
    if(pMap->grid == NULL){
        RAGE_QUIT("Bad grid pointer !");
    }
    // Fill the whole grid using pseudo random
    srand(time(NULL));
    for(int x=0;x<pMap->W;x++){
        for(int y=0;y<pMap->H;y++){
            CellType ct = GRASS;
            // Get random value
            int r = rand()%101;
            // Choose cell type according to random value
            // Except if we are on the edge of the map : put some rocks
            if(x==0 || y==0 || x==pMap->W-1 || y==pMap->H-1){
                ct = ROCK;
            }
            // FLOWERs
            else if(r < 5){
                ct = rand()%7 + HERB;
            }
            // ROCKs
            else if(r < 10){
                ct = ROCK;
            }
            // TREEs
            else if(r < 30){
                ct = rand()%2 + TREE;
            }
            // Add blocking flag if needed
            if(ct>=START_BLOCK && ct<=END_BLOCK){
                ct |= BLOCKING;
            }
            // Write value into the grid
            writeMap(pMap, x, y, ct);
        }
    }
}

//-------------------------------------------------
// API functions
//-------------------------------------------------

CellType readMap(void* pMp, char* pOut, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2){
    // Variables
    Map*     pMap = NULL;
    CellType ct   = NONE;
    // check parameters
    if(pMp == NULL){
        RAGE_QUIT("Bad map pointer !");
    }
    pMap = (Map*)pMp;
    if(pMap->grid == NULL){
        RAGE_QUIT("Bad grid pointer !");
    }
    if(absX<0 || absY <0 || absX>=pMap->W || absY>=pMap->H){
        RAGE_QUIT("Bad parameter dimensions !");
    }    
    // Get value and return (do not look at screen coords, but only absolute coords)
    int index = getIndex( absX, absY, pMap->W);
    ct = pMap->grid[index];
    // Set background color
    if(pRGB2!=NULL){
        *pRGB2 = DEFAULT_BACK_COLOR; 
    }
    // return result
    return ct;
}

void writeMap(Map* pMap, int x, int y, CellType ct){
    // check parameters
    if(pMap == NULL){
        RAGE_QUIT("Bad map pointer !");
    }
    if(pMap->grid == NULL){
        RAGE_QUIT("Bad grid pointer !");
    }
    if(x<0 || y <0 || x>=pMap->W || y>=pMap->H){
        RAGE_QUIT("Bad parameter dimensions !");
    }    
    // Get value and write 
    int index = getIndex(x, y, pMap->W);
    pMap->grid[index] = ct;
}

void createMap(Map* pMap, int w, int h){
    // check parameters
    if(w<=0 || h<=0){
        RAGE_QUIT("Bad dimensions !");
    }
    // Fill map structure
    pMap->W = w;
    pMap->H = h;
    pMap->grid = malloc( w*h*sizeof(CellType) );
    if(pMap->grid == NULL){
        RAGE_QUIT("Map grid alloc failed !");
    }
    // Init Map
    _initMap(pMap);
}

void initCellTypes(char** celltypes){
    // check parameters
    if(celltypes == NULL){
        RAGE_QUIT("cell types array NULL pointer !");
    }
    // Fill the emoticons
    celltypes[NONE]      = "--";
    celltypes[RAW_TEXT]  = "??";

    celltypes[GRASS]     = EMOT_BLANK;
    celltypes[HERB]      = EMOT_HERB;
    celltypes[CLOVER]    = EMOT_CLOVER;
    celltypes[TULIP]     = EMOT_TULIP;
    celltypes[HIBISCUS]  = EMOT_HIBISCUS;
    celltypes[FLOWER]    = EMOT_FLOWER;
    celltypes[ROSE]      = EMOT_ROSE;
    celltypes[SUNFLOWER] = EMOT_SUNFLOWER;

    celltypes[ROCK]      = EMOT_ROCK" ";
    celltypes[TREE]      = EMOT_TREE;
    celltypes[PINE]      = EMOT_PINE;

    celltypes[AXE]       = EMOT_AXE;
    celltypes[HAMMER]    = EMOT_HAMMER;
    celltypes[WRENCH]    = EMOT_WRENCH;
    celltypes[LOCK1]     = EMOT_LOCK_CLOSED;
    celltypes[LOCK2]     = EMOT_LOCK_OPEN;
    celltypes[KEY]       = EMOT_KEY;
    celltypes[TOOLBOX]   = EMOT_TOOLBOX;
    celltypes[MAGNET]    = EMOT_MAGNET;


    celltypes[GUI_BORDER_H]  = EMOT_HORIZONTAL""EMOT_HORIZONTAL;
    celltypes[GUI_BORDER_V]  = EMOT_VERTICAL;
    celltypes[GUI_CORNER_TL] = EMOT_CORNER_TL;
    celltypes[GUI_CORNER_TR] = EMOT_CORNER_TR;
    celltypes[GUI_CORNER_BL] = EMOT_CORNER_BL;
    celltypes[GUI_CORNER_BR] = EMOT_CORNER_BR;
    celltypes[GUI_TEE_L]     = EMOT_TEE_LEFT;
    celltypes[GUI_TEE_R]     = EMOT_TEE_RIGHT;
    celltypes[GUI_TEE_T]     = EMOT_TEE_TOP;
    celltypes[GUI_TEE_B]     = EMOT_TEE_BOTTOM;
    celltypes[GUI_CROSS]     = EMOT_CROSS;

    // Dynamic emoticons
    celltypes[CLOCK] = malloc(strlen(EMOT_CLK_00)+1);
    if(celltypes[CLOCK]==NULL){
        RAGE_QUIT("celltypes malloc FAILED !");
    }
    strcpy(celltypes[CLOCK], EMOT_CLK_00);
}

void updateCellTypes(char** celltypes, float deltaTime){
    // Variables
    static float time=0.0;
    float  step = 1000.0/12;
    // check parameters
    if(celltypes == NULL){
        RAGE_QUIT("cell types array NULL pointer !");
    }
    // change clock item each 1/12 sec.
    time += deltaTime;
    if(time >= step){
        time -= step;
        celltypes[CLOCK][3]++;
        if( (unsigned char)(celltypes[CLOCK][3])>0x9B){
            celltypes[CLOCK][3] = 0x90;
        }    
    }       
}

 
