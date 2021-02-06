/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Array.h
* Date Created:   1/7/19
**************************************************************/
/************************************************************************
* Class: Array
*
* Purpose: Store and manage a dynamic array of objects
*
* Manager functions:	
*	Array();
*	Array(int length, int start_index = 0);
*	Array(const Array& rhs);
*	Array(Array&& rhs);//move fix
*	Array& operator =(const Array& rhs);
*	Array& operator =(Array&& rhs);//move needs to nullptr, not delete
*	~Array();
*	
*	T & operator [] (int index);
*
* Methods:
*	int GetStartIndex() const;
*	void SetStartIndex(int start_index);
*	int GetLength() const;
*	void SetLength(int length);
*
*
*************************************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <exception>
using std::exception;

template <class T>class Array
{
public:
	Array();
	Array(int length, int start_index = 0);
	Array(const Array& rhs);
	Array(Array&& rhs);
	Array& operator =(const Array& rhs);
	Array& operator =(Array&& rhs);
	~Array();

	T & operator [] (int index);

	int GetStartIndex() const;
	void SetStartIndex(int start_index);
	int GetLength() const;
	void SetLength(int length);

private:

	T* m_array;
	int m_start_index;
	int m_length;
};

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: An array is created with no inputs supplied
*    
*
* Postcondition: and array is created with default values 
*     
*
************************************************************************/
template <class T>
Array<T>::Array()
	:m_array(nullptr), m_length(0), m_start_index(0)
{
}

/**********************************************************************
* Purpose: 2 arg constructor
*
* Precondition: and array is created with inputs supplied, start index is optional
*
*
* Postcondition: an array is created with the given length and start index
*
*
************************************************************************/
template <class T>
Array<T>::Array(int length, int start_index)
	: m_array(nullptr), m_length(length), m_start_index(start_index)
{
	m_array = new T[m_length];
}

/**********************************************************************
* Purpose: destructor
*
* Precondition: called explicity by consumer or implicitly when array is out of scope
*
*
* Postcondition: all member variables a deleted and returned to default values
*
*
************************************************************************/
template <class T>
Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
	m_length = 0;
	m_start_index = 0;
}

/**********************************************************************
* Purpose: copy constructor
*
* Precondition: a new array is created by copying all data in another array, 
*				if its data is valid.
*
* Postcondition: a new array is created with the same data and characteristics
*
*
************************************************************************/
template <class T>
Array<T>::Array(const Array& rhs)
	: m_array(nullptr), m_length(rhs.m_length), m_start_index(rhs.m_start_index)
{
	//deep copy whole list
	if (rhs.m_array != nullptr)
	{
		//create new array
		m_array = new T[rhs.m_length + 1];

		//Copy old arry into new
		for (int i = 0; i < rhs.m_length; i++)
		{
			m_array[i] = rhs.m_array[i];
		}
	}
}

/**********************************************************************
* Purpose: move constructor
*
* Precondition: a new array is created with data from another
*
*
* Postcondition: the new array is assigned the old one's data, the old array is reset
*
*
************************************************************************/
template<class T>
inline Array<T>::Array(Array&& rhs)
	: m_array(nullptr), m_length(rhs.m_length), m_start_index(rhs.m_start_index)
{ //shallow copy data to new object, delete old one

	//shallow copy rhs to lhs
	m_array = rhs.m_array;
	rhs.m_array = nullptr;

	//copy length & start
	m_length = rhs.m_length;
	m_start_index = rhs.m_start_index;
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: an array's data is assigned to another
*
*
* Postcondition: rhs data is copied to lhs, along with other characteristics
*					all data originally in lhs is discarded
*
************************************************************************/
template <class T>
Array<T>& Array<T>::operator=(const Array& rhs)
{
	//check for self assignment
	if (this != &rhs)
	{
		//empty this list
		delete[] m_array;
		m_array = nullptr;

		if (rhs.m_array != nullptr)
		{	//deep copy rhs to lhs

			//create new array
			m_array = new T[rhs.m_length + 1];

			//Copy old arry into new
			for (int i = 0; i < rhs.m_length; i++)
			{
				m_array[i] = rhs.m_array[i];
			}

			//copy length & start
			m_length = rhs.m_length;
			m_start_index = rhs.m_start_index;
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: move assignment operator
*
* Precondition: an array's data is assigned to another
*
*
* Postcondition: the data of one array is reassigned to another. the rhs is reset
*
*
************************************************************************/
template<class T>
Array<T>& Array<T>::operator=( Array&& rhs)
{
	//check for self assignment
	if (this != &rhs)
	{
		//empty this list
		delete[] m_array;
		m_array = nullptr;

		if (rhs.m_array != nullptr)
		{	
			//shallow copy rhs to lhs
			m_array = rhs.m_array;
			rhs.m_array = nullptr;

			//copy length & start
			m_length = rhs.m_length;
			m_start_index = rhs.m_start_index;
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Obtain data from a specific index
*
* Precondition: the array has valid data and the index supplied is valid
*
*
* Postcondition: the data at the specified index is returned
*					if the index is invalid, an exception is thrown
*
************************************************************************/
template<class T>
inline T& Array<T>::operator[](int index)
{
	int test = (index - m_start_index);
	//check bounds
	if (index >= m_start_index 
		&& index < (m_start_index + m_length))
	{
		return m_array[index - m_start_index];
	}
	else
	{
		throw exception("Index specified is out of bounds!");
	}


}

/**********************************************************************
* Purpose: return the start index of the array
*
* Precondition: the start index is valid
*
*
* Postcondition: the start index is returned as an integer
*
*
************************************************************************/
template<class T>
inline int Array<T>::GetStartIndex() const
{
	return m_start_index;
}

/**********************************************************************
* Purpose: set the starting index of the array
*
* Precondition: the supplied integer is valid
*
*
* Postcondition: the array is set to begin at the index supplied
*
*
************************************************************************/
template<class T>
inline void Array<T>::SetStartIndex(int start_index)
{
	m_start_index = start_index;
}

/**********************************************************************
* Purpose: return the length of the array
*
* Precondition: the length is intialized
*
*
* Postcondition: the length is returned as an integer
*
*
************************************************************************/
template<class T>
inline int Array<T>::GetLength() const
{
	return m_length;
}

/**********************************************************************
* Purpose: set the length of the array, adding or cutting data members as needed
*
* Precondition: the length is greater than zero
*
*
* Postcondition: the array is set to the new length OR an exception is thrown if the length is invalid
*
*
************************************************************************/
template<class T>
inline void Array<T>::SetLength(int length)
{
	if (length > 0)
	{
			//need to make bigger array and deep copy
			//create new array
			T* temp = m_array;
			m_array = new T[length];

			int shortest = m_length < length ? m_length : length;

			//Copy old arry into new
			for (int i = 0; i < shortest; i++)
			{
				m_array[i] = temp[i];
			}

			//copy length 
			m_length = length;
			delete[] temp;
	}
	else
	{
		throw exception("Negative length is invalid!");
	}
}



