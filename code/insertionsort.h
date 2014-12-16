//============================================================================
// Name        : insertionsort.h
// Author      : rm7536 
// Description : Sorts a generic array using insertion sort algorithm.
// Version     : $Id$
// Revision    : $Log$
//============================================================================

#ifndef INSERTSORT_H_
#define INSERTSORT_H_

/* Name: insertSort()
 * Description:	sorts array through insertion sort algorithm.
 * Arguments: T *array: generic array passed in by pointer.
 *            long size - size of the array
 * Modifies: position of each element in array
 * Returns: None.
 * Pre: None.
 * Post: The number of elements in array are now sorted in ascending order
 * Exceptions: None.
 */
template<typename T>
void insertSort(T *array, long size, long *comparisons) {

	long j;
	T temp;
	//skip the first element it has nothing to compare to
	for(long i = 1; i < size; i++) {
		temp = array[i];
		j = i;
		(*comparisons)++;
		while(j > 0 && array[j-1] > temp) {
			(*comparisons)++;
			array[j] = array[j-1];
			--j;
		}
		array[j] = temp;
	}
}

#endif /* INSERTSORT_H_ */

