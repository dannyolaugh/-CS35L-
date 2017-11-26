#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import random, sys, locale
from optparse import OptionParser


def main():
	version_msg = "%prog 2.0"
	usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""
#add required options
	parser = OptionParser()
	parser.add_option("-u", "--unsorted",
	action="store_true", dest="unsorted", default=False,
	help="outputs columns whether or not files are sorted")
	parser.add_option("-1", action="store_true", dest="one", default=False, 
	help="outputs lines unique to file one")
	parser.add_option("-2", action="store_true", dest="two", default=False, 
	help="outputs lines unique to file two")
	parser.add_option("-3", action="store_true", dest="three", 
	default=False, help="outputs lines that are in both files")
	options, args = parser.parse_args(sys.argv[1:])
                      #non-options are placed into args, while options
                      #holds the 4 options above

                      #we now that in order for comm to work properly, there
                      #there must be exactly two input files so..
	if(len(args) != 2):
		parser.error("Error: comm needs two argument to compare")


	#set up variables to store the files and their contents
	file1=""
	file2=""
	content1=""
	content2=""
	
	#args holds the files
	# "-" means that the argument is from stdin

	if args[0] == "-":
                      #we know that the first arg is from stdin so we
                      #set content1 to the contents of stdin
		if not options.unsorted:
			content1 = sys.stdin.readlines()
		else:
			content1 = sys.stdin.readlines()
		file2 = open(args[1], 'r')  #open file2 with read permis
		content2 = file2.readlines()
                      #add file2's content into content2
                      #close file2
		file2.close()
#now we handle the case where the second argument is from stdin
	elif args[1] == "-":
		if not options.unsorted:
			content2 = sys.stdin.readlines()
		else:
			content2 = sys.stdin.readlines()
		file1 = open(args[0], 'r')
		content1 = file1.readlines()
		file1.close()

	else:      #if neither file is from stdin
		file1 = open(args[0], 'r')
		if not options.unsorted:
			content1 = file1.readlines()
		else:
			content1 = file1.readlines() 
		file1.close()
		file2 = open(args[1], 'r')
		if not options.unsorted:
			content2 = file2.readlines()
		else:
			content2 = file2.readlines()
		file2.close()

#so now lets make arrays to hold what is unique to each file
#and what is shared

	column1=[]
	column2=[]
	column3=[]
#now make a final array that will ultimately contain the output
	final_array = []
#the things in column1 should be those which are UNIQUE to file1.


#The difference function loses duplicates within the same file
#so i have to write my own

	if not options.unsorted:
		content1.sort()
		content2.sort()
#mydiff puts contents into correct columns
	def mydiff (column1, column2, column3):
		iequaledx = False  #if words from contents are the same
		xequaledi = False
		for i in range(len(content1)):    #loop and append
                        tempx = content1[i]
                        for x in range(len(content2)):
                                if content1[i] == content2[x]:
                                        column3.append(content1[i])
                                        content2[x] = ""
                                        tempx = content1[i]
                                        content1[i] = ""
                                        iequaledx = True
                        if (not iequaledx):
                                column1.append(tempx)
                        iequaledx = False

                for i in range(len(content2)):
                        for x in range(len(content1)):
                                if content1[x] == content2[i]:
                                        xequaledi = True
                        if (not xequaledi):
                                column2.append(content2[i])
                        xequaledi = False
		
		column1 = column1.sort()     #sort the results
		column2 = column2.sort()
		column3 = column3.sort()	
		return
	
	if not options.unsorted:
		mydiff (column1, column2, column3)

		#for i in column1:
		#	print i
		#print "end of column1"

#we use the same logic as above in order to store what is unique to
#file2

		#for i in column2:
		#	print i
		#print "end of column2"

		#for i in column3:
		#	print i
		#print "end of column3"
#now define a function that will test the possible combinations of
#options
#Note** my code orders capital letters first 
	def comboCheck (option1, option2, option3):
                      #first we check if options -1, -2, and -3
                      #are all used. If so, print nothing
            #because all is surpressedif (option1 & option2 & option3):
		#column with greatest number of characters	
		greatest=[]   
		if (option1 & option2 & option3):
			print ""
        #find the greatest number of elements in the 
	#array and make that my for loop range
		if ((len(column1) >= len(column2)) and (len(column1) >=  len(column3))):
			greatest = column1

		elif ((len(column2) >= len(column1)) and (len(column2) >= len(column3))):
                	greatest = column2

		else:
			greatest = column3

		done = False
		count1 = 0;
		count2 = 0;
		count3 = 0;
		count1_OutOfBounds = False
		count2_OutOfBounds = False
		count3_OutOfBounds = False
               #if array is empty set the count_OutOfBounds = True
		if column1 == []:
			count1_OutOfBounds = True
		if column2 == []:
			count2_OutOfBounds = True
		if column3 == []:
			count3_OutOfBounds = True 
	                     
                
		while (not done):  
		 #iterate through the length of the longest column
			#print "while runs"
			#print "count 1 is " + str(count1)
			#print "size of col 1 is " + str(len(column1))
			#print "count 2 is " + str(count2)
			#print "size of col 2 is " + str(len(column2))
			#print "count 3 is " + str(count3)
			#print "size of col 3 is " + str(len(column3))
                      
       			#print count1_OutOfBounds
			#print count2_OutOfBounds
			#print count3_OutOfBounds         	
			#print count1
			#print count2
			#print count3
			if count1_OutOfBounds == False and count2_OutOfBounds == False and count3_OutOfBounds == False:
				
				
				if ((column1[count1] <= column2[count2]) and (column1[count1] <= column3[count3])):
					print column1[count1].rstrip()
					count1 += 1
                                elif ((column2[count2] <= column1[count1]) and (column2[count2] <= column3[count3])):
                                        print '\t' + column2[count2].rstrip()
                                        count2 += 1
                                elif ((column3[count3] <= column2[count2]) and (column3[count3] <= column1[count1])):
                                        print '\t' * 2 + column3[count3].rstrip()
                                        count3 += 1
			if count1_OutOfBounds == False and count2_OutOfBounds == False and count3_OutOfBounds == True:
				if (column1[count1] <= column2[count2]):   
#column3 has all already been checked
                                        print column1[count1].rstrip()
                                        count1 += 1
                                elif (column2[count2] <= column1[count1]):
                                        print '\t' + column2[count2].rstrip()
                                        count2 += 1
			if count1_OutOfBounds == False and count2_OutOfBounds == True and count3_OutOfBounds == False:
				if (column1[count1] <= column3[count3]):
					print column1[count1].rstrip()
                                        count1 += 1
                                elif (column3[count3] <= column1[count1]):
                                        print '\t' * 2 + column3[count3].rstrip()
                                        count3 += 1
			if count1_OutOfBounds == False and count2_OutOfBounds == True and count3_OutOfBounds == True:
				print column1[count1].rstrip()
				count1 += 1
#now do the same thing but for the check against column
                                
                        if count1_OutOfBounds == True and count2_OutOfBounds == False and count3_OutOfBounds == False:
                                if (column2[count2] <= column3[count3]):
                                        print '\t' + column2[count2].rstrip()
                                        count2 += 1
                                elif (column3[count3] <= column2[count2]):
                                        print '\t' * 2 + column3[count3].rstrip()
                                        count3 += 1
			if count1_OutOfBounds == True and count2_OutOfBounds == False and count3_OutOfBounds == True:
				print '\t' + column2[count2].rstrip()
				count2 += 1
                                        
			if count1_OutOfBounds == True and count2_OutOfBounds == True and count3_OutOfBounds == False:
				print '\t' * 3 + column3[count3].rstrip()
				count3 += 1

			if (count1_OutOfBounds and count2_OutOfBounds and count3_OutOfBounds):
				done = True
			if (count1 >= len(column1)):
				count1_OutOfBounds = True
				#print "count 1 set to true"
			if (count2 >= len(column2)):
				count2_OutOfBounds = True
				#print "count 2 set to true"
			if (count3 >= len(column3)):
				count3_OutOfBounds = True
				#print "count 3 is set to true"
				
		return

	column1u=[]
        column2u=[]
        column3u=[]
	iequaledx = False
	xequaledi = False
	if not options.unsorted:
		comboCheck (options.one, options.two, options.three)

	else: 
		for i in range(len(content1)):
			tempx = content1[i]
			for x in range(len(content2)):
				if content1[i] == content2[x]:
					column3u.append(content1[i])
					print '\t' * 2 + content1[i].rstrip()
					content2[x] = ""
					tempx = content1[i]
					content1[i] = ""
					iequaledx = True
			if (not iequaledx):
				column1u.append(tempx)
				print tempx.rstrip()
			iequaledx = False	

		for i in range(len(content2)):
			for x in range(len(content1)):
				if content1[x] == content2[i]:
					xequaledi = True
			if (not xequaledi):
				column2u.append(content2[i])
				print '\t' + content2[i].rstrip()	
			xequaledi = False

	#print "Unsorted columns"
	#for i in column1u:
	#	print i
	#print "end of column1u"
	#for i in column2u:
	#	print i
	#print "end of column2u"
	#for i in column3u:
	#	print i
	#print "end of column3u"
	#wdr



if __name__ == "__main__":
	main()


#my code prioritizes capital letters before their lowercase counterparts 
		                  
