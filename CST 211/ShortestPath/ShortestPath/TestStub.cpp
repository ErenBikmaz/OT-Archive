#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <conio.h>

#include "Graph.h"

#include <iostream>
using std::cout;
using std::cin;
#include <fstream>
using std::ifstream;
#include <sstream>
using std::stringstream;

#include <string>
using std::string;
using std::stoi;

#include <vector>
using std::vector;
#include <stack>
using std::stack;

struct Table
{
	vector<int> distance;
	vector<string> verts;
	vector<int> predecessor;
};

string Getstr(const char * msg);
void InitializeTable(Table & t);
void ReadMap(Graph<string, string> & map);
void Dijkstra(Graph<string, string> & map); //USES FIXED VALUES ATM
void ReadEdges(Graph<string, string>& map, string current,
	Table & t);
string FindNext(Graph<string, string>& map, 
	Table & t);
void FindPath(Graph<string, string>& map, 
	string current, Table& t);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//instantiate a graph
	Graph<string, string> map;

	//read in verts and connections from source file
	ReadMap(map);

	//determine distance between two given points
	Dijkstra(map);

	//done
	cout << "\nPress ENTER to Exit";
	cin.get();
}

/**********************************************************************
* Purpose: Get a string from user input
*
************************************************************************/
string Getstr(const char* msg)
{
	string out;
	cout << msg;
	getline(cin, out);
	return out;
}

/**********************************************************************
* Purpose: Intitalize all cells of the table to default values
*
************************************************************************/
void InitializeTable(Table & t)
{
	for (int i = 0; i < t.verts.size(); i++)
	{
		t.distance[i] = 0;
		t.verts[i] = " ";
		t.predecessor[i] = 0;
	}
}

/**********************************************************************
* Purpose: Read-in a provided txt file and create a graph
*
*	The format for the file is:
*		Start Node,End Node,Path,Mileage
*
* Precondition: "Map" is empty or has no conflicting data
*
* Postcondition: OUTPUTANDPOTENTIALTHROWNERRORS
*
************************************************************************/
void ReadMap(Graph<string, string>& map)
{
	//open the file
	ifstream txt("lab05.txt");

	string buffer;
	string src;
	string dest;
	string edge;
	int weight;

	//if (file isn't opened)
	if (!txt.is_open())
	{
		throw exception("File not found");
	}

	//while (not at EOF)
	while (getline(txt, buffer))
	{
		//read in a line of data
		stringstream ss(buffer);
		getline(ss, src, ',');
		getline(ss, dest, ',');
		getline(ss, edge, ',');
		getline(ss, buffer, ',');
		weight = stoi(buffer);

		//if start node doesn't exist, create it
		map.InsertVertex(src);
		//if end node doesn't exist, create it
		map.InsertVertex(dest);

		//connect those nodes
		map.Connect(src, dest, edge, weight);
	}

	//close the file
	txt.close();
}

/**********************************************************************
* Purpose: Find the shortest path between two points
*
*		Write a program that allows the user to enter in any 
*	starting point and any ending point and your program 
*	will provide the shortest (distance) path to the desired destination. 
*	Show the path from the source to the destination as well as the 
*	estimated time to arrive at your destination (assume you go the 
*	speed limit and that I-5 is 65 mph while all other roads are 55 mph).
*
* Precondition: Map
*
* Postcondition: Shortest Path is printed to screen
*
************************************************************************/
void Dijkstra(Graph<string, string> & map)
{
	string origin;
	string dest;
	while (!map.CheckVert(origin) || !map.CheckVert(dest))
	{
		//Get str for starting vert
		origin = Getstr("\nEnter Starting Point: ");
		if (!map.CheckVert(origin))
		{
			cout << "Starting Point not found!\n";
		}
		else
		{
			//get str for destination
			dest = Getstr("\nEnter Destination: ");
			if (!map.CheckVert(dest))
			{
				cout << "Destination not found!\n Please try again.\n";
			}
		}
	}

	//1: Instantiate vectors based on size of graph
	Table t;
	t.distance.resize(map.GetSize()+1);
	t.verts.resize(map.GetSize()+1);
	t.predecessor.resize(map.GetSize()+1);
	InitializeTable(t);

	//2: Identify the starting index (origin)
	string current = origin;

	//3: Update distance for start ( = 0)
	t.distance[0] = 0;
	t.verts[0] = origin;
	t.predecessor[0] = -1;

	//for (int i = 0; i < map.GetSize(); i++)
	while (current != "done")
	{
		//4: Using current vert, update distance to other verts
		//5: when a change is made to distace, update predacessor
		ReadEdges(map, current, t);

		//6: Mark this vert as processed
		map.SetFlag(current);

		//7: choose the vert with smallest distance, return to step 4
		current = FindNext(map, t);
	}

	//now we have the shortest path to anywhere, now find path to dest
	FindPath(map, dest, t);

}

/**********************************************************************
* Purpose: Add all the verts connected to current
*
* Precondition: current is unprocessed
*
* Postcondition: all neighbors are added or updated, if needed
*
************************************************************************/
void ReadEdges(Graph<string, string>& map, string current, 
	Table & t)
{
	//use a const-iterator
	typename list<Edge<string, string>>::const_iterator
		iter = map.GetEdgeIter(current);
	//also get the end 
	typename list<Edge<string, string>>::const_iterator
		end = map.GetEdgeIterEnd(current);

	//find current's index in the table
	int currentIndex = 0;
	while (current != t.verts[currentIndex] )
	{
		currentIndex++;
	}

	//while (not at end of list)
	while (iter != end)
	{
		//read edge data
		int weight = (*iter).GetWeight();
		string vert = (*iter).GetVert();

		//detrmine if this vert has been seen before
		int index = 0;

		//travel to open cell or matching cell
		while (vert != t.verts[index] && t.verts[index] != " ")
		{
			index++;
		}

		//if so, create its space
		if (t.verts[index] == " ")
		{
			t.distance[index] = weight + t.distance[currentIndex];
			t.verts[index] = vert;
			t.predecessor[index] = currentIndex;
		}
		else if ( t.distance[index] > weight + t.distance[currentIndex])
		{
			//otherwise, update path if smaller
			t.distance[index] = weight + t.distance[currentIndex];
			//t.verts[index] = vert;
			t.predecessor[index] = currentIndex;
		}

		//proceed to next edge
		iter++;
	}
}

/**********************************************************************
* Purpose: Determine which vertex to visit next
*
* Precondition: current has been processed
*
* Postcondition: returns unprocessed vertex with lowest distance 
*
************************************************************************/
string FindNext(Graph<string, string>& map, Table & t)
{
	//find lowest value in distance and return if not flagged
	int min = 99999;
	int index = -1;
	int i = 1;
	while (t.verts[i] != " " && i < t.verts.size())
	{
		if (t.distance[i] < min && !map.CheckFlag(t.verts[i]))
		{
			min = t.distance[i];
			index = i;
		}
		i++;
	}
	//based on min, return approprate vert
	if (index == -1)
	{
		return "done";
	}
	return t.verts[index];
}

/**********************************************************************
* Purpose: Determine the shortest route with data from the table
*
* Precondition: table is correct
*
* Postcondition: prints shortest route, mileage and time
*
************************************************************************/
void FindPath(Graph<string, string>& map, string dest, Table& t)
{
	//create stack to store verts and edges names
	stack<string> s;
	//add mileage for roads 
	int miles = 0;
	int I5miles = 0;

	//find index of dest
	int index = 0;
	while (dest != t.verts[index])
	{
		index++;
	}

	string edge;
	//starting from dest, traverse table unti you hit -1
	while (t.predecessor[index] != -1)
	{
		//push vert into stack
		s.push(t.verts[index]);

		edge = map.GetEdge(t.verts[index], t.verts[t.predecessor[index]]);
		//push edge name onto stack
		s.push(edge);
		//accumulate miles
		if (edge == "I5")
		{
			I5miles += map.GetWeight(t.verts[index], t.verts[t.predecessor[index]]);
		}
		else
		{
			miles += map.GetWeight(t.verts[index], t.verts[t.predecessor[index]]);
		}

		//go to predecssor
		index = t.predecessor[index];
	}

	cout << "\nStarting at " << t.verts[0] << ", go to: ";

	//now pop that stack and print route
	while (!s.empty())
	{
		cout << "via " << s.top() << ", ";
		s.pop();
		cout << s.top() << ", ";
		s.pop();
	}

	cout << "\nThe trip will cover " << miles << " miles";

	//minutes for miles
	int minutes = (miles / 0.92) + (I5miles / 1.08);

	//calculate hours
	int hours = minutes / 60;
	minutes %= 60;

	cout << "\nAnd take approximately " << hours << " hours and " << minutes << " minutes";
}
