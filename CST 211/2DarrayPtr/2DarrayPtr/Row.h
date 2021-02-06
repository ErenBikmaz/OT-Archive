/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Row.h
* Date Created:   1/12/20
* Modifications:  
*	1/13/20 - outlined header and documentation
*	1/14/20 - implemented functionality and testing
**************************************************************/
/************************************************************************
* Class: Row
*
* Purpose: Implement 2D functionality for Array2D, primarly the 2nd subscript
*		A row uses it's reference and integer to 'hone in" on a section of m_array
*
* Canonical Methods:
*	Row(Array2D & array2D, int column)
*
* Accessor Methods:
*	T & operator [] (int column)
*
*************************************************************************/
#pragma once
#include "Exception.h"

//forward declaration of Array2D
template <class T>
class Array2D;

template <class T>
class Row
{
	//Friend with Array2D class
	friend class Array2D<T>;

public:

	Row(Array2D<T> & array2D, int row);
	T & operator [] (int column);

private:

	Array2D<T> & m_array2D;

	int m_row;
};

/**********************************************************************
* Purpose: 2-arg constructor
*
* Precondition: Row is created with 2 inputs supplied
*
* Postcondition: Row is created with given values
*
************************************************************************/
template<class T>
inline Row<T>::Row(Array2D<T> & array2D, int row) 
	:m_array2D(array2D), m_row(row)
{
	
}

/**********************************************************************
* Purpose: Subscript operator overload,
*		works with array 2D  to read a particular 2D  index
*
* Precondition: m_row and column provide a valid index
*
* Postcondition: 
*	RETURN: a reference to the desired index
*	EXCEPTION: Invalid index was provided
*
************************************************************************/
template<class T>
T & Row<T>::operator[](int column)
{
	if (column > m_array2D.getColumns())
	{
		throw Exception("Invalid index");
	}
	return m_array2D.Select(m_row, column);
}
