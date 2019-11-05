#ifndef _GENHEAP_
#define _GENHEAP_

/* - - - USER DEFINED FIELDS - - - */

#define MaxNodes 15

// the user must define the struct HeapNode somewhere as follows
/*
	struct HeapNode{
	     stuff goes here
	};
*/

/*  
	@description 			: returns a priority comparison of two nodes

	@var a (struct HeapNode): a pointer to a heap
	@var b (struct HeapNode): position to swap
	@return      			: 1 if a is of a higher priority than b, 0 if a is of a lower priority than b and -1 otherwise

	NOTE: The user must implement this
*/
extern int nodeCompare(struct HeapNode, struct HeapNode); // The User must implement this method to compare nodes. Output should be 1 if HeapNode a higher priority or 0 for no percolate up and -1 if the nodes are the same

/* - - - END USER DEFINED FIELDS - - - */

struct Heap {
	struct HeapNode heapArray[MaxNodes + 1];
	int numItems;
};

struct HeapNode peek(struct Heap);
void insert(struct Heap*, struct HeapNode);
struct HeapNode pop(struct Heap*);
int remove(struct Heap*, struct HeapNode);


#endif
