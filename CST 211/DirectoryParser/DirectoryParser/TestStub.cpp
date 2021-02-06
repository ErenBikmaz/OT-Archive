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

#include <string>
using std::string;
#include <list>
using std::list;

#include <crtdbg.h>
#include <conio.h>
#include <filesystem>
using std::filesystem::directory_iterator;

void IterRecursive(list<string> & List, string path, string & condition, string & filter);
void SaveList(list<string>& List);
void ReadListFromMemory(list<string>& List);
void SearchList(string data);
void ParseDriectory(string & path, string& condition, string& filter);
/************************************************************************
* Assignment: Create a program that will dig through provided directories 
* and store files in a data structure
*
*************************************************************************/
int main(int argc, char* argv[])
{
    string path;
    string filter = "***";
    string condition = "***";
    //Get Arguments
    if (argc < 2 || argc > 3)
    {
        //not enough/too many args, complain and do nothing
        cout << "Invalid number of command arguments! \nExample:-r 'c:/test/'*.docx ";
    }
    //valid # of args, now need to check them
    else if (argc == 2) // 2 args
    {
        path = argv[1];
        //either just directory, directory w/ filter, or search term
        if (path.find(":") != string::npos)
        {
            cout << "Parsing Directory: " << path << endl;
            ParseDriectory(path, condition, filter);
        }
        else //argv[1] is search term
        {
            //Arg is Term to search from previous data
            cout << "Searching for provided argument: " << path << endl;
            SearchList(path);
        }
    }
    else // 3 args = modfier, directory with/without filter
    {
        //get condition (argv[1])
        condition = argv[1];
        //get path (argv[2])
        path = argv[2];

        cout << "Parsing Directory Recursively: " << path << endl;
        ParseDriectory(path, condition, filter);
    }
}

/**********************************************************************
* Purpose: Iterate through a given directory and save file paths, if appropriate
*
* Precondition: Path is valid, List is initialized
*
* Postcondition: List is filled with file paths as dictated by condition and filter
*
************************************************************************/
void IterRecursive(list<string>& List, string path, string & condition, string & filter)
{
    //Iterate through this directory
    for (const auto& entry : directory_iterator(path))
    {
        //if matches filter OR no filter set, save and print
        int pivot = entry.path().generic_string().find(filter);
        if (pivot != string::npos || filter == "***")
        {
            //print directory(debug)
            cout << entry.path().generic_string() << endl;
            //Save to list
            List.push_back(entry.path().generic_string());
        }
        //if at folder & recursive condition met, delve deeper
        if (entry.is_directory() && condition == "-r")
        {
            IterRecursive(List, entry.path().generic_string(), condition, filter);
        }
    }
}

/**********************************************************************
* Purpose: Save the contents of list to a txt file
*
* Precondition: List has data to write, txt file exists
*
* Postcondition: contents of list are saved to Results.txt
*
************************************************************************/
void SaveList(list<string>& List)
{
    ofstream txt("Results.txt");
    if (!txt.is_open())
    {
        cout << "\n\nError, output file not found, please try again";
    }
    typename list<string>::iterator i;
    for (i = List.begin(); i != List.end(); i++)
    {
        txt << (*i) << endl;
    }
    txt.close();
}

/**********************************************************************
* Purpose: Read .txt file into a list
*
* Precondition: list is initalized
*
* Postcondition: .txt file has valid data
*
************************************************************************/
void ReadListFromMemory(list<string>& List)
{
    ifstream txt("Results.txt");
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
    ReadListFromMemory(List);

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

/**********************************************************************
* Purpose: Parse a given directory with or without a filter
*
* Precondition: path is valid
*
* Postcondition: path directory is written to file with given arguments
*
************************************************************************/
void ParseDriectory(string& path, string& condition, string& filter)
{
    //Check if path has a filter
    int pivot = path.find('*');
    if (pivot != string::npos)
    {
        //filter found, must split from path
        filter = path.substr(pivot+1, path.size());
        path.resize(pivot);
    }

    //Populate Data Struct
    list<string> list;
    IterRecursive(list, path, condition, filter);
    //Write list to file 
    SaveList(list);
}
