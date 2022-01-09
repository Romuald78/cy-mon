#ifndef CAMERA_H
    #define CAMERA_H
    
    #include "errors.h"
    #include "map.h"
    #include "RGR_list.h"
    
    #define CAMERA_SPEED_INIT 15.0
    #define CAMERA_STEP       1.0

    // Call back for generic read (used for any layer)
    // first pointer is for font color, second is fo background color.
    typedef CellType (*GenericRead)(void* pObject,
                                    int   absX, int  absY,
                                    int   scrX, int  scrY,
                                    int*  pRGB, int* pRGB2 );
    
    typedef struct {
        GenericRead callback;
        void*       data;
    } Layer;
    
    typedef struct{
        float x;
        float y;
        int W;
        int H;
        int destX;
        int destY;
        int manualMove;
        float speed; // cell/sec.
        Node* pLayerList;  // linked list containing layers        
    } Camera;

    // Functions for camera
    void     initCamera    (Camera* pCam, int x, int y, int w, int h, float speed);   
    void     moveCamera    (Camera* pCam, float dx, float dy);
    void     moveCameraTo  (Camera* pCam, float x, float y);
    void     setCameraTo   (Camera* pCam, float x, float y);
    void     updateCamera  (Camera* pCam, float deltaTime);
    void     saturateCamera(Camera* pCam, int x0, int y0, int x1, int y1);
    
    void     addLayer      (Camera* pCam, GenericRead callback, void* data);
    CellType getLayerCell  (Camera* pCam, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2);

#endif
