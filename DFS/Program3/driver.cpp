//Program 3
//By Kade Walter
//CS 340
//This program allows users to select different file names and find out if the graphs are DAGs, and if so it topologically sorts the nodes

#include"driver.h"
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

//file names
const string graphinc1 = "graphin-c1.txt";
const string graphinc2 = "graphin-c2.txt";
const string graphinDAG = "graphin-DAG.txt";

//prototypes
void dfs();
void dfsVisit(int i);

int main()
{
	//variables
		int txtError = 1;
		int txtFile;
		string filename;

		//asks user which file they want to use
		while (txtError == 1)
		{
			cout << "Select file: (input 1 - 3)" << endl;
			cout << "   1. graphin-c1.txt" << endl;
			cout << "   2. graphin-c2.txt" << endl;
			cout << "   3. graphin-DAG.txt" << endl;

			cin >> txtFile;
			cout << endl;

			if (txtFile == 1 || txtFile == 2 || txtFile == 3)
			{
				txtError = 0;
			}
			else
			{
				cout << "Please select a correct input file option..." << "\n" << endl;
			}
		}

		//gets the file name
		switch (txtFile)
		{
			//graphin-c1
			case 1:
			{
				filename = graphinc1;
				break;
			}
			//graphin-c2
			case 2:
			{
				filename = graphinc2;
				break;
			}
			//graphin-DAG
			case 3:
			{
				filename = graphinDAG;
				break;
			}
		}

		//fill list
		ifstream in(filename);
		string line;
		int data;
		char colon;
		int d = 0;
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
				}
			}
			d++;
		}

		//set size of the list
		listSize = list.size();

		//call dfs
		dfs();

		//print statements
		int lastTime = ((2 * listSize) + 1);
		//if there is a back edge
		if (backTrack == true)
		{
			cout << "List is not an Acyclic Graph." << endl;
			//back edges
			for (int l = 0; l < backEdge.size(); l++)
			{
				int j = 0;
				cout << "There is a back edge from " << backEdge[l][j] << " to " << backEdge[l][j+1] << endl;
			}
		}
		//if there is not a back edge
		else
		{
			//print it is acyclic
			cout << "List is an Acyclic Graph." << endl;
			//topological sort algorithm
			cout << "Topological Sort: ";
			for (int l = (topoSort.size() - 1); l >= 0; l--)
			{
				cout << topoSort[l] << " ";
			}
			cout << endl;
		}

	return 0;
}

//set the timer and call the dfsVisit function if the node hasn't been visited yet
void dfs()
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

//dfsVisit
void dfsVisit(int i)
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