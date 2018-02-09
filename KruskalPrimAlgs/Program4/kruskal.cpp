#include "kruskal.h"
#include"structs.h"
#include"driver.h"

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

//globals moved over
extern vector<edgeSet*> graph;
extern vector<edgeSet*> path;
extern vector<node*> dis;
extern int vertices;
extern int edges;

void kruskal::krusMain()
{
	//variables
	int p = 0;
	int pathSize = vertices - 1;
	int i = 0;

	//sort the graph by weight of edges
	sort(graph.begin(), graph.end(), compareByWeight);

	//make the nodes for the the disjoint set
	for (int k = 0; k < vertices; k++)
	{
		node* temp = newNode(k + 1);
		dis.push_back(temp);
	}
	//make the parents and the ranks of the disjoint set
	disjoinSet();

	//while the path isnt full, find the nodes whose roots are different and union them
	while (p < pathSize)
	{
		edgeSet* curr_edge;
		curr_edge = graph[i];
		int a = find(curr_edge->node1->data);
		int b = find(curr_edge->node2->data);

		if (a != b)
		{
			path.push_back(graph[i]);
			Union(a, b);
			p++;
		}
		i = i + 2;
	}
	
	printKrus();
}

bool kruskal::compareByWeight(const edgeSet *a, const edgeSet *b)
{
	//sorting the list by weight
	return (a->weight < b->weight);
}

void kruskal::disjoinSet()
{
	//creating a vector full of nodes whose parents are themselves
	for (int x = 1; x < vertices + 1; x++)
	{
		dis[x - 1]->parent = x;
		dis[x - 1]->rank = 0;
	}
}

void kruskal::Union(int a, int b)
{
	//get the parents 
	int aparent = find(a);
	int bparent = find(b);

	//see which is bigger and combine them
	if (dis[aparent - 1]->rank < dis[bparent - 1]->rank)
	{
		dis[aparent - 1]->parent = bparent;
		dis[bparent - 1]->rank++;
	}
	else if (dis[aparent - 1]->rank > dis[bparent - 1]->rank)
	{
		dis[bparent - 1]->parent = aparent;
		dis[aparent - 1]->rank++;
	}
	else if (dis[aparent - 1]->rank == dis[bparent - 1]->rank)
	{
		dis[bparent - 1]->parent = aparent;
		dis[aparent - 1]->rank++;
	}
}

int kruskal::find(int x)
{
	//finding the parent of nodes until the node is its own parent (meaning it is the root)
	if (dis[x - 1]->parent != x)
		find(dis[x - 1]->parent);

	return dis[x - 1]->parent;
}

void kruskal::printKrus()
{
	//print the results to the console
	cout << "Kruskal's Algorithm Results: (sorted by weight)" << endl;
	for (int x = 0; x < path.size(); x++)
	{
		cout << "	Edge between " << path[x]->node1->data << " and " << path[x]->node2->data << " with a weight of " << path[x]->weight << endl;
	}

	//print the results to a file
	ofstream myFile;
	string fileName;
	fileName = "Kruskal's Algorithm Results.txt";
	myFile.open(fileName);
	myFile << "Kruskal's Algorithm Results:" << endl;
	for (int x = 0; x < path.size(); x++)
	{
		myFile << "	    Edge between " << path[x]->node1->data << " and " << path[x]->node2->data << " with a weight of " << path[x]->weight << endl;
	}
	cout << "\nResults also printed to file (which can be found by the other text files for the program)." << endl;
}

kruskal::kruskal()
{
}
kruskal::~kruskal()
{
}
