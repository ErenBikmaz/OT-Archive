#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "Queue.h"
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

bool Enqueue();
bool Dequeue();
bool Peek();
bool getSize();
bool isEmpty();

bool ComplexDatatype();

// Array of test functions
FunctionPointer test_functions[] = { CtorDefault, getSize, isEmpty, 
Enqueue, Dequeue, Peek, CopyCtor, OpEquals, ComplexDatatype };

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

	Queue<int> test = Queue<int>();
	int size = test.getSize();

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
	Queue<int> test = Queue<int>();
	//add data to test
	test.Enqueue(1);
	//copy to new Queue
	Queue<int> testc = Queue<int>(test);
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
	Queue<int> test = Queue<int>();
	//add data to test
	test.Enqueue(1);
	//copy to new Queue
	Queue<int> testc;
	testc = Queue<int>(test);
	//peek
	if (testc.Peek() != 1)
	{
		pass = false;
	}

	cout << "OpEquals ";
	return pass;
}

bool Enqueue()
{
	bool pass = true;
	Queue<int> test = Queue<int>();
	test.Enqueue(1);
	//test data addition
	if (test.getSize() != 1)
	{
		pass = false;
	}

	cout << "Enqueue ";
	return pass;
}

bool Dequeue()
{
	bool pass = true;
	Queue<int> test = Queue<int>();
	test.Enqueue(42);
	//test data return
	if (test.Dequeue() != 42)
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
		test.Dequeue();
	}
	catch(Exception)
	{
		pass = true;
	}

	cout << "Dequeue ";
	return pass;
}

bool Peek()
{
	bool pass = true;
	Queue<int> test = Queue<int>();
	test.Enqueue(42);
	if (test.Peek() != 42)
	{
		pass = false;
	}


	cout << "Peek ";
	return pass;
}

bool getSize()
{
	bool pass = true;
	Queue<int> test = Queue<int>();
	if (test.getSize() != 0)
	{
		pass = false;
	}
	test.Enqueue(1);
	if (test.getSize() != 1)
	{
		pass = false;
	}
	cout << "getSize ";
	return pass;
}

bool isEmpty()
{
	bool pass = false;
	Queue<int> test = Queue<int>();
	if (test.isEmpty())
	{
		pass = true;
	}
	test.Enqueue(1);
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
	Queue<string> test = Queue<string>();

	//add data
	for (int i = 0; i < NUM_NAMES; i++)
	{
		test.Enqueue(NAMES[i]);
	}
	//check first cell (peek)
	if (test.Peek() != NAMES[0])
	{
		pass = false;
	}

	Queue<string> testcopy = test;
	Queue<string> testequ = testcopy;
	for (int i = 0; i < NUM_NAMES; i++)
	{
		if (test.Peek() != testcopy.Peek()
			|| test.Peek() != testequ.Peek())
		{
			pass = false;
		}
		test.Dequeue();
		testcopy.Dequeue();
		testequ.Dequeue();
	}

	cout << "ComplexDatatype ";
	return pass;
}

