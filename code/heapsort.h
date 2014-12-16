//============================================================================
// Name        : heapsort.h
// Author      : rm7536
// Description : Sorts a generic array using heapsort algorithm.
// Version     : $Id$
// Revision    : $Log$
//============================================================================

#ifndef HEAPSORT_H_
#define HEAPSORT_H_

#include "swap.h"

/* Name: siftDown()
 * Description:	Sends an element down the heap until it is larger than its children
 * Arguments: T *array: array element passed in by pointer.
 *            long current - the element to sift down
 *            long end - the last element that is considered part of the heap
 * Modifies: Position of current in the heap.
 * Returns: None.
 * Pre: None.
 * Post: Current is in the correct place in the heap in relation to its children
 * Exceptions: None.
 */
template<typename T>
void siftDown(T *array, long current, long end, long* comparisons) {

	//2i is the first child of any node
	//algorithm works for nodes numbered 1..n but the array is numbered 0..n-1
	//index is converted here, but convert back every time we access the array
	//by subtracting 1
	current += 1;
	end += 1;
	while( current*2 <= end ) {
		(*comparisons)++;
		long max = current;
		long child = current*2;
		//max becomes the larger of the parent & left child
		if ( array[current-1] < array[child-1] ) {
			max = child;
		}
		//if parent has a right child max becomes the end of the parent
		//& right child
		//right child here would be array[child+1] except for array index issue discussed above
		if ( (current*2+1) <= end && array[max-1] < array[child] ) {
			max = child+1;
		}
		//one of the children was larger, swap them
		if (max != current) {
			swap(array+(current-1), array+(max-1));
			current = max;
		}
		else {
			return;
		}
	}
}

/* Name: heapify()
 * Description:	Creates a heap out of this array working from the bottom up
 * Arguments: T *array: generic array passed in by pointer.
 *            long size - the size of the array
 * Modifies: position of each element in array to have heap property
 * Returns: None.
 * Pre: None.
 * Post: The elements are now in a heap.
 * Exceptions: None.
 */
template<typename T>
void heapify(T *array, long size, long* comparisons) {

	//index of parent of last leaf node is size/2 - 1
	//start there and work up to the root
	for(long start = (size/2) - 1; start >= 0; start--) {
		siftDown(array, start, size-1, comparisons);
	}
}

/* Name: heapSort()
 * Description:	sorts array through heap algorithm.
 * Arguments: T *array: generic array passed in by pointer.
 *            long size - size of the array
 * Modifies: position of each element in array
 * Returns: None.
 * Pre: None.
 * Post: The number of elements in array are now sorted in ascending order
 * Exceptions: None.
 */
template<typename T>
void heapSort(T *array, long size, long* comparisons) {

	//first make the array into a heap
	heapify(array, size, comparisons);
	//divider is the position in the array that marks the boundary between sorted list and heap.
	//Moves from the end to the beginning of the array at which point we are done
	for(long divider = size - 1; divider > 0; divider--) {
		//put max element at the end
		swap( array, array + divider );
		//restore heap property
		siftDown(array, 0L, divider-1, comparisons);
	}
}

#endif /* HEAPSORT_H_ */
