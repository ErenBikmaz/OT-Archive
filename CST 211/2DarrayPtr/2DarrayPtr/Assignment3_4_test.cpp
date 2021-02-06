#define _CRTDBG_MAP_ALLOC

typedef bool(*FunctionPointer)();  // Define a funtion pointer type

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;

#include <crtdbg.h>
#include <conio.h>
#include "Array2D.h"
#include "Exception.h"

// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };

const int NUM_NAMES = 15;

// Test function declaration
bool test_neg_row();
bool test_neg_col();
bool test_upper_bounds_row();
bool test_upper_bounds_col(); 
bool test_default_ctor();
bool test_2_arg_ctor();
bool test_set_row();
bool test_set_col();
bool test_add_data();
bool test_copy_ctor(); 
bool test_op_eql(); 
bool test_increase_rows_with_data(); 
bool test_decrease_rows_with_data(); 
bool test_increase_cols_with_data();
bool test_decrease_cols_with_data(); 
bool test_neg_row_complex();
bool test_neg_col_complex();
bool test_upper_bounds_row_complex();
bool test_upper_bounds_col_complex();
bool test_default_ctor_complex();
bool test_2_arg_ctor_complex();
bool test_set_row_complex();
bool test_set_col_complex();
bool test_add_data_complex();
bool test_copy_ctor_complex();
bool test_op_eql_complex();
bool test_increase_rows_with_data_complex();
bool test_decrease_rows_with_data_complex();
bool test_increase_cols_with_data_complex();
bool test_decrease_cols_with_data_complex();


// Array of test functions
FunctionPointer test_functions[] = {test_neg_row, test_neg_col, test_upper_bounds_row, test_upper_bounds_col,
									test_default_ctor, test_2_arg_ctor, test_set_row, test_set_col,
									test_add_data, test_copy_ctor, test_op_eql, test_increase_rows_with_data,
									test_decrease_rows_with_data, test_increase_cols_with_data, test_decrease_cols_with_data,
									test_neg_row_complex, test_neg_col_complex, test_upper_bounds_row_complex ,
									test_upper_bounds_col_complex, test_default_ctor_complex,
									test_2_arg_ctor_complex, test_set_row_complex, test_set_col_complex,
									test_add_data_complex, test_copy_ctor_complex, test_op_eql_complex, test_increase_rows_with_data_complex,
									test_decrease_rows_with_data_complex, test_increase_cols_with_data_complex, test_decrease_cols_with_data_complex };

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

bool test_neg_row()
{
	bool pass = false;

	Array2D<int> val_len(5, 10);

	try
	{
		val_len[-1][5] = 0;
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Negative row test ";

	return pass;
}

bool test_neg_col()
{
	bool pass = false;

	Array2D<int> val_len(5, 10);

	try
	{
		val_len[1][-1] = 0;
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Negative column test ";

	return pass;
}

bool test_upper_bounds_row()
{
	bool pass = false;

	Array2D<int> val_len(5, 10);

	try
	{
		val_len[10][5] = 0;
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Upper bounds row test ";

	return pass;
}

bool test_upper_bounds_col()
{
	bool pass = false;

	Array2D<int> val_len(5, 10);

	try
	{
		val_len[1][20] = 0;
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Upper bounds column test ";

	return pass;
}

bool test_default_ctor()
{
	bool pass = true;
	int default_row = 0;
	int default_col = 0;

	Array2D<int> val_len;

	if (val_len.getRow() != default_row)
		pass = false; 

	if (val_len.getColumns() != default_col)
		pass = false;

	cout << "Default ctor test ";

	return pass;
}


bool test_2_arg_ctor()
{
	bool pass = true;
	int row = 5;
	int col = 10;

	Array2D<int> val_len(row, col);

	if (val_len.getRow() != row)
		pass = false;

	if (val_len.getColumns() != col)
		pass = false;

	cout << "2 arg ctor test ";

	return pass;
}

bool test_set_row()
{
	bool pass = true;
	int new_row_val = 15;

	Array2D<int> val_len(3, 5);

	val_len.setRows(new_row_val);

	if (val_len.getRow() != new_row_val)
		pass = false;

	cout << "set row test ";

	return pass;
}

bool test_set_col()
{
	bool pass = true;
	int new_col_val = 15;

	Array2D<int> val_len(3, 5);

	val_len.setColumns(new_col_val);

	if (val_len.getColumns() != new_col_val)
		pass = false;

	cout << "set col test ";

	return pass;
}

bool test_add_data()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0; 
	int temp = 0;

	int num_elements = 15;

	int test_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	Array2D<int> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
		{
			for ( int j (0); j < val_len.getColumns(); j++ )
			val_len[i][j] = num++;
		}

	num = 0; 

	for (int i(0); i < val_len.getRow() && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != test_data[num++])
				pass = false;
		}
	}

	cout << "Adding data test ";

	return pass;
}

bool test_copy_ctor()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	int temp = 0;

	int num_elements = 15;

	int test_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	Array2D<int> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = num++;
	}

	Array2D<int> val_len_cpy(val_len);

	num = 0;

	for (int i(0); i < val_len_cpy.getRow() && pass; i++)
	{
		for (int j(0); j < val_len_cpy.getColumns() && pass; j++)
		{
			temp = val_len_cpy[i][j];

			if (temp != test_data[num++])
				pass = false;
		}
	}

	cout << "Copy ctor test ";

	return pass;
}

bool test_op_eql()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	int temp = 0;

	int num_elements = 15;

	int test_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	Array2D<int> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = num++;
	}

	Array2D<int> val_len_cpy;

	val_len_cpy = val_len;

	num = 0;

	for (int i(0); i < val_len_cpy.getRow() && pass; i++)
	{
		for (int j(0); j < val_len_cpy.getColumns() && pass; j++)
		{
			temp = val_len_cpy[i][j];

			if (temp != test_data[num++])
				pass = false;
		}
	}

	cout << "Op eql test ";

	return pass;
}

bool test_increase_rows_with_data()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	int temp = 0;
	int new_row = 10; 

	int num_elements = 15;

	int test_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	Array2D<int> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = num++;
	}

	val_len.setRows(new_row);
	
	num = 0;

	for (int i(0); i < row && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != test_data[num++])
				pass = false;
		}
	}

	// Test the newly added rows (should be garbage or 0)
	for (int i(row); i < val_len.getRow() && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp > 0)
				pass = false;
		}
	}

	cout << "Increase rows with data test ";

	return pass;
}

bool test_decrease_rows_with_data()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	int temp = 0;
	int new_row = 1;

	int num_elements = 15;

	int test_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	Array2D<int> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = num++;
	}

	val_len.setRows(new_row);

	num = 0;

	for (int i(0); i < val_len.getRow() && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != test_data[num++])
				pass = false;
		}
	}

	cout << "Decrease rows with data test ";

	return pass;
}

bool test_increase_cols_with_data()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	int temp = 0;
	int new_col = 10;

	int num_elements = 15;

	int test_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	Array2D<int> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = num++;
	}

	val_len.setColumns(new_col);

	num = 0;

	for (int i(0); i < row && pass; i++)
	{
		for (int j(0); j < col && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != test_data[num++])
				pass = false;
		}
	}

	// Test the newly added columns (should be garbage or 0)
	for (int i(row); i < val_len.getRow() && pass; i++)
	{
		for (int j(col); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp > 0)
				pass = false;
		}
	}

	cout << "Increase cols with data test ";

	return pass;
}

bool test_decrease_cols_with_data()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	int temp = 0;
	int new_col = 2;

	int num_elements = 15;

	int test_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	Array2D<int> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = num++;
	}

	val_len.setColumns(new_col);

	num = 0;

	for (int i(0); i < row && pass; i++)
	{
		for (int j(0); j < new_col && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != test_data[num++])
				pass = false;
		}
		num += 3; // Account for the numbers missed after removing columns
	}

	cout << "Decrease cols with data test ";

	return pass;
}

////////////////////////////////////////////
// Complex data type tests
////////////////////////////////////////////

bool test_neg_row_complex()
{
	bool pass = false;

	Array2D<string> val_len(5, 10);

	try
	{
		val_len[-1][5] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Negative row test complex ";

	return pass;
}

bool test_neg_col_complex()
{
	bool pass = false;

	Array2D<string> val_len(5, 10);

	try
	{
		val_len[1][-1] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Negative column test complex ";

	return pass;
}

bool test_upper_bounds_row_complex()
{
	bool pass = false;

	Array2D<string> val_len(5, 10);

	try
	{
		val_len[10][5] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Upper bounds row test complex ";

	return pass;
}

bool test_upper_bounds_col_complex()
{
	bool pass = false;

	Array2D<string> val_len(5, 10);

	try
	{
		val_len[1][20] = "test";
	}
	catch (Exception &exception)
	{
		pass = true;
	}

	cout << "Upper bounds column test complex ";

	return pass;
}

bool test_default_ctor_complex()
{
	bool pass = true;
	int default_row = 0;
	int default_col = 0;

	Array2D<string> val_len;

	if (val_len.getRow() != default_row)
		pass = false;

	if (val_len.getColumns() != default_col)
		pass = false;

	cout << "Default ctor test complex ";

	return pass;
}

bool test_2_arg_ctor_complex()
{
	bool pass = true;
	int row = 5;
	int col = 10;

	Array2D<string> val_len(row, col);

	if (val_len.getRow() != row)
		pass = false;

	if (val_len.getColumns() != col)
		pass = false;

	cout << "2 arg ctor test complex ";

	return pass;
}

bool test_set_row_complex()
{
	bool pass = true;
	int new_row_val = 15;

	Array2D<string> val_len(3, 5);

	val_len.setRows(new_row_val);

	if (val_len.getRow() != new_row_val)
		pass = false;

	cout << "set row test complex ";

	return pass;
}

bool test_set_col_complex()
{
	bool pass = true;
	int new_col_val = 15;

	Array2D<string> val_len(3, 5);

	val_len.setColumns(new_col_val);

	if (val_len.getColumns() != new_col_val)
		pass = false;

	cout << "set col test complex ";

	return pass;
}

bool test_add_data_complex()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	string temp;

	Array2D<string> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = NAMES[num++];
	}

	num = 0;

	for (int i(0); i < val_len.getRow() && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != NAMES[num++])
				pass = false;
		}
	}

	cout << "Adding data test complex ";

	return pass;
}

bool test_copy_ctor_complex()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	string temp;

	Array2D<string> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = NAMES[num++];
	}

	Array2D<string> val_len_cpy(val_len);

	num = 0;

	for (int i(0); i < val_len_cpy.getRow() && pass; i++)
	{
		for (int j(0); j < val_len_cpy.getColumns() && pass; j++)
		{
			temp = val_len_cpy[i][j];

			if (temp != NAMES[num++])
				pass = false;
		}
	}

	cout << "Copy ctor test complex ";

	return pass;
}

bool test_op_eql_complex()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	string temp;

	Array2D<string> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = NAMES[num++];
	}

	Array2D<string> val_len_cpy;

	val_len_cpy = val_len;

	num = 0;

	for (int i(0); i < val_len_cpy.getRow() && pass; i++)
	{
		for (int j(0); j < val_len_cpy.getColumns() && pass; j++)
		{
			temp = val_len_cpy[i][j];

			if (temp != NAMES[num++])
				pass = false;
		}
	}

	cout << "Op eql test complex ";

	return pass;
}

bool test_increase_rows_with_data_complex()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	string temp;
	int new_row = 10;

	Array2D<string> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = NAMES[num++];
	}

	val_len.setRows(new_row);

	num = 0;

	for (int i(0); i < row && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != NAMES[num++])
				pass = false;
		}
	}

	// Test the newly added rows (should be garbage or 0)
	for (int i(row); i < val_len.getRow() && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];
			if (temp != "")
				pass = false;
		}
	}

	cout << "Increase rows with data test complex ";

	return pass;
}

bool test_decrease_rows_with_data_complex()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	string temp;
	int new_row = 1;

	Array2D<string> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = NAMES[num++];
	}

	val_len.setRows(new_row);

	num = 0;

	for (int i(0); i < val_len.getRow() && pass; i++)
	{
		for (int j(0); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != NAMES[num++])
				pass = false;
		}
	}

	cout << "Decrease rows with data test complex ";

	return pass;
}

bool test_increase_cols_with_data_complex()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	string temp;
	int new_col = 10;

	Array2D<string> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = NAMES[num++];
	}

	val_len.setColumns(new_col);

	num = 0;

	for (int i(0); i < row && pass; i++)
	{
		for (int j(0); j < col && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != NAMES[num++])
				pass = false;
		}
	}

	// Test the newly added columns (should be garbage or 0)
	for (int i(row); i < val_len.getRow() && pass; i++)
	{
		for (int j(col); j < val_len.getColumns() && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != "")
				pass = false;
		}
	}

	cout << "Increase cols with data test complex ";

	return pass;
}

bool test_decrease_cols_with_data_complex()
{
	bool pass = true;
	int row = 3;
	int col = 5;
	int num = 0;
	string temp;
	int new_col = 2;

	Array2D<string> val_len(row, col);

	for (int i(0); i < val_len.getRow(); i++)
	{
		for (int j(0); j < val_len.getColumns(); j++)
			val_len[i][j] = NAMES[num++];
	}

	val_len.setColumns(new_col);

	num = 0;

	for (int i(0); i < row && pass; i++)
	{
		for (int j(0); j < new_col && pass; j++)
		{
			temp = val_len[i][j];

			if (temp != NAMES[num++])
				pass = false;
		}
		num += 3; // Account for the numbers missed after removing columns
	}

	cout << "Decrease cols with data test complex ";

	return pass;
}