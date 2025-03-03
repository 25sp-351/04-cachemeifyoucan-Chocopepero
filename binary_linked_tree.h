#ifndef BINARY_LINKED_TREE_H
#define BINARY_LINKED_TREE_H

#include "./loadable_cache/cache.h"

typedef struct Node {
    KeyType key;
    ValueType value;
    int count;
    struct Node* next;
    struct Node* prev;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct {
    int size;
    int capacity;
    Node* evic_head;
    Node* tail;
    Node* tree_root;
} BinaryLinkedTree;

void insert_node_end(BinaryLinkedTree* tree, Node* new_node);
void insert_node_front(BinaryLinkedTree* tree, Node* new_node);
void move_node_front(BinaryLinkedTree* tree, Node* current);
Node* create_node(KeyType key, ValueType value);
Node* insert_bst(Node* root, Node* new_node);
Node* search_bst(Node* root, KeyType key);
Node* find_min(Node* root);
Node* delete_bst(Node* root, KeyType key);

#endif
