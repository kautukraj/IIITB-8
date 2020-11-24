#ifndef STATS_H
#define STATs_H
#include<ostream>
#include<iostream>
#include<fstream>
using namespace std;
class Stats{
    private:
        int words,char_with_spaces,char_without_spaces,lines,bytes;
    public:
        Stats(){}//default
        Stats(int words,int char_with_spaces,int char_without_spaces,int lines,int bytes);//main constructor
        ~Stats(){}//destructor
        Stats(const Stats &S);//copy constructor
        int getWords(){return words;}//getters
        int getLines(){return lines;}
        int getCharWithSpaces(){return char_with_spaces;}
        int getCharWithOutSpaces(){return char_without_spaces;}
        int getBytes(){return bytes;}
        Stats operator + (const Stats &s);//overriding the + operator to add the data of each stats
        friend ofstream & operator <<(ofstream &fout,Stats &S);//To print stats into file
        

};
#endif