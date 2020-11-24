#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include "Task8.h"
#define all(x) x.begin(), x.end()

using namespace std;

Task8::Task8(string fn, string c1, string c2) {
	filename = fn;
	int j = 1;
	for(int i = 0; i < c1.size(); i++) {
		col1 += (c1[i] - 'A')*j;
		j *= 26;
	}

	j = 1;
	for(int i = 0; i < c2.size(); i++) {
		col2 += (c2[i] - 'A')*j;
		j *= 26;
	}
}

Task8::Task8(Task8 &task8) {
	col = task8.col;
	row = task8.row;
	matrix = task8.matrix;
	col1 = task8.col1;
	col2 = task8.col2;
	filename = task8.filename;
}

Task8::~Task8() {}

void Task8::read() {
  	
  	ifstream file;
  	file.open(filename);

  	string s;
  	while(getline(file, s)) {
  		col = 0;
  		vector<string> vs;
  		string word = "";
  		for(char c : s) {
  			if(c == ',') {
  				col++;
  				vs.push_back(word);
  				word = "";
  				continue;
  			}
  			word += c;
  		}
  		vs.push_back(word);
  		col++;
  		if(row == 0) {
  			first = vs;
  		}
  		else {
  			matrix.push_back(vs);
  		}
  		row++;
  	}

}


 void Task8::operate() {

 	if(col1 < 0 || col1 >= matrix.size() || col2 <  0 || col2 >= matrix.size()) {
 		cout << "INVALID COLUMNS";
 		return;
 	}

 	sort(matrix.begin(), matrix.end(), [&](const auto &lhs, const auto &rhs) {
 		if(lhs[col1] == rhs[col1]) {
 			return lhs[col2] < rhs[col2];
 		}
 		return lhs[col1] < rhs[col1];
 	});


}



void Task8::write() {
	fstream fout;
 	fout.open("new.csv", ios::out);

 	for(int i = 0; i < first.size(); i++) {
 		fout << first[i];
 		if(i != first.size() - 1) {
 			fout << ",";
 		}
 	}

 	for(int i = 0; i < matrix.size(); i++) {
 		for(int j = 0; j < matrix[i].size(); j++) {
 			fout << matrix[i][j];
 			if(j + 1 != matrix[i].size()) {
 				fout << ",";
 			}
 		}
 		fout << '\n';
 	}

}
