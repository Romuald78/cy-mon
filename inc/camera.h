#ifndef CAMERA_H
    #define CAMERA_H
    
    #include "./inc/errors.h"
    
    #define CAMERA_SPEED_INIT 15.0
    #define CAMERA_STEP       1.0
    
    typedef struct{
        float x;
        float y;
        int W;
        int H;
        int destX;
        int destY;
        int manualMove;
        float speed; // cell/sec.
    } Camera;

    void initCamera  (Camera* pCam, int x, int y, int w, int h, float speed);   
    void moveCamera  (Camera* pCam, float dx, float dy);
    void moveCameraTo(Camera* pCam, float x, float y);
    void setCameraTo (Camera* pCam, float x, float y);
    void updateCamera(Camera* pCam, float deltaTime);
    void saturateCamera(Camera* pCam, int x0, int y0, int x1, int y1);

#endif
