#ifndef ITEMS_H
    #define ITEMS_H
    
    #define ITEM_NAME_LEN 32
    #define NO_DECAY (-1)
    
    // Structures
    typedef struct {
        char     name[ITEM_NAME_LEN+1];
        CellType cType;
        float    decayPerSec; // -1/NO_DECAY means no decay over time
        float    decayPerUse; // -1/NO_DECAY means no decay per use
        float    life; //  Remaining life (0 or less means 'useless/destroyed')
    } Item;

    Item* createItem(char* name, CellType ct, float initLife, float decayPerTime, float decayPerUse); 
    void  destroyItem(Item* pItem);
    
       
#endif
