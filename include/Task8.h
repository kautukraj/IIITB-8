#ifndef TASK8_H
#define TASK8_H

#include "Base.h"
#include<bits/stdc++.h>

using namespace std;

class Task8: public Base
{
private:
	int col = 0, row = 0;
	vector<vector<string>> matrix;
	vector<string> first;
	string filename;
	int col1 = 0, col2 = 0;

public:
	Task8(string filename, string col1, string col2);
    Task8(Task8 &task8);
    ~Task8();

    void read() override;
    void operate() override;
    void write() override;
};








#endif //APROJECT_TASK1_H
