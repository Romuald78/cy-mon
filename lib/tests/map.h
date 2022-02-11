#ifndef MAP_H
    #define MAP_H

    // Structures
    typedef struct{
        int W;
        int H;
        unsigned char* pGrid;
    } Map;

    // Functions
    Map* createMap(int w, int h);
    void destroyMap(Map* pMap);
    
#endif // MAP_H
