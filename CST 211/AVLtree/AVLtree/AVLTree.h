/*************************************************************
* Author:         Eren Bikmaz
* Filename:       AVLTree.h
* Date Created:   2/4/20
**************************************************************/

/************************************************************************
* Class: AVLTree
*
* Purpose: Contain and manage an AVL Tree
*
* Stipulations:
*	1.You must include the following functions.
*		a.Insert
*		b.Delete
*		c.Purge
*		d.Height
*		e.InOrder Traversal
*		f.PreOrder Traversal
*		g.PostOrder Traversal
*		h.BreadthFirst Traversal
*		i. <<Appropriate Manager Functions>>
*
* Canonical Methods:
*	AVLTree();
*	~AVLTree();
*	AVLTree(const AVLTree & copy);
*	AVLTree(AVLTree && move);
*	AVLTree<T> & operator=(const AVLTree<T> & copy);
*	AVLTree<T> & operator=(AVLTree<T> && move);
*
* public accessors/mutators
*	void Insert(T data);
*	void Delete(T data);
*	void Purge();
*	int Height();
*	int HeightIter();
*
*************************************************************************/
#pragma once
#include "AVLNode.h"
#include "Exception.h"

#include <queue>
using std::queue;

template <class T>
class AVLTree
{
public:
	//Cannocial Methods
	AVLTree();
	~AVLTree();
	AVLTree(const AVLTree & copy);
	AVLTree(AVLTree && move);
	AVLTree<T> & operator=(const AVLTree<T> & copy);
	AVLTree<T> & operator=(AVLTree<T> && move);

	//Mutators/Accessors
	void Insert(T data);
	void Delete(T data);
	void Purge();
	int Height();
	int HeightIter();

	//Traversal Function wrappers, must accept function pointers from consumer
	void InOrder(void (*visit)(T data));
	void PreOrder(void (*visit)(T data));
	void PostOrder(void (*visit)(T data));
	void BreadthFirst(void (*visit)(T data));

protected:
	//Private accessors
	int HeightCheck(AVLNode<T>*& root);
	const int IterativeHeight(AVLNode<T>* root);

	//private mutators
	void InsertNode(AVLNode<T>*& root, T data);//deprecated
	void DeleteNode(AVLNode<T>*& parent, T data);
	void CheckNode(T data);
	void Copy(const AVLNode<T>* root);
	void Purging(AVLNode<T>*& root);

	//Traversal Functions, must accept function pointers from consumer
	void InOrderTraversal(AVLNode<T>*& root, void (*visit)(T data));
	void PreOrderTraversal(AVLNode<T>*& root, void (*visit)(T data));
	void PostOrderTraversal(AVLNode<T>*& root, void (*visit)(T data));
	void BreadthFirstTraversal(AVLNode<T>* root, void (*visit)(T data));

	//AVL-specific functions
	void CheckBalance(AVLNode<T>*& root);
	void EfficentInsert(AVLNode<T>*& root, T data, bool& taller);
	void LeftBalance(AVLNode<T>*& root);
	void RightBalance(AVLNode<T>*& root);
	void UpdateBalance(AVLNode<T>*& root);

	//Balance Cases
	void RightRight(AVLNode<T>*& root);
	void LeftLeft(AVLNode<T>*& root);
	void RightLeft(AVLNode<T>*& root);
	void LeftRight(AVLNode<T>*& root);

	AVLNode<T>* m_root;
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
inline AVLTree<T>::AVLTree(): m_root(nullptr)
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
inline AVLTree<T>::~AVLTree()
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
inline AVLTree<T>::AVLTree(const AVLTree & copy): m_root(nullptr)
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
inline AVLTree<T>::AVLTree(AVLTree&& move)
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
inline AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& copy)
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
inline AVLTree<T>& AVLTree<T>::operator=(AVLTree<T>&& move)
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
inline void AVLTree<T>::Insert(T data)
{
	//InsertNode(m_root, data);
	bool taller = false;
	EfficentInsert(m_root, data, taller);
}

/**********************************************************************
* Purpose: Efficently inserts and balances the tree
*
* Precondition: valid nodes are provided, no duplicate data supplied
*
* Postcondition: Node is inserted and list is rebalanced, if needed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::EfficentInsert(AVLNode<T>*& root, T data, bool& taller)
{
	if (!root)
	{	//if at a leaf
		root = new AVLNode<T>(data);
		taller = true;
	}
	else if (data < root->m_data)
	{
		EfficentInsert(root->m_left, data, taller);
		if (taller)
		{
			switch (root->m_weight)
			{
			case LH:
				LeftBalance(root);
				taller = false;
				break;
			case EH:
				root->m_weight = LH;
				break;
			case RH:
				root->m_weight = EH;
				taller = false;
				break;
			}
		}
	}
	else
	{
		EfficentInsert(root->m_right, data, taller);
		if (taller)
		{
			switch (root->m_weight)
			{
			case RH:
				RightBalance(root);
				taller = false;
				break;
			case EH: //PROBLEM	
				root->m_weight = RH;
				break;
			case LH:
				root->m_weight = EH;
				taller = false;
				break;
			}
		}
	}
}

/**********************************************************************
* Purpose: Perform LL or LR rotation, as approiate 
*
* Precondition: the situation calls for an LL or LR rotation
*
* Postcondition: tree is re balanced
*
************************************************************************/
template<typename T>
inline void AVLTree<T>::LeftBalance(AVLNode<T>*& root)
{
	if (root->m_left->m_weight == LH)
	{	
		//LL
		LeftLeft(root);
		UpdateBalance(root);
	}
	else if (root->m_left->m_weight == RH)
	{	//LR
		LeftRight(root);
		UpdateBalance(root);
	}
}

/**********************************************************************
* Purpose: Perform RR or RL rotation, as approiate
*
* Precondition: the situation calls for an RR or RL rotation
*
* Postcondition: tree is re balanced
*
************************************************************************/
template<typename T>
inline void AVLTree<T>::RightBalance(AVLNode<T>*& root)
{
	if (root->m_right->m_weight == RH)
	{ 
		//RR
		root->m_weight = EH;
		RightRight(root);
		UpdateBalance(root);
	}
	else if (root->m_right->m_weight == LH)
	{ //RL
		RightLeft(root);
		UpdateBalance(root);
	}
}

template<class T>
inline void AVLTree<T>::UpdateBalance(AVLNode<T>*& root)
{
	if (root->m_left->m_left == nullptr && root->m_left->m_right == nullptr
		|| root->m_right->m_left != nullptr && root->m_right->m_right != nullptr)
	{
		root->m_left->m_weight = EH;
	}
	if (root->m_right->m_left == nullptr && root->m_right->m_right == nullptr
		|| root->m_right->m_left != nullptr && root->m_right->m_right != nullptr)
	{
		root->m_right->m_weight = EH;
	}
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
inline void AVLTree<T>::Delete(T data)
{
	if (m_root == nullptr)
	{
		throw Exception("Tree is empty");
	}
	
	CheckNode(data);

	bool shorter = true;

	CheckBalance(m_root);
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
inline void AVLTree<T>::Purge()
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
inline int AVLTree<T>::Height()
{
	int height = 0;
	if (m_root != nullptr)
	{
		height = HeightCheck(m_root);
	}
	return height - 1;
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
inline int AVLTree<T>::HeightIter()
{
	return IterativeHeight(m_root);
}

/**********************************************************************
* Purpose: public wrapper for InOrderTraversal
*
* Precondition: function provided is valid
*
* Postcondition: tree is traversed and visit function performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::InOrder(void(*visit)(T data))
{
	InOrderTraversal(m_root, visit);
}

/**********************************************************************
* Purpose: public wrapper for PreOrderTraversal
*
* Precondition: function provided is valid
*
* Postcondition: tree is traversed and visit function performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::PreOrder(void(*visit)(T data))
{
	PreOrderTraversal(m_root, visit);
}

/**********************************************************************
* Purpose: public wrapper for PostOrderTraversal
*
* Precondition: function provided is valid
*
* Postcondition: tree is traversed and visit function performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::PostOrder(void(*visit)(T data))
{
	PostOrderTraversal(m_root, visit);
}

/**********************************************************************
* Purpose: public wrapper for BreadthFirstTraversal
*
* Precondition: function provided is valid
*
* Postcondition: tree is traversed and visit function performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::BreadthFirst(void(*visit)(T data))
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
inline int AVLTree<T>::HeightCheck(AVLNode<T>*& root)
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
inline void AVLTree<T>::InsertNode(AVLNode<T> *& root, T data)
{
	if (root == nullptr)
	{	//resolve: new node
		root = new AVLNode<T>(data);
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
		throw Exception("Node already exists!");
	}
}

/**********************************************************************
* Purpose: Handle the deletion of a particular node
*
* Precondition: node must be valid
*
* Postcondition: matching node is deleted
*
************************************************************************/
template<class T>
inline void AVLTree<T>::DeleteNode(AVLNode<T>*& parent, T data)
{
	AVLNode<T>* cur = parent;
	if (cur == nullptr)
	{
		throw Exception("node doesnt exist!");
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
		AVLNode<T>* prev = cur;
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
* Postcondition: calls delete on appropriate node
*
************************************************************************/
template<class T>
inline void AVLTree<T>::CheckNode(T data)
{
	if (m_root == nullptr)
	{
		throw Exception("Tree empty");
	}
	else
	{
		AVLNode<T>* cur = m_root;
		AVLNode<T>* prev = m_root;
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
			throw Exception("error");
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

/**********************************************************************
* Purpose: copy another tree
*
* Precondition: tree provided is valid
*
* Postcondition: tree is copied into this tree
*
************************************************************************/
template<class T>
inline void AVLTree<T>::Copy(const AVLNode<T>* root)
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

/**********************************************************************
* Purpose: Recursive purge function, delete all contents of list
*
* Precondition: none
*
* Postcondition: list is emptied
*
************************************************************************/
template<class T>
inline void AVLTree<T>::Purging(AVLNode<T>*& root)
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
inline void AVLTree<T>::InOrderTraversal(AVLNode<T> *& root, void(*visit)(T data))
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
inline void AVLTree<T>::PreOrderTraversal(AVLNode<T>*& root, void(*visit)(T data))
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
inline void AVLTree<T>::PostOrderTraversal(AVLNode<T>*& root, void(*visit)(T data))
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
inline void AVLTree<T>::BreadthFirstTraversal(AVLNode<T>* root, void(*visit)(T data))
{
	if (root != nullptr)
	{
		//make a queue and add root to queue
		queue <AVLNode<T>*> q;
		q.push(root);

		while (!q.empty()) //while queue isnt empty
		{
			//Dequeue
			AVLNode<T>* node = q.front();
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
		
		}
	}
}

/**********************************************************************
* Purpose: Determine height without recursion
*
* Precondition: root is valid 
*
* Postcondition: returns height of tree
*
************************************************************************/
template<typename T>
inline const int AVLTree<T>::IterativeHeight(AVLNode<T>* root)
{
	int height = 0;
	if (root != 0)
	{
		queue<AVLNode<T>*> queue;
		//queue.push(root);
		AVLNode<T>* front;

		while (!queue.empty())
		{
			int size = queue.size();

			while (size--)
			{
				front = queue.front();
				queue.pop();

				if (front->m_left != nullptr)
				{
					queue.push(front->m_left);

				}
				if (front->m_right != nullptr)
				{
					queue.push(front->m_right);

				}
			}
			height++;
		}
	}
	return height;
}

/**********************************************************************
* Purpose: Correct all balance factors of the tree, rebalance if needed
*
* Precondition: list exists
*
* Postcondition: list is balanced
*
************************************************************************/
template<class T>
inline void AVLTree<T>::CheckBalance(AVLNode<T>*& root)
{
	if (root != nullptr)
	{
		//go left
		CheckBalance(root->m_left);
		//go right
		CheckBalance(root->m_right);
		//resolve: check for weight -2 or 2
		if (root->m_left == nullptr && root->m_right == nullptr)
		{	//at a leaf
			root->m_weight = EH;
		}
		else if (root->m_left == nullptr && root->m_right != nullptr)
		{	//right heavy
			root->m_weight = RH;
			if (root->m_right->m_weight != EH )
			{	//this node is unbalanced!
				RightBalance(root);
			}
		}
		else if (root->m_left != nullptr && root->m_right == nullptr)
		{	//left heavy
			root->m_weight = LH;
			if (root->m_left->m_weight != EH)
			{	//this node is unbalanced!
				LeftBalance(root);
			}
		}
		else if (root->m_left != nullptr && root->m_right != nullptr)
		{	//two balance factors to consider
			if (root->m_left->m_weight != EH)
			{	//this node is unbalanced!
				LeftBalance(root);
			}
			else if (root->m_right->m_weight != EH)
			{
				//this node is unbalanced!
				RightBalance(root);
			}
		}

	}
	
}

/**********************************************************************
* Purpose: Perform RR Rotation
*
* Precondition: this rotation is appropriate 
*
* Postcondition: rotation is performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::RightRight(AVLNode<T>*& root)
{
	//backup data of what will become the root
	T newrootdata = root->m_right->m_data;
	//backup all subtrees
	AVLNode<T>* t1 = root->m_left;
	AVLNode<T>* t2 = root->m_right->m_left;
	AVLNode<T>* t3 = root->m_right->m_right;

	//move root's data to the left node and give correct subtrees
	//replace left child with copy of right child
	root->m_left = root->m_right;
	//move root data to the left
	root->m_left->m_data = root->m_data;
	//move t2 to the right
	root->m_left->m_right = t2;
	//assign t1 from earlier 
	root->m_left->m_left = t1;

	//assign t3 to the right of root
	root->m_right = t3;

	//reassign data to root
	root->m_data = newrootdata;
}

/**********************************************************************
* Purpose: Perform LL Rotation
*
* Precondition: this rotation is appropriate
*
* Postcondition: rotation is performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::LeftLeft(AVLNode<T>*& root)
{
	//backup data of what will become the root
	T newrootdata = root->m_left->m_data;
	//backup all subtrees
	AVLNode<T>* t1 = root->m_right;
	AVLNode<T>* t2 = root->m_left->m_right;
	AVLNode<T>* t3 = root->m_left->m_left;

	//move root's data to the left node and give correct subtrees
	//replace right child with copy of left child
	root->m_right = root->m_left;
	//move root data to the right
	root->m_right->m_data = root->m_data;
	//move t2 to the right
	root->m_right->m_left = t2;
	//assign t1 from earlier 
	root->m_right->m_right = t1;

	//assign t3 to the right of root
	root->m_left = t3;

	//reassign data to root
	root->m_data = newrootdata;
}

/**********************************************************************
* Purpose: Perform RL Rotation
*
* Precondition: this rotation is appropriate
*
* Postcondition: rotation is performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::RightLeft(AVLNode<T>*& root)
{
	//call LL on right
	LeftLeft(root->m_right);
	//call RR
	RightRight(root);
}

/**********************************************************************
* Purpose: Perform LR Rotation
*
* Precondition: this rotation is appropriate
*
* Postcondition: rotation is performed
*
************************************************************************/
template<class T>
inline void AVLTree<T>::LeftRight(AVLNode<T>*& root)
{
	//call RR on left
	RightRight(root->m_left);
	//call LL
	LeftLeft(root);
}
