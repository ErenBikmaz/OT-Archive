/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Exception.cpp
* Date Created:   1/7/19
**************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Exception.h"

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: An exception is created with no inputs supplied
*
*
* Postcondition: and exception is created with default values
*
*
************************************************************************/
Exception::Exception():m_msg(nullptr)
{
}

/**********************************************************************
* Purpose: 1 arg constructor
*
* Precondition: An exception is created with input supplied
*
*
* Postcondition: and exception is created with supplied message
*
*
************************************************************************/
Exception::Exception(const char * msg) : m_msg(nullptr)
{
	if (msg != nullptr)
	{
		delete[] m_msg;
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}
}

/**********************************************************************
* Purpose: copy constructor
*
* Precondition: An exception is created with another exception
*
*
* Postcondition: an exception is created with the same message as the one supplied
*
*
************************************************************************/
Exception::Exception(const Exception& copy)
{	//deep copy data to new object
	if (&copy.m_msg != nullptr)
	{
		m_msg = new char[strlen(copy.m_msg) + 1];
		strcpy(m_msg, copy.m_msg);
	}
}

/**********************************************************************
* Purpose: move constructor
*
* Precondition: An exception is created with another exception
*
*
* Postcondition: an exception is created with the same message as the one supplied, whose data is reset
*
*
************************************************************************/
Exception::Exception(Exception  && copy)
{	//shallow copy data to new object, delete old one
	if (copy.m_msg != nullptr)
	{
		m_msg = copy.m_msg;
		delete &copy;
	}
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: An exception's data is set equal to by that of another
*
*
* Postcondition: An exception's data is overwritten by that of another
*
*
************************************************************************/
Exception& Exception::operator=(const Exception & rhs)
{	//deep copy data to another object
		//check for self assignment
	if (this != &rhs)
	{
		//empty this list
		delete[] m_msg;
		m_msg = nullptr;

		if (rhs.m_msg != nullptr)
		{
			//deep copy rhs to lhs
			m_msg = new char[strlen(rhs.m_msg) + 1];
			strcpy(m_msg, rhs.m_msg);
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: move assignment operator
*
* Precondition: An exception's data is set equal to by that of another
*
*
* Postcondition: An exception's data is overwritten by that of another , which is also reset
*
*
************************************************************************/
Exception& Exception::operator=(Exception && rhs)
{	//shallow copy data to another object, delete old one
		//check for self assignment
	if (this != &rhs)
	{
		//empty this list
		delete[] m_msg;
		m_msg = nullptr;

		if (rhs.m_msg != nullptr)
		{
			//shallow copy rhs to lhs
			m_msg = rhs.m_msg;
			rhs.m_msg = nullptr;
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: deconstructor
*
* Precondition: called explicity by consumer or implicitly when exception is out of scope
*
*
* Postcondition: all member variables a deleted and returned to default values
*
*
************************************************************************/
Exception::~Exception()
{//deallocate message
	delete[] m_msg;
	m_msg = nullptr;
}

/**********************************************************************
* Purpose: ostream override
*
* Precondition: an exception is printed to console
*
*
* Postcondition: the message of the exception is printed
*
*
************************************************************************/
ostream& operator<<(ostream& out, const Exception& except)
{
	return out << except.m_msg;
}

/**********************************************************************
* Purpose: getter
*
* Precondition: this method is called and the exception has a valid message
*
*
* Postcondition: the message is returned
*
*
************************************************************************/
const char* Exception::getMessage() const 
{
	return m_msg;
}

/**********************************************************************
* Purpose: setter
*
* Precondition: a valid message is supplied
*
*
* Postcondition: the exception's message is changed to that which was supplied
*
*
************************************************************************/
void Exception::setMessage(const char * msg)
{
	if (msg != nullptr)
	{
		delete[] m_msg;
		m_msg = new char[strlen(msg) + 1];
		strcpy(m_msg, msg);
	}

}


