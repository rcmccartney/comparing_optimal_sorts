#Usage: python algo_project1_int.py 
import os, sys
import random
import subprocess
from scipy.stats import poisson

if(len(sys.argv) != 2):
    print "Usage: python algo_project1.py Type"
    print "Type = ['int', 'long', or 'double'] is the type of data you want to create"
    sys.exit()

# Command line args
primitive = sys.argv[1]
if (primitive == "long"):
    #using 8 byte long long values in this case 
    values = [-9223372036854775807, 9223372036854775807]
elif (primitive == "double"):
    #keeping double in the same range as int below 
    values = [-2147483647.0, 2147483647.0]
elif (primitive == "int"):
    #using 4 byte int in this case since that is the norm on the lab machines 
    values = [-2147483647, 2147483647]
else: 
    print "Your command line input is not recognized. Proceeding with 2 byte int's"
    values = [-32768, 32767]

def nextRand():
    if (primitive == "double"):
        return random.uniform( values[0], values[1] )
    else:
        return random.randint( values[0], values[1] )
#end nextRand()

data_size = [1000, 10000, 50000, 500000, 1000000]
type_set = ["Ordered", "Random", "Quarter_sorted","Poisson"]

for size in data_size:
    for distr in type_set:       
        outputF = "dataset_" + distr + str(size) + "_" + primitive + ".txt"
        fout = open(outputF, 'w')
        if (distr == "Random"):
            for i in range(size):
                #using 8 byte long long in this case 
                fout.write("%s " % nextRand() ) 
        elif (distr == "Poisson"):
            for i in range(size):
                sample = poisson.rvs(size/2)
                fout.write("%s " % sample)
        elif (distr == "Quarter_sorted"):
            #first get a sorted first quarter of the size and write to file            
            array = []
            for i in range(size/4):
                array.append( nextRand() )            
            array.sort()
            for data in array:
                fout.write("%s " % data)
            #now just becomes the same as random for the last 3/4
            for i in range(3*size/4):
                fout.write("%s " % nextRand() ) 
        else: #distribution is ordered
            array = []
            for i in range(size):
                array.append( nextRand() )            
            array.sort()
            for data in array:
                fout.write("%s " % data)
        fout.close()
        print("Working %s distribution for size = %s" % (distr, size) )
        #call the c++ code from here with the data we just made
        #first give it the arguments it needs:
        #   filename type size distr
        args = ("./project1", outputF, primitive, str(size), distr)
        #This subprocess will throw an error and inform us if the C++ program
	#throws a non-zero exit code, otherwise it continues
	subprocess.check_output(args, stderr=subprocess.STDOUT)
	#delete the output file once we are done.
	os.remove(outputF)

