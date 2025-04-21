#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Graph
{
    int V; // количество вершин
    vector<vector<int>> adj; // список смежности

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v)
    {
        // Добавление ребра для неориентированного графа
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Вывести количество вершин, смежных с данной
    int countAdjacentUndirected(int v) 
    {
        return adj[v].size();
    }

    // Подсчитать степень каждой вершины
    vector<int> vertexDegrees() 
    {
        vector<int> degrees(V);
        for (int i = 0; i < V; ++i)
            degrees[i] = adj[i].size();
        return degrees;
    }

    // Проверить связность
    bool isConnected() 
    {
        vector<bool> visited(V, false);
        dfs(0, visited);
        for (bool v : visited)
            if (!v) return false;
        return true;
    }

    void dfs(int v, vector<bool>& visited)
    {
        visited[v] = true;
        for (int u : adj[v])
            if (!visited[u])
                dfs(u, visited);
    }

    // Вывести все истоки графа
    vector<int> sourcesDirected() 
    {
        vector<int> inDegree(V, 0);
        for (int u = 0; u < V; ++u)
            for (int v : adj[u])
                ++inDegree[v];

        vector<int> sources;
        for (int i = 0; i < V; ++i)
            if (inDegree[i] == 0)
                sources.push_back(i);
        return sources;
    }

    void print()
    {
        cout << "Adjacency List (vertex: neighbors): " << endl;
        for (size_t i = 0; i < adj.size(); ++i) 
        {
            cout << i << ": ";
            for (int neighbor : adj[i]) 
                cout << neighbor << ' ';
            cout << '\n';
        }
    }

};

int main()
{
    int V;
    string t;
    cout << "Input count of vertices: ";
    cin >> V;
    Graph g(V);
    cout << "Input elements: ";

/*        
        1 2 4 5
        0 3
        0 5 
        1
        0 6
        0 2 6 
        4 5 
*/

    for (int i = 0; i < V; ++i)
    {
        cin >> t;
        istringstream iss(t);
        int v;
        while (iss >> v)
            g.addEdge(i, v);
    }
    g.print();

    int vertex = 0;
    cout << "Count of adjacent vertices to " << vertex << ": " << g.countAdjacentUndirected(vertex) << endl;

    g.addEdge(3, 6);
    cout << "Edge inserted between 3 and 6." << endl;
    g.print();

    vector<int> degrees = g.vertexDegrees();
    cout << "Degrees of vertices: ";
    for (int d : degrees) cout << d << ' ';
    cout << endl;

    cout << "Graph is " << (g.isConnected() ? "connected" : "not connected") << endl;

    vector<int> sources = g.sourcesDirected();
    cout << "Sources in directed graph: ";
    for (int s : sources) cout << s << ' ';
    cout << endl;

    return 0;
}
