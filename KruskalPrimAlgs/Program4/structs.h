#pragma once
//struct
struct node
{
	int data;
	int parent;
	int rank;
};

node *newNode();

node *newNode(int x);

struct edgeSet
{
	int weight;
	node* node1 = newNode();
	node* node2 = newNode();
};

edgeSet *newEdge(int node1, int node2, int weight);