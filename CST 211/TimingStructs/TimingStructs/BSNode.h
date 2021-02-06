/*************************************************************
* Author:         Eren Bikmaz
* Filename:       BSNode.h
* Date Created:   1/24/20
**************************************************************/
#pragma once

//forward declaration
template <class T>
class BSTree;

template <class T>
class BSNode
{
	//Friend with tree class
	friend class BSTree<T>;

public:

	BSNode();
	~BSNode<T>();
	BSNode(T data);
	BSNode<T>(const BSNode<T> & copy);
	BSNode<T>& operator=(const BSNode<T>& copy);

private:
	T m_data;
	BSNode<T> * m_left;
	BSNode<T> * m_right;
};

template <class T>
BSNode<T>::BSNode(): m_left(nullptr), m_right(nullptr)
{
}

template <class T>
BSNode<T>::BSNode(T data) : m_data(data), m_left(nullptr), m_right(nullptr)
{
}

template<class T>
inline BSNode<T>& BSNode<T>::operator=(const BSNode<T>& copy)
{
	if (this != &copy)
	{
		//copy data
		m_left = copy.m_left;
		m_right = copy.m_right;
		m_data = copy.m_data;
	}
	return *this;
}

template<class T>
inline BSNode<T>::~BSNode()
{
	m_left = nullptr;
	m_right = nullptr;
}

template <class T>
BSNode<T>::BSNode(const BSNode<T>& copy) : m_left(nullptr), m_right(nullptr)
{
	if (copy.m_data == NULL)
	{
		m_data = copy.m_data;
		m_left = copy.m_left;
		m_right = copy.m_right;
	}
}

