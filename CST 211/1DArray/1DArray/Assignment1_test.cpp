/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Assignment1_test.cpp
* Date Created:   1/7/19
**************************************************************/
#define _CRTDBG_MAP_ALLOC
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
#include "Array.h"
#include "Exception.h"

// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "Seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

// Test function declaration
bool test_neg_length();
bool test_lower_bounds();
bool test_upper_bounds();
bool test_2_arg_ctor();
bool test_1_arg_ctor();
bool test_default_ctor();
bool test_set_pos_start_index();
bool test_set_neg_start_index();
bool test_adding_values();
bool test_larger_length_with_data();
bool test_smaller_length_with_data();
bool test_set_start_index_with_data();
bool test_copy_ctor();
bool test_op_eql();
bool test_neg_length_complex();
bool test_lower_bounds_complex();
bool test_upper_bounds_complex();
bool test_2_arg_ctor_complex();
bool test_1_arg_ctor_complex();
bool test_default_ctor_complex();
bool test_set_pos_start_index_complex();
bool test_set_neg_start_index_complex();
bool test_adding_values_complex();
bool test_larger_length_with_data_complex();
bool test_smaller_length_with_data_complex();
bool test_set_start_index_with_data_complex();
bool test_copy_ctor_complex();
bool test_op_eql_complex();

// Array of test functions
FunctionPointer test_functions[] = {test_neg_length, test_lower_bounds, test_upper_bounds, 
									test_2_arg_ctor, test_1_arg_ctor, test_default_ctor,
									test_set_pos_start_index, test_set_neg_start_index, 
									test_adding_values, test_larger_length_with_data, 
									test_smaller_length_with_data, test_set_start_index_with_data,
									test_copy_ctor, test_op_eql, test_neg_length_complex, 
									test_lower_bounds_complex, test_upper_bounds_complex,
									test_2_arg_ctor_complex, test_1_arg_ctor_complex, test_default_ctor_complex,
									test_set_pos_start_index_complex, test_set_neg_start_index_complex,
									test_adding_values_complex, test_larger_length_with_data_complex,
									test_smaller_length_with_data_complex, test_set_start_index_with_data_complex,
									test_copy_ctor_complex, test_op_eql_complex };

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

bool test_neg_length()
{
	// Exception should be thrown for negative number
	bool pass = false;

	Array<int> val_len(20, 0);

	try
	{
		val_len.SetLength(-5);
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Negative length test ";

	return pass;
}

bool test_lower_bounds()
{
	bool pass = false;

	Array<int> val_len(20, 0);

	try
	{
		val_len[-3] = 0;
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Lower bounds test ";

	return pass;
}

bool test_upper_bounds()
{
	bool pass = false;

	Array<int> val_len(20, 0);

	try
	{
		val_len[30] = 0;
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Upper bounds test ";

	return pass;
}

bool test_2_arg_ctor()
{
	bool pass = true;
	int length = 15; 
	int start_index = 3;


	Array<int> val_len(length, start_index);

	if (val_len.GetLength() != length)
		pass = false;

	if (val_len.GetStartIndex() != start_index)
		pass = false;

	cout << "2 arg ctor test ";

	return pass;
}

bool test_1_arg_ctor()
{
	bool pass = true;
	int length = 15;
	int default_start_index = 0;


	Array<int> val_len(length);

	if (val_len.GetLength() != length)
		pass = false;

	if (val_len.GetStartIndex() != default_start_index)
		pass = false;

	cout << "1 arg ctor test ";

	return pass;
}

bool test_default_ctor()
{
	bool pass = true;
	int default_length = 0;
	int default_start_index = 0;


	Array<int> val_len;

	if (val_len.GetLength() != default_length)
		pass = false;

	if (val_len.GetStartIndex() != default_start_index)
		pass = false;

	cout << "Default ctor test ";

	return pass;
}

bool test_set_pos_start_index()
{
	bool pass = true;
	int start_index = 6;


	Array<int> val_len(10, 5);

	val_len.SetStartIndex(start_index);

	if (val_len.GetStartIndex() != start_index)
		pass = false;

	cout << "Pos start index test ";

	return pass;
}

bool test_set_neg_start_index()
{
	bool pass = true;
	int start_index = -6;


	Array<int> val_len(10, 5);

	val_len.SetStartIndex(start_index);

	if (val_len.GetStartIndex() != start_index)
		pass = false;

	cout << "Neg start index test ";

	return pass;
}

bool test_adding_values()
{
	bool pass = true;
	int temp;

	int num_elements = 10;  // Change this if test data changes
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	Array<int> val_len(10);

	for (int i = 0; i < num_elements; ++i)
		val_len[i] = test_data[i];

	for (int i = 0; i < num_elements && pass; ++i)
	{
		temp = val_len[i];

		if (temp != test_data[i])
			pass = false;
	}

	cout << "Add values test ";

	return pass;
}

bool test_larger_length_with_data()
{
	bool pass = true;
	int temp;

	int new_length = 20;
	int num_elements = 10;  // Change this if test data changes
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	Array<int> val_len(10);

	for (int i = 0; i < num_elements; ++i)
		val_len[i] = test_data[i];

	val_len.SetLength(new_length);  // Double the length after data was assigned

	// First 10 should match
	for (int i = 0; i < num_elements && pass; ++i)
	{
		temp = val_len[i];

		if (temp != test_data[i])
			pass = false;
	}

	// Last 10 should be garbage (negative number) or 0
	for (int i = 10; i < new_length && pass; ++i)
	{
		temp = val_len[i];

		if (temp > 0)
			pass = false;
	}

	cout << "Change larger length with data test ";

	return pass;
}

bool test_smaller_length_with_data()
{
	bool pass = true;
	int temp;
	int new_length = 8;

	int num_elements = 10;  // Change this if test data changes
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	Array<int> val_len(10);

	for (int i = 0; i < num_elements; ++i)
		val_len[i] = test_data[i];

	val_len.SetLength(new_length);

	// First 8 should match
	for (int i = 0; i < new_length && pass; ++i)
	{
		temp = val_len[i];

		if (temp != test_data[i])
			pass = false;
	}

	cout << "Change smaller length with data test ";

	return pass;
}

bool test_set_start_index_with_data()
{
	bool pass = true;
	int temp;
	int new_start_index = 8;

	int num_elements = 10;  // Change this if test data changes
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	Array<int> val_len(10);

	for (int i = 0; i < num_elements; ++i)
		val_len[i] = test_data[i];

	val_len.SetStartIndex(new_start_index);

	// Check data integrity
	for (int i = 0; i < num_elements && pass; ++i)
	{
		temp = val_len[i + new_start_index];

		if (temp != test_data[i])
			pass = false;
	}

	cout << "Set start index with data test ";

	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;

	int num_elements = 10;  // Change this if test data changes
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	Array<int> val_len(10);

	for (int i = 0; i < num_elements; ++i)
		val_len[i] = test_data[i];

	Array<int> val_len_cpy(val_len);

	// Check data integrity
	for (int i = 0; i < num_elements && pass; ++i)
	{	
		if (val_len_cpy[i] != test_data[i])
			pass = false;
	}

	cout << "Copy ctor test ";

	return pass;
}

bool test_op_eql()
{
	bool pass = true;

	int num_elements = 10;  // Change this if test data changes
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	Array<int> val_len(10);

	for (int i = 0; i < num_elements; ++i)
		val_len[i] = test_data[i];

	Array<int> val_len_cpy;

	val_len_cpy = val_len;

	// Check data integrity
	for (int i = 0; i < num_elements && pass; ++i)
	{
		if (val_len_cpy[i] != test_data[i])
			pass = false;
	}

	cout << "Op equal test ";

	return pass;
}

////////////////////////////////////////////
// Complex data type tests
////////////////////////////////////////////

bool test_neg_length_complex()
{
	// Exception should be thrown for negative number
	bool pass = false;

	Array<string> val_len(20, 0);

	try
	{
		val_len.SetLength(-5);
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Negative length test complex ";

	return pass;
}

bool test_lower_bounds_complex()
{
	bool pass = false;

	Array<string> val_len(20, 0);

	try
	{
		val_len[-3] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Lower bounds test complex ";

	return pass;
}

bool test_upper_bounds_complex()
{
	bool pass = false;

	Array<string> val_len(20, 0);

	try
	{
		val_len[30] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Upper bounds test complex ";

	return pass;
}

bool test_2_arg_ctor_complex()
{
	bool pass = true;
	int length = 15;
	int start_index = 3;


	Array<string> val_len(length, start_index);

	if (val_len.GetLength() != length)
		pass = false;

	if (val_len.GetStartIndex() != start_index)
		pass = false;

	cout << "2 arg ctor test complex ";

	return pass;
}

bool test_1_arg_ctor_complex()
{
	bool pass = true;
	int length = 15;
	int default_start_index = 0;


	Array<string> val_len(length);

	if (val_len.GetLength() != length)
		pass = false;

	if (val_len.GetStartIndex() != default_start_index)
		pass = false;

	cout << "1 arg ctor test complex ";

	return pass;
}

bool test_default_ctor_complex()
{
	bool pass = true;
	int default_length = 0;
	int default_start_index = 0;


	Array<string> val_len;

	if (val_len.GetLength() != default_length)
		pass = false;

	if (val_len.GetStartIndex() != default_start_index)
		pass = false;

	cout << "Default ctor test complex ";

	return pass;
}

bool test_set_pos_start_index_complex()
{
	bool pass = true;
	int start_index = 6;


	Array<string> val_len(10, 5);

	val_len.SetStartIndex(start_index);

	if (val_len.GetStartIndex() != start_index)
		pass = false;

	cout << "Pos start index test complex ";

	return pass;
}

bool test_set_neg_start_index_complex()
{
	bool pass = true;
	int start_index = -6;


	Array<string> val_len(10, 5);

	val_len.SetStartIndex(start_index);

	if (val_len.GetStartIndex() != start_index)
		pass = false;

	cout << "Neg start index test complex ";

	return pass;
}

bool test_adding_values_complex()
{
	bool pass = true;
	string temp;

	Array<string> val_len(15);

	for (int i = 0; i < NUM_NAMES; ++i)
		val_len[i] = NAMES[i];

	for (int i = 0; i < NUM_NAMES && pass; ++i)
	{
		temp = val_len[i];

		if (temp != NAMES[i])
			pass = false;
	}

	cout << "Add values test complex ";

	return pass;
}

bool test_larger_length_with_data_complex()
{
	bool pass = true;
	string temp;

	int new_length = 20;

	Array<string> val_len(15);

	for (int i = 0; i < NUM_NAMES; ++i)
		val_len[i] = NAMES[i];

	val_len.SetLength(new_length);  // Double the length after data was assigned

	// First 15 should match
	for (int i = 0; i < NUM_NAMES && pass; ++i)
	{
		temp = val_len[i];

		if (temp != NAMES[i])
			pass = false;
	}

	// Last 5 should be empty strings
	for (int i = 15; i < new_length && pass; ++i)
	{
		temp = val_len[i];

		if (temp != "")
			pass = false;
	}

	cout << "Change larger length with data test complex ";

	return pass;
}

bool test_smaller_length_with_data_complex()
{
	bool pass = true;
	string temp;
	int new_length = 8;

	Array<string> val_len(15);

	for (int i = 0; i < NUM_NAMES; ++i)
		val_len[i] = NAMES[i];

	val_len.SetLength(new_length);

	// First 8 should match
	for (int i = 0; i < new_length && pass; ++i)
	{
		temp = val_len[i];

		if (temp != NAMES[i])
			pass = false;
	}

	cout << "Change smaller length with data test complex ";

	return pass;
}

bool test_set_start_index_with_data_complex()
{
	bool pass = true;
	string temp;
	int new_start_index = 8;

	Array<string> val_len(15);

	for (int i = 0; i < NUM_NAMES; ++i)
		val_len[i] = NAMES[i];

	val_len.SetStartIndex(new_start_index);

	// Check data integrity
	for (int i = 0; i < NUM_NAMES && pass; ++i)
	{
		temp = val_len[i + new_start_index];

		if (temp != NAMES[i])
			pass = false;
	}

	cout << "Set start index with data test complex ";

	return pass;
}

bool test_copy_ctor_complex()
{
	bool pass = true;

	Array<string> val_len(15);

	for (int i = 0; i < NUM_NAMES; ++i)
		val_len[i] = NAMES[i];

	Array<string> val_len_cpy(val_len);

	// Check data integrity
	for (int i = 0; i < NUM_NAMES && pass; ++i)
	{
		if (val_len_cpy[i] != NAMES[i])
			pass = false;
	}

	cout << "Copy ctor test complex ";

	return pass;
}

bool test_op_eql_complex()
{
	bool pass = true;

	Array<string> val_len(15);

	for (int i = 0; i < NUM_NAMES; ++i)
		val_len[i] = NAMES[i];

	Array<string> val_len_cpy;

	val_len_cpy = val_len;

	// Check data integrity
	for (int i = 0; i < NUM_NAMES && pass; ++i)
	{
		if (val_len_cpy[i] != NAMES[i])
			pass = false;
	}

	cout << "Op equal test complex ";

	return pass;
}