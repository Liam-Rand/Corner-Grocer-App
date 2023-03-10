import re
import string

#
#  Grocery Frequency Program
#
#  PythonCode.py
#
#  Date: 12-9-2022
#  Author: Liam Rand
#

GROCERY_FILE = "CS210_Project_Three_Input_File.txt"
ITEM_FREQUENCY_FILE = "frequency.dat"

# Read a specified grocery file and generate a grocery list dictionary.
# The item name is the key and the amount purchased is the value.
def getgrocerylist():
    # Create a new dictionary to hold all the grocery items.
    grocery_list = {}

    # Open the specified grocery file containing all the purchased items.
    grocery_file = open(GROCERY_FILE)

    # Loop through all the items and add them to the grocery list.
    for item in grocery_file:

        # Remove newlines from the items.
        item = item.replace("\n", "")

        # Loop through the items and add them to the dictionary (grocery_list) if they do not exist.
        # If they do exist, increment the value of that item by one.
        if item in grocery_list:
            # The item already exists within the dictionary.
            grocery_list[item] = (grocery_list.get(item) + 1)
        else:
            # The item does not exist within the dictionary.
            grocery_list[item] = 1

    # Close the specified grocery file.
    grocery_file.close()

    # Return the created grocery list.
    return grocery_list

# Returns a string of length size, each character a char.
def ncharstring(size, char):

    # The generated string containing n amount of cs.
    charString = ''

    # Loop size times and append char to the generated string each time.
    for i in range(size):
        charString += char

    # Return the generated string.
    return charString

# Prints the grocery list dictionary to the console.
def printgrocerylist():
    # Get the dictionary of grocery items and frequency.
    grocery_list = getgrocerylist()

    # Print the header
    print('Item Name         Amount Purchased')
    print('----------------------------------\n')

    # Print each item along with its corresponding frequency to the console.
    for item in grocery_list:
        value = grocery_list.get(item)
        print(item, ncharstring((32 - len(item) - len(str(value))), ' '), value)

# Get the frequency of the specified item within the grocery list
def getitemfrequency(item_name):
    # Get the dictionary of grocery items and frequency.
    grocery_list = getgrocerylist()

    if(item_name in grocery_list):
        return grocery_list.get(item_name)
    else:
        return 0

# Get the grocery list dictionary and write it to a file.
def writefrequencyfile():
    # Get the dictionary of grocery items and frequency.
    grocery_list = getgrocerylist()

    # Create and open the specified frequency file that the grocery list dictionary will be saved to.
    # If the file does not exist, it will be created automatically.
    frequency_file = open(ITEM_FREQUENCY_FILE, "w")

    # Write each item name along with its corresponding purchase frequency to the file.
    for item in grocery_list:
        value = grocery_list.get(item)
        frequency_file.write(item + " " + str(value) + "\n")

    # Close the frequency file
    frequency_file.close()