//============================================================================
// Name        : quicksort.h
// Author      : rm7536
// Description : Sorts a generic array using quicksort algorithm.
// Version     : $Id$
// Revision    : $Log$
//============================================================================

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <stdlib.h>     /* srand, rand */
#include "swap.h"
#include <iostream>
using namespace std;

/* Name: partition()
 * Description:	In-place swapping of values to get them into two buckets,
 * 				one that is <= pivot and one that is > pivot
 * Arguments: T *array: generic array passed in by pointer.
 *            long left - the starting point in this array to partition on the pivot
 *            long right - the ending point into the array, inclusive
 *            pivotIndex - the index of the pivot being used
 * Modifies: position of each element in array into left and right buckets
 * Returns: None.
 * Pre: None.
 * Post: The number of elements in array are now split into two buckets around the pivot
 * Exceptions: None.
 */
template<typename T>
long partition(T *array, long &left, long &right, long &pivotIndex, long* comparisons) {

	T pivot( array[pivotIndex] );
	//move the pivot to the end
	swap( array + pivotIndex, array + right );
	long bucketEnd(left);
	//Go through array moving smaller elements to the left bucket
	//and increase where the left bucket ends
	for(int i = left; i < right; i++) {
		(*comparisons)++;
		if (array[i] <= pivot) {
			swap( array + i, array + bucketEnd );
			bucketEnd++;
		}
	}
	//move the pivot back to the divider between left and right
	swap( array + right, array + bucketEnd );
	return bucketEnd;
}

/* Name: quickSort()
 * Description:	sorts array through quicksort algorithm.
 * Arguments: T *array: generic array passed in by pointer.
 *            long left - left side of the array on this recursive call
 *            long right - right side of the array on this recursive call
 * Modifies: position of each element in array
 * Returns: None.
 * Pre: None.
 * Post: The number of elements in array are now sorted in ascending order
 * Exceptions: None.
 */
template<typename T>
void quickSort(T *array, long left, long right, long* comparisons, long* partitionCount) {
	//keep track of the number of recursive calls you've made
	(*partitionCount)++;
	//base case is when left and right are equal, there is no list to sort & the function returns
	//Here we are not at the base yet
	if (right > left) {
		long pivot( ( rand() % (right - left + 1) ) + left );
		long newPosition( partition(array, left, right, pivot, comparisons) );
		quickSort(array, left, newPosition-1, comparisons, partitionCount);
		quickSort(array, newPosition+1, right, comparisons, partitionCount);
	}
}

#endif /* QUICKSORT_H_ */
