/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Array2D.h
* Date Created:   1/12/20
* Modifications:  
*	1/13/20 - Header outline and documentation
*	1/14/20 - Implementation and testing
*	1/16/20 - converted to pointer-type
*	1/17/20 - finalized pointer conversion
**************************************************************/
/************************************************************************
* Class: Array 2D
*
* Purpose: Store and manage a 2D dynamic array of objects.
*	
*
* Stipulations:
*	Make sure the user never goes out of bounds. If they do, throw an exception.
*	Use your Exception class to throw if they do go out of bounds.
*	Modify the class so that the subscript operators can be called from const objects. Hint: You can only call const methods from const objects.
*	Don�t forget that because there is now dynamic memory allocation, you will need the move constructor and move operator =.
*
* Manager functions:	
*	Array2D(int rows, int columns);
*	Array2D(const Array2D& copy);
*	Array2D& operator =(const Array2D& copy);
*	~Array2D();
*	
*
* Methods:
*	Row<T> operator [] (int index);
*
*	int getRows() const;
*	int getColumns() const;
*	void setRows(int rows);
*	void setColumns(int columns);
*
*	T & Select(int desired_row, int desired_column) const;
*
*
*************************************************************************/
#pragma once

#include "Row.h"
#include "Exception.h"

template <class T>class Array2D
{
public:

	Array2D(int rows = 0, int columns = 0);
	Array2D(const Array2D & copy);
	Array2D(Array2D && move);
	Array2D& operator =(const Array2D & copy); 
	Array2D& operator =(Array2D && move);
	~Array2D();
	void Purge();

	Row<T> operator [] (int row);

	int getRow() const;
	int getColumns() const;
	void setRows(int rows);
	void setColumns(int columns);

	T & Select(int desired_row, int desired_column) const;

private:

	T ** m_array;
	int m_rows;
	int m_columns;
};

/**********************************************************************
* Purpose: 2-arg constructor
*
* Precondition: Array2D is created with 2 inputs supplied
*
* Postcondition: Array2D is created with given values
*
************************************************************************/
template<class T>
inline Array2D<T>::Array2D(int rows, int columns)
	: m_rows(rows), m_columns(columns)
{
	//intialize 2D array
	m_array = new T * [rows];

	//intialize each row
	for (int i = 0; i < rows; i++)
	{
		m_array[i] = new T[columns];
	}
	
}

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: Array2D is created given another Array2D
*
* Postcondition: new Array2D is created, identical to the one provided
*
************************************************************************/
template<class T>
inline Array2D<T>::Array2D(const Array2D& copy)
	: m_rows(copy.m_rows), m_columns(copy.m_columns), m_array(nullptr)
{	//deep copy data to new object

	//check data is valid
	if (&copy.m_array != nullptr)
	{
		//intialize 2D array
		m_array = new T * [m_rows];
		//intialize each row and copy data
		for (int i = 0; i < m_rows; i++)
		{
			//instantiate each row
			m_array[i] = new T[m_columns];

			//copy data of each row
			for (int j = 0; j < m_columns; j++)
			{
				m_array[i][j] = copy.m_array[i][j];
			}

		}
	}
}

/**********************************************************************
* Purpose: Move Constructor
*
* Precondition: Array2D is created given another Array2D
*
* Postcondition: a new Array2D is created, and the Array2D provided is reset
*
************************************************************************/
template<class T>
inline Array2D<T>::Array2D(Array2D && move)
	: m_rows(move.m_rows), m_columns(move.m_columns), m_array(nullptr)
{
	if (move.m_array != nullptr)
	{
		//assign to lhs
		m_array = move.m_array;
		m_rows = move.m_rows;
		m_columns = move.m_columns;
		//reset rhs
		move.m_array = nullptr;
		move.m_rows = 0;
		move.m_columns = 0;

	}
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: Array2D's data is set equal to by that of another
*
* Postcondition: Array2D's data is overwritten by that of another
*
************************************************************************/
template<class T>
inline Array2D<T> & Array2D<T>::operator=(const Array2D& copy)
{
	//check for self assignment
	if (this != &copy)
	{
		//check data is valid
		if (&copy.m_array != nullptr)
		{
			//dispose old data
			Purge();

			//copy new data
			m_rows = copy.m_rows;
			m_columns = copy.m_columns;
			//intialize 2D array
			m_array = new T * [m_rows];
			//intialize each row and copy data
			for (int i = 0; i < m_rows; i++)
			{
				//instantiate each row
				m_array[i] = new T[m_columns];

				//copy data of each row
				for (int j = 0; j < m_columns; j++)
				{
					m_array[i][j] = copy.m_array[i][j];
				}

			}
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: move assignment operator
*
* Precondition: An Array2D's data is set equal to by that of another
*
* Postcondition: An Array2D's data is overwritten by that of another , which is also reset
*
************************************************************************/
template<class T>
inline Array2D<T> & Array2D<T>::operator=(Array2D&& move)
{
	if (this != &move)
	{
		//purge data in "old" array
		Purge();
		if (move.m_array != nullptr)
		{
			//reassign lhs
			m_array = move.m_array;
			m_rows = move.m_rows;
			m_columns = move.m_columns;
			//reset rhs
			move.m_array = nullptr;
			move.m_rows = 0;
			move.m_columns = 0;
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the Array2D falls out of scope
*
* Postcondition: members of Array2D are reset
*
************************************************************************/
template<class T>
inline Array2D<T>::~Array2D()
{
	//purge m_array of its contents
	Purge();
	//reset primitives
	m_rows = 0;
	m_columns = 0;
}

/**********************************************************************
* Purpose: Deallocate all data
*
* Precondition: The list has data to remove
*
* Postcondition: data is cleared or an exception is thrown
*
************************************************************************/
template<class T>
inline void Array2D<T>::Purge()
{
	if (m_array == nullptr)
	{
		throw Exception("Nothing to purge!");
	}

	//purge all data
	//delete each row
	for (int i = 0; i < m_rows; i++)
	{
		if (m_array[i] != nullptr)
		{
			delete[] m_array[i];
		}
	}
	//delete main ptr
	delete[] m_array;

	//reset basic variables
	m_array = nullptr;
}

/**********************************************************************
* Purpose: Subscript operator overload
*
* Precondition: given index is valid and within bounds
*
* Postcondition: returns data at given index, or throw an exception
*
************************************************************************/
template<class T>
inline Row<T> Array2D<T>::operator[](int row)
{
	//check
	if (row > m_rows)
	{
		throw Exception("Invalid index");
	}
	//create a row of the given row
	return Row<T>(*this, row);
}

/**********************************************************************
* Purpose: return m_rows
*
* Precondition: m_rows is initialized
*
* Postcondition: m_rows is returned
*
************************************************************************/
template<class T>
inline int Array2D<T>::getRow() const
{
	return m_rows;
}

/**********************************************************************
* Purpose: return m_columns
*
* Precondition: m_columns is initialized
*
* Postcondition: m_columns is returned
*
************************************************************************/
template<class T>
inline int Array2D<T>::getColumns() const
{
	return m_columns;
}

/**********************************************************************
* Purpose: set m_rows
*
* Precondition: rows is a valid int, greater than zero
*
* Postcondition: m_rows is set to rows and data is added/ purged as needed, 
*	or an exception is thrown
*
************************************************************************/
template<class T>
inline void Array2D<T>::setRows(int rows)
{
	//check if input is valid
	if (rows < 0)
	{
		throw Exception("Invalid # of rows!");
	}
	//resize, add rows as needed

	//determine whether m_rows is growing or shrinking
	int smaller = rows < m_rows ? rows : m_rows;

	//intialize new array
	T ** temp = new T * [rows];
	//intialize each row
	for (int i = 0; i < rows; i++)
	{
		temp[i] = new T[m_columns];
	}

	//copy old data to the array
	for (int i = 0; i < smaller; i++)
	{
		for (int j = 0; j < m_columns; j++)
		{
			temp[i][j] = m_array[i][j];
		}
	}
	//delete old arrays
	Purge();

	//reassign head
	m_array = temp;
	//set m_rows
	m_rows = rows;
}

/**********************************************************************
* Purpose: set m_columns
*
* Precondition: columns is a valid int, greater than zero
*
* Postcondition: m_columns is set to columns and data is added/ purged as needed, 
*	or an exception is thrown
************************************************************************/
template<class T>
inline void Array2D<T>::setColumns(int columns)
{
	//check if input is valid
	if (columns < 0)
	{
		throw Exception("Invalid # of columns!");
	}
	//resize, this is more complex
	
	//determine whether m_columns is growing or shrinking
	int smaller = columns < m_columns ? columns : m_columns;

	//intialize new array
	T** temp = new T * [m_rows];
	//intialize each row
	for (int i = 0; i < m_rows; i++)
	{
		temp[i] = new T[columns];
	}

	//copy old data to the array
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < smaller; j++)
		{
			temp[i][j] = m_array[i][j];
		}
	}
	//delete old arrays
	Purge();

	//reassign head
	m_array = temp;

	//set m_columns
	m_columns = columns;
}

/**********************************************************************
* Purpose: return a const reference to a given index in the array
*
* Precondition: the supplied index is > 0 and less than the product of m_rows/m_columns
*
* Postconditions: 
*	RETURN: const ref to supplied index
*	EXCEPTION: invalid index
*
************************************************************************/
template<class T>
inline T& Array2D<T>::Select(int desired_row, int desired_column) const
{
	//check for valid index
	if (desired_column < 0 || desired_row < 0)
	{
		throw Exception("Invalid index!");
	}

	//return
	return m_array[desired_row][desired_column];
	
}