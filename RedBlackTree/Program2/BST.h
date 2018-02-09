#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

//struct for node and new node for BST
struct node
{
	string key;
	node *left, *right, *parent;
};


class BST
{
public:
	//prototypes for BST
	void bst(string filename, int filesize);
	bool searchBST(node* T, string z);
	node* insertNode(node* T, string z);

	BST();
	~BST();
};

