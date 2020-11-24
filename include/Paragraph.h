#ifndef PARAGRAPGH_H
#define PARAGRAPH_H
#include "stats.h"
#include<vector>
#include<iostream>
using namespace std;
class Paragraph{
    private:
        Stats S;//using composition to store the stats of this paragraph
        string text;
    public:
        Paragraph(){}//default
        Paragraph(string text);//main constructor
        Paragraph(const Paragraph &P);//copy constructor
        ~Paragraph(){}//destructor
        void setStats(Stats S){
            this->S = S;
        }
        string getText() const{return text;}//getters for text and stats
        Stats getStats() const{return S;}

};
#endif