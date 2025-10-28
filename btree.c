#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
    int keys[2*T-1];
    struct BTreeNode *children[2*T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* create_node(int leaf) {
    BTreeNode *node = malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
        node->children[i] = NULL;
    return node;
}

void split_child(BTreeNode *parent, int i, BTreeNode *full) {
    BTreeNode *new_node = create_node(full->leaf);
    new_node->n = T - 1;
    
    for (int j = 0; j < T-1; j++)
        new_node->keys[j] = full->keys[j+T];
    
    if (!full->leaf) {
        for (int j = 0; j < T; j++)
            new_node->children[j] = full->children[j+T];
    }
    
    full->n = T - 1;
    
    for (int j = parent->n; j >= i+1; j--)
        parent->children[j+1] = parent->children[j];
    
    parent->children[i+1] = new_node;
    
    for (int j = parent->n-1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];
    
    parent->keys[i] = full->keys[T-1];
    parent->n++;
}

void insert_non_full(BTreeNode *node, int key) {
    int i = node->n - 1;
    
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        
        if (node->children[i]->n == 2*T-1) {
            split_child(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }
        insert_non_full(node->children[i], key);
    }
}

BTreeNode* insert(BTreeNode *root, int key) {
    if (!root) {
        root = create_node(1);
        root->keys[0] = key;
        root->n = 1;
        return root;
    }
    
    if (root->n == 2*T-1) {
        BTreeNode *new_root = create_node(0);
        new_root->children[0] = root;
        split_child(new_root, 0, root);
        insert_non_full(new_root, key);
        return new_root;
    } else {
        insert_non_full(root, key);
        return root;
    }
}

BTreeNode* search(BTreeNode *node, int key) {
    int i = 0;
    while (i < node->n && key > node->keys[i])
        i++;
    
    if (i < node->n && key == node->keys[i])
        return node;
    
    if (node->leaf)
        return NULL;
    
    return search(node->children[i], key);
}

void display(BTreeNode *node, int level) {
    if (node) {
        printf("Level %d: ", level);
        for (int i = 0; i < node->n; i++)
            printf("%d ", node->keys[i]);
        printf("\n");
        
        if (!node->leaf) {
            for (int i = 0; i <= node->n; i++)
                display(node->children[i], level+1);
        }
    }
}

int main() {
    BTreeNode *root = NULL;
    
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 30);
    root = insert(root, 7);
    root = insert(root, 17);
    
    printf("B-Tree:\n");
    display(root, 0);
    
    int key = 6;
    BTreeNode *result = search(root, key);
    printf("\nSearch %d: %s\n", key, result ? "Found" : "Not Found");
    
    return 0;
}
