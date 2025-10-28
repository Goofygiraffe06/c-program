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

Node* insert(Node *root, int data) {
    if (!root) return new_node(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

Node* min_node(Node *node) {
    while (node->left) node = node->left;
    return node;
}

Node* delete(Node *root, int data) {
    if (!root) return root;
    if (data < root->data)
        root->left = delete(root->left, data);
    else if (data > root->data)
        root->right = delete(root->right, data);
    else {
        if (!root->left) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = min_node(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}

Node* search(Node *root, int data) {
    if (!root || root->data == data) return root;
    if (data < root->data) return search(root->left, data);
    return search(root->right, data);
}

void inorder(Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    
    inorder(root); printf("\n");
    
    printf("Search 40: %s\n", search(root, 40) ? "Found" : "Not Found");
    
    root = delete(root, 20);
    inorder(root); printf("\n");
    
    return 0;
}
