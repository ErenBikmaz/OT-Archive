/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Array2D.h
* Date Created:   1/12/20
* Modifications:  
*	1/13/20 - Header outline and documentation
*	1/14/20 - Implementation and testing
**************************************************************/
/************************************************************************
* Class: Array 2D
*
* Purpose: Store and manage a 2D dynamic array of objects.
*	m_array is one-dimensional, class Row will handle 2D functionality
*
* Stipulations:
*	- Make sure the user never goes out of bounds. If they do, throw an exception.
*	- Use your Exception class to throw if they do go out of bounds.
*	- Modify the class so that the subscript operators can be called from const objects. 
*	Hint: You can only call const methods from const objects.
*
* Manager functions:	
	Array2D(int rows, int columns);
	Array2D(const Array2D& copy);
	Array2D& operator =(const Array2D& copy);
	~Array2D();
*	
*
* Methods:
	Row<T> operator [] (int index);

	int getRows() const;
	int getColumns() const;
	void setRows(int rows);
	void setColumns(int columns);

	T & Select(int desired_row, int desired_column) const;
*
*
*************************************************************************/
#pragma once

#include "Row.h"
#include "Array.h"
#include "Exception.h"

template <class T>class Array2D
{
public:
	Array2D(int rows = 0, int columns = 0);
	Array2D(const Array2D& copy);
	Array2D& operator =(const Array2D& copy);
	~Array2D();

	Row<T> operator [] (int row);

	int getRow() const;
	int getColumns() const;
	void setRows(int rows);
	void setColumns(int columns);

	T & Select(int desired_row, int desired_column) const;

private:

	Array<T> m_array;
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
	//intialize 1D array with length equal to area of 2D array
	m_array = Array<T>(rows * columns);
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
	: m_rows(copy.m_rows), m_columns(copy.m_columns), m_array(copy.m_array)
{

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
		if (true)//CONDITIONAL CHECK NEEDED
		{	//copy everything
			m_array = copy.m_array;
			m_rows = copy.m_rows;
			m_columns = copy.m_columns;
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
	//m_array = nullptr;
	m_rows = 0;
	m_columns = 0;
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
	//create a row of the given row
	//Row<T> out = ;
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
	//resize
	m_array.SetLength(rows * m_columns);
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
	//this works but can be optimized
	//size of the new array
	int newsize = (m_rows * columns);
	//length of smallest sized array
	int smaller = newsize < (m_rows * m_columns) ? newsize : (m_rows * m_columns);
	//smallest column length
	int smolcol = columns < m_columns ? columns : m_columns;
	//difference between column lengths, can be negative
	int rowdelta = columns - m_columns;
	//temp new array
	Array<T> rez = Array<T>(newsize);
	int rowskip = 0;

	//copy old data into new, keeping data in correct rows
	for (int i = 0; i < smaller; i++)
	{
		rowskip = (i / smolcol) * (rowdelta);
		if (rowskip < 0)
			rowskip *= -1;
		//debug: read watches
		//copy each cell
		if (rowdelta > 0)
		{
			rez[i + rowskip] = m_array[i];
		}
		else
		{
			rez[i] = m_array[i + rowskip];
		}
	}
	//reassign
	m_array = rez;

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
	//reads correct index with a bit of math
	//(row * m_column) + column
	int index = ((desired_row * m_columns) + desired_column);
	return m_array[index];
	//return m_array[(desired_row * m_columns) + desired_column];
}
