/*************************************************************
* Author:         Eren Bikmaz
* Filename:       BSNode.h
* Date Created:   1/24/20
**************************************************************/
#pragma once

#include <exception>
using std::exception;

//forward declaration
template <class T>
class AVLTree;

enum BalanceFactor { LH = 1, EH = 0, RH = -1 };

template <class T>
class AVLNode
{
	//Friend with tree class
	friend class AVLTree<T>;

public:

	AVLNode();
	~AVLNode<T>();
	AVLNode(T data);
	AVLNode<T>(const AVLNode<T> & copy);
	AVLNode<T>& operator=(const AVLNode<T>& copy);

protected:
	T m_data;
	AVLNode<T> * m_left;
	AVLNode<T> * m_right;
	BalanceFactor m_weight;
};

template <class T>
AVLNode<T>::AVLNode(): m_left(nullptr), m_right(nullptr), m_weight(EH)
{
}

template <class T>
AVLNode<T>::AVLNode(T data) : m_data(data), m_left(nullptr), m_right(nullptr), m_weight(EH)
{
}

template<class T>
inline AVLNode<T>::~AVLNode()
{
	m_left = nullptr;
	m_right = nullptr;
	m_weight = EH;
}

template <class T>
AVLNode<T>::AVLNode(const AVLNode<T>& copy) : m_left(nullptr), m_right(nullptr)
{
	if (copy.m_data == NULL)
	{
		m_data = copy.m_data;
		m_left = copy.m_left;
		m_right = copy.m_right;
		m_weight = copy.m_weight;
	}
}

template<class T>
inline AVLNode<T>& AVLNode<T>::operator=(const AVLNode<T>& copy)
{
	if (this != &copy)
	{
		//copy data
		m_left = copy.m_left;
		m_right = copy.m_right;
		m_data = copy.m_data;
		m_weight = copy.m_weight;
	}
	return *this;
}

