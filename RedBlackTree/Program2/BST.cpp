//Algorithm for Binary Search Tree
#include "BST.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

node *newNode(string key)
{
	node *temp = new node;
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
}

//bst driver
void BST::bst(string filename, int filesize)
{
	//vars
	string search;
	string word;
	bool found;

	//time keepers
	double buildTime;
	double searchTime;

	//timing the building of the BST
	time_t startTime = time(0);

	//set in stream and error trap
	ifstream infile(filename);
	if (!infile)
	{
		cout << "File could not be found!" << endl;
		return;
	}

	//building the tree
	node *root = NULL;
	for (int x = 0; x < filesize; x++)
	{
		getline(infile, word);
		root = insertNode(root, word);
	}
	infile.close();

	//the final time that it takes to build the tree
	buildTime = difftime(time(0), startTime);

	//asks for the word to search for
	cout << "\nWhat word do you want to find? " << endl;
	cin >> search;

	//changing word to uppercase
	for (int i = 0; i < search.size(); i++)
	{
		search.at(i) = toupper(search.at(i));
	}

	//starts timer to see how long it takes to find a word
	time_t startSearchTime = time(0);
	found = searchBST(root, search);
	searchTime = difftime(time(0), startSearchTime);

	//final print statements
	if (found == true)
	{
		cout << "\nWord was found. It took " << buildTime << " seconds to make the tree. And it took " << searchTime << " seconds to find your word." << endl;
	}
	else
	{
		cout << "\nSorry, word not found. It took " << buildTime << " seconds to make the tree. And it took " << searchTime << " seconds to find your word." << endl;
	}
}

//inserting a node into the BST
node* BST::insertNode(node* T, string z)
{
	node* newN = newNode(z);
	node* x = T;
	node* y = NULL;
	//if the node is null, it becomes the root
	if (T == NULL)
	{
		T = newN;
		T->parent = NULL;
		return T;
	}
	while (x != NULL)
	{
		y = x;
		if (z < x->key)
			x = x->left;
		else
			x = x->right;
	}
	newN->parent = y;
	if (y == NULL)
		T = newN;
	else if (z < y->key)
		y->left = newN;
	else
		y->right = newN;

	return T;
}

//search through the BST to find a word
bool BST::searchBST(node* T, string z)
{
	bool found = false;
	//if the tree is not made, return false
	if (T == NULL)
		return false;
	//if the root is the key, return true
	while (T != NULL && found == false)
	{
		if (T->key == z)
			found = true;
		if (found == false)
		{
			if (z < T->key)
				T = T->left;
			else
				T = T->right;
		}
	}
	return found;
}

BST::BST()
{
}

BST::~BST()
{
}
