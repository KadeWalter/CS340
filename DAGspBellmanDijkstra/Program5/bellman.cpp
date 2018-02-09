#include "bellman.h"
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

struct edgeBell
{
	int u;
	int v;
	int w;
};

edgeBell *newEdge(int u, int v, int w)
{
	edgeBell *temp = new edgeBell;
	temp->u = u;
	temp->v = v;
	temp->w = w;
	return temp;
}

//globals
vector<edgeBell*> bellList;
int bellListSize;
int vertices = 0;
int edges = 0;

void bellman::bellmanMain(string filename)
{
	//fill list
	ifstream in(filename);
	string line;
	int u;
	int v;
	int weight;
	char colon;
	int d = 0;
	while (!in.eof())
	{
		getline(in, line);
		stringstream ss(line);
		ss >> u;
		vertices++;
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
				edgeBell* edge = newEdge(u, v, weight);
				bellList.push_back(edge);
				edges++;

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
		for (int x = 1; x < vertices + 1; x++)
		{
			if (x == sourceNo)
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
		for (int x = 1; x < vertices + 1; x++)
		{
			if (x == endNo)
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
	bellListSize = bellList.size();

	//set the distance to each to infinity
	vector<int>totalWeight;
	for (int z = 0; z < vertices; z++)
	{
		totalWeight.push_back(INT_MAX);
	}
	totalWeight[(sourceNo - 1)] = 0;

	vector<int> parent;
	for (int a = 0; a < vertices; a++)
	{
		parent.push_back(a);
	}

	for (int x = 0; x < vertices - 1; x++)
	{
		for (int y = 0; y < edges; y++)
		{
			int u = bellList[y]->u - 1;
			int v = bellList[y]->v - 1;
			int w = bellList[y]->w;
			if ((totalWeight[u] != INT_MAX) && (totalWeight[v] > totalWeight[u] + w))
			{
				totalWeight[v] = totalWeight[u] + w;
				if (parent[v] != u)
				{
					parent[v] = u;
				}
			}
		}
	}

	bellPrint(sourceNo, endNo, parent, totalWeight);
}

void bellman::bellPrint(int start, int end, vector<int>parent, vector<int>totalWeight)
{
	cout << "Bellman Ford's Algorithm: " << endl;
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
		for (a = 0; a < edges; a++)
		{
			if ((bellList[a]->u == finalList[x]) && (bellList[a]->v == finalList[x - 1]))
				break;
		}

		cout << finalList[x] << " to " << finalList[x - 1] << " with a weight of " << bellList[a]->w << endl;
	}
	cout << "\n";
	cout << "Total weight to get from " << start << " to " << end << " is " << totalWeight[end - 1] << endl;
	cout << "\n";
}

bellman::bellman()
{
}
bellman::~bellman()
{
}
