#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

class dfs
{
public:
	bool dfsMain(string filename);
	void dfsSearch();
	void dfsVisit(int i);
	dfs();
	~dfs();
};

