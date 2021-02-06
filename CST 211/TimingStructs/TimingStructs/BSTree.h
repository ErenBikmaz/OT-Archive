/*************************************************************
* Author:         Eren Bikmaz
* Filename:       BSTree.h
* Date Created:   1/24/20
**************************************************************/
/************************************************************************
* Class: BSTree
*
* Purpose: Manage and wrap a binary search tree
*
* Accessor/Mutator Methods:
*	Insert
*	Delete
*	Purge
*	Height
*	
* Traversal
*	InOrderTraversal
*	PreOrderTraversal
*	PostOrderTraversal
*	BreadthFirstTraversal
*
*
*************************************************************************/
#pragma once
#include "BSNode.h"
#include <exception>
using std::exception;

#include <queue>
using std::queue;

template <class T>
class BSTree
{
public:
	//Cannocial Methods
	BSTree();
	~BSTree();
	BSTree(const BSTree & copy);
	BSTree(BSTree && move);
	BSTree<T> & operator=(const BSTree<T> & copy);
	BSTree<T> & operator=(BSTree<T> && move);

	//Mutators/Accessors
	void Insert(T data);
	void Delete(T data);
	void Purge();
	int Height();
	void SearchTest(T data);

	//Traversal Function wrappers, must accept function pointers from consumer
	void InOrder(void (*visit)(T data));
	void PreOrder(void (*visit)(T data));
	void PostOrder(void (*visit)(T data));
	void BreadthFirst(void (*visit)(T data));

private:
	//Private accessors
	int HeightCheck(BSNode<T>*& root);
	void SearchInt(BSNode<T>*& root, T data);

	//private mutators
	void InsertNode(BSNode<T>*& root, T data);
	void DeleteNode(BSNode<T>*& parent, T data);//needs help
	void CheckNode(T data);//needs help
	void Copy(const BSNode<T>* root);
	void Purging(BSNode<T>*& root);

	//Traversal Functions, must accept function pointers from consumer
	void InOrderTraversal(BSNode<T>*& root, void (*visit)(T data));
	void PreOrderTraversal(BSNode<T>*& root, void (*visit)(T data));
	void PostOrderTraversal(BSNode<T>*& root, void (*visit)(T data));
	void BreadthFirstTraversal(BSNode<T>* root, void (*visit)(T data));

	BSNode<T>* m_root;
};

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: BSTree is created with no inputs supplied
*
* Postcondition: BSTree is created with default values
*
************************************************************************/
template<class T>
inline BSTree<T>::BSTree(): m_root(nullptr)
{
}

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the BSTree falls out of scope
*
* Postcondition: contents of BSTree are purged and pointers reset
*
************************************************************************/
template<class T>
inline BSTree<T>::~BSTree()
{
	Purge();
}

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a BSTree is created given another BSTree
*
* Postcondition: a new BSTree is created, identical to the one provided
*
************************************************************************/
template<class T>
inline BSTree<T>::BSTree(const BSTree & copy): m_root(nullptr)
{
	if (copy.m_root != nullptr)
	{
		//use preorder traversal to iterate through tree and add nodes
		Copy(*&copy.m_root);
	}
}

/**********************************************************************
* Purpose: Move Constructor
*
* Precondition: BSTree is created given another BSTree
*
* Postcondition: a new BSTree is created, and the BSTree provided is reset
*
************************************************************************/
template<class T>
inline BSTree<T>::BSTree(BSTree&& move)
{
	if (move.m_root != nullptr)
	{
		//commit theft
		m_root = move.m_root;
		move.m_root = nullptr;
	}
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: BSTree's data is set equal to by that of another
*
* Postcondition: BSTree's data is overwritten by that of another
*
************************************************************************/
template<class T>
inline BSTree<T>& BSTree<T>::operator=(const BSTree<T>& copy)
{
	if (this != &copy)
	{
		//dispose existing data
		Purge();
		if (copy.m_root != nullptr)
		{
			//use preorder traversal to iterate through tree and add nodes
			Copy(copy.m_root);
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: move assignment operator
*
* Precondition: An BSTree's data is set equal to by that of another
*
* Postcondition: An BSTree's data is overwritten by that of another , which is also reset
*
************************************************************************/
template<class T>
inline BSTree<T>& BSTree<T>::operator=(BSTree<T>&& move)
{
	//check for self assignment
	if (this != &move)
	{
		//dispose existing data
		Purge();
		if (move.m_root != nullptr)
		{
			//commit theft
			m_root = move.m_root;
			move.m_root = nullptr;
		}
	}
	return *this;
}

/**********************************************************************
* Purpose: Wrapper function to insert a new node with provided data
*
* Precondition: provided data is valid
*
* Postcondition: none
*
************************************************************************/
template<class T>
inline void BSTree<T>::Insert(T data)
{
	InsertNode(m_root, data);
}

/**********************************************************************
* Purpose: Find a particular node to delete, then pass that on to be deleted
*
* Precondition: data supplied matches a node in the list
*
* Postcondition: If that node exists, it is removed, error thrown otherwise
*
************************************************************************/
template<class T>
inline void BSTree<T>::Delete(T data)
{
	if (m_root == nullptr)
	{
		throw exception("Tree is empty");
	}
	
	CheckNode(data);
}

/**********************************************************************
* Purpose: Empty the tree completely
*
* Precondition: none
*
* Postcondition: the tree is emptied
*
************************************************************************/
template<class T>
inline void BSTree<T>::Purge()
{
	if (m_root != nullptr)
	{
		//delete leaves (easiest to delete) until tree is empty
		Purging(m_root);
	}
}

/**********************************************************************
* Purpose: return the height of the tree
*
* Precondition: none
*
* Postcondition: the height of the tree is returned
*
************************************************************************/
template<class T>
inline int BSTree<T>::Height()
{
	int height = 0;
	if (m_root != nullptr)
	{
		height = HeightCheck(m_root);
	}
	return height - 1;
}

template<class T>
inline void BSTree<T>::SearchTest(T data)
{
	SearchInt(m_root, data);
}

/**********************************************************************
* Purpose: public wrapper for InOrderTraversal
*
* Precondition: INPUTSANDVULNERABLITIES
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
template<class T>
inline void BSTree<T>::InOrder(void(*visit)(T data))
{
	InOrderTraversal(m_root, visit);
}

/**********************************************************************
* Purpose: public wrapper for PreOrderTraversal
*
* Precondition: INPUTSANDVULNERABLITIES
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
template<class T>
inline void BSTree<T>::PreOrder(void(*visit)(T data))
{
	PreOrderTraversal(m_root, visit);
}

/**********************************************************************
* Purpose: public wrapper for PostOrderTraversal
*
* Precondition: INPUTSANDVULNERABLITIES
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
template<class T>
inline void BSTree<T>::PostOrder(void(*visit)(T data))
{
	PostOrderTraversal(m_root, visit);
}

/**********************************************************************
* Purpose: public wrapper for BreadthFirstTraversal
*
* Precondition: INPUTSANDVULNERABLITIES
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
template<class T>
inline void BSTree<T>::BreadthFirst(void(*visit)(T data))
{
	BreadthFirstTraversal(m_root, visit);
}

/**********************************************************************
* Purpose: Private Recursive Function for Height()
*
* Precondition: there is at least one node in the list (Height ensures this)
*
* Postcondition: returns the height of the list
*
************************************************************************/
template<class T>
inline int BSTree<T>::HeightCheck(BSNode<T>*& root)
{
	//use a postorder traversal to determine height
	int left = 0;
	int right = 0;
	if (root != nullptr)
	{
		//go left
		left = HeightCheck(root->m_left) + 1;
		//go right
		right = HeightCheck(root->m_right) + 1;
		//resolve: return highest number of branches
	}
	return left > right ? left: right;
}

template<class T>
inline void BSTree<T>::SearchInt(BSNode<T>*& root, T data)
{
	if (data == root->m_data)
	{	//resolve: data found
		
	}
	else if (data < root->m_data)
	{	//less than: <- left
		SearchInt(root->m_left, data);
	}
	else if (data > root->m_data)
	{	//greater than: -> right
		SearchInt(root->m_right, data);
	}
	else 
	{	
		throw exception("Node not found");
	}
}

/**********************************************************************
* Purpose: Add a new node to the list via recursive logic
*
* Precondition: valid data supplied, root provided internally,
*		data is not equal to any other node!
*
* Postcondition: a new node is added at the appropriate location
*		if data is equal to that of an existing node, an error is thrown
*
************************************************************************/
template<class T>
inline void BSTree<T>::InsertNode(BSNode<T> *& root, T data)
{
	if (root == nullptr)
	{	//resolve: new node
		root = new BSNode<T>(data);
	}
	else if (data < root->m_data)
	{	//less than: <- left
		InsertNode(root->m_left, data);
	}
	else if (data > root->m_data)
	{	//greater than: -> right
		InsertNode(root->m_right, data);
	}
	else
	{	//data is equal
		throw exception("Node already exists!");
	}
}

/**********************************************************************
* Purpose: Handle the deletion of a particular node
*
* Precondition: node must be valid
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
template<class T>
inline void BSTree<T>::DeleteNode(BSNode<T>*& parent, T data)
{
	BSNode<T>* cur = parent;
	if (cur == nullptr)
	{
		throw exception("node doesnt exist!");
	}
	if (cur->m_left == nullptr && cur->m_right == nullptr)
	{	//node is a leaf, delete it
		//inform parent
		parent = nullptr;
	}
	else if (cur->m_left == nullptr && cur->m_right != nullptr)
	{	//data node has empty left
		//point parent to only child
		parent = parent->m_right;
	}
	else if (cur->m_left != nullptr && cur->m_right == nullptr)
	{	//data node has empty right
		//point parent to only child
		parent = parent->m_left;
	}
	else 
	{	//data node has two children
		cur = parent->m_left;
		BSNode<T>* prev = cur;
		while (cur->m_right != nullptr)
		{
			prev = cur;
			cur = cur->m_right;
		}
		parent->m_data = cur->m_data;
		if (prev == nullptr)
		{
			parent->m_left = cur->m_left;
			prev->m_right = nullptr;
		}
		else
		{
			prev->m_right = cur->m_left;
			parent->m_left = nullptr;
		}

	}
	delete cur;
}

/**********************************************************************
* Purpose: Check if a node matches provided data. if so, delete it
*
* Precondition: the appropriate node must exist
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
template<class T>
inline void BSTree<T>::CheckNode(T data)
{
	if (m_root == nullptr)
	{
		throw exception("Tree empty");
	}
	else
	{
		BSNode<T>* cur = m_root;
		BSNode<T>* prev = m_root;
		bool found = false;
		while (cur != nullptr && found == false)
		{
			if (cur->m_data == data)
			{
				found = true;
			}
			else
			{
				prev = cur;
				if (cur->m_data > data)
				{
					cur = cur->m_left;
				}
				else
				{
					cur = cur->m_right;
				}
			}
		}
		if (cur == nullptr)
		{
			throw exception("error");
		}
		else if (found)
		{
			if (m_root == cur)
			{
				DeleteNode(m_root, data);
			}
			else if (prev->m_data > data)
			{
				DeleteNode(prev->m_left, data);
			}
			else
			{
				DeleteNode(prev->m_right, data);
			}
		}
	}
}

template<class T>
inline void BSTree<T>::Copy(const BSNode<T>* root)
{
	//use preorder logic to copy each cell to m_root
	if (root != nullptr)
	{
		//resolve: insert this node
		Insert(root->m_data);
		//go left
		Copy(root->m_left);
		//go right
		Copy(root->m_right);
	}
}

template<class T>
inline void BSTree<T>::Purging(BSNode<T>*& root)
{
	if (root != nullptr)
	{
		//go left
		Purging(root->m_left);
		//go right
		Purging(root->m_right);
		//resolve: delete
		DeleteNode(root, root->m_data);
	}
}

/**********************************************************************
* Purpose: Internal traversal function, in order
*
* Precondition: root and func ptr are valid
*
* Postcondition: traverses the tree, errors must be handled by provided functions
*
************************************************************************/
template<class T>
inline void BSTree<T>::InOrderTraversal(BSNode<T> *& root, void(*visit)(T data))
{
	if (root != nullptr)
	{
		//go left
		InOrderTraversal(root->m_left, visit);
		//perform action with ptr
		visit(root->m_data);
		//go right
		InOrderTraversal(root->m_right, visit);
	}
}

/**********************************************************************
* Purpose: Internal traversal function, Pre order
*
* Precondition: root and func ptr are valid
*
* Postcondition: traverses the tree, errors must be handled by provided functions
*
************************************************************************/
template<class T>
inline void BSTree<T>::PreOrderTraversal(BSNode<T>*& root, void(*visit)(T data))
{
	if (root != nullptr)
	{
		//perform action with ptr
		visit(root->m_data);
		//go left
		PreOrderTraversal(root->m_left, visit);
		//go right
		PreOrderTraversal(root->m_right, visit);
	}
}

/**********************************************************************
* Purpose: Internal traversal function, Post order
*
* Precondition: root and func ptr are valid
*
* Postcondition: traverses the tree, errors must be handled by provided functions
*
************************************************************************/
template<class T>
inline void BSTree<T>::PostOrderTraversal(BSNode<T>*& root, void(*visit)(T data))
{
	if (root != nullptr)
	{
		//go left
		PostOrderTraversal(root->m_left, visit);
		//go right
		PostOrderTraversal(root->m_right, visit);
		//perform action with ptr
		visit(root->m_data);
	}
}

/**********************************************************************
* Purpose: Internal traversal function, breadth first
*
* Precondition: root and func ptr are valid
*
* Postcondition: traverses the tree, errors must be handled by provided functions
*
************************************************************************/
template<class T>
inline void BSTree<T>::BreadthFirstTraversal(BSNode<T>* root, void(*visit)(T data))
{
	if (root != nullptr)
	{
		//make a queue and add root to queue
		queue <BSNode<T>*> q;
		q.push(root);

		while (!q.empty()) //while queue isnt empty
		{
			//Dequeue
			BSNode<T>* node = q.front();
			q.pop();
			//perform action with ptr
			visit(node->m_data);

			//check for left node
			if (node->m_left != nullptr)
			{
				//add that node to queue
				q.push(node->m_left);
			}
			//check for right node
			if (node->m_right != nullptr)
			{
				//add that node to queue
				q.push(node->m_right);
			}
		//delete node;
		}
	}
}
