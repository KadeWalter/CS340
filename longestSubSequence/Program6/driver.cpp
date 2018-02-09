//Program 6
//By Kade Walter
//CS 340
//This program allows users to run LCS and OSA

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

//prototypes
int lcs();
int maxValue(int a, int b);
int osa(int matchScore, int gapScore, int similarScore, int disScore);
bool similarCheck(char a, char b);

//globals
char similarList[12][12] = {{ 'b','p' },{ 'c','k' },{ 'c','s' },{ 'd','t' },{ 'e','y' },{ 'g','j' },{ 'g','k' },{ 'i','y' },{ 'k','q' },{ 'm','n' },{ 's','z' },{ 'v','w' }};
int similarListSize = 12;
vector<char> first;
vector<char> second;

int main()
{
	//variables
	int algErr = 1;
	int alg;
	string one;
	string two;

	//asks user which algorithm they want to use
	while (algErr == 1)
	{
		cout << "Select file: (input 1 or 2)" << endl;
		cout << "   1. Longest Common Subsequence" << endl;
		cout << "   2. Optimal Sequence Alignment" << endl;
		cin >> alg;
		cout << endl;

		if (alg == 1 || alg == 2)
		{
			algErr = 0;
		}
		else
		{
			cout << "Please select a correct input file option..." << "\n" << endl;
		}
	}

	//gets the first sequence
	cout << "Please enter the first sequence: ";
	cin >> one;
	cout << endl;
	//gets the second sequence
	cout << "Please enter the second sequence: ";
	cin >> two;
	cout << endl;

	//make a char vector of the first word
	for (int i = 0; i < one.length(); i++)
	{
		one[i] = tolower(one[i]);
		first.push_back(one[i]);
	}
	//make a char vector of the second word
	for (int i = 0; i < two.length(); i++)
	{
		two[i] = tolower(two[i]);
		second.push_back(two[i]);
	}

	if (alg == 1)
	{
		int longest = lcs();
		cout << "Longest Common Subsequence: " << longest << endl;
	}
	else
	{
		//gathering scoring
		int matchScore = -1;
		int gapScore = 1;
		int similarScore = -1;
		int disScore = 1;

		while (matchScore <= 0)
		{
			cout << "Enter match score (> 0): ";
			cin >> matchScore;
			cout << endl;
		}
		while (similarScore <= 0)
		{
			cout << "Enter similar score (> 0): ";
			cin >> similarScore;
			cout << endl;
		}
		while (gapScore >= 0)
		{
			cout << "Enter gap score (< 0): ";
			cin >> gapScore;
			cout << endl;
		}
		while (disScore >= 0)
		{
			cout << "Enter dissimilar score (< 0): ";
			cin >> disScore;
			cout << endl;
		}

		int score = osa(matchScore, gapScore, similarScore, disScore);
		cout << "Optimal Sequence Alignment: " << score << endl;
	}

	return 0;
}

int lcs()
{
	int a = first.size();
	int b = second.size();
	vector<vector<int>> Length (a+1);
	int lcsValue;
	int x, y;
	//create array for LCS
	for (int i = 0; i <= a; i++)
	{
		Length[i].resize(b+1);
	}
		
	for (int i = 0; i <= a; i++)
	{
		for (int j = 0; j <= b; j++)
		{
			if (i == 0 || j == 0)
			{
				Length[i][j] = 0;
			}
			else if (first[i - 1] == second[j - 1])
			{
				Length[i][j] = Length[i - 1][j - 1] + 1;
			}
			else
			{
				int max = maxValue(Length[i - 1][j], Length[i][j - 1]);
				Length[i][j] = max;
			}
		}
	}
	lcsValue = Length[a][b];
	return lcsValue;
}

int maxValue(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int osa(int matchScore, int gapScore, int similarScore, int disScore)
{
	int a = first.size();
	int b = second.size();
	vector<vector<int>> score(a + 1);
	int osaValue;
	int x, y;
	bool isSimilar = false;
	//create array for LCS
	for (int i = 0; i <= a; i++)
	{
		score[i].resize(b + 1);
	}

	for (int i = 0; i <= a; i++)
	{
		for (int j = 0; j <= b; j++)
		{
			//assign gap score to the first column and first rows
			if (i == 0 || j == 0)
			{
				//if both are zero, make the first box zero
				if (i == 0 && j == 0)
				{
					score[i][j] = 0;
				}
				//if i is zero, add the gap score to the next column
				else if (i == 0)
				{
					score[i][j] = score[i][j - 1] + gapScore;
				}
				//if j is zero, add the gap score to the next row
				else
				{
					score[i][j] = score[i - 1][j] + gapScore;
				}
			}
			else {
				//look for similar pairs
				isSimilar = similarCheck(first[i - 1], second[j -1]);
				//assign score for a match
				if (first[i - 1] == second[j - 1])
				{
					score[i][j] = score[i - 1][j - 1] + matchScore;
				}
				//assign a score for gap if first is shorter than second
				else if (first[i - 1] == '\0' && second[j - 1] != '\0')
				{
					score[i][j] = score[i - 1][j - 1] + gapScore;
				}
				//assign a score for gap if second is shorter than first
				else if (second[j - 1] == '\0' && first[i - 1] != '\0')
				{
					score[i][j] = score[i - 1][j - 1] + gapScore;
				}
				//assign similar score
				else if (isSimilar == true)
				{
					score[i][j] = score[i - 1][j - 1] + similarScore;
				}
				//assign dissimilar score
				else
				{
					score[i][j] = score[i - 1][j - 1] + disScore;
				}
			}

			//find which of the 3 surrounding boxes is highest
			//left is highest
			if (i != 0 && j != 0)
			{
				if (score[i][j - 1] > score[i][j])
				{
					score[i][j] = score[i][j - 1];
				}
				else if (score[i - 1][j] > score[i][j])
				{
					score[i][j] = score[i - 1][j];
				}
				else
					break;
			}
		}
	}
	osaValue = score[a][b];
	return osaValue;
}

bool similarCheck(char a, char b)
{
	for (int x = 0; x < similarListSize; x++)
	{
		if (a == similarList[x][0] && b == similarList[x][1])
		{
			return true;
		}
		else if (a == similarList[x][1] && b == similarList[x][0])
		{
			return true;
		}
	}
	return false;
}