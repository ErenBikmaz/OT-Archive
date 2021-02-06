#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "CircularQueue.h"
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

bool Enqueue();
bool Dequeue();
bool Peek();
bool getSize();
bool isEmpty();
bool isFull();

bool ComplexDatatype();

// Array of test functions
FunctionPointer test_functions[] = { CtorDefault, CtorArg, getSize, isEmpty, 
isFull, Enqueue, Dequeue, Peek, CopyCtor, OpEquals, ComplexDatatype };

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

	CircularQueue<int> test = CircularQueue<int>();
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

	CircularQueue<int> test42 = CircularQueue<int>(42);
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
	CircularQueue<int> test = CircularQueue<int>(2);
	//add data to test
	test.Enqueue(1);
	//copy to new CircularQueue
	CircularQueue<int> testc = CircularQueue<int>(test);
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
	CircularQueue<int> test = CircularQueue<int>(2);
	//add data to test
	test.Enqueue(1);
	//copy to new CircularQueue
	CircularQueue<int> testc;
	testc = CircularQueue<int>(test);
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
	CircularQueue<int> test = CircularQueue<int>(2);
	test.Enqueue(1);
	//test data addition
	if (test.getSize() != 1)
	{
		pass = false;
	}
	//test overflow
	pass = false;
	try
	{
		while (true)
		{
			test.Enqueue(1);
		}
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "Enqueue ";
	return pass;
}

bool Dequeue()
{
	bool pass = true;
	CircularQueue<int> test = CircularQueue<int>(2);
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
	catch (Exception)
	{
		pass = true;
	}

	cout << "Dequeue ";
	return pass;
}

bool Peek()
{
	bool pass = true;
	CircularQueue<int> test = CircularQueue<int>(2);
	test.Enqueue(42);
	if (test.Peek() != 42)
	{
		pass = false;
	}


	cout << "Peek ";
	return pass;
}

bool isEmpty()
{
	bool pass = false;
	CircularQueue<int> test = CircularQueue<int>(2);
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

bool getSize()
{
	bool pass = false;
	CircularQueue<int> test = CircularQueue<int>(1);
	if (test.getSize() == 1)
	{
		pass = true;
	}
	cout << "getSize ";
	return pass;
}

bool isFull()
{
	bool pass = false;
	CircularQueue<int> test = CircularQueue<int>(1);
	test.Enqueue(1);
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
	CircularQueue<string> test = CircularQueue<string>(NUM_NAMES);
	
	//add data
	for (int i = 0; i < NUM_NAMES; i++)
	{
		test.Enqueue(NAMES[i]);
	}
	//check last cell (peek)
	if (test.Peek() != NAMES[0])
	{
		pass = false;
	}

	CircularQueue<string> testcopy = test;
	CircularQueue<string> testequ = testcopy;
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
