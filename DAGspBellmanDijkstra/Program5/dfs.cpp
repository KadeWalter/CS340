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

//struct
struct node
{
	int number;
	int disTime;
	int finTime;
	string color = "white";
	vector<int> next;
};

node *newNode(int key)
{
	node *temp = new node;
	temp->number = key;
	temp->next;
	return temp;
}

//globals
vector<vector<int>> backEdge;
vector<node*> list;
vector<int> usedList;
vector<int> topoSort;
int timer;
int listSize;
int usedListSize;
bool backTrack = false;

bool dfs::dfsMain(string filename)
{
	//fill list
	ifstream in(filename);
	string line;
	int data;
	char colon;
	int d = 0;
	int weight;
	while (!in.eof())
	{
		getline(in, line);
		stringstream ss(line);
		ss >> data;
		node* temp = newNode(data);
		list.push_back(temp);
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
				ss >> data;
				list[d]->next.push_back(data);
				ss >> weight;
			}
		}
		d++;
	}

	//set size of the list
	listSize = list.size();

	//call dfs
	dfsSearch();

	bool isDAG;
	if (backTrack == true)
		isDAG = false;
	if (backTrack == false)
		isDAG = true;

	return isDAG;
}
void dfs::dfsSearch()
{
	timer = 0;
	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->color == "white")
		{
			dfsVisit(i);
		}
	}
}
void dfs::dfsVisit(int i)
{
	//vector for backEdge
	vector<int> row;
	//adds 1 to the timer and makes that the start time of the passed node
	timer = timer + 1;
	list[i]->disTime = timer;
	//change the node color to gray and add it to the used list
	list[i]->color = "gray";
	usedList.push_back(list[i]->number);
	usedListSize = usedList.size();
	int nextSize = list[i]->next.size();
	//if the next node is in usedList and gray, it will cause a cycle
	for (int j = 0; j < nextSize; j++)
	{
		for (int k = 0; k < usedListSize; k++)
		{
			if (list[i]->next[j] == usedList[k])
			{
				for (int u = 0; u < listSize; u++)
				{
					if (list[i]->next[j] == list[u]->number)
					{
						if (list[u]->color == "gray")
						{
							backTrack = true;
							row.push_back(list[i]->number);
							row.push_back(list[u]->number);
							backEdge.push_back(row);
						}
					}
				}
			}
		}
		//if the next node that the current node is looking at is white, go to it
		for (int x = 0; x < listSize; x++)
		{
			if (list[i]->next[j] == list[x]->number)
			{
				if (list[x]->color == "white")
				{
					dfsVisit(x);
				}
			}
		}
	}
	//change the node color to black when done, set the finish time, and add the node to the topoSort "stack"
	list[i]->color = "black";
	timer = timer + 1;
	list[i]->finTime = timer;
	topoSort.push_back(list[i]->number);
}


dfs::dfs()
{
}

dfs::~dfs()
{
}
