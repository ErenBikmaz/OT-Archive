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
#include "AVLTree.h"

// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

//desk checks
void Print(int data);

// Test function declaration
bool Managers();
bool RightRight();
bool LeftLeft();
bool RightLeft();
bool LeftRight();
bool BigTree();
bool Deletion();
bool DeleteRoot();
bool Height();
bool IterHeight();
bool Purge();
bool Traversals();



// Array of test functions
FunctionPointer test_functions[] = { BigTree, Managers, RightRight, LeftLeft, RightLeft, LeftRight,
 Deletion, DeleteRoot, Height, IterHeight, Purge, Traversals };

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

	//char* LEAKDONOTKEEP = new char[42];
}

void Print(int data)
{
	cout << data << " ";
}

bool Managers()
{
	AVLTree<int> test;
	test.Insert(1);
	test.Insert(2);
	test.Insert(3);
	AVLTree<int> test2 = test;
	AVLTree<int> test3(test2);

	cout << "Managers ";
	return true;
}

bool RightRight()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	//test.RightRight(test.m_root);

	test.BreadthFirst(Print);

	cout << "RightRight unbalance ";
	return pass;
}

bool LeftLeft()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(3);
	test.Insert(2);
	test.Insert(1);

	//test.LeftLeft(test.m_root);

	test.BreadthFirst(Print);

	cout << "LeftLeft unbalance ";
	return pass;
}

bool RightLeft()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(1);
	test.Insert(3);
	test.Insert(2);

	//test.RightLeft(test.m_root);

	test.BreadthFirst(Print);

	cout << "RightLeft unbalance ";
	return pass;
}

bool LeftRight()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(3);
	test.Insert(1);
	test.Insert(2);

	//test.LeftRight(test.m_root);

	test.BreadthFirst(Print);

	cout << "LeftRight unbalance ";
	return pass;
}

bool BigTree()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(8);
	test.Insert(9);
	test.Insert(10);
	test.Insert(2);
	test.Insert(1);
	test.Insert(5);
	test.Insert(3);
	test.Insert(6);
	test.Insert(4);
	test.Insert(7);
	test.Insert(11);

	//test.LeftRight(test.m_root);

	test.BreadthFirst(Print);

	cout << "LeftRight unbalance ";
	return pass;
}

bool Deletion()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(9);
	test.Insert(10);
	test.Insert(8);
	test.Insert(12);
	test.Insert(14);
	test.Delete(10);
	test.Delete(14);

	//test.LeftRight(test.m_root);

	test.BreadthFirst(Print);

	cout << "Deletion ";
	return pass;
}

bool DeleteRoot()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	//test.RightRight(test.m_root);
	test.Delete(2);

	test.BreadthFirst(Print);

	cout << "RightRight unbalance ";
	return pass;
}

bool Height()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	if (test.Height() == 1)
	{
		pass = true;
	}

	cout << "Recursive Height ";
	return pass;
}

bool IterHeight()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	if (test.HeightIter() == 1)
	{
		pass = true;
	}

	cout << "Iterative Height ";
	return pass;
}

bool Purge()
{
	bool pass = true;

	AVLTree<int> test;
	test.Insert(1);
	test.Insert(2);
	test.Insert(3);

	test.Purge();

	cout << "Purge ";
	return pass;
}

bool Traversals()
{
	AVLTree<int> test;

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
	return true;
}
