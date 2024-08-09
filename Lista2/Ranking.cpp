#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct jogador {
    string N;
    int P;
};

struct AVLNode {
    jogador data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

AVLNode* newNode(jogador data) {
    AVLNode* node = new AVLNode();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;  // New node is initially added at leaf
    return node;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLNode* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

AVLNode* insert(AVLNode* node, jogador data) {
    if (node == nullptr) return newNode(data);

    if (data.P < node->data.P)
        node->left = insert(node->left, data);
    else if (data.P > node->data.P)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data.P < node->left->data.P)
        return rightRotate(node);

    if (balance < -1 && data.P > node->right->data.P)
        return leftRotate(node);

    if (balance > 1 && data.P > node->left->data.P) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data.P < node->right->data.P) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* search(AVLNode* root, int key) {
    if (root == nullptr || root->data.P == key)
        return root;

    if (root->data.P < key)
        return search(root->right, key);

    return search(root->left, key);
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

AVLNode* maxValueNode(AVLNode* node) {
    AVLNode* current = node;

    while (current->right != nullptr)
        current = current->right;

    return current;
}

void findPredecessorSuccessor(AVLNode* root, AVLNode*& predecessor, AVLNode*& successor, int key) {
    if (root == nullptr)
        return;

    if (root->data.P == key) {
        if (root->left != nullptr)
            predecessor = maxValueNode(root->left);

        if (root->right != nullptr)
            successor = minValueNode(root->right);
        return;
    }

    if (root->data.P > key) {
        successor = root;
        findPredecessorSuccessor(root->left, predecessor, successor, key);
    } else {
        predecessor = root;
        findPredecessorSuccessor(root->right, predecessor, successor, key);
    }
}

int main() {
    int K;
    cin >> K;
    AVLNode* root = nullptr;

    for (int i = 0; i < K; ++i) {
        string command;
        cin >> command;

        if (command == "ADD") {
            string N;
            int P;
            cin >> N >> P;

            if (search(root, P) == nullptr) {
                jogador data = { N, P };
                root = insert(root, data);
                cout << N << " inserido com sucesso!" << endl;
            } else {
                cout << N << " ja esta no sistema." << endl;
            }
        } else if (command == "PROX") {
            int P;
            cin >> P;

            AVLNode* node = search(root, P);
            if (node == nullptr) continue;

            AVLNode* predecessor = nullptr;
            AVLNode* successor = nullptr;
            findPredecessorSuccessor(root, predecessor, successor, P);

            if (predecessor == nullptr && successor == nullptr) {
                cout << "Apenas " << node->data.N << " existe no sistema..." << endl;
            } else if (predecessor == nullptr) {
                cout << node->data.N << " e o menor! e logo apos vem " << successor->data.N << endl;
            } else if (successor == nullptr) {
                cout << node->data.N << " e o maior! e logo atras vem " << predecessor->data.N << endl;
            } else {
                cout << node->data.N << " vem apos " << predecessor->data.N << " e antes de " << successor->data.N << endl;
            }
        }
    }

    return 0;
}
