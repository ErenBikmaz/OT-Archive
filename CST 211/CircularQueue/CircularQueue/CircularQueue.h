/*************************************************************
* Author:         Eren Bikmaz
* Filename:       CircuarQueue.h
* Date Created:   1/20/20
* Modifications:	
*	1/20/20 - Adapted from Queue.h
**************************************************************/


/************************************************************************
* Class: Queue
*
* Purpose: Manage an array-based Queue
*	The Queue's size is preset, and must be changed to prevent overflow
* Stipulations:
*	Throw Underflow and Overflow exceptions using your Exception class where appropriate.
*	Although not shown in the UML class diagram, include the appropriate manager functions. (And you better have the correct ones! )
* Selected data member explanations:
*	m_size – The size of the array.
*	m_top – Where is the top of the Queue.
* Selected function explanations:
*	Push – Puts a data item on the top of the Queue.
*	Pop – Removes and returns the top of the Queue.
*	getNumElements – How many items are currently on the Queue.
*
*
* Canonical Methods:
*	Queue(int size = 0);
*	Queue(const Queue & copy); 
*	Queue & operator = (const Queue& copy);
*	~Queue();
*
* Mutator/Accessor Methods:
*	void Enqueue(T data);
*	T Dequeue();
*	T Peek()const;
*	int getSize()const;
*	bool isEmpty()const;
*	bool isFull()const;
*
*************************************************************************/

#pragma once
#include "Array.h"
#include "Exception.h"

template <class T> class CircularQueue
{
public:

	//Canonical Methods
	CircularQueue(int size = 0);
	CircularQueue(const CircularQueue & copy); 
	CircularQueue & operator = (const CircularQueue& copy);
	~CircularQueue();

	//Mutators/Acessors
	void Enqueue(T data);
	T Dequeue();//needs to pop from tail
	T Peek()const;
	int getSize()const;
	bool isEmpty()const;
	bool isFull()const;//may not work

private:

	Array<T> m_queue;
	int m_size;
	//"front" of the queue
	int m_head;
	//point to add new nodes
	int m_tail;
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
inline CircularQueue<T>::CircularQueue(int size)
	:m_size(size), m_head(0), m_tail(0)
{
	m_queue = Array<T>(size);
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
inline CircularQueue<T>::CircularQueue(const CircularQueue& copy)
	:m_size(copy.m_size), m_head(copy.m_head), m_tail(copy.m_tail)
{
	m_queue = Array<T>(copy.m_queue);
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
inline CircularQueue<T> & CircularQueue<T>::operator=(const CircularQueue& copy)
{
	if (this != & copy)
	{
		if (copy.m_size != 0) //check for valid data
		{
			m_size = copy.m_size;
			m_head = copy.m_head;
			m_tail = copy.m_tail;
			m_queue = Array<T>(copy.m_queue);
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
inline CircularQueue<T>::~CircularQueue()
{
	//reset primitives
	m_size = 0;
	m_head = 0;
	m_tail = 0;
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
inline void CircularQueue<T>::Enqueue(T data)
{
	//check that Queue has space
	if (isFull())
	{
		//overflow has occured
		throw Exception("Queue Overflow!");
	}
	//add new data to top of Queue
	m_queue[m_tail] = data;
	//if at the end of the queue, loop back
	if (m_tail == m_size)
	{
		m_tail = 0;
	}
	m_tail++;
}

/**********************************************************************
* Purpose: remove data from head of Queue, also return that data
*
* Precondition: the Queue has data to Dequeue
*
* Postcondition: the top of the Queue is popped, or underflow occurs 
*
************************************************************************/
template<class T>
inline T CircularQueue<T>::Dequeue()
{
	//check that top of Queue is valid
	if (isEmpty())
	{
		//underflow has occured
		throw Exception("Underflow Exception!");
	}
	//otherwise, dequeue the Queue
	//save top data
	T data = m_queue[m_head];
	//move down the queue
	//if at the end of the queue, loop back
	if (m_head == m_size)
	{
		m_head = 0;
	}
	m_head++;
	return data;
}

/**********************************************************************
* Purpose: return a copy of the data at the top of the Queue
*
* Precondition: there is data to be returned
*
* Postcondition: copy of data at top is returned or an error is thrown
*
************************************************************************/
template<class T>
inline T CircularQueue<T>::Peek()const
{
	if (m_size == 0)
	{
		throw Exception("No data!");
	}
	return m_queue[m_head];
}

/**********************************************************************
* Purpose: return the current size of the Queue
*
* Precondition: m_size is initialized
*
* Postcondition: m_size is returned
*
************************************************************************/
template<class T>
inline int CircularQueue<T>::getSize() const
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
inline bool CircularQueue<T>::isEmpty()const
{
	bool result = false;
	if (m_tail == m_head)
	{
		result = true;
	}
	return result;
}

/**********************************************************************
* Purpose: return true if Queue is full
*
* Precondition: Queue is initalized
*
* Postcondition: returns true if Queue is full
*
************************************************************************/
template<class T>
inline bool CircularQueue<T>::isFull()const
{
	bool result = false;
	int test = (m_tail - m_head);
	if ((m_tail + 1) == m_head 
		|| m_tail == m_size && m_head == 0 
		|| m_size == 0)
	{
		result = true;
	}
	return result;
}
