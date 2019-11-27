#include <stdio.h>
#include "GenericHeap.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int verifyHeapProperty(struct Heap,int);

int main(int argc, char** argv) {
	// test static heap

	int i;
	srand((unsigned int)time(NULL));
	printf("\ntest 1: full random static heap\n");
	struct BulkHeap* b = getBulkHeap(5);
	struct Heap h1;
	if (initializeHeap(&h1, b, Static_Heap,15)) {

		// test : add max rand nodes
		for (i = 0; i < h1.maxNodes; i++) {
			struct HeapNode n;
			n.a = rand() % h1.maxNodes + 1;

			addToHeap(&h1, n);
		}

		if (!verifyHeapProperty(h1,0))
			printf("Heap Property check failed\n");
		else
			printf("Heap Property check succeeded\n");
	}
	// oversize heap should fail
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	printf("\ntest 2: Static array too large to be allocated\n");
	struct Heap h2;
	if (initializeHeap(&h2, b, Static_Heap, 241)) {

		// test : 
		for (i = 0; i < h2.maxNodes; i++) {
			struct HeapNode n;
			n.a = rand() % 15 + 1;

			addToHeap(&h2, n);
		}

		if (!verifyHeapProperty(h2,0))
			printf("Heap Property check failed\n");
		else
			printf("Heap Property check succeeded\n");
	}
	else
		printf("BulkHeap not large enough\n");
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	printf("\ntest 3: Create Large Static Array 239 elements\n");
	struct Heap h3;
	if (initializeHeap(&h3, b, Static_Heap, 239)) {

		// test : add max rand nodes
		for (i = 0; i < h3.maxNodes; i++) {
			struct HeapNode n;
			n.a = rand() % h3.maxNodes + 1;
			addToHeap(&h3, n);
		}

		if (!verifyHeapProperty(h3,1))
			printf("Heap Property check failed\n");
		else
			printf("Heap Property check succeeded\n");
	}
	else
		printf("BulkHeap not large enough\n");
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	printf("\ntest 4: clear lists\n");
	
	for (i = 0; i < h1.maxNodes; i++) {
		popHeap(&h1);
	}
	for (i = 0; i < h3.maxNodes; i++) {
		popHeap(&h3);
	}

	if (h1.numItems != 0)
		printf("h1 list clear failed\n");
	else
		printf("h1 list clear succeeded\n");
	if (h3.numItems != 0)
		printf("h3 list clear failed\n");
	else
		printf("h3 list clear succeeded\n");
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	printf("\ntest 5: dynamic stack adding nodes\n");

	struct Heap h4;
	if (!initializeHeap(&h4, NULL, Dynamic_Heap, 4))
		printf("Failed to initialize dynamic memory for heap h4\n");
	else {

		// test : add max rand nodes
		for (i = 0; i < 5000; i++) {
			struct HeapNode n;
			n.a = rand() % 1000 + 1;

			if (!addToHeap(&h4, n)) {
				printf("Dynamic allocation failed : heap h4");
			}
		}

		if (!verifyHeapProperty(h4, 1))
			printf("\nHeap Property check failed\n");
		else
			printf("\nHeap Property check succeeded\n");
	}
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - 

	printf("\ntest 6: dynamic stack clear list and pop check\n");
	// test : add max rand nodes
	int prev;
	for (i = 0; i < h4.maxNodes; i++) {
		int tmp = popHeap(&h4).a;
		printf("%d ", tmp);
		prev = tmp;
		if (prev > tmp) {
			printf("\nTest Failed on %d, popped element out of order\n",i);
			break;
		}
	}

	if (!verifyHeapProperty(h4, 1))
		printf("\nHeap clear failed\n");
	else
		printf("\nHeap clear succeeded\n");

	printf("\ntest 7: dynamic/static selective node remove\n");
	
	for (i = 0; i < 5000; i++) {
		struct HeapNode n;
		n.a = rand() % 1000 + 1;

		if (!addToHeap(&h4, n)) {
			printf("Dynamic allocation failed : heap h4");
		}
	}

	if (!verifyHeapProperty(h4, 1))
		printf("\nHeap Property check failed\n");
	else
		printf("\nHeap Property check succeeded\n");

	printf("Removing: ");
	for (i = 200; i < 300; i++) {
		removeFromHeap(&h4,h4.heapArray[i]);
		printf("%d ", h4.heapArray[i].a);
	}

	if (!verifyHeapProperty(h4, 1))
		printf("\nHeap Property check failed\n");
	else
		printf("\nHeap Property check succeeded\n");
	printf("\nFollowing list should be sorted: ");
	for (i = 0; i < h4.numItems; i++) {
		int tmp = popHeap(&h4).a;
		printf("%d ", tmp);
		prev = tmp;
		if (prev > tmp) {
			printf("\nTest Failed on %d, popped element out of order\n", i);
			break;
		}
	}

	if (!verifyHeapProperty(h4, 1))
		printf("\nHeap property invalid\n");
	else
		printf("\nHeap verified\n");

	return 0;
}

int verifyHeapProperty(struct Heap h, int mute) {
	int i,result = 1;
	for (i = 1; 2 * i <= h.numItems; i++) {
		if(!mute)
			printf("Parent: %d ",h.heapArray[i].a);

		if (!compareHeapNodes(h.heapArray[i], h.heapArray[2 * i])) {
			result = 0;
		}
		if (2 * i + 1 <= h.numItems && !compareHeapNodes(h.heapArray[i], h.heapArray[2 * i + 1])) {
			result = 0;
		}

		if (2 * i <= h.numItems && !mute) {
			printf("Left Child: %d ", h.heapArray[2 * i].a);
		}
		if (2 * i + 1 <= h.numItems && !mute) {
			printf("Right Child: %d\n", h.heapArray[2 * i + 1].a);
		}

	}
	return result;
}