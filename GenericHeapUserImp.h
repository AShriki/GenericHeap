#ifndef _GENHEAPUSR_
#define _GENHEAPUSR_

/* - - - USER DEFINED FIELDS - - - */

/* The user must change and/or implement some of these options to suit their application.
	Firstly, decide if the application calls for a statically or dynamically allocated heap (and modify HEAPTYPE and MAXNODE accordingly).
	Secondly, The user MUST implement struct HeapNode, nodeCompare and nodeInit.
	Lastly, to use this heap, it must be initialized using initHeap(struct Heap)
*/

// only applicable to static heap
#define BULKHEAPSIZE0 8
#define BULKHEAPSIZE1 16
#define BULKHEAPSIZE2 32
#define BULKHEAPSIZE3 64
#define BULKHEAPSIZE4 128
#define BULKHEAPSIZE5 256

// please fill struct HeapNode{}; with your required fields
struct HeapNode {
	int a;
};

/*
	@description 			: returns a priority comparison of two nodes

	@var a (struct HeapNode): a pointer to a heapNode
	@var b (struct HeapNode): a pointer to a heapNode
	@return      			: 1 if a is higher up in the heap than b, 0 if a is in a lower position than b and -1 otherwise
*/
int compareHeapNodes(struct HeapNode, struct HeapNode);
/*
	@description 			: initializes the fields of a node.

	@var a (struct HeapNode): a pointer to a struct HeapNode
	@return      			: 1 if sucessful and 0 if not;
*/
int initHeapNode(struct HeapNode*); // The User must implement this method.

/* - - - END USER DEFINED FIELDS - - - */

#endif // !_GENHEAPUSR_
