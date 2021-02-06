#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "Exception.h"
#include "BSTree.h"

// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

//desk checks
void Print(int data);

// Test function declaration
bool temp();
bool DefaultCtor();
bool InsertHeight();
bool InsertDuplicate();
bool Traversals();
bool CopyCtors();
bool InsertDeleteOneChild();
bool InsertDeleteTwoChildren();

// Array of test functions
FunctionPointer test_functions[] = { temp, DefaultCtor, InsertHeight, InsertDuplicate,
Traversals, CopyCtors, InsertDeleteOneChild,  InsertDeleteTwoChildren };

/*
temp, DefaultCtor, InsertHeight, InsertDuplicate,
Traversals, CopyCtors
*/

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
	cout << "\nPress Any Key to Exit";
	cin.get();
}

void Print(int data)
{
	cout << data << " ";
}

bool temp()
{
	bool pass = true;

	cout << "FUNC ";
	return pass;
}

bool DefaultCtor()
{
	bool pass = true;

	BSTree<int> test;

	cout << "Default Ctor ";
	return pass;
}

bool InsertHeight()
{
	bool pass = false;

	BSTree<int> test;

	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	if (test.Height() == 2)
	{
		pass = true;
	}
	//desk check
	test.InOrder(Print);

	cout << "basic insertion & height check ";
	return pass;
}

bool InsertDuplicate()
{
	bool pass = false;

	BSTree<int> test;

	test.Insert(1);

	try
	{
		test.Insert(1);
	}
	catch (Exception)
	{
		pass = true;
	}

	cout << "InsertDuplicate ";
	return pass;
}

bool Traversals()
{
	bool pass = true;

	BSTree<int> test;

	test.Insert(5);
	test.Insert(1);
	test.Insert(2);
	test.Insert(3);
	test.Insert(4);
	test.Insert(6);
	test.Insert(7);
	test.Insert(8);
	test.Insert(9);

	//desk check
	cout << "\nInOrder: ";
	test.InOrder(Print);
	cout << "\nPreOrder: ";
	test.PreOrder(Print);
	cout << "\nPostOrder: ";
	test.PostOrder(Print);
	cout << "\nBreadthFirst: ";
	test.BreadthFirst(Print);
	cout << "\n";

	cout << "Traversals ";
	return pass;
}

bool CopyCtors()
{
	bool pass = true;
	BSTree<int> test;

	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	BSTree<int> copy(test);

	cout << "\noriginal contents:";
	test.InOrder(Print);
	cout << "\ncopied contents:";
	copy.InOrder(Print);
	copy.Insert(4);
	test = copy;
	cout << "\ntest contents:";
	test.InOrder(Print);
	cout << "\ncopy contents:";
	copy.InOrder(Print);
	cout << "\nCopyCtors: ";
	return pass;
}

bool InsertDeleteOneChild()
{
	bool pass = true;

	BSTree<int> test;

	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	test.Delete(2);

	//desk check
	test.InOrder(Print);

	cout << "InsertDeleteOneChild";
	return pass;
}

bool InsertDeleteTwoChildren()
{
	bool pass = true;

	BSTree<int> test;

	test.Insert(5);
	test.Insert(3);
	test.Insert(4);
	test.Insert(2);

	test.Delete(3);

	//desk check
	test.InOrder(Print);

	cout << "\nInsertDeleteTwoChildren";
	return pass;
}
