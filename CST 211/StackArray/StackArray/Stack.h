/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Stack.h
* Date Created:   1/18/20
* Modifications:	
*	1/18/20 - Set up header and documentation
*	1/19/20 - fully implemented all methods
**************************************************************/


/************************************************************************
* Class: Stack
*
* Purpose: Manage an array-based stack
*	The stack's size is preset, and must be changed to prevent overflow
* Stipulations:
*	Throw Underflow and Overflow exceptions using your Exception class where appropriate.
*	Although not shown in the UML class diagram, include the appropriate manager functions. (And you better have the correct ones! )
* Selected data member explanations:
*	m_size – The size of the array.
*	m_top – Where is the top of the stack.
* Selected function explanations:
*	Push – Puts a data item on the top of the stack.
*	Pop – Removes and returns the top of the stack.
*	getNumElements – How many items are currently on the stack.
*
*
* Canonical Methods:
*	Stack(int size = 0);
*	Stack(const Stack & copy); 
*	Stack & operator = (const Stack& copy);
*	~Stack();
*
* Mutator/Accessor Methods:
* 	void Push(T data);
*	T Pop();
*	T Peek()const;
*	int getNumElements() const; 
*	int getSize()const;
*	void setSize(int new_size);
*	bool isEmpty()const;
*	bool isFull()const;
*
*************************************************************************/

#pragma once
#include "Array.h"
#include "Exception.h"

template <class T> class Stack
{
public:

	//Canonical Methods
	Stack(int size = 0);
	Stack(const Stack & copy); 
	Stack & operator = (const Stack& copy);
	~Stack();

	//Mutators/Acessors
	void Push(T data);
	T Pop();
	T Peek()const;
	int getNumElements() const; 
	int getSize()const;
	void setSize(int new_size);
	bool isEmpty()const;
	bool isFull()const;

private:

	Array<T> m_stack;
	int m_size;
	int m_top;
};

/**********************************************************************
* Purpose: 1-arg constructor
*
* Precondition: Stack is created with 1 input supplied
*
* Postcondition: Stack is created with given values
*
************************************************************************/
template<class T>
inline Stack<T>::Stack(int size)
	:m_size(size), m_top(0)
{
	m_stack = Array<T>(size);
}

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a Stack is created given another Stack
*
* Postcondition: a new Stack is created, identical to the one provided
*
************************************************************************/
template<class T>
inline Stack<T>::Stack(const Stack& copy)
	:m_size(copy.m_size), m_top(copy.m_top)
{
	m_stack = Array<T>(copy.m_stack);
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: Stack's data is set equal to by that of another
*
* Postcondition: Stack's data is overwritten by that of another
*
************************************************************************/
template<class T>
inline Stack<T> & Stack<T>::operator=(const Stack& copy)
{
	if (this != & copy)
	{
		if (copy.m_top != 0) //check for valid data
		{
			m_size = copy.m_size;
			m_top = copy.m_top;
			m_stack = Array<T>(copy.m_stack);
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the Stack falls out of scope
*
* Postcondition: contents of Stack are purged and pointers reset
*
************************************************************************/
template<class T>
inline Stack<T>::~Stack()
{
	//reset primitives
	m_size = 0;
	m_top = 0;
}

/**********************************************************************
* Purpose: Push data onto the stack
*
* Precondition: valid data is supplied, the stack has space for more data
*
* Postcondition: The data is added OR an overflow exception is thrown
*
************************************************************************/
template<class T>
inline void Stack<T>::Push(T data)
{
	//check that stack has space
	if (isFull())
	{
		//overflow has occured
		throw Exception("Stack Overflow!");
	}
	//add new data to top of stack
	m_stack[m_top] = data;
	m_top++;
}

/**********************************************************************
* Purpose: Pop data off the stack, also return that data
*
* Precondition: the stack has data to pop
*
* Postcondition: top top of the stack is popped, or underflow occurs 
*
************************************************************************/
template<class T>
inline T Stack<T>::Pop()
{
	//check that top of stack is valid
	if (isEmpty())
	{
		//underflow has occured
		throw Exception("Underflow Exception!");
	}
	//otherwise, pop the stack
	//save top data
	T data = m_stack[m_top - 1];
	//remove the top
	m_top--;
	return data;
}

/**********************************************************************
* Purpose: return a copy of the data at the top of the stack
*
* Precondition: none
*
* Postcondition: copy of data at top is returned
*
************************************************************************/
template<class T>
inline T Stack<T>::Peek()const
{
	return m_stack[m_top - 1];
}

/**********************************************************************
* Purpose: return how many items are currently on the stack
*
* Precondition: m_top is initialized
*
* Postcondition: m_top is returned
*
************************************************************************/
template<class T>
inline int Stack<T>::getNumElements() const
{
	return m_top;
}

/**********************************************************************
* Purpose: return the current size of the stack
*
* Precondition: m_size is initialized
*
* Postcondition: m_size is returned
*
************************************************************************/
template<class T>
inline int Stack<T>::getSize() const
{
	return m_size;
}

/**********************************************************************
* Purpose: change the current size of the stack,
*			cutting off data as needed
*
* Precondition: new_size is < 0
*
* Postcondition: Array is resized or an error is thrown
*
************************************************************************/
template<class T>
inline void Stack<T>::setSize(int new_size)
{
	if (new_size < 0)
	{
		throw Exception("Invalid size");
	}

	//if stack is shrinking, move top appropriately 
	if (new_size < m_size)
	{
		m_top -= (m_top - new_size);
	}
	//change size of array and stack classes
	m_stack.SetLength(new_size);
	m_size = new_size;
}

/**********************************************************************
* Purpose: return true if stack is empty
*
* Precondition: stack is initalized
*
* Postcondition: returns true if stack is empty
*
************************************************************************/
template<class T>
inline bool Stack<T>::isEmpty()const
{
	bool result = false;
	if (m_top == 0)
	{
		result = true;
	}
	return result;
}

/**********************************************************************
* Purpose: return true if stack is full
*
* Precondition: stack is initalized
*
* Postcondition: returns true if stack is full
*
************************************************************************/
template<class T>
inline bool Stack<T>::isFull()const
{
	bool result = false;
	if (m_size == m_top)
	{
		result = true;
	}
	return result;
}
