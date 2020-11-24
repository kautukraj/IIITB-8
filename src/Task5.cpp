#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Task5.h"

using namespace std;

Task5::Task5(string filename) // constructor
{
    this->filename = filename;
}


/*
Generic function to find an element in vector and also its position.
It returns a pair of bool & int i.e.
bool : Represents if element is present in vector or not.
int : Represents the index of element in vector if its found else -1
*/
template < typename T> // declare a function template

std::pair <bool, int > findInVector(const std::vector<T>  & vecOfElements, const T  & element)
{
    std::pair<bool, int > result;

    // Find given element in vector
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
    if (it != vecOfElements.end())
    {
        result.second = distance(vecOfElements.begin(), it); // index of element
        result.first = true; // element is present
    }
    else
    {
        result.first = false; // element is not present
        result.second = -1; // index is -1
    }
    return result;
}



void addEdge(vector <pair<int, float> > adj[], int u, int v, float wt) // add an edge to undirected graph
{
    adj[u].emplace_back(v, wt); // --> direction
    adj[v].emplace_back(u, wt); // <-- direction
}


// Print adjacency list representation ot graph
void printGraph(vector <pair<int, float> > adj[], int V)
{
    int v; // neighbouring node
    float weight; // weight of edge

    for (int u = 0; u < V; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto &it : adj[u]) // auto iterator
        {
            v = it.first;
            weight = it.second;
            cout << "\tNode " << v << " with edge weight = " << weight << "\n";
        }
        cout << "\n";
    }
}



void filterGraph(vector <pair<int, float> > adj[], int V, const vector<int>& filteredNodes, vector <string> nodes)
{

    int v; float weight;

    int tag[V][V]; // array to store if an edge has been printed or not
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            tag[i][j]= -1; // initially no node is printed

    ofstream MyFile ("output.dl");

    MyFile << "Dl n=" << V/2 << endl;
    MyFile << "format = edgelist1" << endl;
    MyFile << "labels embedded:" << endl;
    MyFile << "data:" << endl;

    cout << "Output\n" << endl;

    for (int u = 0; u < V; u++)
    {
        std::pair<bool, int> result = findInVector<int>(filteredNodes, u);
        if (!result.first)
            continue;

        cout << "Node " << u << " makes an edge with \n";
        for (auto &it : adj[u])
        {
            v = it.first;

            std::pair<bool, int> result = findInVector<int>(filteredNodes, v);
            if (!result.first || tag[u][v] == 1)
                continue;

            tag[u][v] = 1;
            tag[v][u] = 1; // make the adjacent also true

            weight = it.second;
            cout << "\tNode " << v << " with edge weight = " << weight << "\n";

            MyFile << nodes.at(u) << " " << nodes.at(v) << " " << weight << endl;

        }
        cout << "\n";
    }

    // Close the file
    MyFile.close();
}




vector <int> findDegree(vector <pair<int, float> > adj[], int V) // utility function to find degree of each node
{
    vector <int> degrees;
    degrees.reserve(V); // request a reservation in capacity of vector

    for (int u = 0; u < V; u++)
        degrees.push_back(adj[u].size());

    return degrees;

}


void Task5::read()
{
    string data;

    ifstream my_file; // stream class to read from files
    //my_file.open(R"(D:\this\C++\aproject\input.txt)", ios::in); // allow input (read operations) from a stream

    my_file.open(filename, ios::in); // Clion looks for input files and writes output files to the Debug folder.
    // If you put your input files in there it will see them.

    if(!my_file) // if file is not present or unable to open
        cout << "No such file";

    getline(my_file, data); // DL n=#

    int equalsIndex = data.find_first_of('=');
    V = stoi(data.substr(equalsIndex + 1, data.length() - equalsIndex - 1)); // number of nodes/vertices

    getline(my_file, data); // format = edgelist1
    getline(my_file, data); // labels embedded:
    getline(my_file, data); // data:

    vector<pair<int, float> > adj[V];

    for (int i = 0; i < V; i++) // read all the nodes from the file
    {
        getline(my_file, data);

        int firstSpace = data.find_first_of(' ');
        int lastSpace = data.find_last_of(' ');

        string leftNode = data.substr(0, firstSpace);
        int leftIndex = 0;
        std::pair<bool, int> leftResult = findInVector<string>(nodes, leftNode);
        if (leftResult.first)
        {
            //std::cout << "Element Found at index : " << leftResult.second << std::endl;
            leftIndex = leftResult.second;
        }
        else
        {
            //std::cout << "Element Not Found" << std::endl;
            nodes.push_back(leftNode);
            leftIndex = nodes.size() - 1;
        }

        //cout << "Left index = " << leftIndex << endl;

        string rightNode = data.substr(firstSpace + 1, lastSpace - firstSpace - 1);
        int rightIndex = 0;
        std::pair<bool, int> rightResult = findInVector<string>(nodes, rightNode);
        if (rightResult.first)
        {
            //std::cout << "Element Found at index : " << rightResult.second << std::endl;
            rightIndex = rightResult.second;
        }
        else
        {
            //std::cout << "Element Not Found" << std::endl;
            nodes.push_back(rightNode);
            rightIndex = nodes.size() - 1;
        }

        //cout << "Right index = " << rightIndex << endl;

        float weight = stof(data.substr(lastSpace + 1, data.length() - lastSpace - 1));

        addEdge(adj, leftIndex, rightIndex, weight); // add edge to the graph
    }

    my_file.close();

    printGraph(adj, V);

    vector <int> degrees = findDegree(adj, V);
    int mapping[V][V]; // create a double dimensional array of node index and node degree

    for (int i = 0; i < V; i++) // initialize the values in the mapping
    {
        mapping[i][0] = i;
        mapping[i][1] = degrees.at(i);
    }

    for(int i = 0; i < V; i++) // sort the mapping according to the degree
    {
        for(int j = i+1; j < V; j++)
        {
            if(mapping[i][1] < mapping[j][1])
            {
                int temp = mapping[i][1];
                mapping[i][1] = mapping[j][1];
                mapping[j][1] = temp;

                int temp1 = mapping[i][0];
                mapping[i][0] = mapping[j][0];
                mapping[j][0] = temp1;

            }
        }
    }


    vector <int> filteredNodes; // store node indices as per 50% criteria
    filteredNodes.reserve(V/2);
    for (int i = 0; i < V/2; i++)
        filteredNodes.push_back(mapping[i][0]);



    filterGraph(adj, V, filteredNodes, nodes); // filter the graph (nodes and edges) as per requirement

}


 void Task5::operate()
{
    // write code here
}



void Task5::write()
{
    // write code here
}

Task5::~Task5()
{
    // destructor
}

Task5::Task5(Task5 &Task5)
{
    this->filename = Task5.filename;
    this->V = Task5.V;

}
