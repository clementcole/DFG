__author__ = 'clementacole75@gmail.com'
#!/usr/bin/python
import sys
import csv
import json
import os.path
import struct
import re
import os
import glob
import errno
import itertools
import pprint
from DFG import*


instr_dict = {}
absolute_address = []
relative_address = []
macro_op         = []
micro_op         = []
micro_instr		 = []
L_list           = []


sys.dont_write_bytecode = True
from bisect import bisect_right

def refined_absolute(line_list):
	#line_list.replace(" ", "")
	for letters in line_list:
		line_list = line_list.replace(" ", "")
	absolute_address.append(line_list)


def refined_relative(line_list):
	#line_list.replace(" ", "")
	line_list.lstrip()
	relative_address.append(line_list)

def refined_macro_op(line_list):
	#line_list.replace(" ", "")
	line_list.lstrip()
	macro_op.append(line_list)


def refined_micro_inst(line_list):
	refined_list = line_list.split(" ") #get the actuall micro_expression
	first_index = line_list.index(line_list[0])
	line_list = [x.strip(' ') for x in line_list]
	line_list = filter(bool, line_list)
	refined_list = [x.strip(' ') for x in refined_list] # Remove strip
	refined_list = filter(bool, refined_list)  # Remove all spaces
	refined_list = [x.strip(',') for x in refined_list]  #Strip list from all commas, I hate them
	really_refined = map(str.strip, refined_list)
	micro_instr.append(really_refined)
	while '' in really_refined:
		really_refined.remove('')
	micro_instr.append(really_refined)

def test_dict(a_addr, r_addr, macro, micro_ins):
	#print('\n'.join('{}: {}'.format(*k) for k in enumerate(micro_ins)))
	s_list = []
	for index, (a, b, c, d) in enumerate(zip(a_addr, r_addr, macro, micro_ins)):
		s_list.append(b)  #0
		s_list.append(c)  #1
		s_list.append(d)  #2
		instr_dict[a] = d
	with open('dictionary.json', 'w') as fp:
		json.dump(instr_dict, fp)
	with open('dictionary.json') as json_file:
		json_data = json.load(json_file)
		json_data
	#print json.dumps([{'name': k, 'size': v} for k,v in instr_dict.items()], indent=4)
	#items = json.loads(instr_dict)
	#print len(items['result'][0]['run'])



def read_trace():
	counter = 1  #counter for each line of file
	count = 0      #{Count for each item in list more of like an index for elements}
	founds = 0
	line_list2 = []  #Personal note {don't forget to register list to prevent exceptions}
	not_founds = 0
	refined_list= []
	refined_list2 = []
	pattern = "0x"
	i = 0  #Iterator for lists
	for name in files:
		try:
			with open(name, 'r') as f:
				text = f.readlines()
				for line in text:  #For each line the the assembly file do the following
					counter = counter + 1
					if re.match( r'(.*)0x[a-zA-Z0-9](.*?) .*', line, re.M | re.I):   #Check to see if the first two characters are 0x {more accurate}
						line_list = line.split(":")  #Turn each line into a list of words for text processing
						refined_absolute(line_list[0])
						refined_relative (line_list[1])
						refined_macro_op(line_list[2])
						refined_micro_inst(line_list[3])
						#test_dict(absolute_address, relative_address, macro_op, micro_instr)

		except IOError as exc:
			if exc.errno != errno.EISDIR:
				raise

	#for i in dest_nodes:
	#	del i
	#for i in dest_node_labels:
	#	del i
read_trace()
test_dict(absolute_address, relative_address, macro_op, micro_instr)

os.system("rm *.pyc")
