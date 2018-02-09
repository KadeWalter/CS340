//Program 2
//By Kade Walter
//CS 340
//This program allows users to select different sizes of dictionaries, make them into a RBT or BST, and then search for words

#include"driver.h"
#include"BST.h"
#include"RBT.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

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
	bool playing = true;
	while (playing == true)
	{
		BST bst;
		RBT rbt;
		int sortError = 1;
		int sizeError = 1;
		int typeError = 1;

		int sortType;
		int fileSize;
		int fileType;
		string filename;
		string outFile;
		string outFileName;
		string search;

		//gets sorting algorithm
		while (sortError == 1)
		{
			cout << "Select a tree type: (input 1 - 2)" << endl;
			cout << "   1. Binary Search Tree" << endl;
			cout << "   2. Red-Black Tree" << endl;

			cin >> sortType;

			if (sortType == 1 || sortType == 2)
			{
				sortError = 0;
			}
			else
			{
				cout << "Please select a correct tree type..." << "\n" << endl;
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

		//push to the correct sorting algorithm
		switch (sortType)
		{
			//sends to binary search tree
		case 1:
		{
			bst.bst(filename, fileSize);
			break;
		}
		//sends to red-black tree
		case 2:
		{
			rbt.rbt(filename, fileSize);
			break;
		}
		}

		int ans;
		cout << "\n" << "Do you want to go again? (input 1-2): " << endl;
		cout << "   1. Yes" << endl;
		cout << "   2. No" << "\n" << endl;
		cin >> ans;

		if (ans == 1)
			playing = true;
		else
			playing = false;

	}
	return 0;
}
