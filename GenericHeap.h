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

typedef enum { Static = 0, Dynamic = 1 } HeapType;

struct Heap {
	struct HeapNode* heapArray;
	int numItems;
	int maxNodes;
	HeapType type;
};

struct BulkHeap {
	struct HeapNode* bulk;
	int spaceHolder;
	int maxNodes;
	unsigned int bulkSet;
};
struct BulkHeap* getBulkHeap(int);
int initializeStaticHeap(struct Heap* , struct BulkHeap* , int );
int initializeDynamicHeap(struct Heap* , int);

const struct HeapNode* peekHeap(struct Heap);
int addToHeap(struct Heap*, struct HeapNode);
struct HeapNode popHeap(struct Heap*);
int removeFromHeap(struct Heap*, struct HeapNode);


#endif
