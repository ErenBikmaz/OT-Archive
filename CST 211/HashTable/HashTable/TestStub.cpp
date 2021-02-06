#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "HashTable.h"

// Struct to test
struct Book
{
	string m_title;
	string m_author;
	int m_pages;
};

//hash generators
int hash(int key);

bool test();
// Test function declaration
bool tests();
bool books();

// Array of test functions
FunctionPointer test_functions[] = { tests , books };

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
	cout << "\nPress ENTER to Exit";
	cin.get();
}

int hash(int key)
{
	//hard-coded for given size
	return key % 5;
}

int stringhash(string key)
{
	//hard-coded for given size
	return key.length() % 10;
}

void print(string key)
{
	cout << key <<" ";
}

bool tests()
{
	HashTable<int, string> test(hash, 5);
	test.setHash(hash);
	test.Insert(5, "AAA");
	test.Insert(10, "BBB");
	test.Insert(15, "CCC");
	test.Insert(21, "ZZZ");
	cout << test[5];
	test.Delete(10);
	test.setHash(hash);
	cout << "\n";
	test.Traverse(print);

	cout << "Basic operations ";
	return true;
}

bool books()
{
	HashTable<string, Book> table(10);

	table.setHash(stringhash);

	Book temp = { "C++: Learn by Doing", "Todd Breedlove, Troy Scevers, et. al.", 635 };
	table.Insert("0763757233", temp);

	Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 1 };
	table.Insert("7063757233", temp1);

	Book temp3 = { "And That n There", "Ralph Carestia", 1 };
	table.Insert("7063757234", temp3);

	cout << table["0763757233"].m_title << "\n";
	cout << table["7063757233"].m_title << "\n";
	cout << table["7063757234"].m_title << "\n";
	return true;
}

bool test()
{
	bool pass = false;

	cout << "FUNC ";
	return pass;
}
