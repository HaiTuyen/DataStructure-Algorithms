#include <iostream>
#include <map>
#include <list>
#include <stack>
#include <vector>
using namespace std;

// RECURSIVE VERSION:
/* class Graph {
    public: 
    map<int ,bool> visited;
    map<int, list<int> > adj;

    void addEdge(int v, int w);
    void DFS(int v);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::DFS(int v)
{
    visited[v] = true;
    cout << v << " ";

    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i])
        {
            DFS(*i);
        }
    }
} */

// ITARATIVE VERSION:
class Graph
{
    int V;
    list<int> *adj;
    public:
    Graph(int V); 
    void addEdge(int v, int w);
    void DFS(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::DFS(int s)
{
    vector<bool> visited(V, false);
    stack<int> stack;
    stack.push(s);

    while (!stack.empty())
    {
        int s = stack.top();
        stack.pop();

        if (!visited[s])
        {
            cout << s << " ";
            visited[s] = true;
        }

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                stack.push(*i);
            }
        }
    }
}

int main()
{
    // Create a graph given in the above diagram
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Depth First Traversal"
            " (starting from vertex 2) \n";
    g.DFS(2);


    return 0;
}