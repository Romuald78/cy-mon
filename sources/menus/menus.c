#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libRGR/emoticons.h"
#include "menus.h"


unsigned int utf8ToInt(char* utf8){
    int L;
    unsigned int res = 0x00;
    if(utf8==NULL){
        RAGE_QUIT("UTF8 to Integer NULL parameter !");
    }
    L = strlen(utf8);
    for(int i=0;i<L;i++){
        unsigned char c = utf8[i];
        res = (res<<8)+c;
    }
    return res;
}

void createItemMenu(Menu* pMenu, int x, int y, int w, int h){   
    // Variables
    unsigned int value;
    int index; 
    // check parameters
    if(pMenu==NULL){
        RAGE_QUIT("MENU pointer NULL !");
    }
    if(w<=0 || h<=0){
        RAGE_QUIT("Bad dimensions !");
    }
    // Fill menu structure
    pMenu->x = x;
    pMenu->y = y;
    pMenu->w = w;
    pMenu->h = h;
    pMenu->hidden = 0;
    pMenu->grid = malloc( w*h*sizeof(CellType) );
    if(pMenu->grid == NULL){
        RAGE_QUIT("Menu grid alloc failed !");
    }
    // Fill cell types
    for(int row=0;row<h;row++){
        for(int col=0;col<w;col++){
            value = utf8ToInt("  ");
            index = getIndex(col, row, w);
            if(col==0 || row==0 || col==w-1 || row==h-1){
                value = utf8ToInt(EMOT_CROSS);
            }
            pMenu->grid[index] = value;       
        }
    }   
}

CellType readItemMenu(void* pMn, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2){
    // Variables
    Menu*    pMenu = NULL;
    CellType ct    = NONE;
    int W,H,refX,refY;
    // check parameters
    if(pMn == NULL){
        RAGE_QUIT("Bad menu pointer !");
    }
    pMenu = (Menu*)pMn;
    if(pMenu->grid == NULL){
        RAGE_QUIT("Bad grid pointer !");
    }
    // Check if screen coords are in the menu
    W    = pMenu->w;
    H    = pMenu->h;
    refX = pMenu->x;
    refY = pMenu->y;
    if( (scrX>=refX) && (scrX<refX+W) && (scrY>=refY) && (scrY<refY+H) ){
        // update background color
        if(pRGB2!=NULL){
            *pRGB2 = ((*pRGB2 & 0x00FCFCFC)>>2)+0xFF000000;
        }
        ct = NONE;
    }    
    // Return result 
    return ct;
}

 
