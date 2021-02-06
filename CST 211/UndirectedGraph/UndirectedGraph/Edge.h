/*************************************************************
* Author:         Eren Bikmaz
* Filename:       OBJ.h
* Date Created:    2/16/2020
* Modifications:
*
**************************************************************/

/************************************************************************
* Class: Edge
*
* Purpose: connect one vertex to another
*
*************************************************************************/
#pragma once
#include <list>
using std::list;

//Forward Declaration
template <typename V, typename E>
class Graph;
//
template <typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge
{
	//Friend with graph/vertex class??
	friend class Graph<V, E>;
	friend class Vertex<V, E>;


public:
	//Canonical Methods//
	//Con/Destructors
	Edge();
	Edge(E data);
	Edge(Vertex<V, E>* vert, E data, int weight);
	~Edge();
	//Copy
	Edge(const Edge<V,E> & copy);
	//Assignment
	Edge<V, E>& operator=(const Edge<V, E> & copy);
	//Comparison
	bool operator == (Edge<V, E> rhs) const;

private:
	//Node Variables
	int m_weight;
	E m_data;
	Vertex<V, E>* m_vert;
};

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: OBJ is created with no inputs supplied
*
* Postcondition: OBJ is created with default values
*
************************************************************************/
template <typename V, typename E>
Edge<V, E>::Edge()
	: m_data(), m_vert(nullptr)
{ }

template<typename V, typename E>
inline Edge<V, E>::Edge(E data)
	: m_data(data)
{
}

/**********************************************************************
* Purpose: NUMS-arg constructor
*
* Precondition: OBJ is created with NUMS inputs supplied
*
* Postcondition: OBJ is created with given values
*
************************************************************************/
template <typename V, typename E>
Edge<V, E>::Edge(Vertex<V, E>* vert, E data, int weight)
	:m_data(data), m_weight(weight), m_vert(vert)
{ }

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the OBJ falls out of scope
*
* Postcondition: contents of OBJ are purged and pointers reset
*
***********************************************************************/
template<typename V, typename E>
Edge<V, E>::~Edge()
{
	m_vert = nullptr;
}

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a OBJ is created given another OBJ
*
* Postcondition: a new OBJ is created, identical to the one provided
*
************************************************************************/
template<typename V, typename E>
Edge<V, E>::Edge(const Edge<V, E> & copy)
	:m_data(copy.m_data), m_weight(copy.m_weight), m_vert(copy.m_vert)
{

}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: OBJ's data is set equal to by that of another
*
* Postcondition: OBJ's data is overwritten by that of another
*
************************************************************************/
template<typename V, typename E>
inline Edge<V, E>& Edge<V, E>::operator=(const Edge<V, E>& copy)
{
	//check for self-assignment
	if (&copy != this)
	{
		m_data = copy.m_data;
		m_weight = copy.m_weight;
		m_vert = copy.m_vert;
	}

	return *this;
}

template<typename V, typename E>
inline bool Edge<V, E>::operator==(Edge<V, E> rhs) const
{
	if (rhs.m_data == m_data)
	{
		return true;
	}
	return false;
}
