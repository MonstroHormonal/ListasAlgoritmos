#include <iostream>
#include <string>

using namespace std;

// Estrutura para representar uma carta
struct Card {
    int value;
    char suit;

    Card() : value(0), suit('0') {}
    Card(int v, char s) : value(v), suit(s) {}

    bool operator>(const Card &other) const {
        if (value == other.value) {
            return suit > other.suit;
        }
        return value > other.value;
    }

    bool operator==(const Card &other) const {
        return value == other.value && suit == other.suit;
    }
};

// Estrutura de nó para lista encadeada
struct Node {
    Card card;
    Node* next;

    Node(Card c) : card(c), next(nullptr) {}
};

// Estrutura de fila usando lista encadeada
struct Queue {
    Node* front;
    Node* rear;
    int size;

    Queue() : front(nullptr), rear(nullptr), size(0) {}

    void enqueue(Card card) {
        Node* newNode = new Node(card);
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
        size++;
    }

    Card dequeue() {
        if (front) {
            Node* temp = front;
            Card card = temp->card;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
            size--;
            return card;
        }
        return Card();
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
        size = 0;
    }
};

int charToValue(char c) {
    return c - '0';
}

int main() {
    int N;
    cin >> N;
    Queue* queues = new Queue[N];
    string command;
    Card* cuscuz = nullptr;
    int cuscuzSize = 0;
    int roundCount = 0;

    while (cin >> command && command != "END") {
        if (command == "DEA") {
            for (int i = 0; i < N; ++i) {
                string cardStr;
                cin >> cardStr;
                Card card(charToValue(cardStr[0]), cardStr[1]);
                queues[i].enqueue(card);
            }
        } else if (command == "RND") {
            Card* roundCards = new Card[N];
            for (int i = 0; i < N; ++i) {
                if (!queues[i].isEmpty()) {
                    roundCards[i] = queues[i].dequeue();
                }
            }

            Card highestCard = roundCards[0];
            int winner = 0;
            bool tie = false;

            for (int i = 1; i < N; ++i) {
                if (roundCards[i] > highestCard) {
                    highestCard = roundCards[i];
                    winner = i;
                    tie = false;
                } else if (roundCards[i] == highestCard) {
                    tie = true;
                }
            }

            if (tie) {
                cout << roundCount << " -1" << endl;
            } else {
                cout << roundCount << " " << winner << endl;
            }

            if (cuscuz) {
                delete[] cuscuz;
            }
            cuscuz = roundCards;
            cuscuzSize = N;
            roundCount++;
        } else if (command == "PRT") {
            for (int i = cuscuzSize - 1; i >= 0; --i) {
                cout << cuscuz[i].value << cuscuz[i].suit;
                if (i > 0) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    for (int i = 0; i < N; ++i) {
        queues[i].clear();
    }
    delete[] queues;

    if (cuscuz) {
        delete[] cuscuz;
    }

    return 0;
}
