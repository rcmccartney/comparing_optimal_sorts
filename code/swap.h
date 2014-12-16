/*
 * swap.h
 *
 *  Created on: Feb 25, 2014
 *      Author: rm7536
 */

#ifndef SWAP_H_
#define SWAP_H_

/* Name: swap()
 * Description:	Swaps two elements in place in an array
 * Arguments: T *array: array element passed in by pointer.
 *            T *other - other array element with which to swap
 * Modifies: None.
 * Returns: None.
 * Pre: None.
 * Post: Two elements are swapped within the array
 * Exceptions: None.
 */
template<typename T>
void swap(T *array, T *other) {
	T tempElement(*array);
	*array = *other;
	*other = tempElement;
}

#endif /* SWAP_H_ */
