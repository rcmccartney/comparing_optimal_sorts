//============================================================================
// Name        : My_Choice_Qsort.h
// Author      : rm7536
// Description : Sorts a generic array using introsort algorithm. This algorithm is
//				 the same as quicksort but with some optimizations. First, the
//				 pivot is selected as the median of three elements: first, last, and middle.
//				 Second, if the sort is taking a long time then it switches to heapsort
//				 (for instance when an attacker is using denial of service from
// 				 his knowledge of our choice of pivot to construct bad input).  Finally,
//				 if the array is less than size 16, it switches to insertion sort since
//				 even though insertion sort is O(n^2) in the worst case it is a lot
//				 faster in practice since it is in-place and doesn't use recursive calls.
//				 And if the array is size 3 or 2 it uses a an in-place swap.
//				 This is similar to what is used in Microsoft's .NET
//
//				 Invented in 1997 by David Musser
//
// Version     : $Id$
// Revision    : $Log$
//============================================================================

#ifndef MYQUICKSORT_H_
#define MYQUICKSORT_H_

#include "insertionsort.h"
#include "swap.h"
#include "quicksort.h"

/* Name: choosePivot()
 * Description:	Chooses a pivot as the median of three random choices
 * Arguments: T *array: array element passed in by pointer.
 *            long left - the starting point in this array to partition on the pivot
 *            long right - the ending point into the array, inclusive
 * Modifies: Sorts the three choices in the array and returns the median.
 * Returns: Choice of pivot.
 * Pre: None.
 * Post: None.
 * Exceptions: None.
 */
template<typename T>
long choosePivot(T *array, long left, long right, long *comparisons) {

	(*comparisons) += 3;
	long middle = (right - left) / 2 + left;
	if (array[left] > array[middle]) swap(array+left, array+middle);
	if (array[left] > array[right]) swap(array+left, array+right);
	if (array[middle] > array[right]) swap(array+middle, array+right);

	return middle;
}

/* Name: introSort()
 * Description:	sorts array through introsort algorithm.
 * Arguments: T *array: generic array passed in by pointer.
 *            long left - left side of the array on this recursive call
 *            long right - right side of the array on this recursive call
 *            int depthlimit - the number of recursive calls we will do from here
 *            until we switch to heapsort
 * Modifies: position of each element in array
 * Returns: None.
 * Pre: None.
 * Post: The number of elements in array are now sorted in ascending order
 * Exceptions: None.
 */
template<typename T>
void introSort(T *array, long left, long right, int depthlimit, long* comparisons, long* partitionCount) {
	//keep track of the number of recursive calls you've made
	(*partitionCount)++;
	//introsort changes behavior to optimize small array sizes
	long size = right - left + 1;
	if (size <= 16) {
		//base case, you are done
		if (size == 0 || size == 1) {
			return;
		}
		else if (size == 2) {
			(*comparisons)++;
			if (array[left] > array[right]) {
				swap(array+left, array+right);
			}
			return;
		}
		//optimization for three elements here
		else if (size == 3) {
			(*comparisons) += 3;
			if (array[left] > array[left+1]) swap(array+left, array+left+1);
			if (array[left] > array[right]) swap(array+left, array+right);
			if (array[left+1] > array[right]) swap(array+left+1, array+right);
			return;
		}
		//optimization to use in-place insertion sort rather than recursion
		//for size 3 < and <= 16
		else {
			insertSort(array + left, size, comparisons);
			return;
		}
	}
	//here we do regular quicksort unless we have reached the depthlimit and then we use heapsort
	else {
		if (depthlimit == 0) {
			heapSort(array + left, size, comparisons);
			return;
		}
		else {
			--depthlimit;
			long pivot( choosePivot(array, left, right, comparisons) );
			long newPosition( partition(array, left, right, pivot, comparisons) );
			introSort(array, left, newPosition-1, depthlimit, comparisons, partitionCount);
			introSort(array, newPosition+1, right, depthlimit, comparisons, partitionCount);
		}
	}
}

#endif /* MYQUICKSORT_H_ */
