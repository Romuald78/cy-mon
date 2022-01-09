#ifndef RGR_LIST_H
    #define RGR_LIST_H

    // Constants
    #define ERR_DATA            0x0001
    #define ERR_NODE            0x0002
    #define ERR_LIST            0x0004
    #define ERR_HEAD            0x0008
    #define ERR_TAIL            0x0010
    #define ERR_AT              0x0020
    #define ERR_CREATE          0x0040
    #define ERR_FREE            0x0080
    #define ERR_REMOVE          0x0100
    #define ERR_INSERT          0x0200       
    #define ERR_DISPLAY         0x0400
    #define ERR_GET             0x0800
    #define ERR_GET_NB_OCCUR    0x1000

    #define ERR_LNULL    0x0001
    #define ERR_LMALLOC  0x0002
    #define ERR_LPARAM   0x0004
    #define ERR_LINDEX   0x0008
    
    #define ERR_CREATE_NODE      ((ERR_CREATE | ERR_NODE           )<<8)
    #define ERR_FREE_NODE        ((ERR_FREE   | ERR_NODE           )<<8)
    #define ERR_INSERT_NODE_HEAD ((ERR_INSERT | ERR_NODE | ERR_HEAD)<<8)
    #define ERR_INSERT_DATA_HEAD ((ERR_INSERT | ERR_DATA | ERR_HEAD)<<8)
    #define ERR_INSERT_NODE_TAIL ((ERR_INSERT | ERR_NODE | ERR_TAIL)<<8)
    #define ERR_INSERT_DATA_TAIL ((ERR_INSERT | ERR_DATA | ERR_TAIL)<<8)
    #define ERR_INSERT_NODE_AT   ((ERR_INSERT | ERR_NODE | ERR_AT  )<<8)
    #define ERR_INSERT_DATA_AT   ((ERR_INSERT | ERR_DATA | ERR_AT  )<<8)
    #define ERR_GET_NODE_AT      ((ERR_GET    | ERR_NODE | ERR_AT  )<<8)
    #define ERR_GET_DATA_AT      ((ERR_GET    | ERR_DATA | ERR_AT  )<<8)
    #define ERR_REMOVE_NODE_AT   ((ERR_REMOVE | ERR_NODE | ERR_AT  )<<8)
    
    // STRUCTs    
    typedef struct _node{
        void*         pData;
        struct _node* pPrev;
        struct _node* pNext;
    } Node;

    // Callback (for display data)
    typedef void (*displayCallback)(Node* pNode);
    typedef int  (*compareCallBack)(void* pData1, void* pData2);
        
    // FUNCTIONs    
    Node* createNode(void* pData);
    void  freeNode  (Node* pNode, int freeData); 
    Node* emptyList (Node* pHead, int freeData);

    int   getListSize(Node* pHead);
    void  displayList(Node* pHead, displayCallback dispCB);

    Node* insertNodeHead(Node* pHead, Node* pNode);
    Node* insertNodeAt  (Node* pHead, Node* pNode, int index);
    Node* insertNodeTail(Node* pHead, Node* pNode);

    Node* insertDataHead(Node* pHead, void* pData);
    Node* insertDataAt  (Node* pHead, void* pData, int index);
    Node* insertDataTail(Node* pHead, void* pData);

    Node* getNodeAt(Node* pHead, int index);
    void* getDataAt(Node* pHead, int index);

    Node* removeNodeHead(Node* pHead, Node** ppNode);
    Node* removeNodeTail(Node* pHead, Node** ppNode);
    Node* removeNodeAt  (Node* pHead, Node** ppNode, int index);

    int   getNbOccur(Node* pHead, void* pData, compareCallBack ccb);    

#endif

