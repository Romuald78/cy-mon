#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/emoticons.h"
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
    CellType ct = NONE;
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
    pMenu->grid = malloc( w*h*sizeof(CellType) );
    if(pMenu->grid == NULL){
        RAGE_QUIT("Menu grid alloc failed !");
    }
    // Fill Borders
    for(int row=0;row<h;row++){
        for(int col=0;col<w;col++){
            ct = NONE;
            index = getIndex(col, row, w);
            // Four corners
            if(col==0){
                if(row==0){
                    ct = GUI_CORNER_TL;
                }
                else if(row==h-1){
                    ct = GUI_CORNER_BL;
                }
                else{
                    ct = GUI_BORDER_V;
                }
            }
            else if(col==w-1){
                if(row==0){
                    ct = GUI_CORNER_TR;
                }
                else if(row==h-1){
                    ct = GUI_CORNER_BR;
                }
                else{
                    ct = GUI_BORDER_V;
                }
            }
            // Horizontal borders
            else if(row==0 || row==h-1){
                ct = GUI_BORDER_H;
            }
            pMenu->grid[index] = ct;       
        }
    }   
    // Fill clock
    index = getIndex(1,1,w);
    pMenu->grid[index++] = CLOCK;
    // Fill text
    pMenu->grid[index++] = RAW_TEXT;
    pMenu->grid[index++] = RAW_TEXT;
    pMenu->grid[index++] = RAW_TEXT;
}

CellType readItemMenu(void* pMn, char* pOut, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2){
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
        // get relative grid coords
        int x = scrX-refX;
        int y = scrY-refY;
        // update background color
        if(pRGB2!=NULL){
            *pRGB2 = addRGB(*pRGB2, 0x80FFFFFF);
        }
        // Update font color
        if(pRGB!=NULL){
            *pRGB = 0xFF004000;
        }
        int index = getIndex( x, y, W);
        ct = pMenu->grid[index];
        // Set output string according to position
        if(pOut!=NULL && y==1 && ct==RAW_TEXT){
            switch(x){
                case 2:
                    strcpy(pOut, "12");
                    break;
                case 3:
                    strcpy(pOut, ":3");
                    break;
                case 4:
                    strcpy(pOut, "4 ");
                    break;
                default:
                    break;
            }
        }
    }    
    // Return result 
    return ct;
}


