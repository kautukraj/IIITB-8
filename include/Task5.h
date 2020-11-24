#ifndef TASK5_H
#define TASK5_H
#include <iostream>
#include <utility>
#include "Base.h"
#include <vector>

using namespace std;

class Task5: public Base
{

public:

    Task5(string);
    ~Task5();
    Task5(Task5 &Task5);


    void read() override;
    void operate() override;
    void write() override;


private:
    string filename;
    vector <string> nodes;
    int V;

};




#endif //APROJECT_TASK5_H
