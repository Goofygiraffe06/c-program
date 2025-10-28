#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* new_node(int data) {
    Node *n = malloc(sizeof(Node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

Node* lca(Node *root, int n1, int n2) {
    if (!root || root->data == n1 || root->data == n2) return root;
    Node *left = lca(root->left, n1, n2);
    Node *right = lca(root->right, n1, n2);
    if (left && right) return root;
    return left ? left : right;
}

int main() {
    Node *root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);
    root->left->left = new_node(4);
    root->left->right = new_node(5);
    
    Node *result = lca(root, 4, 5);
    printf("LCA: %d\n", result->data);
    return 0;
}
