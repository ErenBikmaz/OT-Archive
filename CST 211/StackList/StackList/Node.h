/*************************************************************
* Author:         Eren Bikmaz
* Filename:       Node.h
* Date Created:   1/8/20
* Modifications: 1/9/20 - Function headers/documentation
**************************************************************/
/************************************************************************
* Class: Node
*
* Purpose: Act as a node for a linked list
*
*	This class is friends with List
*
* Manager functions:
*	Constructors
*	Node()
*
*	Copy Constructor
*	Node(const Node & rhs)
*
*	Assignment operators
*	Node operator = (const List & rhs)
*
*	Destructor
*	~Node()
*
* Mutator functions:
*	Getters
*	Node<d> * Next();
*	Node<d> * Prev();
*
*	Setters
*	void Next(Node<d> * n);
*	void Prev(Node<d>* n);
*
*************************************************************************/
#pragma once

//Forward Declaration
template <class T>
class List;

template <class T>
class Node
{
	//Friend with node class
	friend class List<T>;

private:
	//Caanonical Methods//
	//Con/Destructors
	Node();
	Node(T data);
	~Node();
	//Copy
	Node(const Node<T> & n);
	//Assignment
	Node<T> & operator=(const Node<T> & rhs);

	bool operator != (const Node& obj);

	//Mutators//
	//Getters
	Node<T> * Next();
	Node<T> * Prev();

	//Setters
	void Next(Node<T> * n);
	void Prev(Node<T>* n);

	//Node Variables
	T m_data;
	Node<T> * m_next;
	Node<T> * m_prev;
};

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: A node is created with no inputs supplied
*
*
* Postcondition: a node is created with default values
*
*
************************************************************************/
template <class T>
Node<T>::Node()
	: m_next(nullptr), m_prev(nullptr), m_data()
{ }

/**********************************************************************
* Purpose: 1 arg constructor
*
* Precondition: A node is created with given data
*
*
* Postcondition: a node is created with the data given
*
*
************************************************************************/
template <class T>
Node<T>::Node(T data)
	: m_next(nullptr), m_prev(nullptr), m_data(data)
{ }

/**********************************************************************
* Purpose: copy constructor
*
* Precondition: A node is created by copying another
*
*
* Postcondition: a node is created with the same characteristics of the node supplied
*
*
************************************************************************/
template <class T>
Node<T>::Node(const Node & n)
	: m_next(n.m_next), m_prev(n.m_prev), m_data(n.m_data)
{
	
}

/**********************************************************************
* Purpose: Assignment overload
*
* Precondition: A node is set equal to another
*
*
* Postcondition: the lhs copies the data and pointers of the rhs
*
*
************************************************************************/
template <class T>
Node<T> & Node<T>::operator=(const Node & rhs)
{
	//check for self-assignment
	if (&rhs != this)
	{
		m_next = rhs.m_next;
		m_prev = rhs.m_prev;
		m_data = rhs.m_data;
	}

	return *this;
}

template<class T>
inline bool Node<T>::operator!=(const Node& obj)
{
	return false;
}

/**********************************************************************
* Purpose: Default destructor
*
* Precondition:called explicity by consumer or implicitly when out of scope
*
*
* Postcondition: all member variables a deleted and returned to default values
*					all variables are primitives, so no action is needed here
*
************************************************************************/
template <class T>
Node<T>::~Node()
{
}

/**********************************************************************
* Purpose: get the pointer to next node
*
* Precondition: a valid pointer exists
*
*
* Postcondition: a copy of the pointer is returned
*
*
************************************************************************/
template <class T>
Node<T>* Node<T>::Next()
{
	return m_next;
}

/**********************************************************************
* Purpose: get the pointer to previous node
*
* Precondition: a valid pointer exists
*
*
* Postcondition: a copy of the pointer is returned
*
*
************************************************************************/
template<class T>
Node<T>* Node<T>::Prev()
{
	return m_prev;
}

/**********************************************************************
* Purpose: set the pointer to next node
*
* Precondition: a valid pointer is supplied
*
*
* Postcondition: the next node is set to the address supplied
*
*
************************************************************************/
template <class T>
void Node<T>::Next(Node<T> * n)
{
	m_next = n;
}

/**********************************************************************
* Purpose: set the pointer to previous node
*
* Precondition: a valid pointer is supplied
*
*
* Postcondition: the next node is set to the address supplied
*
*
************************************************************************/
template<class T>
void Node<T>::Prev(Node<T>* n)
{
	m_prev = n;
}
