//Algorithm for Red Black Tree
#include "RBT.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

const string r = "red";
const string b = "black";

RBNode *newRBNode(string key)
{
	RBNode *temp = new RBNode;
	temp->key = key;
	temp->left = temp->right = NULL;
	temp->color = r;
	return temp;
}

RBNode *NIL = newRBNode("");

//driver for the RBT (very similar to BST)
void RBT::rbt(string filename, int filesize)
{
	NIL->color = b;
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
	RBNode *root = NIL;
	for (int x = 0; x < filesize; x++)
	{
		getline(infile, word);
		root = RBInsert(root, word);
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
	found = searchRBT(root, search);
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

//inserting into the RBT
RBNode* RBT::RBInsert(RBNode* T, string z)
{
	//vars
	RBNode *y = NIL;
	RBNode *x = T;
	RBNode *newN = newRBNode(z);
	RBNode *top;

	while (x != NIL)
	{
		y = x;
		if (z < x->key)
			x = x->left;
		else
			x = x->right;
	}
	newN->parent = y;
	if (y == NIL)
		T = newN;
	else if (z < y->key)
		y->left = newN;
	else
		y->right = newN;
	newN->left = NIL;
	newN->right = NIL;
	newN->color = r;

	//run fixUp
	insertFixUp(T, newN);
	top = T;
	while (top->parent != NIL)
	{
		top = top->parent;
	}
	return top;
}

//fixes colors of nodes
void RBT::insertFixUp(RBNode *T, RBNode *newN)
{
	//variable decleration
	RBNode *y;

		while (newN->parent->color == r)
		{
			//if the parent is the left child of the grandparent,
			if (newN->parent->parent->left == newN->parent)
			{
				y = newN->parent->parent->right;
				//and the right child of the grandparent is null,
				if (y->color == r)
				{
					newN->parent->color = b;
					y->color = b;
					newN->parent->parent->color = r;
					newN = newN->parent->parent;

				}
				//and the right child of the grandparent is not null,
				else
				{
					if (newN == newN->parent->right)
					{
						newN = newN->parent;
						leftrotate(T, newN);
					}
					newN->parent->color = b;
					newN->parent->parent->color = r;
					rightrotate(T, newN->parent->parent);
				}
			}
			//if the parent is the right child of the grandparent,
			else
			{
				//then make the parent black, the null node black, and the grandparent red.
				y = newN->parent->parent->left;
				if (y->color == r)
				{
					newN->parent->color = b;
					y->color = b;
					newN->parent->parent->color = r;
					newN = newN->parent->parent;
				}

				//and the right child of the grandparent is not null,
				else
				{
					//then right rotate and make the parent node black, and the grandparent red.
					if (newN->parent->left == newN)
					{
						newN = newN->parent;
						rightrotate(T, newN);
					}
					newN->parent->color = b;
					newN->parent->parent->color = r;
					leftrotate(T, newN->parent->parent);
				}
			}
		}
		T->color = b;
	}


//rotating items left 
void RBT::leftrotate(RBNode *T, RBNode *newN)
{
	//variable decleration
	RBNode *y;

	//if the left child of the right child of the parent in not null, then make the right child of the parent equal to the left child of the right child of the parent, and then the right child of the parent 
	//equal to the parent 
	y = newN->right;
	newN->right = y->left;
	if (y->left != NIL)
	{
		y->left->parent = newN;
	}
	y->parent = newN->parent;
	//otherwise the right child of the parent is null
	if (newN->parent == NIL)
		T = y;
	//if the parent is not null, they share the same parent
	else if (newN == newN->parent->left)
		newN->parent->left = y;
	//if the parent is null, then we are at the root
	else
		newN->parent->right = y;
	y->left = newN;
	newN->parent = y;
	
}

//rotating items right (opposite of left rotate)
void RBT::rightrotate(RBNode *T, RBNode *newN)
{
	//variable decleration
	RBNode *y;

	//if the left child of the right child of the parent in not null, then make the right child of the parent equal to the left child of the right child of the parent, and then the right child of the parent 
	//equal to the parent 
	y = newN->left;
	newN->left = y->right;
	if (y->right != NIL)
	{
		y->right->parent = newN;
	}
	y->parent = newN->parent;


	//otherwise the right child of the parent is null
	if (newN->parent == NIL)
		T = y;
	//if the parent is not null, they share the same parent
	else if (newN == newN->parent->right)
		newN->parent->right = y;
	//if the parent is null, then we are at the root
	else
		newN->parent->left = y;
	y->right = newN;
	newN->parent = y;
}

//search through RBT (similar to searchBST, but set up in a different way)
bool RBT::searchRBT(RBNode *T, string z)
{
	//vars
	bool found = false;
	//if the tree is empty, return false
	if (T == NIL)
		return false;

	//moving through the lists until it hits null or finds the word.
	while (T != NIL && found == false)
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


RBT::RBT()
{
}

RBT::~RBT()
{
}
