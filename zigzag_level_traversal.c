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

void zigzag_traversal(Node *root) {
    if (!root) return;
    Node *queue[1000];
    int front = 0;
    int rear = 0;
    int ltr = 1;
    queue[rear++] = root;
    
    while (front < rear) {
        int count = rear - front;
        int vals[count];
        for (int i = 0; i < count; i++) {
            Node *n = queue[front++];
            vals[i] = n->data;
            if (n->left) queue[rear++] = n->left;
            if (n->right) queue[rear++] = n->right;
        }
        for (int i = 0; i < count; i++)
            printf("%d ", ltr ? vals[i] : vals[count-1-i]);
        ltr = !ltr;
    }
    printf("\n");
}

int main() {
    Node *root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);
    root->left->left = new_node(4);
    root->left->right = new_node(5);
    root->right->left = new_node(6);
    root->right->right = new_node(7);
    
    zigzag_traversal(root);
    return 0;
}
