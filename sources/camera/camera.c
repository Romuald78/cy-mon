#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "moves.h"


void initCamera  (Camera* pCam, int x, int y, int w, int h, float speed){
    // check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera NULL parameters !");
    }
    if(speed < 1.0){
        RAGE_QUIT("Camera speed is too low !");
    }
    if(w < 1 || h < 1){
        RAGE_QUIT("Camera dimensions are set to ZERO !");
    }
    setCameraTo(pCam, x, y);   
    pCam->W = w;
    pCam->H = h;
    pCam->speed = speed;
    pCam->manualMove = MOVES_NONE;
    pCam->pLayerList = NULL;
}

void addLayer(Camera* pCam, GenericRead callback, void* data){
    // Variables
    Layer* pLayer = NULL;
    // check parameters
    if(pCam==NULL || callback==NULL || data==NULL){
        RAGE_QUIT("Camera add layer NULL parameters !");
    }
    // Create layer structure (alloc)
    pLayer = malloc( sizeof(Layer) );
    if(pLayer==NULL){
        RAGE_QUIT("Camera layer MALLOC failed !");
    }
    // Fill layer struct
    pLayer->callback = callback;
    pLayer->data     = data;
    pLayer->hidden   = 0;
    // Add this data into the linked list
    pCam->pLayerList = insertDataTail(pCam->pLayerList, pLayer);
}

void setCameraTo(Camera* pCam, float x, float y){
    // check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera NULL parameters !");
    }
    // set camera final destination
    pCam->destX = (int)x;
    pCam->destY = (int)y;
    // set camera current position
    pCam->x = x;
    pCam->y = y;
}

void moveCamera(Camera* pCam, float dx, float dy){
    // check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera NULL parameters !");
    }
    setCameraTo(pCam, pCam->x+dx, pCam->y+dy);
}

void moveCameraTo(Camera* pCam, float x, float y){
    // check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera NULL parameters !");
    }
    // set camera final destination
    pCam->destX = (int)x;
    pCam->destY = (int)y;
}

void updateCamera(Camera* pCam, float deltaTime){
    int dirX = 0;
    int dirY = 0;
    float dx = pCam->destX - pCam->x;
    float dy = pCam->destY - pCam->y;        
    // check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera NULL parameters !");
    }
    // Check if we have to move the camera automatically
    if(pCam->x != pCam->destX || pCam->y != pCam->destY){
        // Get auto move difference
        dirX = dx>CAMERA_STEP ? 1 : dx<-CAMERA_STEP ? -1 : 0;
        dirY = dy>CAMERA_STEP ? 1 : dy<-CAMERA_STEP ? -1 : 0;
        dx   = (dirX*pCam->speed*deltaTime)/1000.0;
        dy   = (dirY*pCam->speed*deltaTime)/1000.0;
    }
    // Check if we are moving the camera manually
    // (Stop auto move)
    if( (pCam->manualMove & MOVES_ALL) != MOVES_NONE){
        // Stop auto movement
        pCam->destX = pCam->x;
        pCam->destY = pCam->y;
        // Get dx dy move
        move(pCam->manualMove, pCam->speed, deltaTime, &dx, &dy);
    }
    // Move camera according to variation
    moveCamera(pCam, dx, dy);
}

void saturateCamera(Camera* pCam, int x0, int y0, int x1, int y1){
    // check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera NULL parameters !");
    }
    if(pCam->x < x0){
        pCam->x = x0;
    }
    if(pCam->x > x1){
        pCam->x = x1;
    }
    if(pCam->y < y0){
        pCam->y = y0;
    }
    if(pCam->y > y1){
        pCam->y = y1;
    }
}

// this function gets values from all the layers (from bottom/0 to top/N-1)
// the cell type is returned directly. This is the upper layer with a visible cell.
// the pOut buffer is there for specific strings to display like text
CellType getLayerCell(Camera* pCam, char* pOut, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2){
    // Variables
    CellType ct    = NONE;
    CellType ctOld = NONE;
    Node*    pNode = NULL;
    // check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera NULL parameters !");
    }
    // Set output string
    if(pOut!=NULL){
        pOut[0] = '\0';
    }
    // For all layers
    pNode = pCam->pLayerList;
    while(pNode != NULL){
        Layer* pLayer = (Layer*)(pNode->pData);
        if(pLayer==NULL){
            RAGE_QUIT("Camera layer list NULL pointer !");            
        }
        if(pLayer->callback==NULL){
            RAGE_QUIT("Camera layer callback is NULL !");
        }
        if(pLayer->data==NULL){
            RAGE_QUIT("Camera layer data is NULL !");
        }
        // Read the layer (if it's visible)
        ct = NONE;
        if(pLayer->hidden==0){
            ct = pLayer->callback(pLayer->data, pOut, absX, absY, scrX, scrY, pRGB, pRGB2);
        }
        if (ct != NONE){
            ctOld = ct;
        }
        // Go to next layer
        pNode = pNode->pNext;
    }
    // Return merged cell value
    return ctOld;
}

// hidden is 0 or 1
// if another value, means toggle value
void _layerVisibility(Camera* pCam, int index, int hidden){
    // Check parameters
    if(pCam==NULL){
        RAGE_QUIT("Camera layer pointer is NULL !");
    }
    if(index<0){
        RAGE_QUIT("Layer index is negative !");
    }
    // set item menu hidden 
    Layer* pLayer = getDataAt(pCam->pLayerList, index);
    if(hidden &0xFE){
        pLayer->hidden ^= 0x01;
    }
    else{
        pLayer->hidden = hidden;
    }    
}

void hideLayer(Camera* pCam, int index){
    _layerVisibility(pCam, index, 1);
}

void showLayer(Camera* pCam, int index){
    _layerVisibility(pCam, index, 0);
}

void toggleLayer(Camera* pCam, int index){
    _layerVisibility(pCam, index, 2);
}

