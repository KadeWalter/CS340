#pragma once
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

class dijkstra
{
public:
	void dijkstraMain(string filename);
	int minPath(vector<int>totalWeight, vector<bool>inSet);
	void DijPrint(vector<int>totalWeight, vector<int>parent, int start, int end);
	dijkstra();
	~dijkstra();
};

