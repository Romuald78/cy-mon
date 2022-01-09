#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../libRGR/game_rgr.h"
#include "../libRGR/emoticons.h"
#include "main.h"


void draw(void* pUserData, Pencil* pPencil){
    // Variables
    int X2;
    int Y2;
    int fontRGB = 0;
    int backRGB = 0;
    int lastBackRGB = 0;
    int lastFontRGB = 0;
    // Cast the user data correctly 
    UserData* pDat = (UserData*)pUserData;
    if(!pDat ||!pPencil){
        RAGE_QUIT("DRAW NULL parameters !");
    }

    // Initialise font and background
    setBgColor  (pPencil, lastBackRGB, 1);
    setFontColor(pPencil, lastFontRGB, 1);

    // Display only the part of the grid under the camera 
    for(int y=0;y<pPencil->height;y++){
        // Put cursor on the left side of the screen        
        setPosition(pPencil, 0, y);
        // Start to process each column
        for(int x=0;x<pPencil->width;x++){
            // add camera offset
            // X2,Y2 are the real absolute coordinates, while x,y are the screen coordinates
            X2 = x + (int)(pDat->cam.x);
            Y2 = y + (int)(pDat->cam.y);
            // check if this cell is visible
            if(X2>=0 && Y2>=0 && X2<pDat->map.W && Y2<pDat->map.H){
                // read cell type from ALL the layers
                CellType ct = getLayerCell(&(pDat->cam), X2, Y2, x, y, &fontRGB, &backRGB);
                // Keep only the display value
                ct = ct & (~BLOCKING);
                // Change background color if not the previous one
                if(backRGB != lastBackRGB){    
                    setBgColor(pPencil, backRGB, 1);
                    lastBackRGB = backRGB;                
                }
                // Change font color if not the previous one
                if(fontRGB != lastFontRGB){
                    setFontColor(pPencil, fontRGB, 1);
                    lastFontRGB = fontRGB;                
                }
                // Check if the current cell is the player position
                // TODO : this will create a display issue when using a window over the map
                if( X2==(int)(pDat->player.x) && Y2==(int)(pDat->player.y) ){
                    // Display PLAYER
                    displayChar(pPencil, pDat->player.display);
                }
                else{
                    // Display the result of the map
                    displayChar(pPencil, pDat->map.celltypes[ct]);
                }
            }
            else{
                displayChar(pPencil, EMOT_BLANK);
            }            
        }        
    }
}

