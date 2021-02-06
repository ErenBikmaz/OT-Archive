/*************************************************************
* Author:         Eren Bikmaz
* Filename:       List.h
* Date Created:   1/8/20
**************************************************************/
/************************************************************************
* Class: List
*
* Purpose: Manage a linked list
*
* Canonical Methods:
*	==Constructors
*	List()
*	Destructor
*	~List()
*
*	Copy Constructor
*	List(const List & rhs)
*	Move Constructor
*	List(List && rhs)
*
*	Assignment operators
*	List operator = (const List & rhs)
* 	List operator = (List && src)
*
*
* Mutator/Accessor Methods:
*	isEmpty – does the list have any elements in it?
*	First – return a const reference to the data in the first element.
*	Last – return a const reference to the data in the last element.
*	Prepend – add an item to the front of the list.
*	Append – add an item to the end of the list.
*	Purge – remove all items from the list.
*	Extract – remove a single item from the list.
*	InsertAfter – insert an item after an item in the list. InsertAfter(new_item, existing_item);
*	InsertBefore – insert an item before an item in the list. InsertBefore(new_item, existing_item);
*	getHead – return the head pointer (TESTING ONLY)
*	getTail – return the tail pointer (TESTING ONLY)
*	PrintForwards – print the list forwards (TESTING ONLY)
*	PrintBackwards – print the list backwards (TESTING ONLY)
*
*************************************************************************/
#pragma once
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
#include "Node.h"
#include "Exception.h"

template <class T>
class List
{
public:

	//Canonical Methods
	//Con/destructor
	List();
	~List();
	//Copy and move
	List(const List & copy);
	List(List && move);
	//Copy and move assignment
	List & operator =(const List & copy);
	List & operator =(List && move);

	//Mutators
	bool isEmpty();
	const T & First() const;
	const T & Last() const; 
	void Prepend(T data); 
	void Append(T data); 
	void Purge();
	void Extract(T data); 
	void InsertAfter(T new_item, T existing_item);
	void InsertBefore(T new_item, T existing_item);

	//Accessors (for testing)
	Node<T> * getHead();
	Node<T> * getTail();
	void PrintForward();
	void PrintBackward();

private:
	Node<T> * FindNode(T data);

	Node<T> * m_head;
	Node<T> * m_tail;
};




/**********************************************************************
* Purpose: Default constructor
*
* Precondition: A node is created with no inputs supplied
*
* Postcondition: a node is created with default values
*
************************************************************************/
template <class T>
List<T>::List() : m_head(nullptr), m_tail(nullptr)
{
}

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the list falls out of scope
*
* Postcondition: contents of list are purged and pointers reset
*
************************************************************************/
template <class T>
List<T>::~List()
{
	Purge();
}

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a list is created given another list
*
* Postcondition: a new list is created, identical to the one provided
*
************************************************************************/
template<class T>
inline List<T>::List(const List & copy) : m_head(nullptr), m_tail(nullptr)
{//deep copy data to new object
	if (copy.m_head != nullptr)
	{
		Node<T>* travel = copy.m_head;
		//traverse list to be copied
		while (travel != nullptr)
		{
			//copy node and proceed until complete
			Append(travel->m_data);
			travel = travel->m_next;
		}
	}
}

/**********************************************************************
* Purpose: Move Constructor
*
* Precondition: a list is created given another list
*
* Postcondition: a new list is created, AND THE LIST PROVIDED IS RESET
*
************************************************************************/
template<class T>
inline List<T>::List(List && move) : m_head(nullptr), m_tail(nullptr)
{
	if (move.m_head != nullptr)
	{
		//steal head and tail pointer
		m_head = move.m_head;
		m_tail = move.m_tail;

		//reassign old array's ptrs
		move.m_head = nullptr;
		move.m_tail = nullptr;
	}
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: A list's data is set equal to by that of another
*
* Postcondition: A list's data is overwritten by that of another
*
************************************************************************/
template<class T>
List<T> & List<T>::operator=(const List & copy)
{	//deep copy data to another object
	//check for self assignment
	if (this != &copy)
	{
		//empty this list
		Purge();

		if (copy.m_head != nullptr)
		{
			//deep copy rhs to lhs
			Node<T>* travel = copy.m_head;
			//traverse list to be copied
			while (travel != nullptr)
			{
				//copy node and proceed until complete
				Append(travel->m_data);
				travel = travel->m_next;
			}
		}
	}
	return *this; 
}

/**********************************************************************
* Purpose: move assignment operator
*
* Precondition: An list's data is set equal to by that of another
*
* Postcondition: An list's data is overwritten by that of another , which is also reset
*
************************************************************************/
template<class T>
List<T> & List<T>::operator = (List && move)
{
	//move copy data to another object
	//check for self assignment
	if (this != &move)
	{
		//empty this list
		Purge();

		if (move.m_head != nullptr)
		{
			//steal head and tail pointer
			m_head = move.m_head;
			m_tail = move.m_tail;

			//reassign old array's ptrs
			move.m_head = nullptr;
			move.m_tail = nullptr;
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Determine if the list is empty
*
* Precondition: The list exists and this method is called
*
* Postcondition: Return true if _head is nullptr, false otherwise
*
************************************************************************/
//does the list have any elements in it?
template<class T>
inline bool List<T>::isEmpty()
{
	bool empty = true;
	if (m_head != nullptr)
	{
		empty = false;
	}
	return empty;
}

/**********************************************************************
* Purpose: Obtain the data of the first node
*
* Precondition: the first node has valid data, error otherise
*
* Postcondition: return the data of the first node
*
************************************************************************/
//return a const reference to the data in the first element
template<class T>
inline const T & List<T>::First() const
{
	if (m_head == nullptr)
	{
		throw Exception("List is empty!");
	}
	return m_head->m_data;
}

/**********************************************************************
* Purpose: Obtain the data of the last node
*
* Precondition: the last node has valid data, error otherise
*
* Postcondition: return the data of the last node
*
************************************************************************/
//return a const reference to the data in the last element
template<class T>
inline const T& List<T>::Last() const
{
	if (m_tail == nullptr)
	{
		throw Exception("List is empty!");
	}
	return m_tail->m_data;
}

/**********************************************************************
* Purpose: Add a new node to the front of the list.
*
* Precondition: supplied data is valid
*
* Postcondition: a new node is created and placed at the front of the list with given data
*
************************************************************************/
//PREPEND
template <class T>
void List<T>::Prepend(T data)
{
	if (m_head != nullptr)
	{
		//create a new node
		Node<T> * node = new Node<T>(data);
		//set the next pointer of the new node to the old head
		node->m_next = m_head;
		//update the head to the new node				   
		m_head = node;
		//tail ptr is still nullptr, nothing to point at
		node->m_prev = nullptr;
	}
	else
	{	//there is no head
		m_tail = new Node<T>(data);
		m_head = m_tail;
	}
}

/**********************************************************************
* Purpose: Add a new node to the end of the list.
*
* Precondition: supplied data is valid
*
* Postcondition: a new node is created and placed at the end of the list with given data
*
************************************************************************/
//APPPEND
template <class T>
void List<T>::Append(T data)
{

	if (m_tail != nullptr)
	{
		//(_tail will be pointing to the last node)
		//point the next of _tail to the new node
		m_tail->m_next = new Node<T>(data);
		//and set its tail
		m_tail->m_next->m_prev = m_tail;
		//reassign the tail
		m_tail = m_tail->m_next;
		//set the next of last node to nullptr
		m_tail->m_next = nullptr;
	}
	else //list is empty, just make new node
	{
		m_tail = new Node<T>(data);
		m_head = m_tail;
	}


}

/**********************************************************************
* Purpose: remove all items from the list
*
* Precondition: called by consumer or destructor
*
* Postcondition: list is emptied and reset completely
*
************************************************************************/
//Remove all nodes.
template <class T>
void List<T>::Purge()
{
	Node<T> * trail = nullptr;
	Node<T> * travel = m_head;
	while (travel != nullptr)
	{
		trail = travel;//make a temp copy of travel
		travel = travel->m_next;//advance the travel to next node 
		delete trail;//invokes the destructor for trail
	}
	//empty head and tail pointers
	m_head = nullptr;
	m_tail = nullptr;
}

/**********************************************************************
* Purpose: remove a single item from the list
*
* Precondition: the data provided is valid
*
* Postcondition: if a match is found, it is purged from the list
*
************************************************************************/
template<class T>
inline void List<T>::Extract(T data)
{
	//find with internal method
	Node<T> * target = FindNode(data);

	if (target == m_tail)
	{ //it's at the end, just amputate
		//set previous node as tail
		m_tail = m_tail->m_prev;
		if (m_tail != nullptr)
		{	
			m_tail->m_next = nullptr;
		}
		else
		{	//list is empty
			m_head = nullptr;
		}
	}
	else if (target == m_head)
	{ //it's at the beginning, just amputate
		//set next node as head
		m_head = m_head->m_next;
		//check
		if (m_head != nullptr)
		{
			m_head->m_prev = nullptr;
		}
		else
		{	//list is empty
			m_tail = nullptr;
		}
	}
	else
	{ //it's in the middle, do a little dance
		target->m_prev->m_next = target->m_next;
		target->m_next->m_prev = target->m_prev;
		//both neighbors of target now pointing "around" target
	}

	//delete target
	delete target;
}

/**********************************************************************
* Purpose: insert an item after an item in the list
*
* Precondition: there is a match for the data supplied, valid data is supplied
*
* Postcondition: a new node is created after the matching node
*
************************************************************************/
template<class T>
inline void List<T>::InsertAfter(T new_item, T existing_item)
{
	//find with internal method
	Node<T> * target = FindNode(existing_item);
	//now insert after it
	if (target == m_tail)
	{ //it's at the end, just staple it on
		target->m_next = new Node<T>(new_item);
		//reassign it's prev pointer
		target->m_next->m_prev = target;
		//reassign tail
		m_tail = target->m_next;
	}
	else
	{ //otherise it is followed by another node
		//here we will need another pointer
		Node<T>* neighbor = target->m_next;
		//now we can work freely, create new node
		target->m_next = new Node<T>(new_item);
		//both neighbors of new node now point at it
		neighbor->m_prev = target->m_next;
		//new node's connection to next
		target->m_next->m_next = neighbor;
		target->m_next->m_prev = target;
	}

}

/**********************************************************************
* Purpose: insert an item before an item in the list
*
* Precondition: there is a match for the data supplied, valid data is supplied
*
* Postcondition: a new node is created before the matching node
*
************************************************************************/
template<class T>
inline void List<T>::InsertBefore(T new_item, T existing_item)
{
	//find with internal method
	Node<T>* target = FindNode(existing_item);
	//now insert before it
	if (target == m_head)
	{ //it's at the beginning, just staple it on
		target->m_prev = new Node<T>(new_item);
		//reassign it's next pointer
		target->m_prev->m_next = target;
		//reassign head
		m_head = target->m_prev;
	}
	else
	{ //otherise it is preceeded another node
		//here we will need another pointer
		Node<T>* neighbor = target->m_prev;
		//now we can work freely, create new node
		target->m_prev = new Node<T>(new_item);
		//both neighbors of new node now point at it
		neighbor->m_next = target->m_prev;
		//new node's connection to next and prev
		target->m_prev->m_prev = neighbor;
		target->m_prev->m_next = target;
	}
}


/**********************************************************************
* Purpose: return a copy of the head pointer
*
* Precondition: the head pointer is initialized
*
* Postcondition: the head pointer is returned
*
************************************************************************/
template<class T>
inline Node<T> * List<T>::getHead()
{
	return m_head;
}

/**********************************************************************
* Purpose: return a copy of the tail pointer
*
* Precondition: the tail pointer is initialized
*
* Postcondition: the tail pointer is returned
*
************************************************************************/
template<class T>
inline Node<T> * List<T>::getTail()
{
	return m_tail;
}

/**********************************************************************
* Purpose: print the list forwards 
*
* Precondition: the list has data that can be printed
*
* Postcondition: data is printed
*
************************************************************************/
//Display the full contents of the list
template <class T>
void List<T>::PrintForward()
{
	//start from the front and proceed
	Node<T> * travel = m_head;
	while (travel != nullptr)
	{
		cout << travel->_data << " ";
		//advance the travel pointer
		travel = travel->m_next;
	}
	cout << endl;
}

/**********************************************************************
* Purpose: print the list backwards
*
* Precondition: the list has data that can be printed
*
* Postcondition: data is printed
*
************************************************************************/
template<class T>
inline void List<T>::PrintBackward()
{
	//start from the back and recede
	Node<T>* travel = m_tail;
	while (travel != nullptr)
	{
		cout << travel->_data << " ";
		//advance the travel pointer
		travel = travel->m_prev;
	}
	cout << endl;
}

/**********************************************************************
* Purpose: Find a node with geven data
*
* Precondition: the data exists, the list has nodes
*
* Postcondition: Return adrress of node with same data
*
************************************************************************/
template<class T>
inline Node<T>* List<T>::FindNode(T data)
{
	if (m_head != nullptr)
	{
		Node<T>* travel = m_head;
		//traverse list until a match is found or end of list is encountered
		while ((travel->m_data != data) && (travel->m_next != nullptr) && (travel != nullptr))
		{
			travel = travel->m_next;
		}
		//check if a valid result was found
		if (travel->m_data == data)
		{
			//it's a match!
			return travel;
		}
		else
		{
			//does not exist
			throw Exception("Not found");
		}
	}
	else
	{
		throw Exception("list empty");
	}
}

