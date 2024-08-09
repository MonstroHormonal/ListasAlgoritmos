#include <iostream>
#include <string>

using namespace std;

struct item {
    int ID;
    int WEI;
    int RNK;
};

struct AVLNode {
    item data;
    AVLNode* left;
    AVLNode* right;
    int height;
    int totalWeight;
};

int height(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* newNode(const item& it) {
    AVLNode* node = new AVLNode();
    node->data = it;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    node->totalWeight = it.WEI;
    return node;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    y->totalWeight = (y->left ? y->left->totalWeight : 0) +
                     (y->right ? y->right->totalWeight : 0) +
                     y->data.WEI;
    x->totalWeight = (x->left ? x->left->totalWeight : 0) +
                     (x->right ? x->right->totalWeight : 0) +
                     x->data.WEI;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    x->totalWeight = (x->left ? x->left->totalWeight : 0) +
                     (x->right ? x->right->totalWeight : 0) +
                     x->data.WEI;
    y->totalWeight = (y->left ? y->left->totalWeight : 0) +
                     (y->right ? y->right->totalWeight : 0) +
                     y->data.WEI;

    return y;
}

int getBalance(AVLNode* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

AVLNode* insert(AVLNode* node, const item& it) {
    if (node == nullptr) return newNode(it);

    if (it.ID < node->data.ID) node->left = insert(node->left, it);
    else if (it.ID > node->data.ID) node->right = insert(node->right, it);
    else {
        node->data.WEI += it.WEI;
        node->totalWeight += it.WEI;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    node->totalWeight = (node->left ? node->left->totalWeight : 0) +
                        (node->right ? node->right->totalWeight : 0) +
                        node->data.WEI;

    int balance = getBalance(node);

    if (balance > 1 && it.ID < node->left->data.ID)
        return rightRotate(node);

    if (balance < -1 && it.ID > node->right->data.ID)
        return leftRotate(node);

    if (balance > 1 && it.ID > node->left->data.ID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && it.ID < node->right->data.ID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(AVLNode* root) {
    if (root != nullptr) {
        cout << "(" << root->data.ID << "," << root->data.WEI << "," << root->data.RNK << ") ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int getDepth(AVLNode* node, int ID, int depth) {
    if (node == nullptr) return -1;
    if (ID < node->data.ID) return getDepth(node->left, ID, depth + 1);
    if (ID > node->data.ID) return getDepth(node->right, ID, depth + 1);
    return depth;
}

int getWEI(AVLNode* node, int ID) {
    if (node == nullptr) return 0;
    if (ID < node->data.ID) return getWEI(node->left, ID);
    if (ID > node->data.ID) return getWEI(node->right, ID);
    return node->data.WEI;
}

int getRNK(AVLNode* node, int ID) {
    if (node == nullptr) return 0;
    if (ID <= node->data.ID) return getRNK(node->left, ID);
    return (node->left ? node->left->totalWeight : 0) +
           node->data.WEI +
           getRNK(node->right, ID);
}

int main() {
    AVLNode* root = nullptr;
    string entrada;
    item it;
    int W;
    int totalGlobal = 0;

    do {
        cin >> entrada;
        if (entrada == "ADD") {
            cin >> it.ID;
            cin >> W;
            it.WEI = W;
            it.RNK = 0;
            root = insert(root, it);
            totalGlobal += W;
            cout << totalGlobal << endl;
        } else if (entrada == "WEI") {
            int ID;
            cin >> ID;
            int wei = getWEI(root, ID);
            int depth = getDepth(root, ID, 0);
            if (wei == 0) depth = -1;
            cout << wei << " " << depth << endl;
        } else if (entrada == "RNK") {
            int ID;
            cin >> ID;
            cout << getRNK(root, ID) << endl;
        }
    } while (entrada != "END");

    return 0;
}
