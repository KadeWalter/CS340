//Program 7
//By Kade Walter
//CS 340
//This program allows users to run knapsack vis dynamic programming

#include"driver.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
#include<sstream>
#include<cstdlib>
#include<algorithm>
using namespace std;

//prototype
int knapsack();
void getItemList(vector<vector<int>> table);

//filename
string filename = "knapsack.txt";

//globals
int items;
int weight;
vector<int> values;
vector<int> weights;
vector<int> itemList;

int main()
{
	//variables
	int algErr = 1;
	int alg;
	string one;
	string two;

	//read input file
	ifstream in;
	in.open(filename);
	string line;
	int v, w;

	//read the items and the total weight
	in >> items;
	in >> weight;
	for(int i = 0; i < items; i++)
	{
			in >> w;
			in >> v;
			values.push_back(v);
			weights.push_back(w);
	}	
	
	int optValue = knapsack();

	//prints results
	cout << "Results for knapsack: " << endl;
	cout << "\tItems: " << items << endl;
	cout << "\tTotal Weight allowed: " << weight;
	cout << "\n" << endl;
	cout << "\tThe optimal Knapsack solution has a total value " << optValue << " and involves items {";
	for (int i = itemList.size() - 1; i >= 0; i--)
	{
		if (i == 0)
			cout << itemList[i];
		else
			cout << itemList[i] << ", ";
	}
	cout << "}." << endl;

	return 0;
}

int knapsack()
{
	//variables
	int diagWeight;
	int vertWeight;
	//create list for knapsack table (size ITEMS x WEIGHT)
	vector<vector<int>> table(items + 1);
	for (int i = 0; i <= items; i++)
	{
		table[i].resize(weight + 1);
	}

	for (int i = 0; i <= items; i++)
	{
		for (int j = 0; j <= weight; j++)
		{
			//adds zero to the first row and column of the table
			if (i == 0 || j == 0)
			{
				table[i][j] = 0;
			}
			//checks if the weight is less than total weight permits
			//fills in the table diagonally
			else if (weights[i - 1] <= j)
			{
				//assigns the new weights to variables
				diagWeight = (table[i - 1][j - weights[i - 1]]) + values[i - 1];
				vertWeight = table[i - 1][j];

				//decides if adding diagonally or vertically will give the most value
				table[i][j] = max(diagWeight, vertWeight);
			}
			//fills in the table vertically
			else
				table[i][j] = table[i - 1][j];
		}
	}
	//gets the item list
	getItemList(table);
	//returns the top right corner of the table (the largest value)
	return table[items][weight];
}

//backtracks item list
void getItemList(vector<vector<int>> table)
{
	int j = weight;
	//start at the top of the table and work backwards
	for (int i = items; i >= 0; i--)
	{
			//we reached the end
			if (i == 0)
				return;
			//we made a diaganol move (need)
			else if (table[i][j] > table[i - 1][j])
			{
				j = j - weights[i - 1];
				itemList.push_back(i);
			}		
	}
}