#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct rbtree_node {
    int key;
    Color color;
    struct rbtree_node *left;
    struct rbtree_node *right;
    struct rbtree_node *parent;
} rbtree_node_t;

typedef struct rbtree {
    rbtree_node_t *root;
    rbtree_node_t *nil;  // Sentinel node for leaf nodes
} rbtree_t;

// Initialize tree
void rbtree_init(rbtree_t *tree);

// Destroy tree and free memory
void rbtree_destroy(rbtree_t *tree);

// Insert a key
int rbtree_insert(rbtree_t *tree, int key);

// Delete a key
int rbtree_delete(rbtree_t *tree, int key);

// Search for a key
rbtree_node_t* rbtree_search(rbtree_t *tree, int key);

// Find minimum key
rbtree_node_t* rbtree_min(rbtree_t *tree);

// Find maximum key
rbtree_node_t* rbtree_max(rbtree_t *tree);

// In-order traversal
void rbtree_inorder(rbtree_t *tree, void (*callback)(rbtree_node_t*));

// Pre-order traversal
void rbtree_preorder(rbtree_t *tree, void (*callback)(rbtree_node_t*));

// Post-order traversal
void rbtree_postorder(rbtree_t *tree, void (*callback)(rbtree_node_t*));

// Check if tree is valid red-black tree
int rbtree_is_valid(rbtree_t *tree);

// Get tree height
int rbtree_height(rbtree_t *tree);

// Get black height
int rbtree_black_height(rbtree_t *tree);

#endif // RBTREE_H