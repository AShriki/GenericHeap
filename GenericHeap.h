#ifndef _GENHEAP_
#define _GENHEAP_

#include "GenericHeapUserImp.h"

/*
Library Usage:
1. Implement/modify the methods and fields in the - USER DEFINED FIELDS - section
2. For static heaps, create a BulkHeap via getBulkHeap(int) followed by a call to initializeStaticHeap 
3. Multiple static heaps are permitted as long as bulkHeap has the space for them
4. For a dynamic heap just create the heap struct followed by a call to initializeDynamicHeap
*/

typedef enum { Static_Heap = 0, Dynamic_Heap = 1 } HeapMemoryType;

struct Heap {
	struct HeapNode* heapArray;
	int numItems;
	int maxNodes;
	HeapMemoryType type;
};

struct BulkHeap {
	struct HeapNode* bulk;
	int spaceHolder;
	int maxNodes;
	unsigned int bulkSet;
};
struct BulkHeap* getBulkHeap(int);
int initializeHeap(struct Heap* , struct BulkHeap* , HeapMemoryType , int );

const struct HeapNode* peekHeap(struct Heap);
int addToHeap(struct Heap* , struct HeapNode);
struct HeapNode popHeap(struct Heap*);
int removeFromHeap(struct Heap* , struct HeapNode);


#endif
