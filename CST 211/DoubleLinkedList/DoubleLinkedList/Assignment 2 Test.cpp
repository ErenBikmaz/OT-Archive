/*********************************************************************
* Author: Junmin Yee
* File Name: main.cpp
* Date Created: 08/01/2018
* Modifications:
*	10/01/2020 - Increase test coverage
*********************************************************************/
/*********************************************************************
* Lab/Assignment: Assignment02 - Doubly Linked List ADT
*
* Overview:
*	This program will test a templated Double Linked List
*
* Input:
*	None.
*
* Output:
*	Testing output.
*
**********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "List.h"
#include "Exception.h"

// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;

// Test function declaration
bool test_default_ctor();
bool test_copy_ctor();
bool test_move_ctor();
bool test_op_equal();
bool test_move_op_equal();
bool test_is_empty();
bool test_first_with_value();
bool test_first_empty_list();
bool test_last_with_value();
bool test_last_empty_list();
bool test_prepend();
bool test_append();
bool test_purge();
bool test_extract_empty();
bool test_extract_match();
bool test_extract_no_match();
bool test_inserta_empty();
bool test_inserta_match();
bool test_inserta_no_match();
bool test_insertb_empty();
bool test_insertb_match();
bool test_insertb_no_match();

bool test_default_ctor_complex();
bool test_copy_ctor_complex();
bool test_move_ctor_complex();
bool test_op_equal_complex();
bool test_move_op_equal_complex();
bool test_is_empty_complex();
bool test_first_with_value_complex();
bool test_first_empty_list_complex();
bool test_last_with_value_complex();
bool test_last_empty_list_complex();
bool test_prepend_complex();
bool test_append_complex();
bool test_purge_complex();
bool test_extract_empty_complex();
bool test_extract_match_complex();
bool test_extract_no_match_complex();
bool test_inserta_empty_complex();
bool test_inserta_match_complex();
bool test_inserta_no_match_complex();
bool test_insertb_empty_complex();
bool test_insertb_match_complex();
bool test_insertb_no_match_complex();

// Test functions for moves
List<int> ReturnIntList();
List<string> ReturnStrList();

 //Array of test functions
FunctionPointer test_functions[] = { test_default_ctor, test_copy_ctor, test_move_ctor, 
test_op_equal, test_move_op_equal, test_is_empty, test_first_with_value, 
test_first_empty_list, test_last_with_value, test_last_empty_list, test_prepend, 
test_append, test_purge, test_extract_empty, test_extract_match, test_extract_no_match, 
test_inserta_empty, test_inserta_match, test_inserta_no_match, test_insertb_empty, 
test_insertb_match, test_insertb_no_match, test_default_ctor_complex, test_copy_ctor_complex,
test_move_ctor_complex, test_op_equal_complex, test_move_op_equal_complex, 
test_is_empty_complex, test_first_with_value_complex, test_first_empty_list_complex,
test_last_with_value_complex, test_last_empty_list_complex, 
test_prepend_complex, test_append_complex, test_purge_complex,
test_extract_empty_complex, test_extract_match_complex, test_extract_no_match_complex, 
test_inserta_empty_complex, test_inserta_match_complex, test_inserta_no_match_complex, 
test_insertb_empty_complex, test_insertb_match_complex, test_insertb_no_match_complex };


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int failed_tests = 0;
	
	// Run the test functions
	for (FunctionPointer func : test_functions)
	{
		if (func())
		{
			cout << "passed\n";
		}
		else
		{
			failed_tests++;
			cout << "***** failed *****\n";
		}
	}

	if (failed_tests > 0)
		cout << "\nYou have " << failed_tests << " failed tests";
	else
		cout << "\nAll tests passed! Good job!";

	cout << "\nPress Any Key to Exit";
	cin.get();

	return 0;
}

bool test_default_ctor()
{
	bool pass = true;
	Node<int> * default_head = nullptr;
	Node<int> * default_tail = nullptr;


	List<int> list_test;

	if (list_test.getHead() != default_head)
		pass = false;

	if (list_test.getTail() != default_tail)
		pass = false;

	cout << "Default ctor test ";

	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;

	List<int> test_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		test_list.Append(i);

	List<int> list_test(test_list);

	// Check data integrity
	for (int i = 0; i < NUM_SIZE; ++i)
	{
		if (list_test.First() != test_list.First())
			pass = false;
		list_test.Extract(i); //Remove first value
		test_list.Extract(i);
	}

	cout << "Copy ctor test ";

	return pass;
}

bool test_move_ctor()
{
	bool pass = true;

	List<int> test_list(ReturnIntList());

	// Check data integrity
	for (int i = 0; i < NUM_SIZE; ++i)
	{
		if (i != test_list.First())
			pass = false;
		test_list.Extract(i); // Remove value
	}

	cout << "Move ctor test ";

	return pass;
}

bool test_op_equal()
{
	bool pass = true;

	List<int> test_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		test_list.Append(i);

	List<int> list_test;
	list_test = test_list; //Op =

	// Check data integrity
	for (int i = 0; i < NUM_SIZE; ++i)
	{
		if (list_test.First() != test_list.First())
			pass = false;
		list_test.Extract(i); //Remove first value
		test_list.Extract(i);
	}

	cout << "Op equals test ";

	return pass;
}

bool test_move_op_equal()
{
	bool pass = true;

	List<int> test_list;
	test_list = ReturnIntList(); //Op =

	// Check data integrity
	for (int i = 0; i < NUM_SIZE; ++i)
	{
		if (i != test_list.First())
			pass = false;
		test_list.Extract(i); //Remove first value
	}

	cout << "Move op equals test ";

	return pass;
}

bool test_is_empty()
{
	bool pass = true;

	List<int> full_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		full_list.Append(i);

	List<int> empty_list;

	if (full_list.isEmpty())
		pass = false;

	if (!empty_list.isEmpty())
		pass = false;

	cout << "isEmpty test ";

	return pass;
}

bool test_first_with_value()
{
	bool pass = true;

	List<int> full_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		full_list.Append(i);

	if (full_list.First() != 0)
		pass = false;

	cout << "First with value test ";

	return pass;
}

bool test_first_empty_list()
{
	bool pass = false;

	List<int> empty_list;

	try
	{
		empty_list.First();
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "First with empty list test ";

	return pass;
}

bool test_last_with_value()
{
	bool pass = false;

	List<int> full_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		full_list.Append(i);

	if (full_list.Last() == NUM_SIZE - 1)
		pass = true;

	cout << "Last with value test ";

	return pass;
}

bool test_last_empty_list()
{
	bool pass = false;

	List<int> empty_list;

	try
	{
		empty_list.Last();
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Last with empty list test ";

	return pass;
}

bool test_prepend()
{
	bool pass = true;
	int init_value = 5;
	int next_value = 3;

	List<int> test_list;

	// Prepend empty list
	test_list.Prepend(init_value);
	if (test_list.First() != init_value || test_list.Last() != init_value)
		pass = false;

	// Prepend list with existing values
	test_list.Prepend(next_value);
	if (test_list.First() != next_value || test_list.Last() != init_value)
		pass = false;

	cout << "Prepend test ";

	return pass;
}

bool test_append()
{
	bool pass = true;
	int init_value = 5;
	int next_value = 3;

	List<int> test_list;

	// Append empty list
	test_list.Append(init_value);
	if (test_list.First() != init_value || test_list.Last() != init_value)
		pass = false;

	// Append list with existing values
	test_list.Append(next_value);
	if (test_list.First() != init_value || test_list.Last() != next_value)
		pass = false;

	cout << "Append test ";

	return pass;
}

bool test_purge()
{
	bool pass = true;

	List<int> full_list;
	for (int i = 0; i < NUM_SIZE; ++i)
		full_list.Append(i);

	full_list.Purge();
	if (full_list.getHead() || full_list.getTail())
		pass = false;
	
	cout << "Purge test ";

	return pass;
}

bool test_extract_empty()
{
	bool pass = false;
	int test_value = 5;

	List<int> empty_list;

	try
	{
		empty_list.Extract(test_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Extract empty list test ";

	return pass;
}

bool test_extract_match()
{
	bool pass = true;

	List<int> test_list;
	for (int i = 1; i <= NUM_EXTRACT; ++i)
		test_list.Append(i);

	// List should have 1 2 3 4
	test_list.Extract(3); // Test extract from middle
	if (test_list.First() != 1 || test_list.Last() != 4)
		pass = false;

	// List should have 1 2 4
	test_list.Extract(1); // Test extract from front of list
	if (test_list.First() != 2 || test_list.Last() != 4)
		pass = false;

	// List should have 2 4
	test_list.Extract(4); // Test extract from back of list
	if (test_list.First() != 2 || test_list.Last() != 2)
		pass = false;

	// List should have 2
	test_list.Extract(2); // Test extract from list with 1 node
	if (test_list.getHead() || test_list.getTail())
		pass = false;

	cout << "Extract match test ";

	return pass;
}

bool test_extract_no_match()
{
	bool pass = false;
	int test_value = 5;
	int fake_value = 3;

	List<int> empty_list;
	empty_list.Append(test_value);

	try
	{
		empty_list.Extract(fake_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Extract no match test ";

	return pass;
}

bool test_inserta_empty()
{
	bool pass = false;
	int test_value = 5;
	int search_value = 7;

	List<int> empty_list;

	try
	{
		empty_list.InsertAfter(test_value, search_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert after empty list test ";

	return pass;
}

bool test_inserta_match()
{
	bool pass = true;
	int init_value = 5;
	int first_new_value = 7;
	int second_new_value = 6;

	List<int> test_list;
	test_list.Append(init_value);

	// Test insert to end of list
	test_list.InsertAfter(first_new_value, init_value); 

	// Test insert to middle of list
	test_list.InsertAfter(second_new_value, init_value); 

	// List should contain 5 6 7
	if (test_list.Last() != first_new_value)
		pass = false;

	test_list.Extract(first_new_value);
	// List should contain 5 6
	if (test_list.Last() != second_new_value)
		pass = false;

	cout << "Insert after match test ";

	return pass;
}

bool test_inserta_no_match()
{
	bool pass = false;
	int test_value = 5;
	int fake_value = 7;

	List<int> empty_list;
	empty_list.Append(test_value);

	try
	{
		empty_list.InsertAfter(test_value, fake_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert after no match test ";

	return pass;
}

bool test_insertb_empty()
{
	bool pass = false;
	int test_value = 5;
	int search_value = 7;

	List<int> empty_list;

	try
	{
		empty_list.InsertBefore(test_value, search_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert before empty list test ";

	return pass;
}

bool test_insertb_match()
{
	bool pass = true;
	int init_value = 7;
	int first_new_value = 5;
	int second_new_value = 6;

	List<int> test_list;
	test_list.Prepend(init_value);

	// Test insert to start of list
	test_list.InsertBefore(first_new_value, init_value);

	// Test insert to middle of list
	test_list.InsertBefore(second_new_value, init_value);

	// List should contain 5 6 7
	if (test_list.First() != first_new_value)
		pass = false;

	test_list.Extract(first_new_value);
	// List should contain 6 7
	if (test_list.First() != second_new_value)
		pass = false;

	cout << "Insert before match test ";

	return pass;
}

bool test_insertb_no_match()
{
	bool pass = false;
	int test_value = 5;
	int fake_value = 7;

	List<int> empty_list;
	empty_list.Append(test_value);

	try
	{
		empty_list.InsertBefore(test_value, fake_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert before no match test ";

	return pass;
}

bool test_default_ctor_complex()
{
	bool pass = true;
	Node<string> * default_head = nullptr;
	Node<string> * default_tail = nullptr;


	List<string> list_test;

	if (list_test.getHead() != default_head)
		pass = false;

	if (list_test.getTail() != default_tail)
		pass = false;

	cout << "Default ctor test complex ";

	return pass;
}

bool test_copy_ctor_complex()
{
	bool pass = true;

	List<string> test_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		test_list.Append(NAMES[i]);

	List<string> list_test(test_list);

	// Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (list_test.First() != test_list.First())
			pass = false;
		list_test.Extract(NAMES[i]); //Remove first value
		test_list.Extract(NAMES[i]);
	}

	cout << "Copy ctor test complex ";

	return pass;
}

bool test_move_ctor_complex()
{
	bool pass = true;

	List<string> test_list(ReturnStrList());

	// Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (NAMES[i] != test_list.First())
			pass = false;
		test_list.Extract(NAMES[i]); //Remove first value
	}

	cout << "Move ctor test complex ";

	return pass;
}

bool test_op_equal_complex()
{
	bool pass = true;

	List<string> test_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		test_list.Append(NAMES[i]);

	List<string> list_test;
	list_test = test_list; //Op =

	 // Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (list_test.First() != test_list.First())
			pass = false;
		list_test.Extract(NAMES[i]); //Remove first value
		test_list.Extract(NAMES[i]);
	}

	cout << "Op equals test complex ";

	return pass;
}

bool test_move_op_equal_complex()
{
	bool pass = true;

	List<string> test_list;
	test_list = ReturnStrList(); //Op =

	 // Check data integrity
	for (int i = 0; i < NUM_NAMES; ++i)
	{
		if (NAMES[i] != test_list.First())
			pass = false;
		test_list.Extract(NAMES[i]); //Remove first value
	}

	cout << "Move op equals test complex ";

	return pass;
}

bool test_is_empty_complex()
{
	bool pass = true;

	List<string> full_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		full_list.Append(NAMES[i]);

	List<string> empty_list;

	if (full_list.isEmpty())
		pass = false;

	if (!empty_list.isEmpty())
		pass = false;

	cout << "isEmpty test complex ";

	return pass;
}

bool test_first_with_value_complex()
{
	bool pass = false;

	List<string> full_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		full_list.Append(NAMES[i]);

	if (full_list.First() == NAMES[0])
		pass = true;

	cout << "First with value test complex ";

	return pass;
}

bool test_first_empty_list_complex()
{
	bool pass = false;

	List<string> empty_list;

	try
	{
		empty_list.First();
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "First with empty list test complex ";

	return pass;
}

bool test_last_with_value_complex()
{
	bool pass = false;

	List<string> full_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		full_list.Append(NAMES[i]);

	if (full_list.Last() == NAMES[NUM_NAMES - 1])
		pass = true;

	cout << "Last with value test complex ";

	return pass;
}

bool test_last_empty_list_complex()
{
	bool pass = false;

	List<string> empty_list;

	try
	{
		empty_list.Last();
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Last with empty list test complex ";

	return pass;
}

bool test_prepend_complex()
{
	bool pass = true;
	string init_value = "Person";
	string next_value = "Dog";

	List<string> test_list;

	// Prepend empty list
	test_list.Prepend(init_value);
	if (test_list.First() != init_value || test_list.Last() != init_value)
		pass = false;

	// Prepend list with existing values
	test_list.Prepend(next_value);
	if (test_list.First() != next_value || test_list.Last() != init_value)
		pass = false;

	cout << "Prepend test complex ";

	return pass;
}

bool test_append_complex()
{
	bool pass = true;
	string init_value = "Person";
	string next_value = "Dog";

	List<string> test_list;

	// Append empty list
	test_list.Append(init_value);
	if (test_list.First() != init_value || test_list.Last() != init_value)
		pass = false;

	// Append list with existing values
	test_list.Append(next_value);
	if (test_list.First() != init_value || test_list.Last() != next_value)
		pass = false;

	cout << "Append test complex ";

	return pass;
}

bool test_purge_complex()
{
	bool pass = true;

	List<string> full_list;
	for (int i = 0; i < NUM_NAMES; ++i)
		full_list.Append(NAMES[i]);

	full_list.Purge();
	if (full_list.getHead() || full_list.getTail())
		pass = false;

	cout << "Purge test complex ";

	return pass;
}

bool test_extract_empty_complex()
{
	bool pass = false;
	string test_value = "Person";

	List<string> empty_list;

	try
	{
		empty_list.Extract(test_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Extract empty list test complex ";

	return pass;
}

bool test_extract_match_complex()
{
	bool pass = true;

	List<string> test_list;
	for (int i = 0; i < NUM_EXTRACT; ++i)
		test_list.Append(NAMES[i]);

	// List should have Kyle Brit Seth Alex
	test_list.Extract("Seth"); // Test extract from middle
	if (test_list.First() != "Kyle" || test_list.Last() != "Alex")
		pass = false;

	// List should have Kyle Brit Alex
	test_list.Extract("Kyle"); // Test extract from front of list
	if (test_list.First() != "Brit" || test_list.Last() != "Alex")
		pass = false;

	// List should have Brit Alex
	test_list.Extract("Alex"); // Test extract from back of list
	if (test_list.First() != "Brit" || test_list.Last() != "Brit")
		pass = false;

	// List should have Brit
	test_list.Extract("Brit"); // Test extract from list with 1 node
	if (test_list.getHead() || test_list.getTail())
		pass = false;

	cout << "Extract match test complex ";

	return pass;
}

bool test_extract_no_match_complex()
{
	bool pass = false;
	string test_value = "Person";
	string fake_value = "Dog";

	List<string> empty_list;

	empty_list.Append(test_value);

	try
	{
		empty_list.Extract(fake_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Extract no match test complex ";

	return pass;
}

bool test_inserta_empty_complex()
{
	bool pass = false;
	string test_value = "Person";
	string search_value = "Dog";

	List<string> empty_list;

	try
	{
		empty_list.InsertAfter(test_value, search_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert after empty list test complex ";

	return pass;
}

bool test_inserta_match_complex()
{
	bool pass = true;
	string init_value = "Kyle";
	string first_new_value = "Seth";
	string second_new_value = "Brit";

	List<string> test_list;
	test_list.Append(init_value);

	// Test insert to end of list
	test_list.InsertAfter(first_new_value, init_value);

	// Test insert to middle of list
	test_list.InsertAfter(second_new_value, init_value);

	// List should contain Kyle Brit Seth
	if (test_list.Last() != first_new_value)
		pass = false;

	test_list.Extract(first_new_value);
	// List should contain Kyle Brit
	if (test_list.Last() != second_new_value)
		pass = false;

	cout << "Insert after match test complex ";

	return pass;
}

bool test_inserta_no_match_complex()
{
	bool pass = false;
	string test_value = "Person";
	string fake_value = "Dog";

	List<string> empty_list;
	empty_list.Append(test_value);

	try
	{
		empty_list.InsertAfter(test_value, fake_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert after no match test complex ";

	return pass;
}

bool test_insertb_empty_complex()
{
	bool pass = false;
	string test_value = "Person";
	string search_value = "Dog";

	List<string> empty_list;

	try
	{
		empty_list.InsertBefore(test_value, search_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert before empty list test complex ";

	return pass;
}

bool test_insertb_match_complex()
{
	bool pass = true;
	string init_value = "Seth";
	string first_new_value = "Kyle";
	string second_new_value = "Brit";

	List<string> test_list;
	test_list.Prepend(init_value);

	// Test insert to start of list
	test_list.InsertBefore(first_new_value, init_value);

	// Test insert to middle of list
	test_list.InsertBefore(second_new_value, init_value);

	// List should contain Kyle Brit Seth
	if (test_list.First() != first_new_value)
		pass = false;

	test_list.Extract(first_new_value);
	// List should contain Brit Seth
	if (test_list.First() != second_new_value)
		pass = false;

	cout << "Insert before match test complex ";

	return pass;
}

bool test_insertb_no_match_complex()
{
	bool pass = false;
	string test_value = "Person";
	string fake_value = "Dog";

	List<string> empty_list;
	empty_list.Append(test_value);

	try
	{
		empty_list.InsertBefore(test_value, fake_value);
	}
	catch (Exception &exception)
	{
		exception.GetMessage();
		pass = true;
	}

	cout << "Insert before no match test complex ";

	return pass;
}

List<int> ReturnIntList()
{
	List<int> tempList;
	for (int i = 0; i < NUM_SIZE; ++i)
		tempList.Append(i);
	return tempList;
}

List<string> ReturnStrList()
{
	List<string> tempList;
	for (int i = 0; i < NUM_NAMES; ++i)
		tempList.Append(NAMES[i]);
	return tempList;
}