//============================================================================
// Name        : project1.cpp
// Author      : rm7536 
// Description : Uses sorting algorithms and generic templates to read in data
//               sort it and compare running times
// Version     : $Id$
// Revision    : $Log$
//============================================================================

#include "mergesort.h"
#include "quicksort.h"
#include "heapsort.h"
#include "my_choice_qsort.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <sstream>
#include <math.h>		/* log2 */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
using namespace std;

/* Name: printIt()
 * Description:	Prints a generic array, 50 items per line.
 * Arguments: Filename of the file to be used
 * Modifies: None.
 * Returns: None.
 * Pre: None.
 * Post: None.
 * Exceptions: None.
 */
template<typename T>
void printIt(T *array, long count) {
	for(int i = 0; i < count; i++) {
		cout << array[i];
		if (i != count-1) {
			cout << ", ";
		}
		else {
			cout << ".";
		}
	}
	cout << endl;
}

/* Name: tokenizer()
 * Description:	Fills the array passed to it by pointer.
 * Arguments: tokens - tokens: array of generic type.
 * 					   filename: filename to tokenize.
 *            	 	   count: - how many entries the array contains
 * Modifies: tokens array through pass by reference
 * Returns: None.
 * Pre: None.
 * Post: tokens is filled with entries from the file.
 * Exceptions: None.
 */
template<typename T>
void tokenizer(T* tokens, char* filename, long &count) {

	ifstream file(filename);
	if ( file.is_open() ) {
		cout << "Reading in data file..." << endl;
		int i = 0;
		string line;
		while( i < count ) {
			getline( file, line );
			stringstream ss(line);
			while(ss >> tokens[i]) {
				if (++i == count) {
					break;
				}
			}
		}
		if (i < count) {
			cout << "Warning: file contained less than " << count << " data items."
				 << " Proceeding analysis on " << i << " data items." << endl;
		}
		else {
			cout << "File read in successfully" << endl;
		}
		file.close();
	}
	else {
		cout << "Error: File not open to tokenize." << endl;
		exit(1);
	}
}

/* Name: makeCopy()
 * Description:	Copies one array into another
 * Arguments: tokens - array: array from file
 * 					   copy: array that gets the copy
 *            	 	   count: - how many entries the array contains
 * Modifies: None.
 * Returns: None.
 * Pre: None.
 * Post: Copy contains the same contents as Array
 * Exceptions: None.
 */
template<typename T>
void makeCopy(T* array, T* copy, long count) {
	for(int i =0; i < count; i++) {
		copy[i] = array[i];
	}
}

/* Name: run10times()
 * Description:	Runs each sorting array 10 times on input array & calculates the average time
 * Arguments: tokens - array: array from file
 * 					   copy: array to sort, copied from array before each run
 *            	 	   count: - how many entries the array contains
 * Modifies: sorts the copy array 10 times per algorithm
 * Returns: None.
 * Pre: None.
 * Post: Average running time calculated
 * Exceptions: None.
 */
template<typename T>
void run10times(T* array, T* copy, long count, string distr, string type) {

	string file = "output_" + type + ".txt";
	ofstream output(file.c_str(), ios::app);
	double total = 0;
	//format of each line in the dataset - only print this on first run
	if ( distr == "Ordered" && count == 1000) {
		output << "Dist, Size, MSTime, MSComp, HSTime, HSComp, QSTime, QSComp, QSRec, ISTime, ISComp, ISRec" << endl;
	}
	long *comparisons = new long;
	*comparisons = 0;
	for(int i = 0; i < 10; i++) {
		//read the integers into array, array modified through pass by pointer
		//Have to copy the array to be sorted so that you can run the algorithm
		//10 times on the original unsorted array.  Otherwise it is sorted after the
		//first time.
		makeCopy(array, copy, count);
	    clock_t start = clock();
	    //keep adding up the number of comparisons for all 10 times
	    mergeSort(copy, count, comparisons);
	    clock_t end = clock();
		total += 1000.0 * (end-start) / CLOCKS_PER_SEC;
	}
	total = total / 10;
	(*comparisons) /= 10;
	output << distr << ", " << count << ", " << total << ", " << (*comparisons);
	//print the array if it is small enough, used for testing the sorts worked correctly
	if (count < 101) {
		printIt(copy, count);
	}

	total = 0;
	*comparisons = 0;
	for(int i = 0; i < 10; i++) {
		makeCopy(array, copy, count);
	    clock_t start = clock();
		heapSort(copy, count, comparisons);
	    clock_t end = clock();
	    total += 1000.0 * (end-start) / CLOCKS_PER_SEC;
	}
	total /= 10;
	(*comparisons) /= 10;
	output << ", " << total << ", " << (*comparisons);
	if (count < 101) {
		printIt(copy, count);
	}

	total = 0;
	*comparisons = 0;
	long *partitionCount = new long;
	*partitionCount = 0;
	for(int i = 0; i < 10; i++) {
		makeCopy(array, copy, count);
	    clock_t start = clock();
	    //partitionCount is added up 10 times in a row
		quickSort(copy, 0L, count-1, comparisons, partitionCount);
	    clock_t end = clock();
	    total += 1000.0 * (end-start) / CLOCKS_PER_SEC;
	}
	total /= 10;
	(*comparisons) /= 10;
	(*partitionCount) /= 10;
	output << ", " << total << ", " << (*comparisons) << ", " << (*partitionCount);
	if (count < 101) {
		printIt(copy, count);
	}

	total = 0;
	*comparisons = 0;
	*partitionCount = 0;
	for(int i = 0; i < 10; i++) {
		makeCopy(array, copy, count);
	    clock_t start = clock();
		//use a depth limit of 2*log(n) for the recursion
		introSort(copy, 0L, count-1, 2*log2(count), comparisons, partitionCount );
	    clock_t end = clock();
	    total += 1000.0 * (end-start) / CLOCKS_PER_SEC;
	}
	total /= 10;
	(*comparisons) /= 10;
	(*partitionCount) /= 10;
	output << ", " << total << ", " << (*comparisons) << ", " << (*partitionCount) << endl;
	if (count < 101) {
		printIt(copy, count);
	}
}

/* Name: main()
 * Description:	Reads a file and sorts it using each of the 4 sorting algorithms.  File can contain INT, STRING, LONG, DOUBLE or CHAR.
 * Arguments: Filename of the file to be used.
 * Modifies: None.
 * Returns: None.
 * Pre: None.
 * Post: Prints time taken to sort the file and exits.  If file is small enough it will print the sorted array
 * Exceptions: None.
 */
int main(int argc, char * argv[]) {
  
	if (argc < 5) {
		cout << "Error: Usage is 'project1 Filename Type Size Distribution'" << endl
			 << "Filename = file that holds the generated data" << endl
			 << "TYPE = ['int', 'long', or 'double']" << endl
			 << "Size = the number of data elements in the file" << endl
			 << "and Distribution is a string description" << endl
			 << "Consult the README for more information." << endl;
		return 1;
	}
	try {
		string type(argv[2]);
		long count( atol(argv[3]) );
		/* initialize random seed for quicksort rand() */
		srand (time(NULL));

		if (type == "int") {
			int* array = new int[count];
			int* copy = new int[count];
			//read the values into array, array modified through pass by pointer
			tokenizer(array, argv[1], count );
			run10times(array, copy,  count, argv[4], "int" );
		}
		else if (type == "long") {
			long long* array = new long long[count];
			long long* copy = new long long[count];
			tokenizer(array, argv[1], count );
			run10times(array, copy,  count, argv[4], "long" );
		}
		else if (type == "double") {
			double* array = new double[ count ];
			double* copy = new double[ count ];
			tokenizer(array, argv[1], count );
			run10times(array, copy,  count, argv[4], "double" );
		}
		else {
			cout << "Error: TYPE must be ['int', 'long', or 'double'] and is case-sensitive." << endl;
			return 1;
		}
	}
	catch (exception& e) {
		cout << "Error: Arguments not formatted correctly. Consult README for correct usage." << endl;
		return 1;
	}
}
