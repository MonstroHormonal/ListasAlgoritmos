#include <iostream>

using namespace std;

class BSTNode{
public:
    int key;
    BSTNode *left, *right;

    BSTNode(int k)
    {
        key = k;
        left = right = NULL;
    }
};

class BST{
private:
    BSTNode *root;
    int nodecount;
    BSTNode *inserthelp(BSTNode *rt, int k){
    
        if(rt == NULL) return new BSTNode(k);
        if(rt->key > k) rt->left = inserthelp(rt->left, k);
        else rt->right = inserthelp(rt->right, k);
        return rt;
    }
    
    void preorder(BSTNode *rt){
    
        if(rt != NULL){
            printf(" %d", rt->key);
            preorder(rt->left);
            preorder(rt->right);
        }
    }
    
    void inorder(BSTNode *rt){
    
        if(rt != NULL){
            inorder(rt->left);
            printf(" %d", rt->key);
            inorder(rt->right);
        }
    }
    
    void postorder(BSTNode *rt){
        
        if(rt != NULL){
            postorder(rt->left);
            postorder(rt->right);
            printf(" %d", rt->key);
        }
    }

public:
    BST(){
        root = NULL;
        nodecount = 0;
    }

    ~BST(){
        Clear(root);
    }

    void insert(int k){

        root = inserthelp(root, k);
    }

    void Clear(BSTNode *rt){

            if(rt != NULL){
            Clear(rt->left);
            Clear(rt->right);
            delete rt;
        }
    }
    
    
    void preorder(){
        preorder(root);
    }
    
    void inorder(){
        inorder(root);
    }
    
    void postorder(){
        postorder(root);
    }
};

int main(){

    int i, n, p;
    BST bst;

    cin >> n;
    for(i = 0; i < n; i++){

        cin >> p;
        bst.insert(p);

    }
    
    cout << "Pre order :";
    bst.preorder();
    cout << "\nIn order  :";
    bst.inorder();
    cout << "\nPost order:";
    bst.postorder();

    return 0;
}
