/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Queue.h
* Date Created:   1/19/20
* Modifications:
*	1/19/20 Setup header, documentation, and implemented fully
*	1/23/20 Testing
**************************************************************/


/************************************************************************
* Class: Queue
*
* Purpose: Manage an List-based Queue
*
* Canonical Methods:
*	Queue();
*	Queue(const Queue & copy);
*	Queue & operator = (const Queue& copy);
*	~Queue();
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

template <class T> class Queue
{
public:

	//Canonical Methods
	Queue();
	Queue(const Queue & copy);
	Queue & operator = (const Queue& copy);
	~Queue();

	//Mutators/Acessors
	void Enqueue(T data);
	T Dequeue();
	T Peek()const;
	int getSize() const; 
	bool isEmpty()const;

private:

	List<T> m_queue;
	int m_size;
};

/**********************************************************************
* Purpose: 1-arg constructor
*
* Precondition: Queue is created with 1 input supplied
*
* Postcondition: Queue is created with given values
*
************************************************************************/
template<class T>
inline Queue<T>::Queue(): m_size(0)
{
	m_queue = List<T>();
}

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a Queue is created given another Queue
*
* Postcondition: a new Queue is created, identical to the one provided
*
************************************************************************/
template<class T>
inline Queue<T>::Queue(const Queue& copy)
	:m_size(copy.m_size)
{
	m_queue = List<T>(copy.m_queue);
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: Queue's data is set equal to by that of another
*
* Postcondition: Queue's data is overwritten by that of another
*
************************************************************************/
template<class T>
inline Queue<T> & Queue<T>::operator=(const Queue& copy)
{
	if (this != & copy)
	{
		if (copy.getSize() > 0) //check for valid data
		{
			m_size = copy.m_size;
			m_queue = List<T>(copy.m_queue);
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the Queue falls out of scope
*
* Postcondition: contents of Queue are purged and pointers reset
*
************************************************************************/
template<class T>
inline Queue<T>::~Queue()
{
	//reset primitives
	m_size = 0;
}

/**********************************************************************
* Purpose: Push data onto the Queue
*
* Precondition: valid data is supplied, the Queue has space for more data
*
* Postcondition: The data is added OR an overflow exception is thrown
*
************************************************************************/
template<class T>
inline void Queue<T>::Enqueue(T data)
{
	//Append new data
	m_queue.Append(data);
	//count new node
	m_size++;
}

/**********************************************************************
* Purpose: Pop data off the Queue, also return that data
*
* Precondition: the Queue has data to pop
*
* Postcondition: top top of the Queue is popped, or underflow occurs
*
************************************************************************/
template<class T>
inline T Queue<T>::Dequeue()
{
	//check that top of Queue is valid
	if (isEmpty())
	{
		//underflow has occured
		throw Exception("Underflow Exception!");
	}

	//otherwise, Dequeue
	m_size--;
	//save data of front node
	T data = m_queue.First();
	//then remove it
	m_queue.Extract(data);

	return data;
}

/**********************************************************************
* Purpose: return a copy of the data at the front of the Queue
*
* Precondition: none
*
* Postcondition: copy of data at front is returned
*
************************************************************************/
template<class T>
inline T Queue<T>::Peek()const
{
	return m_queue.First();
}

/**********************************************************************
* Purpose: return how many items are currently on the Queue
*
* Precondition: m_size is initialized
*
* Postcondition: m_size is returned
*
************************************************************************/
template<class T>
inline int Queue<T>::getSize() const
{
	return m_size;
}

/**********************************************************************
* Purpose: return true if Queue is empty
*
* Precondition: Queue is initalized
*
* Postcondition: returns true if Queue is empty
*
************************************************************************/
template<class T>
inline bool Queue<T>::isEmpty()const
{
	bool result = false;
	if (m_size == 0)
	{
		result = true;
	}
	return result;
}

