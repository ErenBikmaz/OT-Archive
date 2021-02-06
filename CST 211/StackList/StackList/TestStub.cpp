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
bool CopyCtor();
bool OpEquals();

bool Push();
bool Pop();
bool Peek();
bool getNumElements();
bool isEmpty();

bool ComplexDatatype();

// Array of test functions
FunctionPointer test_functions[] = { CtorDefault, getNumElements, isEmpty, 
Push, Pop, Peek, CopyCtor, OpEquals, ComplexDatatype };

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

	//leak checker
	//char* leak = new char[42];
	cout << "\nPress Any Key to Exit";
	cin.get();
}

bool CtorDefault()
{
	bool pass = true;

	Stack<int> test = Stack<int>();
	int size = test.getNumElements();

	if (size != 0)
	{
		pass = false;
	}

	cout << "CtorDefault ";
	return pass;
}

bool CopyCtor()
{
	bool pass = true;
	Stack<int> test = Stack<int>();
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
	Stack<int> test = Stack<int>();
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
	Stack<int> test = Stack<int>();
	test.Push(1);
	//test data addition
	if (test.getNumElements() != 1)
	{
		pass = false;
	}

	cout << "Push ";
	return pass;
}

bool Pop()
{
	bool pass = true;
	Stack<int> test = Stack<int>();
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
	catch(Exception)
	{
		pass = true;
	}

	cout << "Pop ";
	return pass;
}

bool Peek()
{
	bool pass = true;
	Stack<int> test = Stack<int>();
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
	Stack<int> test = Stack<int>();
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
	Stack<int> test = Stack<int>();
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

bool ComplexDatatype()
{
	bool pass = true;
	//test everything again but with strings
	Stack<string> test = Stack<string>();

	//add data
	for (int i = 0; i < NUM_NAMES; i++)
	{
		test.Push(NAMES[i]);
	}
	//check last cell (peek)
	if (test.Peek() != NAMES[NUM_NAMES - 1])
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

	cout << "ComplexDatatype ";
	return pass;
}

