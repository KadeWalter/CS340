//Program 5
//By Kade Walter
//CS 340
//This program allows users to run DAG-SP, Bellman-Ford, and Dijkstra on different files 

//headers included
#include"driver.h"
#include"dfs.h"
#include"bellman.h"
#include"dagSP.h"
#include"dijkstra.h"

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

//file names
const string graphin1 = "graphin_Fig1.txt";
const string graphin2 = "graphin_Fig2.txt";
const string graphin4 = "graphin_Fig4.txt";
const string graphin5 = "graphin_Fig5.txt";
const string graphinDAG = "graphin-weighted-DAG.txt";

int main()
{
	//class calls
	dfs dfs;
	dagSP dagSP;
	bellman bell;
	dijkstra dij;

	//variables
	int txtError = 1;
	int txtFile;
	string filename;

	//asks user which file they want to use
	while (txtError == 1)
	{
		cout << "Select file: (input 1 - 3)" << endl;
		cout << "   1. graphin_Fig1.txt" << endl;
		cout << "   2. graphin_Fig2.txt" << endl;
		cout << "   3. graphin_Fig4.txt" << endl;
		cout << "   4. graphin_Fig5.txt" << endl;
		cout << "   5. graphin-weighted-DAG.txt" << endl;

		cin >> txtFile;
		cout << endl;

		if (txtFile == 1 || txtFile == 2 || txtFile == 3 || txtFile == 4 || txtFile == 5)
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
		//graphin1
		case 1:
		{
			filename = graphin1;
			break;
		}
		//graphin2
		case 2:
		{
			filename = graphin2;
			break;
		}
		//graphin4
		case 3:
		{
			filename = graphin4;
			break;
		}
		//graphin5
		case 4:
		{
			filename = graphin5;
			break;
		}
		//graphin-DAG
		case 5:
		{
			filename = graphinDAG;
			break;
		}
	}

	
	//checks to see if the list is a DAG
	bool isDAG;
	isDAG = dfs.dfsMain(filename);

	//if there isnt a cycle
	if (isDAG == true)
	{
		//call DAG-SP
		dagSP.dagSPMain(filename);
	}
	else
	{
		//check for negative weights
		bool isNeg = false;
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
					ss >> weight;
					if (weight < 0)
					{
						isNeg = true;
						break;
					}
				}
			}
			d++;
			if (isNeg == true)
			{
				break;
			}
		}
		//if cycle but no negs, call Dijkstra
		if (isNeg == false)
		{
			dij.dijkstraMain(filename);
		}
		//else, call Bellman-Ford
		else
		{
			bell.bellmanMain(filename);
		}
	}

	return 0;
}

