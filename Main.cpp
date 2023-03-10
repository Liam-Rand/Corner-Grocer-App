#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include "Main.h"
#include "TextUtils.h"

using namespace std;

/*
 *  Grocery Frequency Program
 *
 *  Main.cpp
 *
 *  Date: 12-9-2022
 *  Author: Liam Rand
 */

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	//Set the console text color to green
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);

	//Continue to loop through the program until the runProgram bool is set to
	//false.
	while (runProgram)
		PrintMenu();
}

//Clears the screen and prints the title of the program.
void PrintTitle()
{
	//Clear the console
	system("CLS");

	//Print the program title and author.
	cout << TextUtils::nCharString(34, '=') << endl;
	cout << '|' << TextUtils::nCharString(7, ' ') << "CORNER GROCER APP" << TextUtils::nCharString(8, ' ') << '|' << endl;
	cout << '|' << TextUtils::nCharString(5, ' ') << "Created by: Liam Rand" << TextUtils::nCharString(6, ' ') << '|' << endl;
	cout << TextUtils::nCharString(34, '=') << endl;
}

//Prints the menu along with all available options.
void PrintMenu()
{
	//Print the title of the program
	PrintTitle();

	cout << endl;

	//Print the menu options
	PrintHeader("Options");

	cout << "[1] Display Grocery List" << endl;
	cout << "[2] Calculate Frequency of an Item" << endl;
	cout << "[3] Display Grocery List Histogram" << endl;
	cout << "[4] Exit" << endl;
	cout << "Enter your selection as a number! (1, 2, 3, or 4)" << endl;

	//Get the input from the user for what menu option they would like to select.
	//This number must be between 1 and 3, this is validated by the GetNumberInput() function.
	int input = GetNumberInput("Option Selection >", 1, 4);

	string stringInput;
	map<string, int> groceryList;

	switch (input)
	{
	case 1:
		//Grocery List was selected.
		//Clear the screen and print the title and header.
		PrintTitle();
		PrintHeader("GROCERY LIST");

		//Call the Python function, printgrocerylist().
		CallProcedure("printgrocerylist");

		//Wait for the user to press ENTER before looping through the program again.
		WaitForContinue();
		break;
	case 2:
		//Item Frequency was selected.
		//Clear the screen and print the title and header.
		PrintTitle();
		PrintHeader("ITEM FREQUENCY");

		//Get the user input as a string.
		stringInput = GetStringInput("Item Name >");

		//Clear the screen and print the title and header.
		PrintTitle();
		PrintHeader("ITEM FREQUENCY");

		//Print the returned frequency of the specified item from the getitemfrequency(item_name) Python function.
		cout << endl << "The number of times ";

		//Change console text color to white.
		SetConsoleTextAttribute(hConsole, 15);
		cout << stringInput;

		//Change console text color to green.
		SetConsoleTextAttribute(hConsole, 10);
		cout << " was purchased is ";

		//Change console text color to white.
		SetConsoleTextAttribute(hConsole, 15);
		cout << callIntFunc("getitemfrequency", stringInput);

		//Change console text color to green.
		SetConsoleTextAttribute(hConsole, 10);
		cout << "!" << endl;

		//Wait for the user to press ENTER before looping through the program again.
		WaitForContinue();
		break;
	case 3:
		//Grocery List Histogram was selected.
		//Clear the screen and print the title and header.
		PrintTitle();
		PrintHeader("GROCERY LIST HISTOGRAM");

		cout << endl;

		//Call the Python function, writefrequencyfile().
		CallProcedure("writefrequencyfile");

		//Read the created frequency file and create a grocery list map.
		groceryList = ReadFrequencyData();

		//Create a histogram from the grocery list map.
		CreateHistogram(groceryList, '*');

		//Wait for the user to press ENTER before looping through the program again.
		WaitForContinue();
		break;
	case 4:
		//Exit was selected.
		//End the program.
		runProgram = false;
		cout << endl << "Goodbye...";
		return;
	}
}

/**
* Print a header to the screen with automatically centered text.
* @param titleName The text to be printed within the header.
*/
void PrintHeader(string titleName)
{
	cout << TextUtils::nCharString(34, '=') << endl;
	//Print titleName within the header, making sure to get the difference between the length of titleName 
	//and 34 (The total length of the header) and devide by 2 to center the text within the header.
	cout << TextUtils::nCharString(((34 - titleName.length()) / 2), ' ') << titleName << endl;
	cout << TextUtils::nCharString(34, '=') << endl;
}

/**
* Get an integer input from the user within a specified range between minInput and maxInput. This function also performs input validation.
* @param message The message that is printed to the console before the input is accepted.
* @param minInput The lowest allowed integer input by the user. If -1, no min is used.
* @param maxInput The highest allowed integer input by the user. If -1, no max is used.
*/
int GetNumberInput(string message, int minInput, int maxInput)
{
	//Whether or not the user input is valid.
	bool validInput = false;

	//The user's input is temporarily stored here as a string,
	//allowing the input to be properly checked and converted along
	//with error handling.
	string inputString;

	//The user's input after being converted to an int.
	int inputInt;

	//Continue to ask the user for input until a valid integer input is acquired.
	while (!validInput)
	{
		try
		{
			cout << endl << message + " ";

			//Get the user input as a string
			cin >> inputString;

			//Try to convert the string to an integer.
			//If this fails, throw exception 1. (Must be a whole number)
			//If the input is a number followed by invalid input, the number will be
			//accepted and the invalid input will be truncated. (example: 5test will be converted to 5)
			try
			{
				inputInt = stoi(inputString);
			}
			catch (const std::invalid_argument&)
			{
				throw 1;
			}

			//Check to see if a min and a max are required. (They are not if either are initialized to -1)
			//If so, check to ensure that the number is either less than or greater than the corresponding
			//min or max accepted integer. If not, throw exception 2 (Out of possible range).
			if ((minInput != -1 && inputInt < minInput) || (maxInput != -1 && inputInt > maxInput))
				throw 2;
		}
		catch (int exception)
		{
			//An exception was caught with the user input

			//Clear cin and ignore the next line so that the
			//error message will not be accepted as user input, causing
			//an infinite loop of exceptions.
			cin.clear();
			cin.ignore(10000, '\n');

			//Set the console text color to red for the error message.
			SetConsoleTextAttribute(hConsole, 12);

			//Print the beginning of the error message
			cout << "Input invalid! Reason: ";

			//Check for recieved exception code and print corresponding
			//error message to the console.
			switch (exception)
			{
			case 1:
				cout << "Input must be a whole number!" << endl;
				break;
			case 2:
				cout << "Input must between " << minInput << "-" << maxInput << "!" << endl;
				break;
			default:
				cout << "Unknown" << endl;
			}

			//Set the console text color back to green.
			SetConsoleTextAttribute(hConsole, 10);

			//Since this attempt to get user input failed, skip the rest of the loop and proceed
			//to the next attempt.
			continue;
		}

		//This attempt to get valid user input was a success, therefore break out of the loop.
		validInput = true;
	}

	//Return the valid user input.
	return inputInt;
}

/**
* Get a string input from the user. This function also performs input validation.
* @param message The message that is printed to the console before the input is accepted.
*/
string GetStringInput(string message)
{
	//Whether or not the user input is valid.
	bool validInput = false;

	//The user's input is temporarily stored here as a string,
	//allowing the input to be properly checked and converted along
	//with error handling.
	string inputString;

	cout << endl << message + " ";

	//Get the user input as a string
	cin >> inputString;

	//Return the valid user input.
	return inputString;
}

//Waits for the user to press ENTER before continuing within the program.
void WaitForContinue()
{
	//Wait for the user to press the 'ENTER' key before continuing
	cout << endl << "Press Enter to continue...";

	//Clear cin and ignore the next line so that any previous inputs
	cin.clear();
	cin.ignore(10000, '\n');

	//Wait for the user to press ENTER
	cin.get();
}

//Reads the specified frequency file and stores the information within a map.
//The key is the item name and the value is the frequency.
map<string, int> ReadFrequencyData()
{
	//The map with the grocery list information.
	map<string, int> groceryList;

	//Create the input file stream.
	ifstream frequencyFileStream;

	//Attempt to open the frequency file.
	frequencyFileStream.open(ITEM_FREQUENCY_FILE);

	//Check to ensure that the file was successfuly opened.
	if (!frequencyFileStream.is_open())
	{
		//The file was not opened, therefore something must have failed.
		//Set the console text color to red for the error message.
		SetConsoleTextAttribute(hConsole, 12);

		cout << "Could not open file " + ITEM_FREQUENCY_FILE + "!" << endl;

		//Set the console text color back to green.
		SetConsoleTextAttribute(hConsole, 10);

		//Return because the function failed.
		//The stream does not need to be closed because it was
		//never successfuly opened.
		return groceryList;
	}

	//Temp vars to store the name and frequency of the items before they
	//are permanently stored within the map.
	string itemName;
	int itemFrequency;

	//Read until end-of-file.
	while (!frequencyFileStream.fail())
	{
		//Get the item name.
		frequencyFileStream >> itemName;

		//Check to see if the previous input failed.
		if (frequencyFileStream.fail())
		{
			//The previous input failed.
			//The item name is missing.
			//This generally means the file ended with a blank newline.

			//Continue to the next item because this item failed.
			continue;
		}

		//Get the item frequency.
		frequencyFileStream >> itemFrequency;

		//Check to see if the previous input failed.
		if (frequencyFileStream.fail())
		{
			//The previous input failed.
			//The item frequency is missing.

			//Set the console text color to red for the error message.
			SetConsoleTextAttribute(hConsole, 12);

			cout << itemName << " has no frequency!" << endl;

			//Set the console text color back to green.
			SetConsoleTextAttribute(hConsole, 10);

			//Continue to the next item because this item failed.
			continue;
		}

		//Store the values from the temp vars, itemName and itemFrequency, into the grocery list
		//map
		groceryList.insert(pair<string, int>(itemName, itemFrequency));

		//Ingore the newline
		frequencyFileStream.ignore();
	}

	//Check to see if the file reading ended before the end of the file, signalling
	//an input error.
	if (!frequencyFileStream.eof())
	{
		//An error occured during file input

		//Set the console text color to red for the error message.
		SetConsoleTextAttribute(hConsole, 12);

		cout << "Input failure before reaching end of file!" << endl;

		//Set the console text color back to green.
		SetConsoleTextAttribute(hConsole, 10);
	}

	//Close the file system before returning.
	frequencyFileStream.close();

	//Return the created grocery list map.
	return groceryList;
}

/**
* Create a text histogram of grocery items and their corresponding frequencies using a grocery list map.
* @param groceryList The grocery list map that the histogram will be created from.
* @param histogramChar The character that will be used to represent the frequency of an item within the grocery list.
*/
void CreateHistogram(map<string, int>& groceryList, char histogramChar)
{
	//This variable is used so that alternating lines can have a slightly
	//different color to make the histogram easier for the user to read.
	bool alternateLine = false;

	//Create an iterator to loop through the grocery list map.
	map<string, int>::iterator iterator;

	//Loop through each item within the grocery list map.
	for (iterator = groceryList.begin(); iterator != groceryList.end(); iterator++)
	{
		//Get the name of the item from the key.
		string itemName = iterator->first;

		//Get the frequency of the item from the value.
		int itemFrequency = iterator->second;

		//Spacing for formatting the histogram
		cout << itemName << TextUtils::nCharString((16 - itemName.length()), ' ');

		//Used to alternate between white and gray text for the histogram.
		//This makes it easier to read within the console.
		if (alternateLine)
			//Set the console text to white.
			SetConsoleTextAttribute(hConsole, 15);
		else
			//Set the console text to gray.
			SetConsoleTextAttribute(hConsole, 8);

		//Print multiple of histogramChar matching the itemFrequency for the current
		//grocery list item.
		cout << TextUtils::nCharString(itemFrequency, histogramChar) << endl;

		//Set the console text to green.
		SetConsoleTextAttribute(hConsole, 10);

		//Alternate this value after every line for the
	    //alternating histogram colors.
		alternateLine = !alternateLine;
	}
}