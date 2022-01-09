#include <stdio.h>
#include <stdlib.h>

#include "backpack.h"


void initBackpack(Backpack* pBk, int maxItems){
    // Check parameters
    if(pBk==NULL){
        RAGE_QUIT("Backpack pointer is NULL");
    }
    pBk->pItemList  = NULL;
    pBk->nbItems    = 0;
    pBk->nbMaxItems = maxItems;
}

int getNbItems(Backpack* pBk){
    // Check parameters
    if(pBk==NULL){
        RAGE_QUIT("Backpack pointer is NULL");
    }
    return pBk->nbItems;
}

int isEmpty(Backpack* pBk){
    // Check parameters
    if(pBk==NULL){
        RAGE_QUIT("Backpack pointer is NULL");
    }
    return (pBk->nbItems == 0);
}

int isFull(Backpack* pBk){
    // Check parameters
    if(pBk==NULL){
        RAGE_QUIT("Backpack pointer is NULL");
    }
    return (pBk->nbItems == pBk->nbMaxItems);    
}

int addItem(Backpack* pBk, CellType ct){
    // Variables
    int       res   = 0;
    CellType* pCt   = NULL;
    // Check parameters
    if(pBk==NULL){
        RAGE_QUIT("Backpack pointer is NULL");
    }
    // Check if not full
    if(isFull(pBk)==0){
        pCt = malloc( sizeof(CellType) );
        if(pCt==NULL){
            RAGE_QUIT("Backpack item allocation failed !");
        }
        pBk->pItemList = insertDataHead(pBk->pItemList, pCt);
        pBk->nbItems++;
        res = 1;
    }
    // Return result of add process
    return res;
}

/*
CellType removeItem(Backpack* pBk, int index  ){
    // Check parameters
    if(pBk==NULL){
        RAGE_QUIT("Backpack pointer is NULL");
    }
    // TODO
        
}
//*/




