#pragma once
#include"structs.h"
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<time.h>
#include<vector>
#include<sstream>
#include<cstdlib>
using namespace std;

class kruskal
{
public:
	//prototypes for kruskals
	void krusMain();
	static bool compareByWeight(const edgeSet *a, const edgeSet *b);
	void disjoinSet();
	void Union(int a, int b);
	int find(int x);
	void printKrus();

	kruskal();
	~kruskal();
};

