#include <bits/stdc++.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <regex>
#include "Task1.h"
#define MAX 100
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

vector<string> tokenize(const string str, const regex re) {
	sregex_token_iterator it{ str.begin(), str.end(), re, -1 }; 
	vector<string> tokenized{ it, {} }; 

	// Additional check to remove empty strings 
	tokenized.erase(remove_if(tokenized.begin(), tokenized.end(), [](string const& s) { return s.size() == 0; }), tokenized.end());
	return tokenized; 
}

Task1::Task1(string filename) // constructor
{
	this->filename = filename;
}


void Task1::read()
{
	// code for parsing the file
	ifstream file("Read.gdf");

	// vector<string> lines;
	
	if(file.is_open())
	{
		string str;
		while (getline(file, str))
		{
			//do something with the str
			lines.push_back(str);
		}

		file.close();
	}
}

void Task1::operate()
{
	// code for performing the task
	int n = lines.size();

	int cnt = 0;
	int ndItr = 0, edItr, itr = 0;
	for(auto line : lines){
		for(int i = 0; i < line.size(); i++){
			if(line[i] == '>'){
				cnt++;
			}
		}
		if(cnt == 2){
			edItr = itr;
			break;
		}
		itr++;
	}

	nNodes = edItr - ndItr - 1;
	int nEdges = n - edItr - 1;

	const regex re(R"(>|,)");
	
	// const vector<string> tokenizedNodes = tokenize(lines[ndItr], re);
	const vector<string> tokenizedEdges = tokenize(lines[edItr], re);
	int i1, i2, i3, i4;

	for(int i = 0; i < tokenizedEdges.size(); i++){
		string s1 = tokenizedEdges[i];

		string s2 = "node1";
		string s3 = "node2";
		string s4 = "weight";
		string s5 = "directed";
		
		if (s1.find(s2) != std::string::npos){
			i1 = i;
		}
		if (s1.find(s3) != std::string::npos){
			i2 = i;
		}
		if (s1.find(s4) != std::string::npos){
			i3 = i;
		}
		if (s1.find(s5) != std::string::npos){
			i4 = i;
		}				
	}
	i1--;	i2--;	i3--;	i4--;
	
	// cout << i1 << " " << i2 << " " << i3 << " " << i4 << endl;

	int nodeVariables = 1, edgeVariables = 1;
	for(int i = 0; i < lines[ndItr].size(); i++){
		if(lines[ndItr][i] == ','){
			nodeVariables++;
		}
	}
	for(int i = 0; i < lines[edItr].size(); i++){
		if(lines[edItr][i] == ','){
			edgeVariables++;
		}
	}

	map<string, int> nodeMap;
	map<int, string> nodeMapReversed;
	map<string, string> nodeMapLabel;

	for(int i = 1; i <= nNodes; i++){
		const regex re1(R"(,)");
		const vector<string> tokens = tokenize(lines[i], re1);

		nodeMap.insert({tokens[0], i});
		nodeMapReversed.insert({i, tokens[0]});
		nodeMapLabel.insert({tokens[0], tokens[1]});
	}
	
	// ((node1, node2), (weight, directed)) 
	vector<pair<pair<int, int>, pair<double, string>>> edgeInfo;

	for(int i = edItr + 1; i < n; i++){
		const regex re1(R"(,)");
		const vector<string> tokens = tokenize(lines[i], re1);		

		pair<int, int> edgePair1;
		edgePair1 = make_pair(nodeMap.at(tokens[i1]), nodeMap.at(tokens[i2]));
		pair<double, string> edgePair2;
		edgePair2 = make_pair(stod(tokens[i3]), tokens[i4]);
		edgeInfo.push_back(make_pair(edgePair1, edgePair2));
	}

	// adjacency list
	vector<vi> adjacencyList(nNodes + 1);
	for(int i = 0; i < nEdges; i++){
		adjacencyList[edgeInfo[i].first.first].push_back(edgeInfo[i].first.second);

		if(edgeInfo[i].second.second == "false"){
			adjacencyList[edgeInfo[i].first.second].push_back(edgeInfo[i].first.first);
		}
	}
	
	// adjacency matrix directed
	// initializations
	for (int i = 0; i < nNodes + 1; i++) {
		for(int j = 0; j < nNodes + 1; j++){
			adjMatrix[i][j] = 0;
		}
	}
	// adding edges
	for(int i = 1; i <= nNodes; i++) {
		for(int j = 0; j < (int)adjacencyList[i].size(); j++) {
			adjMatrix[i][adjacencyList[i][j]]++;
		}
	}
}

void Task1::write()
{
	// code for writing the result to a new file
	ofstream myFile("WriteIMT2019052.csv");

	for (int i = 1; i < nNodes + 1; i++) {
		for(int j = 1; j < nNodes + 1; j++){
			myFile << adjMatrix[i][j] << " ";
		}
		myFile << "\n";
	}

	myFile.close();	
}
