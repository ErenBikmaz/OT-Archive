#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>

#include "Graph.h"


// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

// Test function declaration
void Print(char data);
bool test();
bool BasicTest();
bool Traversals();
bool LargeTest();
bool ErrorChecks();


// Array of test functions
FunctionPointer test_functions[] = { BasicTest, Traversals, LargeTest, ErrorChecks };

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

void Print(char data)
{
	cout << data << " ";
}

bool test()
{
	bool pass = true;

	cout << "FUNC ";
	return pass;
}

bool BasicTest()
{
	Graph<string, string> temp;
	temp.InsertVertex("Klamath");
	temp.InsertVertex("Medford");
	temp.Connect("Klamath", "Medford", "Hwy 140", 2);
	temp.Connect("Klamath", "Medford", "Dead Indian", 20);
	temp.RemoveEdge("Hwy 140");
	temp.RemoveVertex("Klamath");

	return true;
}

bool Traversals()
{
	Graph<char, string> temp;
	temp.InsertVertex('A');
	temp.InsertVertex('X');
	temp.InsertVertex('G');
	temp.InsertVertex('H');
	temp.InsertVertex('P');
	temp.InsertVertex('E');
	temp.InsertVertex('Y');
	temp.InsertVertex('M');
	temp.InsertVertex('J');

	temp.Connect('A', 'X', "A-X", 1);
	temp.Connect('X', 'H', "X-H", 1);
	temp.Connect('X', 'G', "X-G", 1);
	temp.Connect('G', 'P', "G-P", 1);
	temp.Connect('P', 'H', "P-H", 1);
	temp.Connect('H', 'E', "H-E", 1);
	temp.Connect('E', 'Y', "E-Y", 1);
	temp.Connect('E', 'M', "E-M", 1);
	temp.Connect('M', 'Y', "M-Y", 1);
	temp.Connect('M', 'J', "M-J", 1);

	cout << "\nBreadth: ";
	temp.BreadthFirstTraversal(Print);
	cout << "\nDepth: ";
	temp.DepthFirstTraversal(Print);

	return true;
}

bool LargeTest()
{
	Graph<char, string> temp;
	temp.InsertVertex('A');
	temp.InsertVertex('X');
	temp.InsertVertex('G');
	temp.InsertVertex('H');
	temp.InsertVertex('P');

	temp.Connect('A', 'X', "A-X", 1);
	temp.Connect('X', 'H', "X-H", 1);
	temp.Connect('X', 'G', "X-G", 1);
	temp.Connect('G', 'P', "G-P", 1);
	temp.Connect('P', 'H', "P-H", 1);

	temp.RemoveVertex('X');

	return true;
}

bool ErrorChecks()
{
	Graph<string, string> temp;
	temp.InsertVertex("Klamath");
	temp.InsertVertex("Medford");
	temp.Connect("Klamath", "Medford", "Hwy 140", 2);

	//Two identical verts
	try
	{
		temp.InsertVertex("Klamath");
	}
	catch (exception)
	{
		cout << "Caught";
	}

	//delete nonexistent node
	try
	{
		temp.RemoveVertex("Ashland");
	}
	catch (exception)
	{
		cout << "Caught";
	}

	return true;
}
