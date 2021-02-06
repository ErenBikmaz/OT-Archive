/*************************************************************
* Author:         Eren Bikmaz
* Filename:       TestStub.cpp
* Date Created:   3/6/20
* Modifications:
*   3/6/20 - Created filesystem iterator
*   3/7/20 - Added reading and writing capabilities
*   3/8/20 - Added command arguement compatibility
**************************************************************/
#define _CRTDBG_MAP_ALLOC

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ofstream;
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <list>
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::list;

#include <string>
using std::string;

#include "Array.h"
#include "List.h"
#include "BSTree.h"
#include "AVLTree.h"
#include "HashTable.h"

#include <crtdbg.h>
#include <conio.h>

//Logistics
void PoplulateFromMemory(list<string>& List);
void SearchList(string data);
void PrintTime(_int64 duration);
void CheckNode(string data);
int stringhash(string key);

//Struct Populators
void PopulateArray(Array<string> & arr, list<string> & src);
void PopulateList(List<string> & List, list<string> & src);
void PopulateBTree(BSTree<string> & BTree, list<string> & src);
void PopulateATree(AVLTree<string> & ATree, list<string> & src);
void PopulateTable(HashTable<string, string>& Table, list<string> & src);

//Struct Searches
void SearchArray(Array<string> & arr, string & item);
void SearchList(List<string> & List, string & item);
void SearchBTree(BSTree<string> & BTree, string & item);
void SearchATree(AVLTree<string> & ATree, string & item);
void SearchTable(HashTable<string, string> & Table, string & item);

template <typename T> //T = type for sorting
void TimeInsertion(void(*func)(T& value, list<string> & src), T & arr, list<string>& src);
template <typename T> //T = type for sorting
void TimeSearch(void(*func)(T& value, string & item), T & arr, string & item);
/************************************************************************
* Assignment: Insert data from Results.txt into various data structs and time it
*               Search that struct for data and time it.
*
*************************************************************************/
int main(int argc, char* argv[])
{
    //Instantiate Everything

    //STL List to read from file
    list<string> buffer;
    PoplulateFromMemory(buffer);
    int num = buffer.size();
    string item = "C:/Users/Eren Bikmaz/source/repos/CST_211/1DArray";

    //Array
    Array<string> Arr;
    Arr.SetLength(num);
    TimeInsertion<Array<string>>(PopulateArray, Arr, buffer);
    TimeSearch<Array<string>>(SearchArray, Arr, item);

    //Linked List
    List<string> Lis;
    TimeInsertion<List<string>>(PopulateList, Lis, buffer);
    TimeSearch<List<string>>(SearchList, Lis, item);

    //Binary Search Tree
    BSTree<string> BTree;
    TimeInsertion<BSTree<string>>(PopulateBTree, BTree, buffer);
    TimeSearch<BSTree<string>>(SearchBTree, BTree, item);

    //AVL Tree
    AVLTree<string> ATree;
    TimeInsertion<AVLTree<string>>(PopulateATree, ATree, buffer);
    TimeSearch<AVLTree<string>>(SearchATree, ATree, item);

    //Hash Table
    HashTable<string, string> test(stringhash, 10);
    PopulateTable(test, buffer);
    SearchTable(test, item);
    
}


/**********************************************************************
* Purpose: Read .txt file into a struct and time it
*
* Precondition: struct is initalized
*
* Postcondition: .txt file has valid data
*
************************************************************************/
void PoplulateFromMemory(list<string>& List)
{
    ifstream txt("Data.txt");
    string buffer;
    string src;

    //if (file isn't opened)
    if (!txt.is_open())
    {
        cout << "\n\nError, input file not found, please try again";
    }

    //while (not at EOF)
    while (getline(txt, buffer))
    {
        //read in a line of data
        stringstream ss(buffer);
        getline(ss, src, '\n');
        //add to list
        List.push_back(src);
    }
    //close the file
    txt.close();
}

/**********************************************************************
* Purpose: Find entires that match data and print if they match
*
* Precondition: data is valid
*
* Postcondition: matching data printed to console
*
************************************************************************/
void SearchList(string data)
{
    //Read data from last run
    list<string> List;

    //Search for matching data in the list
    typename list<string>::iterator i;
    for (i = List.begin(); i != List.end(); i++)
    {
        //check if matching
        if ((*i).find(data) != string::npos)
        {
            //matched: print
            string buffer = (*i);
            cout << "\n" << buffer;
        }
    }
}

void PrintTime(_int64 duration)
{
    //need duration in H:m:s:ms
    //3600000 milisecond in a hour
    //3600000,000 microseconds in a hour
    int hr = duration / 3600000000;
    duration = duration - 3600000000 * hr;
    //60000 milisecond in a minute
    //3600000,000 microseconds in a minute
    int min = duration / 60000000;
    duration = duration - 60000000 * min;
    //1000 milisecond in a second
    //1000,000 microseconds in a second
    int sec = duration / 1000000;
    duration = duration - 1000000 * sec;
    //1000 microseconds in a milisecond
    int ms = duration / 1000;
    duration = duration - 1000 * ms;

    cout << hr << " hrs "
        << min << " min "
        << sec << " sec "
        << ms << " ms "
        << duration << " us";
}

void CheckNode(string data)
{
    if (data == "C:/Users/Eren Bikmaz/source/repos/CST_211/1DArray")
    {

    }
}

int stringhash(string key)
{
    //hard-coded for given size
    return key.length() % 10;
}


void PopulateArray(Array<string> & arr, list<string>& src)
{
    cout << "\n" << "PopulateArray\n";
    typename list<string>::iterator i;
    int j = 0;
    for (i = src.begin(); i != src.end(); i++, j++)
    {
        arr[j] = (*i);
    }
}

void PopulateList(List<string>& List, list<string>& src)
{
    cout << "\n" << "PopulateList\n";
    typename list<string>::iterator i;
    int j = 0;
    for (i = src.begin(); i != src.end(); i++, j++)
    {
        List.Append(*i);
    }
}

void PopulateBTree(BSTree<string>& BTree, list<string>& src)
{
    cout << "\n" << "PopulateBTree\n";
    typename list<string>::iterator i;
    int j = 0;
    for (i = src.begin(); i != src.end(); i++, j++)
    {
        BTree.Insert(*i);
    }
}

void PopulateATree(AVLTree<string>& ATree, list<string>& src)
{
    cout << "\n" << "PopulateATree\n";
    typename list<string>::iterator i;
    int j = 0;
    for (i = src.begin(); i != src.end(); i++, j++)
    {
        ATree.Insert(*i);
    }
}

void PopulateTable(HashTable<string, string>& Table, list<string>& src)
{
    cout << "\n" << "PopulateTable\n";
    //start timer
    auto t1 = high_resolution_clock::now();
    //perform sort
    typename list<string>::iterator i;
    int j = 0;
    for (i = src.begin(); i != src.end(); i++, j++)
    {
        Table.Insert(*i, *i);
    }
    
    //end timer
    auto t2 = high_resolution_clock::now();

    //calculate duration and print results
    _int64 duration = duration_cast<microseconds>(t2 - t1).count();
    //Output results
    PrintTime(duration);
}

void SearchArray(Array<string>& arr, string & item)
{
    cout << "\n" << "SearchArray\n";
    int length = arr.GetLength();
    bool found = false;

    for (int i = 0; i < length && found; i++)
    {
        if (arr[i] == item)
        {
            cout << "Item found";
            found = true;
        }
    }
}

void SearchList(List<string>& List, string& item)
{
    cout << "\n" << "SearchList\n";
    List.Extract(item);

}

void SearchBTree(BSTree<string>& BTree, string& item)
{
    cout << "\n" << "SearchBTree\n";
    BTree.SearchTest(item);
}

void SearchATree(AVLTree<string>& ATree, string& item)
{
    cout << "\n" << "SearchATree\n";
    ATree.SearchTest(item);
}

void SearchTable(HashTable<string, string>& Table, string& item)
{
    cout << "\n" << "SearchTable\n";

    //start timer
    auto t1 = high_resolution_clock::now();
    //perform sort
    Table.SearchTest(item);
    //end timer
    auto t2 = high_resolution_clock::now();

    //calculate duration and print results
    _int64 duration = duration_cast<microseconds>(t2 - t1).count();
    //Output results
    PrintTime(duration);

    
}

template<typename T>
void TimeInsertion(void(*func)(T& value, list<string>& src), T & arr, list<string>& src)
{
    //start timer
    auto t1 = high_resolution_clock::now();
    //perform sort
    func(arr, src);
    //end timer
    auto t2 = high_resolution_clock::now();

    //calculate duration and print results
    _int64 duration = duration_cast<microseconds>(t2 - t1).count();
    //Output results
    PrintTime(duration);
}

template<typename T>
void TimeSearch(void(*func)(T& value, string& item), T & arr, string& item)
{
    //start timer
    auto t1 = high_resolution_clock::now();
    //perform sort
    func(arr, item);
    //end timer
    auto t2 = high_resolution_clock::now();

    //calculate duration and print results
    _int64 duration = duration_cast<microseconds>(t2 - t1).count();
    //Output results
    PrintTime(duration);
}
