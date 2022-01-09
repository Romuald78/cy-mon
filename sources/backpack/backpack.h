#ifndef BACK_PACK_H
    #define BACK_PACK_H

    #include "RGR_list.h"
    #include "map.h"

    #define MAX_NB_ITEMS 5

    typedef struct {
        // Item list
        Node* pItemList;
        // Item length always kept in memory
        int nbItems;
        int nbMaxItems;
    } Backpack;
    
    
    void     initBackpack(Backpack* pBk, int maxItems);    
    int      getNbItems  (Backpack* pBk);
    int      isEmpty     (Backpack* pBk);
    int      isFull      (Backpack* pBk);
    int      addItem     (Backpack* pBk, CellType ct);
    CellType removeItem  (Backpack* pBk, int index  );
    int      getItemCount(Backpack* pBk, CellType ctItem);
    int      compareItems(void* pData1, void* pData2);
    
#endif
