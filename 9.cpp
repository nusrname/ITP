#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Graph
{
protected:

	int V; // количество вершин
	vector<vector<int>> adj; // список смежности

public:

	Graph(int V) : V(V), adj(V) {}

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

	int getVertexCount() const { return V; }
};

class orderedGraph : protected Graph
{
public:
	orderedGraph(int V) : Graph(V) {}

	void addEdge(int u, int v)
	{
		for (int i = 0; i < adj[v].size(); ++i)
			if (adj[v][i] == u)
				return;
		adj[u].push_back(v);
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

	void print() { Graph::print(); }

};

class notOrderedGraph : protected Graph
{
public:

	notOrderedGraph(int V) : Graph(V) {}

	void addEdge(int u, int v)
	{
		for (int i = 0; i < adj[v].size(); ++i)
			if (adj[v][i] == u)
				return;
		adj[v].push_back(u);
		adj[u].push_back(v);
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

	void print() { Graph::print(); }
};

int main()
{
	int V;
	string t;
	cout << "Input count of vertices: ";
	cin >> V;
	notOrderedGraph g(V);
	cout << "Input adjacency list: " << endl;
	cin.ignore();

	for (int i = 0; i < V; ++i)
	{
		getline(cin, t);
		istringstream iss(t);
		int v;
		while (iss >> v)
			g.addEdge(i, v);
	}

	cout << "Input vertex: ";
	int vertex;
	cin >> vertex;
	cout << "Count of adjacent vertices to " << vertex << ": " << g.countAdjacentUndirected(vertex) << endl;

	cout << "Input A and B: ";
	int A, B;
	cin >> A >> B;
	g.addEdge(A, B);
	cout << "Edge inserted between " << A << " and " << B << endl;
	g.print();

	vector<int> degrees = g.vertexDegrees();
	cout << "Degrees of vertices: ";
	for (int d : degrees) cout << d << ' ';
	cout << endl;

	cout << "Graph is " << (g.isConnected() ? "connected" : "not connected") << endl << endl;
	cin.ignore();

	cout << "Work with ordered graph\nInput adjacency list:" << endl;

	orderedGraph dg(V);
	for (int i = 0; i < V; ++i) 
	{
		getline(cin, t);
		istringstream iss(t);
		int v;
		while (iss >> v)
			dg.addEdge(i, v);
	}
	dg.print();
	vector<int> sources = dg.sourcesDirected();
	cout << "Sources in directed graph: ";
	for (int s : sources)
		cout << s << ' ';
	cout << endl;

	return 0;
}
