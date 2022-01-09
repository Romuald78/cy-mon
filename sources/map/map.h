#ifndef MAP_H
    #define MAP_H
    
    #include "errors.h"
    #include "utils.h"
    
    #define DEFAULT_BACK_COLOR (0xFF003000)
    #define DEFAULT_FONT_COLOR (0xFF40F080)
    
    // We can use the 4 bytes as an UTF8 code (without '\0')
    typedef enum {
        // default empty cell
        NONE=0,
        GRASS,

        // non blocking decor cells (that can be picked up)
        //------------------------------------------
        // Nature elements
        HERB, CLOVER, TULIP, HIBISCUS, FLOWER, ROSE, SUNFLOWER,
        // Tools
        AXE,
        //------------------------------------------
        START_PICK_UP = HERB,
        END_PICK_UP   = AXE,
        //------------------------------------------

        // Blocking cells
        ROCK,       
        TREE, PINE,

        // Total number of cell types
        NB_CELL_TYPES,

        // Some cells can have some flags like blocking, camouflage 
        BLOCKING  =0x100,
        CAMOUFLAGE=0x200
    } CellType;

    typedef struct {
        int W;
        int H;
        CellType* grid; 
        char* celltypes[NB_CELL_TYPES]; 
    } Map;

    // API Functions    
    void     createMap(Map*  pMap, int w, int h);
    CellType readMap(void* pMp, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2); 
    void     writeMap (Map*  pMap, int x, int y, CellType ct);
    
#endif
