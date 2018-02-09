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

class bellman
{
public:
	void bellmanMain(string filename);
	void bellPrint(int start, int end, vector<int>parent, vector<int>totalWeight);
	bellman();
	~bellman();
};

