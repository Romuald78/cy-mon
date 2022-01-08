#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "./inc/map.h"

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
                ct = ROCK + BLOCKING;
            }
            // FLOWERs
            else if(r < 5){
                ct = rand()%7 + HERB;
            }
            // ROCKs
            else if(r < 10){
                ct = ROCK + BLOCKING;
            }
            // TREEs
            else if(r < 30){
                ct = rand()%2 + TREE + BLOCKING;
            }
            // Write value into the grid
            writeMap(pMap, x, y, ct);
        }
    }
    // Fill the emoticons
    pMap->celltypes[GRASS]     = EMOT_BLANK;
    pMap->celltypes[HERB]      = EMOT_HERB;
    pMap->celltypes[CLOVER]    = EMOT_CLOVER;
    pMap->celltypes[TULIP]     = EMOT_TULIP;
    pMap->celltypes[HIBISCUS]  = EMOT_HIBISCUS;
    pMap->celltypes[FLOWER]    = EMOT_FLOWER;
    pMap->celltypes[ROSE]      = EMOT_ROSE;
    pMap->celltypes[SUNFLOWER] = EMOT_SUNFLOWER;
    pMap->celltypes[ROCK]      = EMOT_ROCK" ";
    pMap->celltypes[TREE]      = EMOT_TREE;
    pMap->celltypes[PINE]      = EMOT_PINE;
    pMap->celltypes[AXE]       = EMOT_AXE;
    
}

int _getIndex(int x, int y, int W){
    return x + y*W;
}

//-------------------------------------------------
// API functions
//-------------------------------------------------

CellType readMap(Map* pMap, int x, int y){
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
    // Get value and return 
    int index = _getIndex( x, y, pMap->W);
    return pMap->grid[index];
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
    int index = _getIndex(x, y, pMap->W);
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


