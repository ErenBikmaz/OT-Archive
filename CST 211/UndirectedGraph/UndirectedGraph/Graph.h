/*************************************************************
* Author:         Eren Bikmaz
* Filename:       OBJ.h
* Date Created:   2/16/2020
**************************************************************/

/************************************************************************
* Class: Graph
*
* Purpose: Manage and contain a list of inter-connected verticies
*
* Canonical Methods:
*
* Accessor Methods:
*
* Mutator Methods:
*
*************************************************************************/
#pragma once
#include "Vertex.h"

#include <queue>
using std::queue;
#include <stack>
using std::stack;

#include <iterator>
using std::iterator;

#include <exception>
using std::exception;

template <class V, class E>
class Graph
{

public:
	//Caanonical Methods//
	//Con/Destructors
	Graph();
	~Graph();
	//Copy
	Graph(const Graph<V, E>& n);
	//Assignment
	Graph<V, E>& operator=(const Graph<V, E>& rhs);

	//Mutators//
	void InsertVertex(V data);
	void RemoveVertex(V data); 
	void Connect(V first, V second, 
		E firstData, int firstWeight);
	void RemoveEdge(E data);

	//Accessors//
	void BreadthFirstTraversal(void(*visit)(V value));
	void DepthFirstTraversal(void(*visit)(V value));

private:

	//Internal logic
	void AddEdge(Vertex<V, E>* source, Vertex<V, E>* destination, E data, int weight);
	Vertex<V, E> * Find(V data);
	void CheckVert(V data);
	void ResetFlags();


	//Node Variables
	list<Vertex<V,E>> m_verts;

};

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: Graph is created with no inputs supplied
*
* Postcondition: Graph is created with default values
*
************************************************************************/
template <class V, class E>
Graph<V, E>::Graph()
	: m_verts()
{ }

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the Graph falls out of scope
*
* Postcondition: contents of Graph are purged and pointers reset
*
************************************************************************/
template<class V, class E>
inline Graph<V, E>::~Graph()
{ }

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a Graph is created given another Graph
*
* Postcondition: a new Graph is created, identical to the one provided
*
************************************************************************/
template <class V, class E>
Graph<V, E>::Graph(const Graph<V, E>& copy)
	: m_verts(copy.m_verts)
{ }

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: Graph's data is set equal to by that of another
*
* Postcondition: Graph's data is overwritten by that of another
*
************************************************************************/
template<class V, class E>
inline Graph<V, E>& Graph<V, E>::operator=(const Graph<V, E>& copy)
{
	//check for self-assignment
	if (&copy != this)
	{
		m_verts = copy.m_verts;
	}

	return *this;
}

/**********************************************************************
* Purpose: Insert a vertex into the graph
*
* Precondition: V data is valid and can be compared
*
* Postcondition: vertex with v data created
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::InsertVertex(V data)
{
	//check if identical vert already exists
	CheckVert(data);

	//create new vertex
	Vertex<V, E> temp(data);
	
	//add to List
	m_verts.push_back(temp);

}

/**********************************************************************
* Purpose: Remove a vertex with v data
*
* Precondition: vertex exists
*
* Postcondition: vertex is removed
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::RemoveVertex(V data)
{
	//First, completely decouple the vertex from the graph, if needed
	Vertex<V, E>* ptr = Find(data);
	if (!ptr->m_edges.empty())
	{
		stack<E> toDelete;
	
		//find all edges associated with node to delete
		typename list<Edge<V, E>>::iterator i;
		for (i = ptr->m_edges.begin(); i != ptr->m_edges.end(); i++)
		{
			toDelete.push(i->m_data);
		}

		//remove all those edges
		while (!toDelete.empty())
		{
			RemoveEdge(toDelete.top());
			toDelete.pop();
		}
	}

	//vertex for comparison
	Vertex<V, E> vert(data);

	//then just remove this vertex from m_verts
	m_verts.remove(vert);
}

/**********************************************************************
* Purpose: Connect two nodes with edges
*
* Precondition: both nodes exist 
*
* Postcondition: nodes are connected, error thrown if a node is invalid
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::Connect(V first, V second,
								E data, int weight)
{

	//Get ptrs to both nodes to be connected
	Vertex<V, E> *  v1 = Find(first);
	Vertex<V, E> *  v2 = Find(second);

	////connect the nodes by adding edges with given weights
	AddEdge(v1, v2, data, weight);
	AddEdge(v2, v1, data, weight);
}

/**********************************************************************
* Purpose: Perform a Breadth First Traversal
*
* Precondition: visit() is a valid function
*
* Postcondition: visit() is performed at all nodes
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::BreadthFirstTraversal(void(*visit)(V value))
{
	//Enqueue the starting vertex
	queue<Vertex<V, E> * >  q;
	q.push(& m_verts.front());

	while (!q.empty())
	{
		//loop and dequeue
		Vertex<V, E> * vert = q.front();
		q.pop();

		if (!vert->m_flag)
		{
			//after processing vertex, enqueue adjacent verts
			visit(vert->m_data);

			typename list<Edge<V, E>>::iterator i;
			for (i = vert->m_edges.begin(); i != vert->m_edges.end(); i++)
			{
				q.push(i->m_vert);
			}
			//mark this node as visited
			vert->m_flag = true;
		}

		//done when queue is empty
	}

	//reset all flags to false
	ResetFlags();
}

/**********************************************************************
* Purpose: Perform a Depth First Traversal
*
* Precondition: visit() is a valid function
*
* Postcondition: visit() is performed at all nodes
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::DepthFirstTraversal(void(*visit)(V value))
{
	//Push Vertex onto stack
	stack<Vertex<V, E> * > s;
	s.push( & m_verts.front());

	while (!s.empty())
	{
		//loop and pop the stack
		Vertex<V, E> * vert = s.top();
		s.pop();

		if (!vert->m_flag)
		{
			//after processsing this vertex, push all neighbors
			visit(vert->m_data);

			typename list<Edge<V, E>>::iterator i;
			for (i = vert->m_edges.begin(); i != vert->m_edges.end(); i++)
			{
				s.push(i->m_vert);
			}
			//mark this node as visited
			vert->m_flag = true;
		}

		//when stack is empty, done with traversal
	}

	//reset all flags to false
	ResetFlags();
}

/**********************************************************************
* Purpose: Add a single, one-way edge
*
* Precondition: source is a valid vertex
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::AddEdge(Vertex<V, E>* source, 
	Vertex<V, E>* destination, E data, int weight)
{
	//instantiate Edge
	Edge<V, E> edge(destination, data, weight);

	//push to vertex's edge list
	(*source).m_edges.push_back(edge);
}

/**********************************************************************
* Purpose: Remove all instances of a given edge
*
* Precondition: Edge with E data exists
*
* Postcondition: all edges with E data removed
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::RemoveEdge(E data)
{
	//create edge for list.remove
	Edge<V, E> edge(data);

	//remove all edges with matching data
	typename list<Vertex<V, E>>::iterator i;
	for (i = m_verts.begin(); i != m_verts.end(); i++)
	{
		i->m_edges.remove(edge);
	}
}

/**********************************************************************
* Purpose: Reset all traversal flags in the graph
*
* Precondition: m_verts has nodes to traverse
*
* Postcondition: m_flags is set to false in all verts
*
************************************************************************/
template<class V, class E>
inline void Graph<V, E>::ResetFlags()
{
	typename list<Vertex<V, E>>::iterator i = m_verts.begin();
	for (i = m_verts.begin(); i != m_verts.end(); i++)
	{
		//at each vertex...
		i->m_flag = false;
	}
}

/**********************************************************************
* Purpose: Find a vertex with matching data in m_verts
*
* Precondition: data supplied exists in the graph
*
* Postcondition: ptr to matching node is reuturned
*
************************************************************************/
template<class V, class E>
inline Vertex<V, E> * Graph<V, E>::Find(V data)
{
	//traverse list of verticies 
	typename list<Vertex<V, E>>::iterator i = m_verts.begin();
	for (i = m_verts.begin(); i != m_verts.end(); i++)
	{
		if ((*i).m_data == data)
		{
			//if match found, return ptr
			return &(*i);
		}
	}
	//else, throw
	throw exception("No such node exists!");
}

template<class V, class E>
inline void Graph<V, E>::CheckVert(V data)
{
	typename list<Vertex<V, E>>::iterator i = m_verts.begin();
	for (i = m_verts.begin(); i != m_verts.end(); i++)
	{
		if ((*i).m_data == data)
		{
			//vert already exists!
			throw exception("Duplicate nodes are not legal!");
		}
	}
}

