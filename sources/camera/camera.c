#include <stdio.h>
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



