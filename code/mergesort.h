//============================================================================
// Name        : mergesort.h
// Author      : rm7536 
// Description : Sorts a generic array using mergesort algorithm.
// Version     : $Id$
// Revision    : $Log$
//============================================================================

#ifndef MERGESORT_H_
#define MERGESORT_H_

/* Name: mergeSort()
 * Description:	sorts array through mergesort algorithm.
 * Arguments: T *array: generic array passed in by pointer.
 *            long size - size of the number of elements in array
 * Modifies: position of each element in array
 * Returns: None.
 * Pre: None.
 * Post: The number of elements in array are now sorted in ascending order
 * Exceptions: None.
 */
template<typename T>
void mergeSort(T *array, long size, long* comparisons) {
	//base case of recursion when nothing to compare
	if (size == 0 || size == 1) {
		return;
	}
	//base case of recursion with two items to compare.  swap them if they are out of order and return
	else if (size == 2) {
		(*comparisons)++;
		if ( *array > *(array+1) ) {
			T tempElement(*array);
			*array = *(array+1);
			*(array+1) = tempElement;
		}
	}
	else {
		long halfLeft = size / 2;
		//not at base case, continue recursion on each half of the array
		mergeSort(array, halfLeft, comparisons);
		mergeSort( (array+halfLeft), (size-halfLeft), comparisons );
		//Now we have two sorted halves, need to merge them int one list by
		//examining the head of each list, taking the smaller one, and continuing
		//j is counter to lower half
		int j = 0;
		//k is counter on upper half
		int k = halfLeft;
		//store the sorted list into temp until the algorithm has finished
		T temp[size];
		for(int i = 0; i < size; i++) {
			(*comparisons)++;
			//Either no more items in lower half or, if the k element is the next smallest.
			//So take an element from upper half, so long as elements remain
			if ( ( j == halfLeft || *(array+j) > *(array+k) ) && k != size) {
				temp[i] = *(array+k);
				k++;
			}
			//Otherwise take from the lower half
			else {
				temp[i] = *(array+j);
				j++;
			}
		}
		//temp is now sorted.  Overwrite the original string array, so that when we go back up
		//the recursive chain this part of the original array is now sorted.
		for(int i = 0; i < size; i++) {
			*(array+i) = temp[i];
		}
	}
}

#endif /* MERGESORT_H_ */

