#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "binary_linked_tree.h"

int compare_keys(KeyType key1, KeyType key2) {
    if (key1.input_cutlist->total_value < key2.input_cutlist->total_value) {
        return -1;
    } else if (key1.input_cutlist->total_value > key2.input_cutlist->total_value) {
        return 1;
    } else {
        return 0;
    }
}

int compare_values(ValueType value1, ValueType value2) {
    if (value1->total_value < value2->total_value) {
        return -1;
    } else if (value1->total_value > value2->total_value) {
        return 1;
    } else {
        return 0;
    }
}

int compare_nodes(Node* node1, Node* node2) {
    return compare_keys(node1->key, node2->key);
}

void insert_node_end(BinaryLinkedTree* tree, Node* new_node) {
    if (tree->tail == NULL) {
        tree->evic_head = tree->tail = new_node;
    } else {
        new_node->prev = tree->tail;
        tree->tail->next = new_node;
        tree->tail = new_node;
    }
}

void insert_node_front(BinaryLinkedTree* tree, Node* new_node) {
    if (tree->evic_head == NULL) {
        tree->evic_head = tree->tail = new_node;
    } else {
        new_node->next = tree->evic_head;
        tree->evic_head->prev = new_node;
        tree->evic_head = new_node;
    }
}

void move_node_front(BinaryLinkedTree* tree, Node* current) {
    if (current == tree->evic_head) {
        return;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    }

    if (current == tree->tail) {
        tree->tail = current->prev;
    }

    current->next = tree->evic_head;
    current->prev = NULL;
    if (tree->evic_head != NULL) {
        tree->evic_head->prev = current;
    }
    tree->evic_head = current;
}

Node* create_node(KeyType key, ValueType value) {
    Node* new_node  = (Node*)malloc(sizeof(Node));

    new_node->key   = key;
    new_node->value = value;
    new_node->count = 1;
    new_node->next  = NULL;
    new_node->prev  = NULL;
    new_node->left  = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}

Node* insert_bst(Node* root, Node* new_node) {
    if (root == NULL) {
        return new_node;
    }

    int cmp = compare_keys(new_node->key, root->key);
    if (cmp < 0) {
        root->left = insert_bst(root->left, new_node);
        root->left->parent = root;
    } else if (cmp > 0) {
        root->right = insert_bst(root->right, new_node);
        root->right->parent = root;
    } else {
        root->value = new_node->value;
        root->count++;
        free(new_node);
    }

    return root;
}

Node* search_bst(Node* root, KeyType key) {
    if (root == NULL) {
        return NULL;
    }

    int cmp = compare_keys(key, root->key);
    if (cmp < 0) {
        return search_bst(root->left, key);
    } else if (cmp > 0) {
        return search_bst(root->right, key);
    } else {
        return root;
    }
}

Node* find_min(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* delete_bst(Node* root, KeyType key) {
    if (root == NULL) {
        return root;
    }

    int cmp = compare_keys(key, root->key);
    if (cmp < 0) {
        root->left = delete_bst(root->left, key);
    } else if (cmp > 0) {
        root->right = delete_bst(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = find_min(root->right);

        root->key = temp->key;
        root->value = temp->value;
        root->count = temp->count;
        root->right = delete_bst(root->right, temp->key);
    }

    return root;
}