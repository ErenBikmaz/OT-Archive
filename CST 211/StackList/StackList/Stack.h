/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Stack.h
* Date Created:   1/19/20
* Modifications:
*	1/19/20 Setup header, documentation, and implemented fully
**************************************************************/


/************************************************************************
* Class: Stack
*
* Purpose: Manage an List-based stack
*	The stack's size is preset, and must be changed to prevent overflow
* Stipulations:
*	Throw Underflow and Overflow exceptions using your Exception class where appropriate.
*	Although not shown in the UML class diagram, include the appropriate manager functions. (And you better have the correct ones! )
*	Selected function explanations:
*		Push – Puts a data item on the top of the stack.
*		Pop – Removes and returns the top of the stack.
*		getNumElements – How many items are currently on the stack.
*
* Canonical Methods:
*	Stack();
*	Stack(const Stack & copy);
*	Stack & operator = (const Stack& copy);
*	~Stack();
*
* Mutator/Accessor Methods:
*	void Push(T data);
*	T Pop();
*	T Peek()const;
*	int getNumElements() const; 
*	bool isEmpty()const;
*
*************************************************************************/

#pragma once
#include "List.h"
#include "Exception.h"

template <class T> class Stack
{
public:

	//Canonical Methods
	Stack();
	Stack(const Stack & copy);
	Stack & operator = (const Stack& copy);
	~Stack();

	//Mutators/Acessors
	void Push(T data);
	T Pop();
	T Peek()const;
	int getNumElements() const; 
	bool isEmpty()const;

private:

	List<T> m_stack;
	int num_elements;
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
inline Stack<T>::Stack(): num_elements(0)
{
	m_stack = List<T>();
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
	:num_elements(copy.num_elements)
{
	m_stack = List<T>(copy.m_stack);
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
		if (copy.getNumElements() > 0) //check for valid data
		{
			num_elements = copy.num_elements;
			m_stack = List<T>(copy.m_stack);
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
	num_elements = 0;
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
	//prepend new data
	m_stack.Prepend(data);
	//count new node
	num_elements++;
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
	num_elements--;
	//save data of front node
	T data = m_stack.First();
	//then remove it
	m_stack.Extract(data);

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
	return m_stack.First();
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
	return num_elements;
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
	if (getNumElements() == 0)
	{
		result = true;
	}
	return result;
}

