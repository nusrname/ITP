#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

class Graph
{
	int V;
	vector<vector<pair<int, int>>> adj;

public:

	Graph(int V) : V(V), adj(V) {}

	void addEdge(int u, int v, int w)
	{
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}

    void distation(int start) 
    {
        vector<int> dist(V, numeric_limits<int>::max());                        // дистанции до вершин
        vector<int> prev(V, -1);                                                // предыдущие вершины для восстановления пути   
        dist[start] = 0;


        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty())
        {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u])                                                    // пропуск устаревшей записи
                continue;

            for (auto& edge : adj[u])
            {
                int v = edge.first;
                int w = edge.second;
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                    pq.emplace(dist[v], v);
                }
            }
        }

        for (int i = 0; i < V; ++i) 
        {
            if (dist[i] == numeric_limits<int>::max()) 
            {
                cout << "Vertex " << i << ": no path\n";
                continue;
            }

            cout << "Vertex " << i << ": distance = " << dist[i] << ", path = ";
            stack<int> path;

            for (int v = i; v != -1; v = prev[v])
                path.push(v);

            while (!path.empty())
            {
                cout << path.top() << ' ';
                path.pop();
            }
            cout << '\n';
        }
    }
};

int main()
{
	int V, E, start, v, w;
	string str;
	cout << "Input count of vertices: ";
	cin >> V;
	Graph g(V);
	cout << "Input adjacency list with weight after each neighbor: " << endl;
	cin.ignore();

	for (int i = 0; i < V; ++i)
	{
        cout << "Vertex " << i << ": ";
		getline(cin, str);
		istringstream iss(str);
		while (iss >> v >> w)
			g.addEdge(i, v, w);
	}

    cout << "Input start vertex: ";
    cin >> start;

    g.distation(start);
}