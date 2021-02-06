#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "Stack.h"
#include "Exception.h"

// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

// Test function declaration
bool CtorDefault();
bool CtorArg();
bool CopyCtor();
bool OpEquals();

bool Push();
bool Pop();
bool Peek();
bool getNumElements();
bool getSize();
bool setSize();
bool isEmpty();
bool isFull();

bool ComplexDatatype();

// Array of test functions
FunctionPointer test_functions[] = { CtorDefault, CtorArg, getNumElements, isEmpty, 
isFull, Push, Pop, Peek, CopyCtor, OpEquals, getSize, setSize, ComplexDatatype };

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	bool tests_passed;

	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			cout << "***** failed *****\n";
		}
	}

	//char* leak = new char[42];

	cout << "\nPress Any Key to Exit";
	cin.get();
}

bool CtorDefault()
{
	bool pass = true;

	Stack<int> test = Stack<int>();
	int size = test.getSize();

	if (size != 0)
	{
		pass = false;
	}

	cout << "CtorDefault ";
	return pass;
}

bool CtorArg()
{
	bool pass = true;

	Stack<int> test42 = Stack<int>(42);
	int size = test42.getSize();

	if (size != 42)
	{
		pass = false;
	}

	cout << "CtorArg ";
	return pass;
}

bool CopyCtor()
{
	bool pass = true;
	Stack<int> test = Stack<int>(2);
	//add data to test
	test.Push(1);
	//copy to new stack
	Stack<int> testc = Stack<int>(test);
	//peek
	if (testc.Peek() != 1)
	{
		pass = false;
	}

	cout << "CopyCtor ";
	return pass;
}

bool OpEquals()
{
	bool pass = true;
	Stack<int> test = Stack<int>(2);
	//add data to test
	test.Push(1);
	//copy to new stack
	Stack<int> testc;
	testc = Stack<int>(test);
	//peek
	if (testc.Peek() != 1)
	{
		pass = false;
	}

	cout << "OpEquals ";
	return pass;
}

bool Push()
{
	bool pass = true;
	Stack<int> test = Stack<int>(2);
	test.Push(1);
	//test data addition
	if (test.getNumElements() != 1)
	{
		pass = false;
	}
	//test overflow
	pass = false;
	try
	{
		while (true)
		{
			test.Push(1);
		}
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "Push ";
	return pass;
}

bool Pop()
{
	bool pass = true;
	Stack<int> test = Stack<int>(2);
	test.Push(42);
	//test data return
	if (test.Pop() != 42)
	{
		pass = false;
	}
	//test data removal
	if (test.isEmpty() != true)
	{
		pass = false;
	}
	//test undeflow
	pass = false;
	try
	{
		test.Pop();
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "Pop ";
	return pass;
}

bool Peek()
{
	bool pass = true;
	Stack<int> test = Stack<int>(2);
	test.Push(42);
	if (test.Peek() != 42)
	{
		pass = false;
	}


	cout << "Peek ";
	return pass;
}

bool getNumElements()
{
	bool pass = true;
	Stack<int> test = Stack<int>(2);
	if (test.getNumElements() != 0)
	{
		pass = false;
	}
	test.Push(1);
	if (test.getNumElements() != 1)
	{
		pass = false;
	}
	cout << "getNumElements ";
	return pass;
}

bool isEmpty()
{
	bool pass = false;
	Stack<int> test = Stack<int>(2);
	if (test.isEmpty())
	{
		pass = true;
	}
	test.Push(1);
	if (test.isEmpty())
	{
		pass = false;
	}
	cout << "isEmpty ";
	return pass;
}

bool getSize()
{
	bool pass = false;
	Stack<int> test = Stack<int>(1);
	if (test.getSize() == 1)
	{
		pass = true;
	}
	cout << "getSize ";
	return pass;
}

bool setSize()
{
	bool pass = true;
	Stack<int> test = Stack<int>(1);
	test.Push(1);
	//increase size
	test.setSize(3);
	try
	{
		test.Push(2);
		test.Push(3);
	}
	catch (Exception)
	{
		pass = false;
	}

	//decrease size and check data integrity
	test.setSize(1);
	if (test.Peek() != 1)
	{
		pass = false;
	}

	cout << "setSize ";
	return pass;
}


bool isFull()
{
	bool pass = false;
	Stack<int> test = Stack<int>(1);
	test.Push(1);
	if (test.isFull())
	{
		pass = true;
	}

	cout << "isFull ";
	return pass;
}

bool ComplexDatatype()
{
	bool pass = true;
	//test everything again but with strings
	Stack<string> test = Stack<string>(NUM_NAMES);
	
	//add data
	for (int i = 0; i < NUM_NAMES; i++)
	{
		test.Push(NAMES[i]);
	}
	//check last cell (peek)
	if (test.Peek() != NAMES[NUM_NAMES-1])
	{
		pass = false;
	}

	Stack<string> testcopy = test;
	Stack<string> testequ = testcopy;
	for (int i = 0; i < NUM_NAMES; i++)
	{
		if (test.Peek() != testcopy.Peek() 
			|| test.Peek() != testequ.Peek())
		{
			pass = false;
		}
		test.Pop();
		testcopy.Pop();
		testequ.Pop();
	}

	//add data, again
	for (int i = 0; i < NUM_NAMES; i++)
	{
		test.Push(NAMES[i]);
	}

	test.setSize(1);
	//check that data is preserved correctly
	if (test.Peek() != NAMES[0])
	{
		pass = false;
	}

	cout << "ComplexDatatype ";
	return pass;
}
