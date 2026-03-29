#include <gtest/gtest.h>

extern "C" {
#include "rbtree.h"
}

class RBTreeTest : public ::testing::Test {
protected:
    rbtree_t tree;
    
    void SetUp() override {
        rbtree_init(&tree);
    }
    
    void TearDown() override {
        rbtree_destroy(&tree);
    }
};

TEST_F(RBTreeTest, Initialization) {
    EXPECT_EQ(tree.root, tree.nil);
    EXPECT_EQ(tree.nil->color, BLACK);
}

TEST_F(RBTreeTest, InsertSingle) {
    EXPECT_EQ(rbtree_insert(&tree, 10), 0);
    rbtree_node_t *node = rbtree_search(&tree, 10);
    EXPECT_NE(node, tree.nil);
    EXPECT_EQ(node->key, 10);
}

TEST_F(RBTreeTest, InsertMultiple) {
    int keys[] = {10, 20, 30, 15, 25, 5, 1};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(rbtree_insert(&tree, keys[i]), 0);
    }
    
    for (int i = 0; i < n; i++) {
        rbtree_node_t *node = rbtree_search(&tree, keys[i]);
        EXPECT_NE(node, tree.nil);
        EXPECT_EQ(node->key, keys[i]);
    }
}

TEST_F(RBTreeTest, InsertDuplicate) {
    rbtree_insert(&tree, 10);
    EXPECT_EQ(rbtree_insert(&tree, 10), 1);
}

TEST_F(RBTreeTest, DeleteLeaf) {
    rbtree_insert(&tree, 10);
    rbtree_insert(&tree, 5);
    rbtree_insert(&tree, 15);
    
    EXPECT_EQ(rbtree_delete(&tree, 5), 0);
    EXPECT_EQ(rbtree_search(&tree, 5), tree.nil);
}

TEST_F(RBTreeTest, DeleteNodeWithOneChild) {
    rbtree_insert(&tree, 10);
    rbtree_insert(&tree, 5);
    rbtree_insert(&tree, 3);
    
    EXPECT_EQ(rbtree_delete(&tree, 5), 0);
    EXPECT_EQ(rbtree_search(&tree, 5), tree.nil);
    EXPECT_NE(rbtree_search(&tree, 3), tree.nil);
}

TEST_F(RBTreeTest, DeleteNodeWithTwoChildren) {
    rbtree_insert(&tree, 10);
    rbtree_insert(&tree, 5);
    rbtree_insert(&tree, 15);
    rbtree_insert(&tree, 12);
    rbtree_insert(&tree, 20);
    
    EXPECT_EQ(rbtree_delete(&tree, 15), 0);
    EXPECT_EQ(rbtree_search(&tree, 15), tree.nil);
    EXPECT_NE(rbtree_search(&tree, 12), tree.nil);
    EXPECT_NE(rbtree_search(&tree, 20), tree.nil);
}

TEST_F(RBTreeTest, DeleteNonExistent) {
    rbtree_insert(&tree, 10);
    EXPECT_EQ(rbtree_delete(&tree, 20), 1);
}

TEST_F(RBTreeTest, Search) {
    rbtree_insert(&tree, 10);
    rbtree_insert(&tree, 5);
    rbtree_insert(&tree, 15);
    rbtree_insert(&tree, 3);
    rbtree_insert(&tree, 7);
    
    EXPECT_EQ(rbtree_search(&tree, 10)->key, 10);
    EXPECT_EQ(rbtree_search(&tree, 5)->key, 5);
    EXPECT_EQ(rbtree_search(&tree, 15)->key, 15);
    EXPECT_EQ(rbtree_search(&tree, 3)->key, 3);
    EXPECT_EQ(rbtree_search(&tree, 7)->key, 7);
    EXPECT_EQ(rbtree_search(&tree, 20), tree.nil);
}

TEST_F(RBTreeTest, MinMax) {
    rbtree_insert(&tree, 10);
    rbtree_insert(&tree, 5);
    rbtree_insert(&tree, 15);
    rbtree_insert(&tree, 3);
    rbtree_insert(&tree, 7);
    rbtree_insert(&tree, 20);
    
    EXPECT_EQ(rbtree_min(&tree)->key, 3);
    EXPECT_EQ(rbtree_max(&tree)->key, 20);
}

TEST_F(RBTreeTest, EmptyTreeOperations) {
    EXPECT_EQ(rbtree_min(&tree), tree.nil);
    EXPECT_EQ(rbtree_max(&tree), tree.nil);
    EXPECT_EQ(rbtree_search(&tree, 10), tree.nil);
    EXPECT_EQ(rbtree_height(&tree), 0);
    EXPECT_EQ(rbtree_black_height(&tree), 0);
    EXPECT_TRUE(rbtree_is_valid(&tree));
}

TEST_F(RBTreeTest, RedBlackProperties) {
    int keys[] = {10, 20, 30, 15, 25, 5, 1, 50, 40, 60};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        rbtree_insert(&tree, keys[i]);
    }
    
    EXPECT_TRUE(rbtree_is_valid(&tree));
    EXPECT_GT(rbtree_black_height(&tree), 0);
}

TEST_F(RBTreeTest, PropertiesAfterDeletions) {
    int keys[] = {10, 20, 30, 15, 25, 5, 1, 50, 40, 60};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        rbtree_insert(&tree, keys[i]);
    }
    
    rbtree_delete(&tree, 10);
    rbtree_delete(&tree, 30);
    rbtree_delete(&tree, 5);
    
    EXPECT_TRUE(rbtree_is_valid(&tree));
    EXPECT_GT(rbtree_black_height(&tree), 0);
}

TEST_F(RBTreeTest, SequentialInsertions) {
    int n = 100;
    for (int i = 0; i < n; i++) {
        rbtree_insert(&tree, i);
    }
    
    EXPECT_TRUE(rbtree_is_valid(&tree));
    EXPECT_GT(rbtree_black_height(&tree), 0);
}

TEST_F(RBTreeTest, StressTest) {
    srand(42);
    int operations = 1000;
    
    for (int i = 0; i < operations; i++) {
        int op = rand() % 2;
        int key = rand() % 1000;
        
        if (op == 0) {
            rbtree_insert(&tree, key);
        } else {
            rbtree_delete(&tree, key);
        }
        
        if (i % 100 == 99) {
            EXPECT_TRUE(rbtree_is_valid(&tree)) << "Violation at operation " << i + 1;
        }
    }
    
    EXPECT_TRUE(rbtree_is_valid(&tree));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}