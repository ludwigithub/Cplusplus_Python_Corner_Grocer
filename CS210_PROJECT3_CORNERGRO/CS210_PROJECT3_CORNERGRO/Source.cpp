/*
 * CS210_Project_Three_DLUDWIG
 * Date: 08/14/2022
 * Name: Deonne Ludwig
 *
 */

#include <Python.h>
#include <iostream>
#include <fstream>																	//to read and write to files
#include <iomanip>																	//to be able to use setfill, setw, etc.
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


void main()
{
	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);


	int menuChoice('0');																			//variables for user input
	int itemCount = 0;
	int inputQuantity = 0;
	string itemName;
	string inputName;
	ifstream inFS;																					//to access files


	while (menuChoice != '4') {																		//while loop for user menu choices													
		cout << setfill('*') << setw(45) << "*" << endl;											//display menu
		cout << setfill('*') << setw(45) << "*" << endl;
		cout << setfill('*') << setw(3) << "*";
		cout << " CORNER GROCER ITEM TRACKING PROGRAM  " << setw(3) << "*" << endl;
		cout << setfill('*') << setw(45) << "*" << endl;
		cout << "1) LIST ALL - DAILY ITEMS PURCHASED QUANTITY" << endl << endl;
		cout << "2) SPECIFIC - DAILY ITEM PURCHASED QUANTITY" << endl << endl;
		cout << "3) HISTOGRAM - DAILY ITEMS PURCHASED QUANTITY" << endl << endl;
		cout << "4) EXIT THE PROGRAM" << endl << endl << endl;

		cout << "Enter your choice as a number 1, 2, 3, or 4" << endl;								//prompt user for input
		cin >> menuChoice;																			//get user input		

		if (menuChoice == 1) {																		//if user chooses 1 "ListAll" lists all items and quantities
			CallProcedure("ListAll");																//call the Python function "ListAll"
		}
		else if (menuChoice == 2) {																	//if user chooses 2 asked item name						
			cout << "Enter item:  ";
			cin >> itemName;																		//get user input
			cout << endl;
			itemCount = callIntFunc("SpecificItems", itemName);										//call the Python function "SpecificItems"
				if (itemCount < 1) {
					cout << "No such item, choose 1 to see today's list" << endl << endl;			//error for invalid entry
				}
				else {
					cout << itemName << " : " << itemCount << endl << endl;							//outputs requested item and quantity
				}
		}
		else if (menuChoice == 3) {																	//if user chooses 3 "Histogram" of items and quantity produced						
			CallProcedure("Histogram");																//call the Python function "Histogram"
			inFS.open("frequency.dat");																//open python created frequency.dat file to read
			inFS >> itemName;																		//read list and show quantity with stars
			inFS >> itemCount;
				while (!inFS.fail()) {																
					cout << itemName;
					for (int i = 0; i < itemCount; ++i) {
						cout << "*";
					}
					cout << endl;
					inFS >> itemName;
					inFS >> itemCount;
				}
			inFS.close();																			//close frequency.dat file
			cout << endl << endl;
		}
		else if (menuChoice == 4) {																	//option 4 to exit program		
			cout << "Exiting program..." << endl;
			break;
		}
		else {
			cout << "ERROR: Please enter your selection as a number 1, 2, 3, or 4" << endl << endl;	//error for incorrect input
		}
	}
}
