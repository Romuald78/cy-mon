#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "map.h"
#include "items.h"


Item* createItem(char* name, CellType ct, float initLife, float decayPerTime, float decayPerUse){
    // Variables
    Item* pItem=NULL;
    // Check parameters
    if(name==NULL){
        RAGE_QUIT("Item name is not given !");
    }
    if(initLife <= 0.0){
        RAGE_QUIT("Life is below 0 during item creation phase !");
    }
    // Allocate item 
    pItem = malloc( sizeof(Item) );
    if(pItem==NULL){
        RAGE_QUIT("Item allocation failed !");
    }
    // Allocate item name buffer
    pItem->name = malloc( strlen(name)*sizeof(char) );
    if(pItem->name==NULL){
        RAGE_QUIT("Item name allocation failed !");
    }    
    // Fill item fields    
    pItem->cType       = ct;
    pItem->decayPerSec = decayPerTime;
    pItem->decayPerUse = decayPerUse;
    pItem->life        = initLife;
    // Return Item
    return pItem;
}


void destroyItem(Item* pItem){    
    // Check parameters
    if(pItem==NULL){
        RAGE_QUIT("Item pointer is NULL !");
    }
    if(pItem->name){
        RAGE_QUIT("Item name is NULL !");
    }
    // Free buffers
    free(pItem->name);
    free(pItem);    
}





