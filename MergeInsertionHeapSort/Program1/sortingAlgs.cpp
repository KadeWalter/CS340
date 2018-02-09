#include"sortingAlgs.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

//prototypes
void mergeSort(vector<string> &words, int fileSize);
void merge(vector<string> &words, int base, int size, int mid);
void half(vector<string> &words, int l, int h);
void insertionSort(vector<string> &words);
void heapSort(vector<string>& words, int fileSize);
void heapify(vector<string>& words, int fileSize, int i);
void buildHeap(vector<string> &words, int fileSize);

//perm files
const string perm30k = "perm30K.txt";
const string perm60k = "perm60K.txt";
const string perm90k = "perm90K.txt";
const string perm120k = "perm120K.txt";
const string perm150k = "perm150K.txt";

//sorted files
const string sorted30k = "sorted30K.txt";
const string sorted60k = "sorted60K.txt";
const string sorted90k = "sorted90K.txt";
const string sorted120k = "sorted120K.txt";
const string sorted150k = "sorted150K.txt";

int main()
{
	int sortError = 1;
	int sizeError = 1;
	int typeError = 1;

	int sortType;
	int fileSize;
	int fileType;
	string filename;
	char seeList;
	string outFile;
	string outFileName;

	//time keepers
	double startTime;
	double runTime;

	//gets sorting algorithm
	while (sortError == 1)
	{
		cout << "Select a sorting Algorithm: (input 1 - 3)" << endl;
		cout << "   1. Merge Sort" << endl;
		cout << "   2. Insertion Sort" << endl;
		cout << "   3. Heap Sort" << "\n" << endl;

		cin >> sortType;

		if (sortType == 1 || sortType == 2 || sortType == 3 || sortType == 4)
		{
			sortError = 0;
		}
		else
		{
			cout << "Please select a correct sorting algorithm..." << "\n" << endl;
		}
	}

	//gets file size
	while (sizeError == 1)
	{
		cout << "\n" << "Select file size: (input 1 - 5)" << endl;
		cout << "   1. 30,000" << endl;
		cout << "   2. 60,000" << endl;
		cout << "   3. 90,000" << endl;
		cout << "   4. 120,000" << endl;
		cout << "   5. 150,000" << "\n" << endl;

		cin >> fileSize;
		
		if (fileSize == 1 || fileSize == 2 || fileSize == 3 || fileSize == 4 || fileSize == 5)
		{
			sizeError = 0;
		}
		else
		{
			cout << "Please select a correct file size..." << "\n" << endl;
		}
	}

	//sorted or perm
	while (typeError == 1)
	{
		cout << "\n" << "Select file type: (input 1 - 2)" << endl;
		cout << "   1. Sorted" << endl;
		cout << "   2. Permuted" << "\n" << endl;

		cin >> fileType;

		if (fileType == 1 || fileType == 2)
		{
			typeError = 0;
		}
		else
		{
			cout << "Please select a correct file type..." << "\n" << endl;
		}
	}

	//gets the whole file name
	switch (fileSize)
	{
		//30,000 words
		case 1:
		{
			fileSize = 30000;
			if (fileType == 1)
			{
				filename = sorted30k;
				break;
			}
			else
			{
				filename = perm30k;
				break;
			}
		}
		//60,000 words
		case 2:
		{
			fileSize = 60000;
			if (fileType == 1)
			{
				filename = sorted60k;
				break;
			}
			else
			{
				filename = perm60k;
				break;
			}
		}
		//90,000 words
		case 3:
		{
			fileSize = 90000;
			if (fileType == 1)
			{
				filename = sorted90k;
				break;
			}
			else
			{
				filename = perm90k;
				break;
			}
		}
		//120,000 words
		case 4:
		{
			fileSize = 120000;
			if (fileType == 1)
			{
				filename = sorted120k;
				break;
			}
			else
			{
				filename = perm120k;
				break;
			}
		}
		//150,000 words
		case 5:
		{
			fileSize = 150000;
			if (fileType == 1)
			{
				filename = sorted150k;
				break;
			}
			else
			{
				filename = perm150k;
				break;
			}
		}
	}

	//set in stream and error trap
	ifstream infile(filename);
	if (!infile)
	{
		cout << "File could not be found!" << endl;
		return 1;
	}

	//creating vector and populating with the list of words from the file
	string word;
	vector<string> wordList;
	for(int x = 0; x < fileSize; x++)
	{
		getline(infile, word);
		wordList.push_back(word);
	}
	infile.close();

	//push to the correct sorting algorithm
	switch (sortType)
	{
		//sends to merge sort
		case 1:
		{
			time_t startTime = time(0);
			mergeSort(wordList, fileSize);
			runTime = difftime(time(0), startTime);
			break;
		}
		//sends to insertion sort
		case 2:
		{
			time_t startTime = time(0);
			insertionSort(wordList);
			runTime = difftime(time(0), startTime);
			break;
		}
		//sends to heap sort
		case 3:
		{
			time_t startTime = time(0);
			heapSort(wordList, fileSize);
			runTime = difftime(time(0), startTime);
			break;
		}
		
	}

	//shows total runtime
	cout << "\nFile successfully sorted!" << endl;
	cout << "Total run time of the sorting algorithm: " << runTime << " seconds." << endl;

	//setting up the output file for printing
	ofstream myFile;
	string part1 = "Sorted list of ";
	string part2 = " words.txt";
	stringstream path;

	path << part1 << fileSize << part2;
	outFile = path.str();
	myFile.open(outFile);

	//writing to the file
	for (int i = 0; i < wordList.size(); i++)
	{
		myFile << wordList[i] << endl;
	}
	
	//printing location of the file
	cout << "\nLocation of the output file:  \nNavigate to the folder the program is in. \nOpen that folder. \nThen open the Program 1 folder. \nFile is located here with the title: " << outFile << endl;

	return 0;
} 

//merge sort algorithms
void mergeSort(vector<string> &words, int fileSize)
{
	//halves the list
	half(words, 0, fileSize - 1);
}

void half(vector<string> &words, int l, int h)
{
	int mid;
	if (l < h)
	{
		//find the middle of the current list
		mid = (l + h) / 2;

		//keeping halfing the list
		half(words, l, mid);
		half(words, mid + 1, h);

		//rebuild the list
		merge(words, l, mid, h);
	}
}

void merge(vector<string> &words, int l, int m, int h)
{
	// Fill the temp vector in the correct order
	vector<string> temp;
	int x = l;
	int y = m + 1;
	int z = l;
	
	while ((x <= m) && (y <= h))
	{
		if (words[x] < words[y])
		{
			temp.push_back(words[x]);
			x++;
			z++;
		}
		else
		{
			temp.push_back(words[y]);;
			y++;
			z++;
		}
	}

	while (x <= m)
	{
		temp.push_back(words[x]);
		x++;
		z++;
	}

	while (y <= h)
	{
		temp.push_back(words[y]);
		y++;
		z++;
	}

	for (x = l; x <= h; x++)
	{
		words[x] = temp[x - l];
	}

}

//insertion sort algorithm
void insertionSort(vector<string> &words)
{
	//defining variables
	int x, y, size;
	string temp;

	//getting the size of the vector
	size = words.size();

	//algorithm that swaps words if needed
	for (y = 1; y < size; y++)
	{
		temp = words[y];
		for (x = y - 1; (x >= 0) && (words[x] > temp); x--)
		{
			words[x + 1] = words[x];
		}
		words[x + 1] = temp;
	}
}

//heap sort algorithms
void heapSort(vector<string> &words, int fileSize)
{
	//build heap portion
	double buildHeapRunTime;
	time_t buildHeapTime = time(0);

	buildHeap(words, fileSize);

	// prints the buildHeap time
	buildHeapRunTime = difftime(time(0), buildHeapTime);
	cout << "\nRuntime for building the heap is: " << buildHeapRunTime << " seconds." << endl;

	//// One by one extract an element from heap
	for (int j = fileSize - 1; j >= 0; j--)
	{
		// Move current root to end
		swap(words[0], words[j]);

		// call heapify on the smaller heap
		heapify(words, j, 0);
	}
}

void buildHeap(vector<string> &words, int fileSize)
{
	for (int i = ((fileSize / 2) - 1); i >= 0; i--)
	{
		//build heap sends the list to heapify with the correct fileSize
		heapify(words, fileSize, i);
	}
}

void heapify(vector<string> &words, int a, int i)
{
	//establishing root, left child, and right child
	int top = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	//if the left child is larger than the root
	if (left < a && words[left] > words[top])
	{
		top = left;
	}
	
	//if right is larger than root
	if (right < a && words[right] > words[top])
	{
		top = right;
	}

	//if the root is not the largest
	if (top != i)
	{
		//swap the words
		swap(words[i], words[top]);

		//keep running the heapify on the remaining tree
		heapify(words, a, top);
	}
}

