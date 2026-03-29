#include "rbtree.h"
#include <assert.h>

// Helper function to create a new node
static rbtree_node_t* create_node(rbtree_t *tree, int key) {
    rbtree_node_t *node = (rbtree_node_t*)malloc(sizeof(rbtree_node_t));
    if (!node) return NULL;
    
    node->key = key;
    node->color = RED;
    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = tree->nil;
    
    return node;
}

// Left rotation
static void left_rotate(rbtree_t *tree, rbtree_node_t *x) {
    rbtree_node_t *y = x->right;
    x->right = y->left;
    
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

// Right rotation
static void right_rotate(rbtree_t *tree, rbtree_node_t *y) {
    rbtree_node_t *x = y->left;
    y->left = x->right;
    
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    
    x->parent = y->parent;
    
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    
    x->right = y;
    y->parent = x;
}

// Fix red-black tree properties after insertion
static void insert_fixup(rbtree_t *tree, rbtree_node_t *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rbtree_node_t *y = z->parent->parent->right;
            
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            rbtree_node_t *y = z->parent->parent->left;
            
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// Insert a node into the tree
static rbtree_node_t* insert_node(rbtree_t *tree, rbtree_node_t *z) {
    rbtree_node_t *y = tree->nil;
    rbtree_node_t *x = tree->root;
    
    while (x != tree->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else {
            // Key already exists
            return NULL;
        }
    }
    
    z->parent = y;
    
    if (y == tree->nil) {
        tree->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;
    
    insert_fixup(tree, z);
    
    return z;
}

// Find minimum node starting from a given node
static rbtree_node_t* tree_minimum(rbtree_t *tree, rbtree_node_t *x) {
    while (x->left != tree->nil) {
        x = x->left;
    }
    return x;
}

// Transplant one subtree with another
static void transplant(rbtree_t *tree, rbtree_node_t *u, rbtree_node_t *v) {
    if (u->parent == tree->nil) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Fix red-black tree properties after deletion
static void delete_fixup(rbtree_t *tree, rbtree_node_t *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            rbtree_node_t *w = x->parent->right;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            rbtree_node_t *w = x->parent->left;
            
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

// Delete a node from the tree
static rbtree_node_t* delete_node(rbtree_t *tree, rbtree_node_t *z) {
    rbtree_node_t *y = z;
    rbtree_node_t *x;
    Color y_original_color = y->color;
    
    if (z->left == tree->nil) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = tree_minimum(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        
        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    if (y_original_color == BLACK) {
        delete_fixup(tree, x);
    }
    
    return z;
}

// Initialize tree
void rbtree_init(rbtree_t *tree) {
    tree->nil = (rbtree_node_t*)malloc(sizeof(rbtree_node_t));
    tree->nil->color = BLACK;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->parent = tree->nil;
    tree->root = tree->nil;
}

// Destroy tree recursively
static void destroy_recursive(rbtree_t *tree, rbtree_node_t *node) {
    if (node != tree->nil) {
        destroy_recursive(tree, node->left);
        destroy_recursive(tree, node->right);
        free(node);
    }
}

// Destroy tree and free memory
void rbtree_destroy(rbtree_t *tree) {
    destroy_recursive(tree, tree->root);
    free(tree->nil);
}

// Insert a key
int rbtree_insert(rbtree_t *tree, int key) {
    rbtree_node_t *node = create_node(tree, key);
    if (!node) return -1;
    
    if (insert_node(tree, node) == NULL) {
        free(node);
        return 1;  // Key already exists
    }
    
    return 0;  // Success
}

// Delete a key
int rbtree_delete(rbtree_t *tree, int key) {
    rbtree_node_t *node = rbtree_search(tree, key);
    if (node == tree->nil) {
        return 1;  // Key not found
    }
    
    rbtree_node_t *deleted = delete_node(tree, node);
    free(deleted);
    
    return 0;  // Success
}

// Search for a key
rbtree_node_t* rbtree_search(rbtree_t *tree, int key) {
    rbtree_node_t *current = tree->root;
    
    while (current != tree->nil && current->key != key) {
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return current;
}

// Find minimum key
rbtree_node_t* rbtree_min(rbtree_t *tree) {
    if (tree->root == tree->nil) {
        return tree->nil;
    }
    return tree_minimum(tree, tree->root);
}

// Find maximum key
rbtree_node_t* rbtree_max(rbtree_t *tree) {
    rbtree_node_t *current = tree->root;
    
    if (current == tree->nil) {
        return tree->nil;
    }
    
    while (current->right != tree->nil) {
        current = current->right;
    }
    
    return current;
}

// In-order traversal helper
static void inorder_helper(rbtree_t *tree, rbtree_node_t *node, void (*callback)(rbtree_node_t*)) {
    if (node != tree->nil) {
        inorder_helper(tree, node->left, callback);
        callback(node);
        inorder_helper(tree, node->right, callback);
    }
}

// In-order traversal
void rbtree_inorder(rbtree_t *tree, void (*callback)(rbtree_node_t*)) {
    inorder_helper(tree, tree->root, callback);
}

// Pre-order traversal helper
static void preorder_helper(rbtree_t *tree, rbtree_node_t *node, void (*callback)(rbtree_node_t*)) {
    if (node != tree->nil) {
        callback(node);
        preorder_helper(tree, node->left, callback);
        preorder_helper(tree, node->right, callback);
    }
}

// Pre-order traversal
void rbtree_preorder(rbtree_t *tree, void (*callback)(rbtree_node_t*)) {
    preorder_helper(tree, tree->root, callback);
}

// Post-order traversal helper
static void postorder_helper(rbtree_t *tree, rbtree_node_t *node, void (*callback)(rbtree_node_t*)) {
    if (node != tree->nil) {
        postorder_helper(tree, node->left, callback);
        postorder_helper(tree, node->right, callback);
        callback(node);
    }
}

// Post-order traversal
void rbtree_postorder(rbtree_t *tree, void (*callback)(rbtree_node_t*)) {
    postorder_helper(tree, tree->root, callback);
}

// Check red-black tree properties
static int check_properties(rbtree_t *tree, rbtree_node_t *node, int *black_count, int current_black) {
    if (node == tree->nil) {
        if (*black_count == -1) {
            *black_count = current_black;
        } else if (*black_count != current_black) {
            return 0;  // Different black heights
        }
        return 1;
    }
    
    // Property 4: If a node is red, both children are black
    if (node->color == RED) {
        if (node->left->color == RED || node->right->color == RED) {
            return 0;
        }
    }
    
    int new_black = current_black + (node->color == BLACK ? 1 : 0);
    
    return check_properties(tree, node->left, black_count, new_black) &&
           check_properties(tree, node->right, black_count, new_black);
}

// Check if tree is valid red-black tree
int rbtree_is_valid(rbtree_t *tree) {
    if (tree->root == tree->nil) {
        return 1;
    }
    
    // Property 2: Root is black
    if (tree->root->color != BLACK) {
        return 0;
    }
    
    int black_count = -1;
    return check_properties(tree, tree->root, &black_count, 0);
}

// Calculate height
static int height_helper(rbtree_t *tree, rbtree_node_t *node) {
    if (node == tree->nil) {
        return 0;
    }
    
    int left_height = height_helper(tree, node->left);
    int right_height = height_helper(tree, node->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Get tree height
int rbtree_height(rbtree_t *tree) {
    return height_helper(tree, tree->root);
}

// Calculate black height
static int black_height_helper(rbtree_t *tree, rbtree_node_t *node) {
    if (node == tree->nil) {
        return 1;  // NIL nodes are black
    }
    
    int left_black = black_height_helper(tree, node->left);
    int right_black = black_height_helper(tree, node->right);
    
    if (left_black != right_black) {
        return -1;  // Invalid
    }
    
    return left_black + (node->color == BLACK ? 1 : 0);
}

// Get black height
int rbtree_black_height(rbtree_t *tree) {
    if (tree->root == tree->nil) {
        return 0;
    }
    return black_height_helper(tree, tree->root);
}