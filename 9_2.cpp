#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

class Graph 
{
protected:

	int V;
	vector<vector<int>> adj;

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

	void print() { Graph::print(); }

};

class notOrderedGraph : protected Graph
{
	vector<int> EulersPath;

	void notOrderedDelEdge(int u, int v)
	{
		vector<int>& adjU = adj[u];
		vector<int>& adjV = adj[v];

		adjU.erase(find(adjU.begin(), adjU.end(), v));
		adjV.erase(find(adjV.begin(), adjV.end(), u));
	}	
	
	// ѕодсчитать степень каждой вершины
	vector<int> vertexDegrees()
	{
		vector<int> degrees(V);
		for (int i = 0; i < V; i++)
			degrees[i] = adj[i].size();
		return degrees;
	}

	// —в€зность графа
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

	// ќпредел€ем, существует ли Ёйлеров цикл, находим Ёйлеров путь
	bool Exist()
	{
		vector<int> degrees = vertexDegrees(), result;
		stack<int> s;
		int v1 = -1, v2 = -1, head, adjacent;
		bool res = 1;

		for (int i = 0; i < V; i++)
		{
			if (degrees[i] % 2)
			{
				if (v1 == -1)
					v1 = i;
				else if (v2 == -1)
					v2 = i;
				else
					res = 0;
			}
		}

		if (!isConnected())
			res = 0;

		if (v2 != -1)
			addEdge(v1, v2);

		if (v1 == -1)
			v1 = 0;

		s.push(v1);
		while (!s.empty())
		{
			head = s.top();
			if (!adj[head].empty()) 
			{
				adjacent = adj[head].back();
				s.push(adjacent);
				notOrderedDelEdge(head, adjacent);
			}
			else 
			{
				result.push_back(head);
				s.pop();
			}
		}

		for (int el : result)
			cout << el << ' ';
		cout << endl;

		if (v1 != -1)
		{
			for (int i = 0; i < result.size() - 1; i++)
			{
				if (result[i] == v1 && result[i + 1] == v2 || result[i] == v2 && result[i + 1] == v1)
				{
					for (int j = i + 1; j < result.size() - 1; j++)
						EulersPath.push_back(result[j]);
					for (int j = 0; j <= i; j++)
						EulersPath.push_back(result[j]);
					break;
				}
			}
		}

		if (isConnected())
			res = 0;

		cout << "Euler\'s path: ";
		for (int el : EulersPath)
			cout << el << ' ';
		cout << endl;

		return res;
	}

	void print() { Graph::print(); }
};

int main()
{
	// —оздание графа и его ввод
	int V;
	string str;
	cout << "Input count of vertices: ";
	cin >> V;
	notOrderedGraph g(V);
	cout << "Input adjacency list: " << endl;
	cin.ignore();

	for (int i = 0; i < V; ++i)
	{
		getline(cin, str);
		istringstream iss(str);
		int v;
		while (iss >> v)
			g.addEdge(i, v);
	}

	cout << (g.Exist() ? "Euler cycle exists" : "Euler cycle doesn\'t exist") << endl;
}

//1 2 4 5
//0 3 4
//0 3 4
//2 4 5
//0 1 2 3
//0 3