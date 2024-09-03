#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Graph {
private:
    vector<int>* graphList;
    int* mark;
    int* distance;
    int numNodes;
    const int UNVISITED = 0, VISITED = 1;

    void checkNode(int nodeIndex) {
        if (nodeIndex < 0 || nodeIndex >= numNodes) {
            cerr << "node out of bounds - checkNode" << endl;
            exit(1);
        }
    }

    void setMark(int currNode, int state) {
        mark[currNode] = state;
    }

    bool getMark(int currNode) {
        return mark[currNode] == VISITED;
    }

    void BFSDistance(int start) {
        queue<int> nodeQueue;
        nodeQueue.push(start);
        setMark(start, VISITED);
        distance[start] = 0;

        while (!nodeQueue.empty()) {
            int currNode = nodeQueue.front();
            nodeQueue.pop();

            for (int nextNode : graphList[currNode]) {
                if (!getMark(nextNode)) {
                    setMark(nextNode, VISITED);
                    distance[nextNode] = distance[currNode] + 1;
                    nodeQueue.push(nextNode);
                }
            }
        }
    }

public:
    Graph(int size) {
        graphList = new vector<int>[size];
        mark = new int[size];
        distance = new int[size];
        numNodes = size;
    }

    ~Graph() {
        delete[] graphList;
        delete[] mark;
        delete[] distance;
    }

    void setEdge(int a, int b) {
        checkNode(a);
        checkNode(b);
        graphList[a].push_back(b);
    }

    int* MinDistances(int start) {
        checkNode(start);
        for (int i = 0; i < numNodes; i++) {
            setMark(i, UNVISITED);
            distance[i] = -1;
        }
        BFSDistance(start);
        return distance;
    }
};

int main() {
    int n, m, start = -1, end = -1;
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m));
    Graph g(n * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];

            if (matrix[i][j] == 2) start = i * m + j;
            if (matrix[i][j] == 3) end = i * m + j;

            if (matrix[i][j] != 1) {
                if (i > 0 && matrix[i - 1][j] != 1) g.setEdge(i * m + j, (i - 1) * m + j); // cima
                if (i < n - 1 && matrix[i + 1][j] != 1) g.setEdge(i * m + j, (i + 1) * m + j); // abaixo
                if (j > 0 && matrix[i][j - 1] != 1) g.setEdge(i * m + j, i * m + (j - 1)); // esquerda
                if (j < m - 1 && matrix[i][j + 1] != 1) g.setEdge(i * m + j, i * m + (j + 1)); // direita
            }
        }
    }

    if (start == -1 || end == -1) {
        cout << "Labirinto Impossivel" << endl;
        return 0;
    }

    int* distance = g.MinDistances(start);
    if (distance[end] != -1) cout << distance[end] << endl;
    else cout << "Labirinto Impossivel" << endl;

    return 0;
}
