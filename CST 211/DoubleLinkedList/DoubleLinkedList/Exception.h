/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Exception.h
* Date Created:   1/7/19
**************************************************************/
/************************************************************************
* Class: Exception
*
* Purpose: Encapsulate cStrings that act as error messages
*
* Manager functions:
*	Exception();
*	Exception(const char * msg);
*	Exception(const Exception & copy);
*	Exception(Exception && copy);
*	Exception & operator =(const Exception & rhs);
*	Exception & operator =(Exception && rhs);
*	~Exception();
*
*
* Methods:
*	getMessage();	
*	setMessage();
*
*************************************************************************/
#pragma once
#include <iostream>
#include <fstream>
using std::ostream;
class Exception
{
	//output override
	friend ostream& operator <<(ostream& out, const Exception& except);

public:
	Exception();
	Exception(const char * msg);
	Exception(const Exception & copy);
	Exception(Exception && copy);
	Exception & operator =(const Exception & rhs);
	Exception & operator =(Exception && rhs);
	~Exception();

	const char * GetMessage() const;
	void setMessage(const char * msg); 

private:
	char * m_msg;
};

/*
*	isEmpty – does the list have any elements in it?
*	First – return a const reference to the data in the first element.
*	Last – return a const reference to the data in the last element.
*	Prepend – add an item to the front of the list.
*	Append – add an item to the end of the list.
*	Purge – remove all items from the list.
*	Extract – remove a single item from the list.
*	InsertAfter – insert an item after an item in the list. InsertAfter(new_item, existing_item);
*	InsertBefore – insert an item before an item in the list. InsertBefore(new_item, existing_item);
*	getHead – return the head pointer (TESTING ONLY)//SOMETHING WRONG
*	getTail – return the tail pointer (TESTING ONLY)
*	PrintForwards – print the list forwards (TESTING ONLY)
*	PrintBackwards – print the list backwards (TESTING ONLY)
*/

//template<typename T>
//inline void List<T>::Extract(T data)
//{
//	if (m_head != nullptr)
//	{
//		Node<T>* travel = m_head;
//
//		while ((travel->m_data != data) && (travel->m_next != nullptr))
//		{
//			travel = travel->m_next;
//		}
//
//		if (travel->m_data == data)
//		{
//			if (travel == m_head)
//			{ //front
//				m_head = m_head->m_next;
//				if (m_head != nullptr)
//					m_head->m_prev = nullptr;
//			}
//			else if (travel == m_tail)
//			{ // end
//				m_tail = m_tail->m_prev;
//				if (m_tail != nullptr)
//					m_tail->m_next = nullptr;
//			}
//			else
//			{ //middle
//				travel->m_prev->m_next = travel->m_next;
//				travel->m_next->m_prev = travel->m_prev;
//			}
//
//			if (m_head == nullptr)
//				m_tail = nullptr;
//
//			delete travel;
//		}
//		else
//			throw Exception("ITEM TO FIND DOES NOT EXIST");
//	}
//	else
//		throw Exception("EMPTY LIST");
//}