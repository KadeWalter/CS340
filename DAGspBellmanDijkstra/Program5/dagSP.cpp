#include "dagSP.h"
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

struct edgeDAGSP
{
	int v;
	int w;
};

struct nodeDAGSP
{
	int u;
	vector<edgeDAGSP*> next;
};

nodeDAGSP *newNode(int key)
{
	nodeDAGSP *temp = new nodeDAGSP;
	temp->u = key;
	return temp;
}

edgeDAGSP *newEdge(int v, int w)
{
	edgeDAGSP *temp = new edgeDAGSP;
	temp->v = v;
	temp->w = w;
	return temp;
}

//globals
vector<nodeDAGSP*> DAGSPlist;
extern vector<int> topoSort;
vector<int> topologicalOrder;
int DAGSPlistSize;

void dagSP::dagSPMain(string filename)
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
		nodeDAGSP* temp = newNode(data);
		DAGSPlist.push_back(temp);
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
				edgeDAGSP* edges = newEdge(v, weight);
				DAGSPlist[d]->next.push_back(edges);
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
		for (int x = 0; x < DAGSPlist.size(); x++)
		{
			if (DAGSPlist[x]->u == sourceNo)
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
		for (int x = 0; x < DAGSPlist.size(); x++)
		{
			if (DAGSPlist[x]->u == endNo)
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
	DAGSPlistSize = DAGSPlist.size();

    //getting topo sort order
	for (int l = (topoSort.size() - 1); l >= 0; l--)
	{
		topologicalOrder.push_back(topoSort[l]);
	}

	//check to make sure path exists from start to end
	int startNo; 
	int finalNo;
	for (int d = 0; d < topologicalOrder.size(); d++)
	{
		if (topologicalOrder[d] == sourceNo)
		{
			startNo = d;
		}
		if (topologicalOrder[d] == endNo)
		{
			finalNo = d;
		}
			
	}
	if (startNo > finalNo)
	{
		cout << "There is no path between these nodes." << endl;
		cout << "\n";
		return;
	}

		//set the distance to each to infinity
		vector<int> distance;
		for (int z = 0; z < DAGSPlistSize; z++)
		{
			distance.push_back(INT_MAX);
		}
		distance[(sourceNo-1)] = 0;

		vector<int> parent;
		for (int a = 0; a < DAGSPlistSize; a++)
		{
			parent.push_back(a + 1);
		}

		int u;
		for (int i = 0; i < topologicalOrder.size(); i++)
		{
			u = topologicalOrder[i];
			if (distance[(u-1)] != INT_MAX)
			{
				for (int a = 0; a < DAGSPlist[(u-1)]->next.size(); a++)
				{
					if (distance[DAGSPlist[(u - 1)]->next[a]->v - 1] > (distance[(u - 1)] + DAGSPlist[(u - 1)]->next[a]->w))
					{
						distance[DAGSPlist[(u - 1)]->next[a]->v - 1] = (distance[(u - 1)] + DAGSPlist[(u - 1)]->next[a]->w);
						parent[DAGSPlist[(u - 1)]->next[a]->v - 1] = DAGSPlist[(u - 1)]->u;
					}
				}
			}
		}

		dagSPprint(distance, parent, sourceNo, endNo);
}

void dagSP::dagSPprint(vector<int> distance, vector<int> parent, int start, int end)
{
	cout << "DAP-SP Algorithm: " << endl;
	vector<int> finalList;
	int curr = end;
	finalList.push_back(curr);
	while (parent[curr - 1] != curr)
	{
		curr = parent[curr - 1];
		finalList.push_back(curr);
	}
	for (int x = finalList.size() - 1; x > 0; x--)
	{
		int z;
		for ( z = 0; z < DAGSPlistSize; z++)
		{
			if (DAGSPlist[finalList[x]-1]->next[z]->v == finalList[x - 1])
			{
				break;
			}
		}
		cout << finalList[x] << " to " << finalList[x - 1] << " with a weight of " << DAGSPlist[finalList[x]-1]->next[z]->w << endl;
	}
	cout << "\n";
	cout << "Total weight to get from " << start << " to " << end << " is " << distance[end - 1] << endl;
	cout << "\n";
}


dagSP::dagSP()
{
}
dagSP::~dagSP()
{
}
