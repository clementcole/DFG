__author__ = 'clementacole75@gmail.com'
#!/usr/bin/python
import sys
import csv
import json
import os.path
import struct
import re
import os
from itertools import chain, islice
import shutil
 
#Main spawn calls the DFG.py module 
#   ==> {DFG.py} => Generates => /Blocks/ 
#   ==> {/Blocks/} ==> Generates ==> /*.dot 
#   ==> {DFG.py} ==> Generates ==> Graphs
#   ==> {Graphs} ==> Transfer {*.dot's} ==> /Graphs/*.dot
#   ==> {dot} ==> Generates ==> .ps files for visualization 
 
current_dir = os.getcwd()   #Get the current working directory with bash :-)
input_path = "Blocks"   #Name of directory to split blocks
output_path = "Graphs"  #Name of output directory for Graphs
 
 
 
 
if os.path.exists(input_path):  #blah blah
    shutil.rmtree(input_path)   #get path and concatenate with root directory for absolute whatever 
os.makedirs(input_path)         #Finally create the directory
#if os.
#os.makedirs(input_path)
 
if os.path.exists(output_path):  #Same show as above just for output
    shutil.rmtree(output_path)
os.makedirs(output_path)
 
filename = raw_input("Hello Please Enter the name of the trace file: ")  #Be nice to users at least say hello :-)
 
def blocks():  #Recursively run through blocks and 
    n = 0       #initialize a number holder variable
    while True:  #while I'm still in blocks directory do the following
        n += 1      #increment the value of n by one
        yield open(input_path+'/%d' % n, 'w')   #open and hold the path for writing into until finished visiously
 
pattern = "Block count:"        #Check for pattern Block count within the trace file
fs = blocks()                   #Call the function blocks() assign whatever was yeilded into fs (file streamer)
out = next(fs)                  #whatever comes out of fs goes into current block file been yeilded by blocks()
 
with open(filename) as tracefile:  #Ok open tracefile
    for line in tracefile:          #read line
        if pattern not in line:     #for each line check for pattern
            out.write(line)         #As long as string doesn't match pattern don't break eye contact
        else:                       #Anything else
            items = line.split(pattern)     #Oh don't forget to split the the files based on the pattern in case you encounter one
            out.write(items[0])             #write it to the fs stream 
            for item in items[1:]:          #A slice from 1 to who cares
                out = next(fs)              #What sream is next ? idk
                out.write(pattern + item)   #Well always give tips just include the Blocks count on top of each block might be useful later
 
 
 
     
os.system('python vectorize.py')          #Spawn the main dataflow graph generator
 
#def create_blocks():         #Test went wrong
##  if len(os.listdir(input_path)) > 0:  #Wrong test
#       os.removedirs(input_path)   #Passed nolonger needed
#       create_blocks()             #passed 
#   else:                           #never used
#       os.makedirs(input_path)     #so therefore backup
