#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
 
// 1. Convert Adjacency matrix to Adjacency list ()

/* vector<vector<int>> read_AdjMatrix(string file)
{
    ifstream ifs;
    ifs.open(file);
    string str, temp;
    getline(ifs, str);

    int size = stoi(str);
    vector<vector<int>> adjMatrix(size, vector<int>(size, 0));

    int i = 0, j = 0;

    while (!ifs.eof())
    {
        getline(ifs, str);
        stringstream ss(str);
        while (getline(ss, temp, ' '))
        {
            adjMatrix[i][j] = stoi(temp);
            j++;
        }
        i++;
        j = 0;
    } 

    ifs.close();
    return adjMatrix;
} */
// This is a right method, but two fuction read_AdjMatrix() and read_AdjList() is the SAME,
// So I just use one for both: 
vector<vector<int>> readMatrix(string file)
{
    ifstream ifs;
    ifs.open(file);
    string str, temp;
    getline(ifs, str);

    int size = stoi(str);
    vector<vector<int>> adjList(size);

    int i = 0, j = 0;

    while (!ifs.eof())
    {
        getline(ifs, str);
        stringstream ss(str);
        while (getline(ss, temp, ' '))
        {
            adjList[i].push_back(stoi(temp));
        }
        i++;
    } 

    ifs.close();
    return adjList;
}




vector<vector<int>> convert( vector<vector<int>> a)
{
    vector<vector<int>> adjList(a.size());
    for (int i = 0; i < a.size(); i++)
    {
         
        for (int j = 0; j < a[i].size(); j++)
        {
            if (a[i][j] == 1)
            {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

// 2. Convert Adjacency list to Adjacency matrix

// This is a right method, but two fuction read_AdjMatrix() and read_AdjList() is the SAME,
// So I just use the fuction readMatrix() declared before.

/* vector<vector<int>> read_AdjList(string file)
{
    ifstream ifs;
    ifs.open(file);
    string str, temp;
    getline(ifs, str);

    int size = stoi(str);
    vector<vector<int>> adjList(size);

    int i = 0, j = 0;

    while (!ifs.eof())
    {
        getline(ifs, str);
        stringstream ss(str);
        while (getline(ss, temp, ' '))
        {
            adjList[i].push_back(stoi(temp));
        }
        i++;
    } 

    ifs.close();
    return adjList;
}
 */


void printMatrix(vector<vector<int>> adjMatrix)
{
    for(int i = 0; i < adjMatrix.size(); i++)
    {
        for(int j = 0; j < adjMatrix[i].size(); j++)
        {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }    
}

// 3. Implement functions to provide the following information of a given graph:
// ---3.1. Directed or Undirected Graph:
// ** Note: The adjacency matrix for an undirected graph is symmetrical; that is, matrix[i][j] equals matrix[j][i].
bool checkDirected(vector<vector<int>> adjMatrix)
{
    for (int i = 0; i < adjMatrix.size(); i++)
    {
        for (int j = 0; j < adjMatrix.size(); j++)
        {
            if (adjMatrix[i][j] != adjMatrix[j][i])
            {
                return false;
            }
        }
    }
    return true;
}
     
// Driver code
int main()
{
    //---Driver code for task 1: convert adjacency matrix to adjacency list---
    string file = "graph1.txt";
    vector<vector<int>> adjMatrix = readMatrix(file);
    printMatrix(adjMatrix);
    cout << "\n\n";
    vector<vector<int>> adjList = convert(adjMatrix);
    printMatrix(adjList);
    cout << "\n\n";

    //---Driver code for task 2: convert adjacency list to adjacency matrix---
    /* string file = "graph2.txt";
    vector<vector<int>> adjList = readMatrix(file);
    printMatrix(adjList); */

    //---Driver code for task 3: convert adjacency list to adjacency matrix---
    bool id_DirectedGraph = checkDirected(adjMatrix);
    cout << id_DirectedGraph;

    return 0;
}