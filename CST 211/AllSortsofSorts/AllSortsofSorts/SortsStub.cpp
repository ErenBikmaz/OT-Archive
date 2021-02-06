/*************************************************************
* Author:         Eren Bikmaz
* Filename:       TestStub.ccp
* Date Created:   2/28/20
*
**************************************************************/

#define _CRTDBG_MAP_ALLOC

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
#include <fstream>
using std::ofstream;
#include <vector>
using std::vector;
#include "Array.h"

#include <crtdbg.h>
#include <conio.h>
#include <cstdlib>
using std::srand;
using std::rand;

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

#include <exception>
using std::exception;

// Array Logistics
void Randomize(int n, int* ptr, Array<int> & arr, vector<int> & vect);
void DeepCopy(int n, int * src, int *& newArr);
template<typename T, typename V>
void DeepCopy(int n, T& src, V& vect);
void Swap(int & x, int & y);

// I/O and Debugging
void Output(const char * str);
void PrintTime(_int64 duration);
template <typename T>
void PrintArr(int n, T arr);

// Sorts
template <typename T> //T = type for sorting
void RunSort(void(*visit)(int n ,T & value), int n, T arr);
template <typename T>
void BruteForceBubble(int n, T & arr);
template <typename T>
void FlaggedBubble(int n, T & arr);
template <typename T>
void Selection(int n, T & arr);
template <typename T>
void Insertion(int n, T & arr);
template <typename T>
void Shell(int n, T & arr);
//Heap
template <typename T>
void Heap(int n, T & arr);
template <typename T>
void MoveDown(T & arr, int first, int last);
//Merge
template <typename T>
void MergeSort(int n, T& arr);
template <typename T>
void MergeSort(T& arr, vector<int>& temp, int left, int right);
template <typename T>
void Merge(T& arr, vector<int>& temp, int left, int right, int end);
//Quick
template <typename T>
void QuickSort(int n, T& arr);
template <typename T>
void QuickSort(T& arr, int first, int last);

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//check for arguments and assign
	if (argc == 1)
	{
		throw exception("No arguement passed!");
	}
	int n = atoi(argv[1]);
	
	//reset output file
	Output(nullptr);

	//generate array of length n 
	int * ptr = new int[n];
	//and a backup
	int* backup = nullptr;
	//instantiate complex arrays
	Array<int> arr;
	arr.SetLength(n);
	vector<int> vect;
	vect.resize(n);

	//poplate arrs with random values
	Randomize(n, ptr, arr, vect);
	DeepCopy(n, ptr, backup);

	//run every sort, faster sorts go first for your sanity

	//Shell
	RunSort<int*>(Shell, n, ptr);
	RunSort<Array<int>>(Shell, n, arr);
	RunSort<vector<int>>(Shell, n, vect);
	DeepCopy(n, backup, ptr);

	//Heap(iterative)
	RunSort<int*>(Heap, n, ptr);
	RunSort<Array<int>>(Heap, n, arr);
	RunSort<vector<int>>(Heap, n, vect);
	DeepCopy(n, backup, ptr);

	//Merge(recursive)
	RunSort<int*>(MergeSort, n, ptr);
	RunSort<Array<int>>(MergeSort, n, arr);
	RunSort<vector<int>>(MergeSort, n, vect);
	DeepCopy(n, backup, ptr);

	//Quick(recursive)
	RunSort<int*>(QuickSort, n, ptr);
	RunSort<Array<int>>(QuickSort, n, arr);
	RunSort<vector<int>>(QuickSort, n, vect);
	DeepCopy(n, backup, ptr);

	//N^2 Sorts
	//Brute-Force Bubble
	RunSort<int*>(BruteForceBubble, n, ptr);
	RunSort<Array<int>>(BruteForceBubble, n, arr);
	RunSort<vector<int>>(BruteForceBubble, n, vect);
	DeepCopy(n, backup, ptr);

	//Flagged Bubble
	RunSort<int*>(FlaggedBubble, n, ptr);
	RunSort<Array<int>>(FlaggedBubble, n, arr);
	RunSort<vector<int>>(FlaggedBubble, n, vect);
	DeepCopy(n, backup, ptr);

	//Selection
	RunSort<int*>(Selection, n, ptr);
	RunSort<Array<int>>(Selection, n, arr);
	RunSort<vector<int>>(Selection, n, vect);
	DeepCopy(n, backup, ptr);

	//Insertion
	RunSort<int*>(Insertion, n, ptr);
	RunSort< Array<int>>(Insertion, n, arr);
	RunSort<vector<int>>(Insertion, n, vect);
	DeepCopy(n, backup, ptr);

	//Done
	cout << "\nPress ENTER to Exit";
	cin.get();
	delete[] ptr;
	delete[] backup;
}

/**********************************************************************
* Purpose: Populate all 3 arrays with identical random data
*
* Precondition: ptr, arr and vect are of size n
*
* Postcondition: ptr, arr and vect are populated with (0 < numbers < n)
*
************************************************************************/
void Randomize(int n, int* ptr, Array<int>& arr, vector<int>& vect)
{
	int randval = 0;
	srand(time(0));

	//for (each element in arr)
	for (int i = 0; i < n; i++)
	{
		//Get random value
		randval = rand() % n;

		//assign
		ptr[i] = randval;
		arr[i] = randval;
		vect[i] = randval;
		//DEBUG: PRINT
		//cout << ptr[i] << ", ";
	}
}

/**********************************************************************
* Purpose: Perform a deep copy of a dynamically allocated array
*
* Precondition: src and newArr are both of length n
*
* Postcondition: contents of newArr match src
*
************************************************************************/
void DeepCopy(int n, int * src, int *& newArr)
{	
	if (newArr != nullptr)
	{
		delete[] newArr;
		newArr = nullptr;
	}
	//deep copy whole list
	if (src != nullptr)
	{
		//create new array
		newArr = new int[n + 1];

		//Copy old arry into new
		for (int i = 0; i < n; i++)
		{
			newArr[i] = src[i];
		}
	}
}

/**********************************************************************
* Purpose: Swap two values, presumably in an array
*
* Precondition: both x and y are initialized
*
* Postcondition: values are swapped
*
************************************************************************/
void Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

/**********************************************************************
* Purpose: Print to Results.txt
*
* Precondition: txt file exists
*
* Postcondition: if str is nullptr, file is wiped, otherwise file is appended
*
************************************************************************/
void Output(const char* str)
{
	if ( str == nullptr )
	{
		ofstream txt("Results.txt");
		if (!txt.is_open())
		{
			throw exception("File not found");
		}
		txt << "All Sorts of Sorts!";
		txt.close();
	}
	else
	{
		ofstream txt("Results.txt", std::ios_base::app);
		if (!txt.is_open())
		{
			throw exception("File not found");
		}

		txt << str << "\n";

		txt.close();
	}
}

/**********************************************************************
* Purpose: Print elapsed time given miliseconds
*
* Precondition: duration must be initialized
*
* Postcondition: elapsed time is printed and written as h:m:s:ms
*
************************************************************************/
void PrintTime(_int64 duration)
{
	//need duration in H:m:s:ms
	//3600000 milliseconds in a minute
	int hr = duration / 3600000;
	duration = duration - 3600000 * hr;
	//60000 milliseconds in a minute
	int min = duration / 60000;
	duration = duration - 60000 * min;
	//1000 milliseconds in a second
	int sec = duration / 1000;
	duration = duration - 1000 * sec;

	cout << "\n";
	cout << hr << " hours and " 
		<< min << " minutes and " 
		<< sec << " seconds and " 
		<< duration << " milliseconds";

	//add this to file output as well
	ofstream txt("Results.txt", std::ios_base::app);
	if (!txt.is_open())
	{
		throw exception("File not found");
	}

	txt << "\n";
	txt << hr << " hrs "
		<< min << " min "
		<< sec << " sec "
		<< duration << " ms";

	txt.close();
}

/**********************************************************************
* Purpose: Perform a deep copy of another type
*
* Precondition: src and newArr are both of length n, both of same datatype
*
* Postcondition: contents of newArr match src
*
************************************************************************/
template<typename T, typename V>
void DeepCopy(int n, T & src, V & vect)
{
	//deep copy whole list
	if (n > 0)
	{
		//Copy old arry into new
		for (int i = 0; i < n; i++)
		{
			vect[i] = src[i];
		}
	}
}

/**********************************************************************
* Purpose: Print the contents of a given array
*
* Precondition: array is of length and is valid
*
* Postcondition: contents are printed and written to results
*
************************************************************************/
template<typename T>
void PrintArr(int n, T arr)
{
	ofstream txt("Results.txt", std::ios_base::app);
	if (!txt.is_open())
	{
		throw exception("File not found");
	}

	cout << "\n";
	//txt << "\n";
	for (int i = 0; i < n; i += 1000)
	{
		cout << arr[i] << " ";
		txt << arr[i] << " ";
	}
	txt.close();
}

/**********************************************************************
* Purpose: Times the provided sort with I array
*
* Precondition: Valid sort and array supplied
*
* Postcondition: sort is executed and timed, results printed and written
*
************************************************************************/
template <typename T>
void RunSort(void(*Sort)(int n, T & value), int n, T arr)
{
	//start timer
	auto t1 = high_resolution_clock::now();
	//perform sort
	Sort(n, arr);
	//end timer
	auto t2 = high_resolution_clock::now();

	//calculate duration and print results
	_int64 duration = duration_cast<milliseconds>(t2 - t1).count();
	//Output results
	PrintArr(n, arr);
	PrintTime(duration);

}

/**********************************************************************
* Purpose: Performs an Unflagged BubbleSort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template <typename T>
void BruteForceBubble(int n, T & arr)
{
	cout << "\n\nBrutish Bubble of " << typeid(arr).name();
	Output("\n\nBrutish Bubble of ");
	Output(typeid(arr).name());

	//for (each element in arr)
	for (int i = 0; i < n; i++)
	{
		//for (the number of elements -1)
		for (int j = 0; j < n-1; j++)
		{
			//if (current > next)
			if ( arr[j] > arr[j+1])
			{
				//swap current with next
				Swap(arr[j], arr[j+1]);
			}
		}
	}

	//Better approach:
	////for (each element in arr)
	//for (int i = 0; i < n; i++)
	//{
	//	//for (the number of elements not yet "sunk")
	//	for (int j = 0; j < n - i - 1; j++)
	//	{
	//		//if (current > next)
	//		if (arr[j] > arr[j + 1])
	//		{
	//			//swap current with next
	//			Swap(arr[j], arr[j + 1]);
	//		}
	//	}
	//}
}

/**********************************************************************
* Purpose: Performs a Flagged BubbleSort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void FlaggedBubble(int n, T & arr)
{
	cout << "\n\nFlagged Bubble of " << typeid(arr).name();
	Output("\n\nFlagged Bubble of ");
	Output(typeid(arr).name());

	bool sorted = false;
	int pass = 0;
	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < n - pass - 1 ; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				sorted = false;
				Swap(arr[i], arr[i + 1]);
			}
		}
		pass++;
	}

}

/**********************************************************************
* Purpose: Performs a Selection Sort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void Selection(int n, T & arr)
{
	cout << "\n\nSelection Sort of " << typeid(arr).name();
	Output("\n\nSelection Sort of ");
	Output(typeid(arr).name());
	int max = 0;
	for (int i = 0; i < n - 1; i++)
	{
		//int j = 0;
		for (int j = i + 1; j < n; j++)
		{
			max = i;
			if (arr[j] > arr[max])
			{
				max = j;
			}
			Swap(arr[j], arr[max]);
		}
	}
}

/**********************************************************************
* Purpose: Performs a Insertion Sort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void Insertion(int n, T & arr)
{
	cout << "\n\nInsertion Sort of " << typeid(arr).name();
	Output("\n\nInsertion Sort of ");
	Output(typeid(arr).name());

	int temp = 0;
	for (int i = 1; i < n; i++)
	{
		temp = arr[i];
		int j;
		for ( j = i; j > 0 && temp < arr[j - 1]; j--)
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
}

/**********************************************************************
* Purpose: Performs a Shell Sort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void Shell(int n, T & arr)
{
	cout << "\n\nShell Sort of " << typeid(arr).name();
	Output("\n\nShell Sort of ");
	Output(typeid(arr).name());

	//determine increments
	vector<int> increments;
	for (int h = 1; h < n; h = 3 * h + 1)
	{
		increments.push_back(h);
	}

	//perform shell sort
	//for (number of increments)
	for (int i = increments.size() - 1; i >= 0; i--)
	{
		int h = increments[i];
		//for (number of subarrays)
		for (int hCnt = h; hCnt < 2 * h; hCnt++)
		{
			//perform insertion sort
			for (int j = hCnt; j < n; j = j + h)
			{
				int temp = arr[j];
				int k = j;
				while (k - h >= 0 && temp < arr[k - h])
				{
					arr[k] = arr[k - h];
					k = k - h;
				}
				arr[k] = temp;
			}
		}
	}
}

/**********************************************************************
* Purpose: Performs a Heap Sort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void Heap(int n, T & arr)
{
	cout << "\n\nHeap Sort of " << typeid(arr).name();
	Output("\n\nHeap Sort of ");
	Output(typeid(arr).name());

	//Build Heap
	int i = n / 2;
	while (i >= 0)
	{
		MoveDown(arr, i, n - 1);
		i--;
	}

	//Sort Heap
	for (int i = n - 1; i != 0; i--)
	{
		Swap(arr[0], arr[i]);
		MoveDown(arr, 0, i - 1);
	}

}

/**********************************************************************
* Purpose: Performs the legwork of the heapsort, building and sorting the heap
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void MoveDown(T & arr, int first, int last)
{
	int largest = first * 2 + 1;
	while (!(largest > last) )
	{
		//first = parent
		//arr[largest] = left child, + 1 = right child

		//if (largest is less than last AND left child < right child)
		if (largest < last && arr[largest] < arr[largest + 1])
		{
			largest++;
		}

		//if (data of first < right child)
		if (arr[first] < arr[largest])
		{
			Swap(arr[first], arr[largest]);
			first = largest; //next parent
			largest = first * 2 + 1; //next left child
		}
		else
		{
			largest = last + 1;
		}
	}
}

/**********************************************************************
* Purpose: Performs a Merge Sort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void MergeSort(int n, T& arr)
{
	cout << "\n\nMerge Sort of " << typeid(arr).name();
	Output("\n\nMerge Sort of ");
	Output(typeid(arr).name());

	//create temp array of same size
	vector<int> temp;
	temp.resize(n);

	//Begin Recursive logic
	MergeSort(arr, temp, 0, n - 1);
}

/**********************************************************************
* Purpose: Performs a Merge Sort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void MergeSort(T& arr, vector<int>& temp, int left, int right)
{
	//If (looking at valid sub array) 
	if (left < right)
	{
		//find midpoint
		int mid = (left + right) / 2;
		//Seperate into halves
		MergeSort(arr, temp, left, mid);
		MergeSort(arr, temp, mid + 1, right);
		//Re-Merge those halves
		Merge(arr, temp, left, mid + 1, right);
	}
}

/**********************************************************************
* Purpose: Performs a Merge Sort
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void Merge(T& arr, vector<int>& temp, int left, int right, int rightEnd)
{
	int leftEnd = right - 1;
	int tempPos = left;

	int n = rightEnd - left + 1;

	//
	while (right <= rightEnd && left <= leftEnd)
	{
		if (arr[left] <= arr[right])
		{
			temp[tempPos] = arr[left];
			tempPos++;
			left++;
		}
		else
		{
			temp[tempPos] = arr[right];
			tempPos++;
			right++;
		}
	}

	//copy remainder of left
	while (left <= leftEnd)
	{
		temp[tempPos] = arr[left];
		tempPos++;
		left++;
	}

	//copy remainder of right
	while (right <= rightEnd)
	{
		temp[tempPos] = arr[right];
		tempPos++;
		right++;
	}

	//copy temp over the same point in arr
	tempPos = rightEnd;
	for (int i = 0; i < n; i++, tempPos--)
	{
		arr[tempPos] = temp[tempPos];
	}
	
}

/**********************************************************************
* Purpose: Performs a Quick Sort, this is the "starter" function
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void QuickSort(int n, T& arr)
{
	cout << "\n\nQuick Sort of " << typeid(arr).name();
	Output("\n\nQuick Sort of ");
	Output(typeid(arr).name());
	//IF (array is not one element)
	if ( n >= 2)
	{
		//find maximum
		int max = 0;
		for (int i = 1; i < n; i++)
		{
			if (arr[max] < arr[i])
			{
				max = i;
			}
		}
		//Swap Last elemnt with r
		Swap(arr[n - 1], arr[max]);
		//Call recursive for whole array besides last (already one)
		QuickSort(arr, 0, n - 2);
	}
}

/**********************************************************************
* Purpose: Performs a Quick Sort, this is the recursive function
*
* Precondition: arr is of length n
*
* Postcondition: arr is sorted least to greatest
*
************************************************************************/
template<typename T>
void QuickSort(T& arr, int first, int last)
{
	int small = first + 1;
	int large = last;
	int pivot = arr[first];

	while (small <= large)
	{
		while (arr[small] < pivot)
		{
			small++;
		}
		while (arr[large] > pivot)
		{
			large--;
		}
		if (small < large)
		{
			Swap(arr[small++], arr[large--]);
		}
		else
		{
			small++;
		}
	}
	Swap(arr[large], arr[first]);

	if (first < large - 1)
	{
		QuickSort(arr, first, large - 1);
	}
	if (last > large + 1)
	{
		QuickSort(arr, large + 1, last);
	}
}
