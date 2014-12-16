comparing_optimal_sorts
=======================

c++ project to compare actual runtimes of optimal sorts on various forms 
of input data

For the modification to quicksort, I used Introspective Sorting which is 
described here:

D. R. Musser. Introspective sorting and selection algorithms. Software: 
Practice and Experience (Wiley), 27(8):983-993,1997.

project1.cpp reads a file and sorts it using each of the 4 sorting algorithms.  
The file can contain INT, STRING, LONG, DOUBLE or CHAR.

Instead of running the cpp code directly, project1.cpp can be compiled into 
an executable and then algo_project1.py used to run the sorting iteratively
on different input types. The python program creates the actual datasets 
before calling the cpp sort.It makes distributions that are random, Poisson, 
quarter-sorted, and fully sorted before being passed to the cpp executable.

For each of the four types of distributions, it will make a dataset of size
1000, 10000, 50000, 500000, and 1000000.  On each of the 20 datasets each 
of the four sorting algorithms are run 10 times in order to get an average.

