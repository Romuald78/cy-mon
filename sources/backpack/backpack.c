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
        // Fill the data 
        *pCt = ct;
        // insert data into the list
        pBk->pItemList = insertDataHead(pBk->pItemList, pCt);
        // store list length here to increase speed
        pBk->nbItems++;
        res = 1;
    }
    // Return result of add process
    return res;
}

int getItemCount(Backpack* pBk, CellType ctItem){
    // Variables
    int nb;
    // Check parameters
    if(pBk==NULL){
        RAGE_QUIT("Backpack pointer is NULL");
    }
    // Get number of items in the backpack
    nb = getNbOccur(pBk->pItemList, &ctItem, compareItems);
    // return result
    return nb;
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

int compareItems(void* pData1, void* pData2){
    int ct1=0, ct2=0, res=0;
    // Check parameters
    if(pData1==NULL || pData2==NULL){
        RAGE_QUIT("Item pointers for comparison are NULL");
    }
    // Convert inputs
    ct1 = *((int*)pData1);    
    ct2 = *((int*)pData2);    
    if(ct1>ct2){
        res = -1;
    }
    else if(ct1<ct2){
        res = 1;
    }
    return res;
}



