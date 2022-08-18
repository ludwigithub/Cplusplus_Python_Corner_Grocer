# CS210_Project_Three_DLUDWIG
# Date: 08/14/2022
# Name: Deonne Ludwig

import re
import string
import os.path
from os import path


#def printsomething():
    #print("Hello from python!")

#def PrintMe(v):
    #print("You sent me: " + v)
    #return 100;

#def SquareValue(v):
    #return v * v


def ListAll():                                                              #function to list all items and quantity
    file = open(r'C:\Users\Deonne\source\repos\CS210_PROJECT3_CORNERGRO\Release\CS210_Project_Three_Input_File.txt') #open read file
    tempList = dict()                                                       #store item information
    for item in file:                                                       #read file for items
        item = item.strip()                                                 #remove spaces
        if item in tempList:                                                #compare items
            tempList[item] = tempList[item] + 1                             #increment for number of items found
        else:
            tempList[item] = 1
    for key in sorted(tempList.keys()):                                     #output formatted list of items w/ quanities
        print(key, ":", tempList[key])
    file.close()                                                            #close file
    print()
    print()

    
def SpecificItems(itemName):                                                #function to output requested items and quantity          
    file = open(r'C:\Users\Deonne\source\repos\CS210_PROJECT3_CORNERGRO\Release\CS210_Project_Three_Input_File.txt')#open read file
    itemName = itemName.lower()                                             #convert to lowercase
    itemCount = 0                                                           #initalize variable with 0
    for line in file:                                                       #read file for items                                          
        line = line.strip()                                                 #remove spaces
        item = line.lower()                                                 #convert to lowercase
        if item == itemName:                                                #find item in list
            itemCount += 1  
    return itemCount                                                        #return output to C++                                                     
    file.close()                                                            #close file


def Histogram():                                                            #function to output requested items and quantity by graph 
    file = open(r'C:\Users\Deonne\source\repos\CS210_PROJECT3_CORNERGRO\Release\CS210_Project_Three_Input_File.txt')#open read file
    frequency = open("frequency.dat", "w")                                  #create frequency.dat file for writing
    tempList = dict()                                                       #store item information
    for item in file:                                                       #read input file for items
        item = item.strip()                                                 #remove spaces
        if item in tempList:                                                #compare items
            tempList[item] = tempList[item] + 1                             #increment for number of items found
        else:
            tempList[item] = 1
    for key in sorted(tempList.keys()):                                     #write formatted list of items w/ quanities to frequency.dat file
        frequency.write(str(key) + " " + str(tempList[key]))
        frequency.write("\n")
    frequency.close()                                                       #close frequency.dat file
    file.close()                                                            #close given input file

