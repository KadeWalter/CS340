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

//struct for node and new node for RBT
struct RBNode
{
	string key;
	string color;
	RBNode *left, *right, *parent;

};

class RBT
{
public:
	//prototypes for RBT
	void rbt(string filename, int filesize);
	RBNode* RBInsert(RBNode* T, string z);
	void insertFixUp(RBNode *T, RBNode *newN);
	void rightrotate(RBNode *T, RBNode *newN);
	void leftrotate(RBNode *T, RBNode *newN);
	bool searchRBT(RBNode *T, string z);

	RBT();
	~RBT();
};
