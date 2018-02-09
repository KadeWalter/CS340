//Program 4
//By Kade Walter
//CS 340
//This program implements Kruskal's algorithm and Prim's algorithm

#include"driver.h"
#include"structs.h"
#include"kruskal.h"
#include"prims.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>

using namespace std;

//globals
vector<edgeSet*> graph;
vector<edgeSet*> path;
vector<node*> dis;
int vertices = 0;
int edges = 0;

//file names
const string graphinwud = "graphin_w_ud.txt";
const string graphinwud2 = "graphin_w_ud2.txt";

int main()
{
	//variables
	kruskal k;
	prims p;
	int txtError = 1;
	int txtFile;
	string filename;

	//asks user which file they want to use
	while (txtError == 1)
	{
		cout << "Select file: (input 1 - 2)" << endl;
		cout << "   1. graphin_w_ud.txt" << endl;
		cout << "   2. graphin_w_ud2.txt" << endl;

		cin >> txtFile;
		cout << endl;

		if (txtFile == 1 || txtFile == 2)
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
			filename = graphinwud;
			break;
		}
		case 2:
		{
			filename = graphinwud2;
			break;
		}
		
	}

	//fill list
	ifstream in(filename);
	string line;
	int node1, node2, weight;
	char colon;
	while (!in.eof())
	{
		getline(in, line);
		stringstream ss(line);
		ss >> node1;
		vertices = node1;
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
				ss >> node2;
				ss >> weight;
				edgeSet* temp = newEdge(node1, node2, weight);
				graph.push_back(temp);
				edges += 1;
			}
		}
	}

	//call kruskal
	 k.krusMain();
	 cout << "\n" << endl;
	 p.primMain();
	 cout << "\n";

	return 0;
}