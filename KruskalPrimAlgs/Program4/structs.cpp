#include"structs.h"

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>

using namespace std;

node *newNode()
{
	node *temp = new node;
	return temp;
}

node *newNode(int x)
{
	node *temp = new node;
	temp->data = x;
	return temp;
}

edgeSet *newEdge(int node1, int node2, int weight)
{
	edgeSet *temp = new edgeSet;
	temp->node1->data = node1;
	temp->node2->data = node2;
	temp->weight = weight;
	return temp;
}


