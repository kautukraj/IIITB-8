#ifndef TASK6_H
#define TASK6_H

#include "Base.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<bits/stdc++.h>
#include <string>
#include<cstring>
using namespace std;

class Task6: public Base{  

    private:
        vector<string> input_read;
        vector<string> output_write;
        int vertices, faces;
        string filename;
        vector<string> split_str(string);
        string custom_trunc(string);
      
    protected:
    public:
        Task6(string);
        void read() override;
        void operate() override;
        void write() override;

};

#endif //APROJECT_TASK6_H