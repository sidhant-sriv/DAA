#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

#define V 6 // Number of vertices in the graph

// Returns true if there is a path from source 's' to sink 't' in residual graph. Also fills parent[] to store the path
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}

void dfs(int rGraph[V][V], int s, bool visited[]) {
    visited[s] = true;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && rGraph[s][v] > 0) {
            dfs(rGraph, v, visited);
        }
    }
}

bool dfsAugmentingPath(int rGraph[V][V], int s, int t) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));
    dfs(rGraph, s, visited);
    return visited[t];
}

// Ford-Fulkerson algorithm
int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // This array is filled by BFS and to store path

    int max_flow = 0;

    // Augment the flow while there is a path from source to sink
    // While there is a path from source to sink in the residual graph
    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX; // Initialize the path flow to a large value
        // Find the minimum residual capacity along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        // Update the residual capacities and reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow; // Reduce the residual capacity of the forward edge
            rGraph[v][u] += path_flow; // Increase the residual capacity of the backward edge
        }
        max_flow += path_flow; // Add the path flow to the maximum flow
    }

    return max_flow;
}

// Example Usage
int main() {
    int graph[V][V] = {{0, 16, 13, 0, 0, 0},
                       {0, 0, 10, 12, 0, 0},
                       {0, 4, 0, 0, 14, 0},
                       {0, 0, 9, 0, 0, 20},
                       {0, 0, 0, 7, 0, 4},
                       {0, 0, 0, 0, 0, 0}};

    cout << "Max Flow: " << fordFulkerson(graph, 0, 5) << '\n';

    return 0;
}
