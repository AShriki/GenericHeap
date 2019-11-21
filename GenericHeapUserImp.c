#include "GenericHeapUserImp.h"
/*
	@description 			: returns a priority comparison of two nodes

	@var a (struct HeapNode): a pointer to a heapNode
	@var b (struct HeapNode): a pointer to a heapNode
	@return      			: 1 if a is higher up in the heap than b, 0 if a is in a lower position than b and -1 otherwise
*/
int compareHeapNodes(struct HeapNode a, struct HeapNode b) {
	if (a.a > b.a)
		return 1;
	else if (a.a < b.a)
		return 0;
	else
		return -1;
}
/*
	@description 			: initializes the fields of a node.

	@var a (struct HeapNode): a pointer to a struct HeapNode
	@return      			: 1 if sucessful and 0 if not;
*/
int initHeapNode(struct HeapNode* n) {
	n->a = -10101010;
	return 1;
}