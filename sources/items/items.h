#ifndef ITEMS_H
    #define ITEMS_H
    
    #define NO_DECAY (-1)
    
    // Structures
    typedef struct {
        char*    name;
        CellType cType;
        float    decayPerSec; // -1/NO_DECAY means no decay over time
        float    decayPerUse; // -1/NO_DECAY means no decay per use
        float    life; //  Remaining life (0 or less means 'useless/destroyed')
    } Item;

    Item* createItem(char* name, CellType ct, float initLife, float decayPerTime, float decayPerUse); 
    void  destroyItem(Item* pItem);
    
       
#endif
