#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from, to, cost;
};

int find(int u, vector<int>& parent) {
    if (u != parent[u]) {
        parent[u] = find(parent[u], parent);
    }
    return parent[u];
}

void unite(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = find(u, parent);
    v = find(v, parent);
    if (u != v) {
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
    }
}

int HoarePartition(vector<Edge>& edges, int low, int high) {
    int pivot = edges[high].cost;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (edges[j].cost < pivot) {
            i++;
            Edge temp = edges[i];
            edges[i] = edges[j];
            edges[j] = temp;
        }
    }
    Edge temp = edges[i + 1];
    edges[i + 1] = edges[high];
    edges[high] = temp;
    return i + 1;
}

void quickSort(vector<Edge>& edges, int low, int high) {
    if (low < high) {
        int pi = HoarePartition(edges, low, high);
        quickSort(edges, low, pi - 1);
        quickSort(edges, pi + 1, high);
    }
}

int main() {
    int M, N;
    cin >> M >> N;

    vector<Edge> edges(N);

    for (int i = 0; i < N; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    quickSort(edges, 0, N - 1);

    vector<int> parent(M), rank(M, 0);
    for (int i = 0; i < M; i++) {
        parent[i] = i;
    }

    int minCost = 0;

    for (int i = 0; i < N; i++) {
        if (find(edges[i].from, parent) != find(edges[i].to, parent)) {
            minCost += edges[i].cost;
            unite(edges[i].from, edges[i].to, parent, rank);
        }
    }

    cout << minCost << endl;

    return 0;
}
