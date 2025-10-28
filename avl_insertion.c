#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *n) {
    return n ? n->height : 0;
}

Node* new_node(int data) {
    Node *n = malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

Node* right_rotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* left_rotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int get_balance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* insert(Node *node, int data) {
    if (!node) return new_node(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;
    
    node->height = 1 + max(height(node->left), height(node->right));
    int balance = get_balance(node);
    
    if (balance > 1 && data < node->left->data)
        return right_rotate(node);
    if (balance < -1 && data > node->right->data)
        return left_rotate(node);
    if (balance > 1 && data > node->left->data) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance < -1 && data < node->right->data) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

void preorder(Node *root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    
    preorder(root);
    printf("\n");
    return 0;
}
