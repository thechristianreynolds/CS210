import re
import string



def GetItemsAndQuantities():
    # open text file using with to automatically close file when done
    with open('input.txt', 'r') as f:
        # store read lines in variable
        lines = f.readlines()
        # results variable to hold dictionary with unique items and quantities
        results = {}

        # loop through lines keeping track of new items and updating quantities
        for line in lines:
            # remove newline character from each line
            line = line.strip()
            # check if item is present in results dictionary already
            if line in results:
                # if it is then increment quantity
                results[line] += 1
            else:
                # else set quantity to 1
                results[line] = 1

        # print results
        PrintDict(results)

# function to return quantity of single item
def GetSingleItemQuantity(userstring):
    # open text file using with to automatically close file when done
    with open('input.txt', 'r') as f:
        # store read lines in variable
        lines = f.readlines()
        # results variable to hold dictionary with unique items and quantities
        results = {}

        # loop through lines keeping track of new items and updating quantities
        for line in lines:
            # remove newline character from each line
            line = line.strip()
            # check if item is present in results dictionary already
            if line in results:
                # if it is then increment quantity
                results[line] += 1
            else:
                # else set quantity to 1
                results[line] = 1

    # check if entered string is in the dictionary
    if userstring in results:
        # if it is then return the quantity
        return results[userstring]
    else:
        # if not then return -1 c++ will display the error
        return -1

# function to neatly print a dictionary
def PrintDict(dict):
    for key, value in dict.items():
        print(key, value)
    
# function to create frequency.dat file with appropriate contents
def PrintItemsAndQuantitiesToFile():
    # open text file using with to automatically close file when done
    with open('input.txt', 'r') as f:
        # store read lines in variable
        lines = f.readlines()
        # results variable to hold dictionary with unique items and quantities
        results = {}

        # loop through lines keeping track of new items and updating quantities
        for line in lines:
            # remove newline character from each line
            line = line.strip()
            # check if item is present in results dictionary already
            if line in results:
                # if it is then increment quantity
                results[line] += 1
            else:
                # else set quantity to 1
                results[line] = 1

        # print results to file
        PrintDictToDat(results)

# function to print dictionary to dat file
def PrintDictToDat(dict):
    # open dat file for writing, create if it does not exist
    with open('frequency.dat', 'w') as f:
        for key, value in dict.items():
            f.write('{0} {1}\n'.format(key, value))