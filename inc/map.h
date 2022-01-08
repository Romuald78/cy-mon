#ifndef MAP_H
    #define MAP_H
    
    #include "./inc/errors.h"
    
    typedef enum {
        // default empty cell
        GRASS=0,
        // non blocking decor cells 
        HERB, CLOVER, TULIP, HIBISCUS, FLOWER, ROSE, SUNFLOWER,
        // Blocking cells
        ROCK,       
        TREE, PINE,
        // Tools
        AXE,
        // Total number of cell types
        NB_CELL_TYPES,

        // Some cells can have some flags like blocking, camouflage 
        BLOCKING  =0x1000,
        CAMOUFLAGE=0x2000
    } CellType;

    typedef struct {
        int W;
        int H;
        CellType* grid; 
        char* celltypes[NB_CELL_TYPES]; 
    } Map;

    // API Functions    
    void     createMap(Map* pMap, int w, int h);
    CellType readMap(Map* pMap, int x, int y);
    void     writeMap(Map* pMap, int x, int y, CellType ct);
    
#endif
