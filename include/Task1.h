#ifndef Task1_H
#define Task1_H
#include <iostream>
#include <utility>
#include "Base.h"
#include <vector>
#include <bits/stdc++.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <regex>
#include "Base.h"
#define MAX 100
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

class Task1: public Base
{

public:

	Task1(string);

	void read() override;
	void operate() override;
	void write() override;


private:
	int nNodes;
	string filename;
	vector<string> lines;
	int adjMatrix[MAX][MAX];
};

#endif