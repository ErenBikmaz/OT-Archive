/*************************************************************
* Author:         Eren Bikmaz
* Filename:       HashTable.h
* Date Created:   2/11/20
* Modifications:
*
**************************************************************/

/************************************************************************
* Class: HashTable
*
* Stipulations:
*	Using the STL vector, list, and pair classes, create a Hash Table ADT. 
*	The data in the hash table must be stored in a pair object that contains 
*	both the key and the value. The HashTable class must have at least the 
*	following functions besides the canonical functions:	
*		void Insert(K key, V value);
*		void setHash(int (*hash)(K key)); // store the function ptr in data member
*		V operator [] (K key);
*		void Delete(K key);
*		void Traverse(void (*visit)(V value));
*
* Purpose: Contain and manage a hashtable
*
* Canonical Methods:
*	HashTable();
*	HashTable(int numBuckets = 0);
*	HashTable(int (*hash)(K key) = nullptr, int numBuckets = 0);
*	~HashTable();
*	HashTable(const HashTable& copy);
*	HashTable& operator = (const HashTable& copy);
*
* Hashing Functions:
*	void Insert(K key, V value);
*	void setHash(int (*hash)(K key)); 
*	V operator [] (K key);
*	void Delete(K key);
*	void Traverse(void (*visit)(V value));
*
*************************************************************************/
#pragma once
#include <exception>
using std::exception;
#include <iterator>
using std::iterator;
#include <vector>
using std::vector;
#include <list>
using std::list;

using std::pair;


template<class K, class V> class HashTable
{
public:

	//Cannocial Methods
	HashTable();
	HashTable(int numBuckets = 0);
	HashTable(int (*hash)(K key) = nullptr, int numBuckets = 0);
	~HashTable();
	HashTable(const HashTable& copy);
	HashTable& operator = (const HashTable& copy);

	//Hashing Functions
	void Insert(K key, V value);
	void setHash(int (*hash)(K key)); 
	V operator [] (K key);
	void Delete(K key);
	void Traverse(void (*visit)(V value));

private:

	vector<list<pair<K, V>>> m_table;
	int (*m_hash)(K key);

};

/**********************************************************************
* Purpose: Default constructor
*
* Precondition: HashTable is created with no inputs supplied
*
* Postcondition: HashTable is created with default values
*
************************************************************************/
template<class K, class V>
inline HashTable<K, V>::HashTable():m_hash(nullptr), m_table(0)
{
}

/**********************************************************************
* Purpose: 1-arg constructor
*
* Precondition: HashTable is created with 1 inputs supplied
*
* Postcondition: HashTable is created with given values
*
************************************************************************/
template<class K, class V>
inline HashTable<K, V>::HashTable(int numBuckets) : m_hash(nullptr), m_table(numBuckets)
{
}

/**********************************************************************
* Purpose: 2-arg constructor
*
* Precondition: HashTable is created with 2 inputs supplied
*
* Postcondition: HashTable is created with given values
*
************************************************************************/
template<class K, class V>
inline HashTable<K, V>::HashTable(int (*hash)(K key), int numBuckets)
	:m_hash(hash), m_table(numBuckets)
{
}

/**********************************************************************
* Purpose: Destructor
*
* Precondition: manually called or the HashTable falls out of scope
*
* Postcondition: contents of HashTable are purged and pointers reset
*
************************************************************************/
template<class K, class V>
inline HashTable<K, V>::~HashTable()
{
	m_table.clear();
	m_hash = nullptr;
}

/**********************************************************************
* Purpose: Copy Constructor
*
* Precondition: a HashTable is created given another HashTable
*
* Postcondition: a new HashTable is created, identical to the one provided
*
************************************************************************/
template<class K, class V>
inline HashTable<K, V>::HashTable(const HashTable& copy)
	:m_hash(copy.m_hash), m_table(copy.m_table)
{
}

/**********************************************************************
* Purpose: copy assignment operator
*
* Precondition: HashTable's data is set equal to by that of another
*
* Postcondition: HashTable's data is overwritten by that of another
*
************************************************************************/
template<class K, class V>
inline HashTable<K, V>& HashTable<K, V>::operator=(const HashTable& copy)
{
	return *this;
}

/**********************************************************************
* Purpose: Insert new data, key is used to make hash.
*
* Precondition: Key and data are valid
*
* Postcondition: if key is unique, data is inserted
*
************************************************************************/
template<class K, class V>
inline void HashTable<K, V>::Insert(K key, V value)
{
	if (m_hash == nullptr)
	{
		//hash function is nullptr
		throw "nullptr";
	}

	//generate a hash with provided key & hash function
	int index = m_hash(key);

	//check if the given bucket contains the same key
	typename list<pair<K, V>>::iterator i = m_table[index].begin();
	for (i = m_table[index].begin(); i != m_table[index].end(); i++)
	{
		if ((*i).first == key)
		{
			//identical key in this bucket
			throw "identical key";
		}
	}

	//instantiate new data pair
	pair<K, V> temp(key, value);

	//push into appropriate bucket
	m_table[index].push_back(temp);

}

/**********************************************************************
* Purpose: Sets m_hash to a provided hashing function
*
* Precondition: hash is assumed to be a reliable hashing function
*
* Postcondition: provided hash is set as m_hash, for good or ill
*
************************************************************************/
template<class K, class V>
inline void HashTable<K, V>::setHash(int(*hash)(K key))
{
	if ( hash == nullptr)
	{
		//hash function is nullptr
		throw exception("no hash function supplied!");
	}
	//set new hash function
	m_hash = hash;

	//dig out all data to rehash
	list<pair<K, V>> temp;

	//traverse table and push
	for (int j = 0; j < m_table.size(); j++)
	{	//in each bucket....
		typename list<pair<K, V>>::iterator i = m_table[j].begin();
		for (i = m_table[j].begin(); i != m_table[j].end(); i++)
		{
			temp.push_back((*i));
		}
	}

	int size = m_table.size();
	m_table.clear();
	m_table.resize(size);

	while (!temp.empty())
	{
		Insert(temp.front().first, temp.front().second);
		temp.pop_front();
	}
}

/**********************************************************************
* Purpose: Subscript operator overload
*
* Precondition: given key is valid and within bounds
*
*
* Postcondition: returns data at given key, or throw an exception
*
************************************************************************/
template<class K, class V>
inline V HashTable<K, V>::operator[](K key)
{
	V output;
	if (m_hash == nullptr)
	{
		//hash function is nullptr
		throw "nullptr";
	}
	//generate a hash with provided key & hash function
	int index = m_hash(key);
	
	//at given bucket, get value from given key
	typename list<pair<K, V>>::iterator i = m_table[index].begin();
	for (i = m_table[index].begin(); i != m_table[index].end(); i++)
	{
		if ((*i).first == key)
		{
			//now at desired index
			output = (*i).second;
		}
	}

	//return value 
	return output;
}

/**********************************************************************
* Purpose: Delete the item at the given key's hash
*
* Precondition: given key has data to delete
*
* Postcondition: delete node with given key
*
************************************************************************/
template<class K, class V>
inline void HashTable<K, V>::Delete(K key)
{
	if (m_hash == nullptr)
	{
		//hash function is nullptr
		throw "nullptr";
	}

	//generate a hash with provided key & hash function
	K index = m_hash(key);

	pair<K, V> toDelete;

	//delete information in appropriate bucket
	typename list<pair<K, V>>::iterator i = m_table[index].begin();
	for (i = m_table[index].begin(); i != m_table[index].end(); i++)
	{
		if ((*i).first == key)
		{
			//pair identified, copy data
			toDelete = (*i);
		}
	}
	//remove identified element
	m_table[index].remove(toDelete);

}

/**********************************************************************
* Purpose: Traverse the whole table, and perform the given function on each
*
* Precondition: provided function will operate on value of each pair
*
* Postcondition: each node's value is passed to visit.
*
************************************************************************/
template<class K, class V>
inline void HashTable<K, V>::Traverse(void(*visit)(V value))
{
	//through the whole table...w
	for (int j = 0; j < m_table.size(); j++)
	{	//in each bucket....
		typename list<pair<K, V>>::iterator i = m_table[j].begin();
		for (i = m_table[j].begin(); i != m_table[j].end(); i++)
		{
			//pass visit value of this node
			visit((*i).second);
		}
	}
}
