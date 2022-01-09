#ifndef MENUS_H
    #define MENUS_H

    #include "errors.h"
    #include "map.h"
    #include "utils.h"

    typedef struct {
        int x;
        int y;
        int w;
        int h;
        int hidden;
        CellType* grid;
    } Menu;

    void createItemMenu(Menu* pMenu, int x, int y, int w, int h);
    CellType readItemMenu(void* pMn, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2);



#endif
