#include <stdio.h>
#include <stdlib.h>

#include "RGR_list.h"


// This is up to the user to allocate the data part
// and give the corresponding address (NULL is not allowed)
Node* createNode(void* pData){
    // Variables
    Node* pNode = NULL;
    int error = ERR_CREATE_NODE;
    // Check parameters
    if(pData==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // Alloc node 
    pNode = malloc(sizeof(Node));
    if(pNode==NULL){
        error |= ERR_LMALLOC;
        exit(error);
    }
    // Fill node data
    pNode->pData = pData;
    pNode->pPrev = NULL; 
    pNode->pNext = NULL; 
    // Return the newly created node
    return pNode;
}

// This function will free the data pointer if requested.
void freeNode(Node* pNode, int freeData){
    int error = ERR_FREE_NODE;
    // Check parameters
    if(pNode==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;        
        exit(error);
    }
    if(pNode->pData==NULL){
        error |= ERR_LNULL;
        exit(error);
    }    
    // Free data memory area
    if(freeData != 0){
        free(pNode->pData);
    }
    // erase current Node structure
    pNode->pData = NULL;
    pNode->pPrev = NULL;
    pNode->pNext = NULL;
    // Free node memory area
    free(pNode);
}

// This function will free all the list memory area
Node* emptyList(Node* pHead, int freeData){
    while(pHead != NULL){
        Node* pNext = pHead->pNext;
        freeNode(pHead, freeData);
        pHead = pNext;    
    }
    return NULL;
}

int getListSize(Node* pHead){
    // Variables
    int count = 0;
    // If head is NULL, size already equals to 0, else we browse the full list
    while(pHead != NULL){
        pHead = pHead->pNext;
        count++;
    }
    // Return number of nodes
    return count;
}

// display the list (debug)
void displayList(Node* pHead, displayCallback dispCB){
    // Variables
    Node* pNode = pHead;
    int i = 0;
    // Display list
    printf("-----------------\n");
    printf("SIZE = %d \n", getListSize(pNode));
    while(pNode != NULL){
        printf("[Node %3d]\n    ", i);
        printf("node=%p / ", pNode);
        printf("prev=%p / ", pNode->pPrev);
        printf("next=%p \n    ", pNode->pNext);
        printf("data=%p ", pNode->pData);
        if(dispCB != NULL){
            dispCB(pNode);
        }
        printf("\n");
        pNode = pNode->pNext;
        i++;
    }
    printf("-----------------\n\n");
}

// Add node at the beginning of the list
Node* insertNodeHead(Node* pHead, Node* pNode){
    // Variables
    int error = ERR_INSERT_NODE_HEAD;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pNode==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // Create link between node and head
    if(pHead != NULL){
        pNode->pNext = pHead;
        pHead->pPrev = pNode;
    }
    // Return the new head of the list
    return pNode;
}

// Add data at the beginning
Node* insertDataHead(Node* pHead, void* pData){
    // Variables
    int error  = ERR_INSERT_DATA_HEAD;
    Node* pNode = NULL;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pData==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // Create node from data pointer
    pNode = createNode(pData);
    if(pNode==NULL){
        error |= ERR_LNULL;
        exit(error);
    }
    // Insert node in the list
    return insertNodeHead(pHead, pNode);    
}

// Add node at the end of the list
Node* insertNodeTail(Node* pHead, Node* pNode){
    // Variables
    int error = ERR_INSERT_NODE_TAIL;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pNode==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // if the list is empty
    if(pHead==NULL){
        pHead = pNode;
    }
    else{
        // Search for the last node
        Node* pLast = pHead;
        while(pLast->pNext != NULL){    
            pLast = pLast->pNext;
        }
        // We have found the last node
        // Create link between node and head
        pLast->pNext = pNode;
        pNode->pPrev = pLast;
    }
    // Return the head of the list (may have been updated)
    return pHead;
}

// Add data at the end of the list
Node* insertDataTail(Node* pHead, void* pData){
    // Variables
    int error  = ERR_INSERT_DATA_TAIL;
    Node* pNode = NULL;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pData==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // Create node from data pointer
    pNode = createNode(pData);
    if(pNode==NULL){
        error |= ERR_LNULL;
        exit(error);
    }
    // Insert node in the list
    return insertNodeTail(pHead, pNode);    
}

// Get Node from the list
Node* getNodeAt(Node* pHead, int index){
    // Variables
    int   error = ERR_GET_NODE_AT;
    Node* pOut  = NULL;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pHead==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // Start to browse the list and stop at the end or at requested index
    while(pHead != NULL && index >= 0){
        if(index == 0){
            pOut = pHead;
        }
        pHead = pHead->pNext;
        index--;
    }
    // If pOut is still NULL, we have not found the node
    if(pOut==NULL){
        error |= ERR_LINDEX;
        exit(error);
    }   
    // Return result
    return pOut;
}

// Get data from the list
void* getDataAt(Node* pHead, int index){
    // Variables
    int   error = ERR_GET_DATA_AT;
    Node* pNode = NULL;
    void* pOut  = NULL;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pHead==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    pNode = getNodeAt(pHead, index);
    if(pNode==NULL){
        error |= ERR_LNULL;
        exit(error);
    }
    // Return data from this node
    return pNode->pData;
}

// Insert Node at index
// the previous node at this index becomes
// the next of the new node
Node* insertNodeAt(Node* pHead, Node* pNode, int index){
    // Variables
    int   error    = ERR_INSERT_NODE_AT;
    int   inserted = 0;
    Node* pInsert  = pHead;
    Node* pOut     = NULL;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pNode==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // Start to browse the list and stop at the requested index
    while(pInsert != NULL && index >= 0){
        if(index == 0){
            // Insert here between (pInsert->pPrev) and (pInsert)
            pNode->pNext = pInsert;
            pNode->pPrev = pInsert->pPrev;
            pInsert->pPrev = pNode;
            if(pNode->pPrev != NULL){
                // If there is a previous node
                pNode->pPrev->pNext = pNode;
                pOut = pHead;    
            }
            else{
                // if no previous node, pNode is the new head
                pOut = pNode;
            }
        }
        pInsert = pInsert->pNext;
        index--;
    }
    // If insertion has failed
    if(pOut==NULL){
        error |= ERR_LINDEX;
        exit(error);
    }   
    // Return result
    return pOut;
}

// Insert data @ index
Node* insertDataAt(Node* pHead, void* pData, int index){
    // Variables
    int   error    = ERR_INSERT_DATA_AT;
    int   inserted = 0;
    Node* pInsert  = pHead;
    Node* pNode    = NULL;
    // Check parameters (pHead can be NULL if the list is empty)
    if(pData==NULL){
        error |= ERR_LNULL;
        error |= ERR_LPARAM;
        exit(error);
    }
    // Create node from data pointer
    pNode = createNode(pData);
    if(pNode==NULL){
        error |= ERR_LNULL;
        exit(error);
    }
    // Insert node
    return insertNodeAt(pHead, pNode, index);
}

// Remove head (return new head, and double pointer for removed element)
Node* removeNodeHead(Node* pHead, Node** ppNode){
    // Variables
    Node* pNode = NULL;
    // pHead can be NULL if the list is empty
    // ppNode can be NULL if we don't want to retrieve the removed node
    
    // If the list is not empty    
    if(pHead != NULL){
        // Store old head
        pNode = pHead;
        // New head is the next node
        pHead = pHead->pNext;
        // If the new head is a node...
        if(pHead!=NULL){
            // ...Remove previous link
            pHead->pPrev = NULL;
        }
        // Remove next link for the old head
        pNode->pNext = NULL;
    }
    // output parameter : removed node address (if requested)
    if(ppNode != NULL){
        *ppNode = pNode;
    }
    // Return the new head of the list
    return pHead;
}

// Remove tail (return new head, and double pointer for removed element)
Node* removeNodeTail(Node* pHead, Node** ppNode){
    // Variables
    Node* pNode = NULL;
    Node* pLast = pHead;
    // pHead can be NULL if the list is empty
    // ppNode can be NULL if we don't want to retrieve the removed node
    
    // Browse all nodes
    while(pLast!=NULL){
        // We have reached the last node (the one to be removed)
        if(pLast->pNext == NULL){
            // This node is the current head
            if(pLast->pPrev == NULL){
                pHead = NULL;
            }
            else{
                // Remove link with previous nodes
                pLast->pPrev->pNext = NULL;
                pLast->pPrev        = NULL;         
            }
            // Store address of the noe to be removed
            pNode = pLast;
        }        
        // Go to next node
        pLast = pLast->pNext;
    }
    // output parameter : removed node address (if requested)
    if(ppNode != NULL){
        *ppNode = pNode;
    }   
    // return head
    return pHead;
}

// Remove tail (return new head, and double pointer for removed element)
Node* removeNodeAt(Node* pHead, Node** ppNode, int index){
    // Variables
    Node* pInsert = pHead;
    Node* pOut    = NULL;
    int   error   = ERR_REMOVE_NODE_AT;
    // pHead can be NULL if the list is empty
    // ppNode can be NULL if we don't want to retrieve the removed node

    // Start to browse the list and stop at the requested index
    while(pInsert != NULL && index >= 0){
        if(index == 0){
            // Forget link (next)
            if(pInsert->pNext != NULL){
                pInsert->pNext->pPrev = pInsert->pPrev;
            }
            // Forget link (previous)
            if(pInsert->pPrev != NULL){
                pInsert->pPrev->pNext = pInsert->pNext;
                // head remains unchanged
                pOut = pHead;
            }
            else{
                // New head is the second node (may be NULL)
                pOut = pInsert->pNext;
            }
            pInsert->pNext = NULL;
            pInsert->pPrev = NULL;
        }
        // Go to next node
        pInsert = pInsert->pNext;
        index--;
    }
    // If insertion has failed
    if(pOut==NULL){
        error |= ERR_LINDEX;
        exit(error);
    }   
    // Return result
    return pOut;
}

