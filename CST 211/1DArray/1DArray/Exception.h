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

	const char * getMessage() const;
	void setMessage(const char * msg); 

private:
	char * m_msg;
};