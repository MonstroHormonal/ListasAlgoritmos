#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;

vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& adjList) {
    int n = adjList.size();
    vector<int> dist(n, INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (currentDist > dist[currentNode]) continue;

        for (const auto& edge : adjList[currentNode]) {
            int nextNode = edge.first;
            int weight = edge.second;

            if (dist[currentNode] + weight < dist[nextNode]) {
                dist[nextNode] = dist[currentNode] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    return dist;
}

struct Edge {
    int from, to, cost;
};

int main() {
    int Q, R, N; // Número de quadras, número de ruas iniciais, número de eventos
    int input;

    cin >> Q >> R >> N;

    vector<vector<pair<int, int>>> adjList(Q); // Lista de adjacência

    for (int i = 0; i < R; i++) {
        int from, to, cost;
        cin >> from >> to >> cost;
        adjList[from].push_back({to, cost});
    }

    for (int i = 0; i < N; i++) {
        cin >> input;
        if (input == 1) {
            int from, to, cost;
            cin >> from >> to >> cost;
            adjList[from].push_back({to, cost});
        } else if (input == 2) {
            int from, to;
            cin >> from >> to;

            vector<int> dist = dijkstra(from, adjList);

            if (dist[to] == INF) {
                cout << -1 << endl;
            } else {
                cout << dist[to] << endl;
            }
        }
    }

    return 0;
}
