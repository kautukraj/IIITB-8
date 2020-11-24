#ifndef TASK4_H
#define TASK4_H
#include "Base.h"
#include "Paragraph.h"
#include<vector>
#include<iostream>
using namespace std;
class Task4: public Base{
private:
    string txt;//This is the whole text of the file
    vector<Paragraph> paragraphs;//this is use of aggregation to store big text in form of small paragraphs
    string filename;//This is the name of input file
    Stats Total;//This are the final stats for whole file
    
public:
    Task4(string s):Total(0, 0, 0, 0, 0){filename = s;}//taking file name
    ~Task4(){};
    void read() override;//overriding the methods of the base class to perform specific task
    void operate() override;
    void write() override;
    void calculateStats(Paragraph &P);//Given a specific paragraph this function will compute the stats of that particular paragraph

};
#endif //APROJECT_TASK1_H
