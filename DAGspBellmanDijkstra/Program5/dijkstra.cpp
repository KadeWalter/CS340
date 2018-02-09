#include "dijkstra.h"
#include"driver.h"
#include"dfs.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

struct edgeDij
{
	int v;
	int w;
};

struct nodeDij
{
	int u;
	vector<edgeDij*> next;
};

nodeDij *newNode(int key)
{
	nodeDij *temp = new nodeDij;
	temp->u = key;
	return temp;
}

edgeDij *newEdge(int v, int w)
{
	edgeDij *temp = new edgeDij;
	temp->v = v;
	temp->w = w;
	return temp;
}

//globals
vector<nodeDij*> DijList;
int DijListSize;

void dijkstra::dijkstraMain(string filename)
{
	//fill list
	ifstream in(filename);
	string line;
	int data;
	int v;
	int weight;
	char colon;
	int d = 0;
	while (!in.eof())
	{
		getline(in, line);
		stringstream ss(line);
		ss >> data;
		nodeDij* temp = newNode(data);
		DijList.push_back(temp);
		while (!ss.eof())
		{
			if (ss.peek() == ':')
			{
				ss >> colon;
				if (ss.peek() != ' ')
					break;
			}
			else
			{
				ss >> v;
				ss >> weight;
				edgeDij* edges = newEdge(v, weight);
				DijList[d]->next.push_back(edges);
			}
		}
		d++;
	}

	//ask user for source node and end node
	bool sourceError = true;
	int sourceNo;
	while (sourceError == true)
	{
		cout << "Enter start node: ";
		cin >> sourceNo;
		for (int x = 0; x < DijList.size(); x++)
		{
			if (DijList[x]->u == sourceNo)
			{
				sourceError = false;
			}
		}
		if (sourceError == true)
		{
			cout << "Not a valid start node. Please try again.\n";
		}
		cout << endl;
	}

	bool endError = true;
	int endNo;
	while (endError == true)
	{
		cout << "Enter end node: ";
		cin >> endNo;
		for (int x = 0; x < DijList.size(); x++)
		{
			if (DijList[x]->u == endNo)
			{
				endError = false;
			}
		}
		if (endError == true)
		{
			cout << "Not a valid end node. Please try again.\n";
		}
		cout << endl;
	}

	//set size of the list
	DijListSize = DijList.size();

	//set the distance to each to infinity
	vector<int> totalWeight;
	vector<bool>inSet;
	for (int z = 0; z < DijListSize; z++)
	{
		totalWeight.push_back(INT_MAX);
		inSet.push_back(false);
	}
	totalWeight[(sourceNo - 1)] = 0;

	vector<int> parent;
	for (int a = 0; a < DijListSize; a++)
	{
		parent.push_back(a);
	}

	for (int x = 0; x < DijListSize - 1; x++)
	{
		bool inNext = false;
		int u;
		int counter;
		u = minPath(totalWeight, inSet);
		inSet[u] = true;

		for (int b = 0; b < DijListSize; b++)
		{
			for (int a = 0; a < DijList[u]->next.size(); a++)
			{
				if (DijList[u]->next[a]->v == (b+1))
				{
					inNext = true;
					counter = a;
					break;
				}
			}
			if (inNext == true)
			{
				if ((inSet[b] == false) && (totalWeight[u] != INT_MAX) && ((totalWeight[u] + DijList[u]->next[counter]->w) < totalWeight[b]))
				{
					totalWeight[b] = (totalWeight[u] + DijList[u]->next[counter]->w);
					if (parent[DijList[(u)]->next[counter]->v - 1] != DijList[(u)]->u - 1)
					{
						parent[DijList[(u)]->next[counter]->v - 1] = DijList[(u)]->u - 1;
					}
				}
			}
			inNext = false;
		}
	}
	DijPrint(totalWeight, parent, sourceNo, endNo);
}

void dijkstra::DijPrint(vector<int>totalWeight, vector<int>parent, int start, int end)
{
	cout << "Dijkstra's Algorithm: " << endl;
	if (totalWeight[end - 1] == INT_MAX)
	{
		cout << "No path between " << start << " and " << end << "." << endl;
		return;
	}

	vector<int> finalList;
	int curr = end - 1;
	finalList.push_back(curr + 1);
	while (parent[curr] != curr)
	{
		curr = parent[curr];
		finalList.push_back(curr + 1);
	}
	for (int x = finalList.size() - 1; x > 0; x--)
	{
		int a;
		for (a = 0; a < DijList[finalList[x] - 1]->next.size(); a++)
		{
			if (DijList[finalList[x] - 1]->next[a]->v == finalList[x - 1])
				break;
		}
		cout << finalList[x] << " to " << DijList[finalList[x] - 1]->next[a]->v << " with a weight of " << DijList[finalList[x] - 1]->next[a]->w << endl;
	}
	cout << "\n";
	cout << "Total weight to get from " << start << " to " << end << " is " << totalWeight[end - 1] << endl;
	cout << "\n";
}

int dijkstra::minPath(vector<int>totalWeight, vector<bool>inSet)
{
	int minPath = INT_MAX;
	int minVertex;
	
	for (int x = 0; x < DijListSize; x++)
	{
		if (totalWeight[x] <= minPath && inSet[x] == false)
		{
			minPath = totalWeight[x];
			minVertex = x;
		}
	}
	return minVertex;
}

dijkstra::dijkstra()
{
}
dijkstra::~dijkstra()
{
}
