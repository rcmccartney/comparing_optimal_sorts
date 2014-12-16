To run the program, which will create a total of 20 different datasets and sort them 10 times each to get an average for each of the four sorting algorithms:

First compile the C++ code then run the python script:
% make
% python algo_project1.py [int|double|long]

where you specify EITHER int, double, or long values to be created for the datasets.  Results are stored in a file called "output_[int|double|long].txt", depending on what the user specified.  To run the C++ sorting code directly with a dataset of your choosing (values must be separated by a space), first compile like above then run:

% ./project1 Filename Type Size Distribution

where: 
Filename = file that holds the generated data you want to sort
TYPE = ['int', 'long', or 'double'] is the type of data contained in the file to read into the array
Size = the number of data elements in the file, which becomes the size of the array.  If the file has more than this number, the extra data entries are ignored.  If it has less, a warning is issued.
Distribution = A string description of what data file you are sorting, used to label this execution run in the output file. 

Note the output file is appended rather than overwritten to capture multiple runs of the program.
 
zip contents:
1) The .h and .cpp files implement the sorting algorithms.  A Makefile is included to compile them.
2) algo_project.py creates the datasets, and calls the C++ executable to sort each dataset 
3) I have included two sample datasets created by the Python code, one for Poisson ints and one for random doubles.
4) lab1_report.pdf is the writeup of my results.
