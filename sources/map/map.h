#ifndef MAP_H
    #define MAP_H
    
    #include "errors.h"
    #include "utils.h"
    
    #define DEFAULT_BACK_COLOR (0xFF003000)
    #define DEFAULT_FONT_COLOR (0xFF40F080)
    
    typedef enum {
        // default empty cell
        NONE=0,
        GRASS,
        RAW_TEXT,

        //==================================================
        // ITEMS (can be picked up)
        //==================================================
        // Nature elements
        HERB, CLOVER, TULIP, HIBISCUS, FLOWER, ROSE, SUNFLOWER,
        // Tools
        HAMMER, WRENCH, AXE, TOOLBOX, MAGNET,
        LOCK1, LOCK2, KEY, 
        //------------------------ 
        START_PICKUP = HERB,
        END_PICKUP   = KEY,
        //------------------------ 

        //==================================================
        // MISC. ITEMS (no pickup)
        //==================================================
        // Misc. Items
        CLOCK,

        //==================================================
        // Blocking cells (BLOCKING value will be added in the code)
        //==================================================
        ROCK,       
        TREE, PINE,
        //------------------------ 
        START_BLOCK = ROCK,
        END_BLOCK   = PINE,
        //------------------------ 

        //==================================================
        // GUI Elements
        //==================================================
        GUI_BORDER_H , GUI_BORDER_V ,
        GUI_CORNER_TL, GUI_CORNER_TR, GUI_CORNER_BL, GUI_CORNER_BR,
        GUI_TEE_L    , GUI_TEE_R    , GUI_TEE_T    , GUI_TEE_B    ,
        GUI_CROSS    ,


        // Total number of cell types
        NB_CELL_TYPES,
        // Some cells can have some flags like blocking, camouflage 
        BLOCKING  =0x01000000,
        CAMOUFLAGE=0x02000000        
    } CellType;

    typedef struct {
        int W;
        int H;
        CellType* grid; 
    } Map;

    // API Functions    
    void     createMap(Map*  pMap, int w, int h);
    CellType readMap(void* pMp, char* pOut, int absX, int absY, int scrX, int scrY, int* pRGB, int* pRGB2); 
    void     writeMap (Map*  pMap, int x, int y, CellType ct);
    void     initCellTypes(char** cellTypes);
    void     updateCellTypes(char** celltypes, float deltaTime);

#endif
