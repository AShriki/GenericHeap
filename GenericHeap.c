#include "GenericHeap.h"
/*
	Created by Avshalom Shriki
	E-mail: Av.shriki@gmail.com

	This file implements an array based 2-heap which is sorted based on a user implemented nodeCompare on a user implemented structure "HeapNode"
	
	See the .h file to change the type of heap to maxheap
*/

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
struct HeapNode peek(struct Heap h) {
	return h.heapArray[1];
}
/*
	@description : Inserts a HeapNode into the heap using perc up

	@var h       : a pointer to a heap
	@var n       : node to be inserted
	@return      : nothing
*/
void insert(struct Heap* h, struct HeapNode n) {
	if (h->numItems == 16)
		return;
	int index = ++h->numItems ;
	h->heapArray[index] = n;
	// perc down
	if (h->numItems - 1) {
		for (; nodeCompare(h->heapArray[index], h->heapArray[index / 2]) && index > 1; index /= 2) {
			swap(h, index, index / 2);
		}
	}
}
/*
	@description : Removes the highest/lowest priority node

	@var h       : a pointer to a heap
	@return      : the HeapNode of highest/lowest priority
*/
struct HeapNode pop(struct Heap* h) {
	if (!h->numItems)
		return h->heapArray[0];
	struct HeapNode n = h->heapArray[1];
	h->heapArray[1] = h->heapArray[h->numItems--];
	int i = 1,c = 0;
	// perc up
	while (2*i + 1 <= h->numItems) {

		c = nodeCompare(h->heapArray[i * 2], h->heapArray[i * 2 + 1]) == 1 ? i * 2 : i * 2 + 1;

		if (nodeCompare(h->heapArray[c], h->heapArray[i]) == 1) {
			swap(h, i, c);
			i = c;
		}
		else
			break;
	}

	return n;
}
/*
	@description : Searches the heap and removes a node

	@var h       : a pointer to a heap
	@var n       : node to be removed
	@return      : 1 on success, 0 if the node is not present and -1 if the list is empty
*/
int remove(struct Heap* h, struct HeapNode n) {
	if (!h->numItems)
		return -1;
	int found = 0;
	int i = 1;

	for (; i <= h->numItems; i++) {
		if (nodeCompare(h->heapArray[i], n) == -1) {
			found = 1;
			break;
		}
	}
	h->heapArray[i] = h->heapArray[h->numItems--];
	int c = 0;
	// perc up
	while (2 * i + 1 <= h->numItems) {

		c = nodeCompare(h->heapArray[i * 2], h->heapArray[i * 2 + 1]) == 1 ? i * 2 : i * 2 + 1;

		if (nodeCompare(h->heapArray[c], h->heapArray[i]) == 1) {
			swap(h, i, c);
			i = c;
		}
		else
			break;
	}

	return found;
}


