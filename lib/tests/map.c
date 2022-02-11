#include <stdlib.h>
#include "libGameRGR.h"
#include "map.h"

Map* createMap(int w, int h){
    // Variables
    Map* pMap = NULL;
    unsigned char* pGrid = NULL;
    // Check parameters
    if(w<=0 || h <=0){
        rageQuit(1000, "Map size is not correct (w=%d/h=%d)", w, h);
    }    
    // Allocate grid
    pGrid = malloc(sizeof(unsigned char)*w*h);
    if(pGrid == NULL){
        rageQuit(1001, "Map Grid allocation failed !");
    }
    // Allocate Map
    pMap = malloc(sizeof(Map));
    if(pMap == NULL){
        rageQuit(1002, "Map Structure allocation failed !");
    }
    // Fill map
    pMap->W = w;
    pMap->H = h;
    pMap->pGrid = pGrid;
    // Return map address
    return pMap;
}

void destroyMap(Map* pMap){
    // Check parameters
    if(pMap==NULL){
        rageQuit(1003, "Map pointer is NULL");
    }    
    // Free grid and map
    free(pMap->pGrid);
    pMap->pGrid = NULL;
    free(pMap);
}






