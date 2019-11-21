#include "GenericHeap.h"

#include <stdlib.h>
/*
	Created by Avshalom Shriki
	E-mail: Av.shriki@gmail.com

	This file implements an array based 2-heap which is sorted based on a user implemented nodeCompare on a user implemented structure "HeapNode"
	
	See the .h file on how to use this project.
*/

int reduceHeapMemory(struct Heap* , int);
int increaseHeapMemory(struct Heap* , int);

/*
	@description		: Generates the bulk memory from which which we "allocate" pointers to smaller heaps for statically allocated heaps.
						  As a note, this method can only be called once, all subsequent calls will be ignored

	@var bulkheapsize   : A number choosing from the number of elements displayed by #define BULKHEAPSIZE(0-5) in GenericHeapUsrImp.h 
	@return				: A datastructure containing the array if allocation was successful and NULL if not
*/
struct BulkHeap* getBulkHeap(int bulkheapsize) {
	static struct BulkHeap bulkHeap = { .spaceHolder = 0,.bulkSet = 0 };
	 
	if (!bulkHeap.bulkSet) {
		switch (bulkheapsize) {
			case 0: {	
				int i;
				static struct HeapNode bulkSpace[BULKHEAPSIZE0];
				for (i = 0; i <= BULKHEAPSIZE0; i++)
					initHeapNode(&bulkSpace[i]);
				bulkHeap.bulk = &bulkSpace;
				bulkHeap.maxNodes = BULKHEAPSIZE0;
				bulkHeap.spaceHolder = 0;
				break; 
			}
			case 1: {
				int i;
				static struct HeapNode bulkSpace[BULKHEAPSIZE1];
				for (i = 0; i <= BULKHEAPSIZE1; i++)
					initHeapNode(&bulkSpace[i]);
				bulkHeap.bulk = &bulkSpace;
				bulkHeap.maxNodes = BULKHEAPSIZE1;
				bulkHeap.spaceHolder = 0;
				break;
			}
			case 2: {
				int i;
				static struct HeapNode bulkSpace[BULKHEAPSIZE2];
				for (i = 0; i <= BULKHEAPSIZE2; i++)
					initHeapNode(&bulkSpace[i]);
				bulkHeap.bulk = &bulkSpace;
				bulkHeap.maxNodes = BULKHEAPSIZE2;
				bulkHeap.spaceHolder = 0;
				break;
			}
			case 3: {
				int i;
				static struct HeapNode bulkSpace[BULKHEAPSIZE3];
				for (i = 0; i <= BULKHEAPSIZE3; i++)
					initHeapNode(&bulkSpace[i]);
				bulkHeap.bulk = &bulkSpace;
				bulkHeap.maxNodes = BULKHEAPSIZE3;
				bulkHeap.spaceHolder = 0;
				break;
			}
			case 4: {
				int i;
				static struct HeapNode bulkSpace[BULKHEAPSIZE4];
				for (i = 0; i <= BULKHEAPSIZE4; i++)
					initHeapNode(&bulkSpace[i]);
				bulkHeap.bulk = &bulkSpace;
				bulkHeap.maxNodes = BULKHEAPSIZE4;
				bulkHeap.spaceHolder = 0;
				break;
			}
			case 5: {
				int i;
				static struct HeapNode bulkSpace[BULKHEAPSIZE5];
				for (i = 0; i <= BULKHEAPSIZE5; i++)
					initHeapNode(&bulkSpace[i]);
				bulkHeap.bulk = &bulkSpace;
				bulkHeap.maxNodes = BULKHEAPSIZE5;
				bulkHeap.spaceHolder = 0;
				break;
			}
			default: {
				int i;
				static struct HeapNode bulkSpace[BULKHEAPSIZE5];
				for (i = 0; i <= BULKHEAPSIZE5; i++)
					initHeapNode(&bulkSpace[i]);
				bulkHeap.bulk = &bulkSpace;
				bulkHeap.maxNodes = BULKHEAPSIZE5;
				bulkHeap.spaceHolder = 0;
				break;
			}
		}
		bulkHeap.bulkSet = 1;
		return &bulkHeap;
	}
	return NULL;
}

/*
	@description : Generates the heap using a statically declared arrayy

	@var h       : a pointer to an unallocated, uninitialized heap
	@var b		 : The BulkHeap to use for array elements
	@var n       : For static heap, n is the number of elements to "allocate" to this heap
	@return      : 1 if allocation was successful, 0 if not
*/

int initializeStaticHeap(struct Heap* h, struct BulkHeap* b, int n) {
	h->numItems = 0;
	h->maxNodes = n;

	if (b->maxNodes < b->spaceHolder + n + 1 || !b->bulkSet)
		return 0;

	h->heapArray = &b->bulk[b->spaceHolder];

	b->spaceHolder += n + 1;

	h->maxNodes = n;
	h->numItems = 0;
	h->type = Static;

	return 1;
}

/*
	@description : Generates the heap dynamically using malloc

	@var h       : a pointer to an unallocated heap
	@var n       : For dynamic heap, n is the number of elements to initialize this heap
	@return      : 1 if allocation was successful, 0 if not
*/

int initializeDynamicHeap(struct Heap* h, int n) {
	h->maxNodes = n;
	h->numItems = 0;
	h->type = Dynamic;
	h->heapArray = malloc(sizeof(struct HeapNode) * ( n + 1) );
	if (h->heapArray == NULL)
		return 0;
	int i;
	for (i = 0; i < n + 1; i++) {
		initHeapNode(&h->heapArray[i]);
	}
	return 1;
}

/*
	@description : Swaps two indecies in a heap

	@var h       : a pointer to a heap
	@var m       : position to swap
	@var n       : position to swap
	@return      : nothing
*/
void swap(struct Heap* h, int m, int n) {// swap m and n
	struct HeapNode tmp;
	tmp = h->heapArray[m];
	h->heapArray[m] = h->heapArray[n];
	h->heapArray[n] = tmp;
}
/*
	@description : Returns the node of highest/lowest priority without removing it

	@var h       : a pointer to a heap
	@return      : a HeapNode of highest/lowest priority
*/

const struct HeapNode* peekHeap(struct Heap h) {
	if(h.numItems > 0)
		return &h.heapArray[1];
	return 0;
}
/*
	@description : adds a HeapNode to the heap

	@var h       : a pointer to a heap
	@var n       : node to be inserted
	@return      : 0 on failure to add or allocate memory 1 on success
*/
int addToHeap(struct Heap* h, struct HeapNode n) {
	if (h->numItems == h->maxNodes) {
		if(!h->type)
			return 0;
		if (!increaseHeapMemory(h,2))
			return 0;
	}
	
	int index = ++h->numItems ;
	h->heapArray[index] = n;
	// perc down
	if (h->numItems - 1) {
		for (; compareHeapNodes(h->heapArray[index], h->heapArray[index / 2]) == 1 && index > 1; index /= 2) {
			swap(h, index, index / 2);
		}
	}
	return 1;
}
/*
	@description : Removes the highest/lowest priority node

	@var h       : a pointer to a heap
	@return      : the HeapNode of highest/lowest priority
*/
struct HeapNode popHeap(struct Heap* h) {
	if (!h->numItems) {
		struct HeapNode n;
		initHeapNode(&n);
		return n;
	}
	struct HeapNode n = h->heapArray[1];
	h->heapArray[1] = h->heapArray[h->numItems--];
	int i = 1,c = 0;
	// perc up
	while (2*i + 1 <= h->numItems) {

		c = compareHeapNodes(h->heapArray[i * 2], h->heapArray[i * 2 + 1]) == 1 ? i * 2 : i * 2 + 1;

		if (compareHeapNodes(h->heapArray[c], h->heapArray[i]) == 1) {
			swap(h, i, c);
			i = c;
		}
		else
			break;
	}
	// reduce the heap by half if we're using only a third of the array elements
	if (h->type && h->maxNodes > 4 && h->numItems < h->maxNodes / 3) {
		if (!reduceHeapMemory(h, 2))
			return h->heapArray[0];
	}

	return n;
}
/*
	@description : Searches the heap and removes a node

	@var h       : a pointer to a heap
	@var n       : node to be removed
	@return      : 1 on success, 0 if the node is not present, -1 if the list is empty and -2 if memory allocation failed
*/
int removeFromHeap(struct Heap* h, struct HeapNode n) {
	if (!h->numItems)
		return -1;
	int found = 0;
	int i = 1;

	for (; i <= h->numItems; i++) {
		if (compareHeapNodes(h->heapArray[i], n) == -1) {
			found = 1;
			break;
		}
	}

	if (!found)
		return 0;

	h->heapArray[i] = h->heapArray[h->numItems--];
	int c = 0;
	// perc up
	while (2 * i + 1 <= h->numItems) {

		c = compareHeapNodes(h->heapArray[i * 2], h->heapArray[i * 2 + 1]) == 1 ? i * 2 : i * 2 + 1;

		if (compareHeapNodes(h->heapArray[c], h->heapArray[i]) == 1) {
			swap(h, i, c);
			i = c;
		}
		else
			break;
	}

	// reduce the heap by half if we're using only a third of the array elements
	if (!h->type && h->maxNodes > 4 && h->numItems < h->maxNodes / 3) {
		if (!reduceHeapMemory(h, 2))
			return -2;
	}

	return found;
}
/*
	@description : reduces the heap memory

	@var h       : a pointer to a heap
	@var f       : memory reduction factor
	@return      : 1 on success, 0 if memory reallocation failed
*/
int reduceHeapMemory(struct Heap* h , int f) {
	if (f == 0 || h->maxNodes <= 4)
		return 0;
	void* tmp;
	tmp = realloc(h->heapArray, sizeof(struct HeapNode) * h->maxNodes / f);
	if (tmp == NULL)
		return 0;

	h->heapArray = tmp;
	h->maxNodes /= 2;
	return 1;
}
/*
	@description : Increases the heap memory

	@var h       : a pointer to a heap
	@var f       : memory increase factor
	@return      : 1 on success, 0 if memory reallocation failed
*/
int increaseHeapMemory(struct Heap* h, int f) {
	if (f == 0)
		return 0;
	void* tmp;
	tmp = realloc(h->heapArray, sizeof(struct HeapNode) * h->maxNodes * f);
	if (tmp == NULL)
		return 0;

	h->heapArray = tmp;
	h->maxNodes *= 2;

	int i;
	for (i = h->maxNodes; i < h->maxNodes; i++) {
		initHeapNode(&h->heapArray[i]);
	}

	return 1;
}
