#include <Python.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

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


// function to display program menu
void DisplayMenu() 
{
	cout << "1: Display unique items purchased along with quantity purchased." << endl;
	cout << "2: Display how many times a specific item was purchased." << endl;
	cout << "3: Display a histogram showing all items purchased along with a graphical representation of their quantity." << endl;
	cout << "4: Exit program." << endl;
	cout << "Please enter 1, 2, 3, or 4." << endl;
}

// function to ensure valid input type. in this case an integer is required
// returns a valid int from user input
int GetValidInput() {
	int userInput;

	try
	{
		//try to get user input
		cin >> userInput;
		// newline for formatting
		cout << endl;
	}
	catch (ios_base::failure& e)
	{
		// newline for formatting
		cout << endl;

		// if getting user input fails then clear the input buffer and ignore all text until
		// the next newline character
		cin.clear();
		cin.ignore(256, '\n');
		// alert user of error and recursively call GetValidInput
		cout << "Error! You may only enter numbers to select a menu option: " << endl;
		userInput = GetValidInput();
	}

	return userInput;
}

// function to read file and display resulting histogram
void DisplayHistogram()
{
	// variable for file
	ifstream datFile;
	// variable to hold item name
	string itemName;
	// variable to hold quantity
	int quantity;

	// open file for reading
	datFile.open("frequency.dat");

	// make sure file can be opened
	if (!datFile.is_open())
	{
		cout << "Could not open file frequency.dat" << endl;
		return;
	}

	// read first itemName
	datFile >> itemName;

	// read until end of file
	while (!datFile.fail())
	{
		// read quantity
		datFile >> quantity;
		cout << itemName << " ";
		// loop to print quantity in stars
		for (int i = 0; i < quantity; ++i) {
			cout << "*";
		}
		cout << endl;

		// ignore newline in dat file
		datFile.ignore();

		datFile.clear();

		// read next item
		datFile >> itemName;
	}

	datFile.close();
}

void main()
{
	// variable to hold user menu input
	int userInput;
	// variable to hold string input for menu option 2
	string userStringInput;
	// variable to hold results from python
	int singleItemQuantity;

	// set exception mask for cin stream
	cin.exceptions(ios::failbit);

	// display menu
	DisplayMenu();

	// get user input
	userInput = GetValidInput();

	// loop to continue accepting input until 4 is selected
	while (userInput != 4)
	{
		// perform appropriate function based on user input, default case means an invalid number was enetered
		switch (userInput)
		{
		case 1:
			// call python function to determine unique items and their quantity. print results with python
			CallProcedure("GetItemsAndQuantities");
			cout << endl;
			break;
		case 2:
			//prompt user to enter item string to search for
			cout << "Please enter a specific item to determine its quantity: " << endl;
			// get line for entire user string. use getline because the user string might include spaces
			cin.ignore();
			getline(cin, userStringInput);
			// call python function to determine if entered string is present in the file and return its quantity
			singleItemQuantity = callIntFunc("GetSingleItemQuantity", userStringInput);
			// handle value returned from python
			// if quantity is -1 item does not exist
			if (singleItemQuantity == -1)
			{
				cout << "Sorry that item does not exist." << endl;
			}
			// otherwise just print the quantity returned from python
			else
			{
				cout << "Quantity: " << singleItemQuantity << endl;
			}
			cout << endl;
			break;
		case 3:
			// call python function to read from input file and write results to frequency.dat
			CallProcedure("PrintItemsAndQuantitiesToFile");
			// display histogram
			DisplayHistogram();
			cout << endl;
			break;
		default:
			cout << "You may only enter 1, 2, 3, or 4." << endl;
			break;
		}

		// display menu to remind user of valid options
		DisplayMenu();

		// get user input again
		userInput = GetValidInput();
	}

	// print exit message
	cout << "Good Bye. Exiting Program." << endl;
}