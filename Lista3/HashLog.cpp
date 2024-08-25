#include <iostream>
#include <cstring>

using namespace std;

struct Node {
    int T;
    long long int C;
    Node* next;
};

Node* table[100000];
int M;
float Lmax;
int table_size = 0;

int h(int T, int M) {
    return T % M;
}

void rehash() {
    int newM = 2 * M + 1;
    Node* newTable[100000] = {nullptr};

    for (int i = 0; i < M; ++i) {
        Node* current = table[i];
        while (current) {
            Node* nextNode = current->next;
            int newIndex = h(current->T, newM);

            if (!newTable[newIndex]) {
                newTable[newIndex] = current;
                current->next = nullptr;
            } else {
                Node* newCurrent = newTable[newIndex];
                Node* prev = nullptr;
                while (newCurrent && newCurrent->T < current->T) {
                    prev = newCurrent;
                    newCurrent = newCurrent->next;
                }
                if (prev) {
                    prev->next = current;
                } else {
                    newTable[newIndex] = current;
                }
                current->next = newCurrent;
            }
            current = nextNode;
        }
    }

    for (int i = 0; i < newM; ++i) {
        table[i] = newTable[i];
    }

    M = newM;
}

void insert(int T, long long int C) {
    if (static_cast<float>(table_size) / M > Lmax) {
        rehash();
    }

    int index = h(T, M);
    Node* newNode = new Node{T, C, nullptr};

    if (!table[index]) {
        table[index] = newNode;
    } 
    else {
        Node* current = table[index];
        Node* prev = nullptr;
        while (current && current->T < T) {
            prev = current;
            current = current->next;
        }
        if (prev) {
            prev->next = newNode;
        } 
        else {
            table[index] = newNode;
        }
        newNode->next = current;
    }
    table_size++;

    int count = 0;
    Node* countNode = table[index];
    while (countNode) {
        count++;
        countNode = countNode->next;
    }

    cout << index << " " << count << endl;
}

void query(int T) {
    int index = h(T, M);
    Node* current = table[index];

    int position = 0;
    while (current) {
        if (current->T == T) {
            cout << current->C << " " << position << endl;
            return;
        }
        position++;
        current = current->next;
    }
    cout << "-1 -1" << endl;
}

int main() {
    cin >> M >> Lmax;

    memset(table, 0, sizeof(table));

    string command;
    while (cin >> command && command != "END") {
        if (command == "NEW") {
            int T;
            long long int C;
            cin >> T >> C;
            insert(T, C);
        } 
        else if (command == "QRY") {
            int T;
            cin >> T;
            query(T);
        }
    }

    return 0;
}
