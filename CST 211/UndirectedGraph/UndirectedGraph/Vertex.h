/*************************************************************
* Author:         Eren Bikmaz
* Filename:       OBJ.h
* Date Created:    2/16/2020
* Modifications:
*
**************************************************************/

/************************************************************************
* Class: Vertex
*
* Purpose: contain data and edges to other verticies 
*
*************************************************************************/
#pragma once
#include "Edge.h"

#include <list>
using std::list;

//forward declaration
template <class V, class E>
class Graph;

template <class V, class E>
class Vertex
{
	//Friend with graph class??
	friend class Graph<V, E>;

public:
	//Canonical Methods//
	//Con/Destructors
	Vertex();
	~Vertex();
	Vertex(V data);
	//Copy
	Vertex(const Vertex<V, E>& copy);
	//Assignment
	Vertex<V, E> & operator=(const Vertex<V, E>& copy);
	bool operator==(Vertex<V, E> rhs) const;
	
private:
	//Node Variables
	V m_data;
	list<Edge<V, E>> m_edges;
	bool m_flag;
	
};

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: OBJ is created with no inputs supplied
*
* Postcondition: OBJ is created with default values
*
************************************************************************/
template <class V, class E>
Vertex<V, E>::Vertex()
	: m_data(), m_edges(), m_flag(false)
{ }

template<class V, class E>
inline Vertex<V, E>::Vertex(V data)
	: m_data(data), m_edges(), m_flag(false)
{ }

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the OBJ falls out of scope
*
* Postcondition: contents of OBJ are purged and pointers reset
*
************************************************************************/
template<class V, class E>
inline Vertex<V, E>::~Vertex()
{ }

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a OBJ is created given another OBJ
*
* Postcondition: a new OBJ is created, identical to the one provided
*
************************************************************************/
template <class V, class E>
Vertex<V, E>::Vertex(const Vertex<V, E>& copy)
	: m_data(copy.m_data), m_edges(copy.m_edges), m_flag(copy.m_flag)
{ }

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: OBJ's data is set equal to by that of another
*
* Postcondition: OBJ's data is overwritten by that of another
*
************************************************************************/
template<class V, class E>
inline Vertex<V, E>& Vertex<V, E>::operator=(const Vertex<V, E> & copy)
{
	//check for self-assignment
	if (&copy != this)
	{
		m_data = copy.m_data;
		m_edges = copy.m_edges;
		m_flag = copy.m_flag;
	}

	return *this;
}

template<typename V, typename E>
inline bool Vertex<V, E>::operator==(Vertex<V, E> rhs) const
{
	if (rhs.m_data == m_data)
	{
		return true;
	}
	return false;
}


