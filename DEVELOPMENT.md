# Red-Black Tree Implementation in C

## Project Overview

This project implements a Red-Black Tree data structure in C with comprehensive testing using both traditional C test framework and Google Test (gtest).

## What is a Red-Black Tree?

A Red-Black Tree is a self-balancing binary search tree where each node has an extra bit for denoting the color of the node, either red or black. It satisfies the following properties:

1. **Color Property**: Every node is either red or black
2. **Root Property**: The root is always black
3. **Leaf Property**: Every leaf (NIL) is black
4. **Red Property**: If a node is red, both its children are black
5. **Black Height Property**: All paths from a node to its descendant leaves contain the same number of black nodes

These properties guarantee that the longest path from the root to any leaf is no more than twice the length of the shortest path, ensuring O(log n) time complexity for search, insert, and delete operations.

## Project Structure

```
rbtree/
├── rbtree.h              # Header file with type definitions and function declarations
├── rbtree.c              # Implementation of all Red-Black Tree operations
├── test_rbtree.c         # Traditional C test suite (16 tests)
├── test_rbtree_gtest.cpp # Google Test suite (15 tests)
├── Makefile              # Build configuration
└── googletest/           # Google Test framework
    ├── googletest/
    │   ├── include/gtest/ # Gtest headers
    │   └── src/           # Gtest source files
    └── build/
        └── libgtest.a    # Compiled gtest static library
```

## Core Data Structures

### Node Structure

```c
typedef enum { RED, BLACK } Color;

typedef struct rbtree_node {
    int key;                    // Key value
    Color color;                // Node color (RED or BLACK)
    struct rbtree_node *left;   // Left child
    struct rbtree_node *right;  // Right child
    struct rbtree_node *parent; // Parent node
} rbtree_node_t;
```

### Tree Structure

```c
typedef struct rbtree {
    rbtree_node_t *root;  // Root node
    rbtree_node_t *nil;   // Sentinel node for leaf nodes
} rbtree_t;
```

## API Reference

### Initialization and Cleanup

```c
void rbtree_init(rbtree_t *tree);
void rbtree_destroy(rbtree_t *tree);
```

- `rbtree_init`: Initializes an empty Red-Black Tree
- `rbtree_destroy`: Frees all memory used by the tree

### Insertion

```c
int rbtree_insert(rbtree_t *tree, int key);
```

- Returns: 0 on success, 1 if key already exists, -1 on error
- Time Complexity: O(log n)

### Deletion

```c
int rbtree_delete(rbtree_t *tree, int key);
```

- Returns: 0 on success, 1 if key not found
- Time Complexity: O(log n)

### Search

```c
rbtree_node_t* rbtree_search(rbtree_t *tree, int key);
```

- Returns: Pointer to node if found, nil node if not found
- Time Complexity: O(log n)

### Minimum and Maximum

```c
rbtree_node_t* rbtree_min(rbtree_t *tree);
rbtree_node_t* rbtree_max(rbtree_t *tree);
```

- Returns: Pointer to node with minimum/maximum key
- Time Complexity: O(log n)

### Traversals

```c
void rbtree_inorder(rbtree_t *tree, void (*callback)(rbtree_node_t*));
void rbtree_preorder(rbtree_t *tree, void (*callback)(rbtree_node_t*));
void rbtree_postorder(rbtree_t *tree, void (*callback)(rbtree_node_t*));
```

- `inorder`: Left → Root → Right (sorted order)
- `preorder`: Root → Left → Right
- `postorder`: Left → Right → Root

### Validation

```c
int rbtree_is_valid(rbtree_t *tree);
int rbtree_height(rbtree_t *tree);
int rbtree_black_height(rbtree_t *tree);
```

- `rbtree_is_valid`: Returns 1 if tree satisfies all Red-Black properties
- `rbtree_height`: Returns the height of the tree
- `rbtree_black_height`: Returns the black height of the tree

## Implementation Details

### Sentinel Node

The implementation uses a sentinel node (`nil`) instead of NULL pointers for leaf nodes. This simplifies the code by eliminating NULL checks and provides a consistent way to represent empty children.

### Rotation Operations

Two fundamental operations maintain tree balance:

1. **Left Rotation**: Rotates a node to the left, promoting its right child
2. **Right Rotation**: Rotates a node to the right, promoting its left child

### Insertion Algorithm

1. Perform standard BST insertion
2. Color the new node red
3. Fix Red-Black tree violations using `insert_fixup`

### Insertion Fixup

The fixup procedure handles three cases:
- **Case 1**: Uncle is red → Recolor parent, uncle, and grandparent
- **Case 2**: Uncle is black and new node is right child → Left rotation
- **Case 3**: Uncle is black and new node is left child → Right rotation

### Deletion Algorithm

1. Find the node to delete
2. Determine the replacement node
3. Transplant the node
4. Fix Red-Black tree violations using `delete_fixup`

### Deletion Fixup

The fixup procedure handles four cases:
- **Case 1**: Sibling is red
- **Case 2**: Sibling is black with two black children
- **Case 3**: Sibling is black with red left child and black right child
- **Case 4**: Sibling is black with red right child

## Testing

### Traditional C Tests (test_rbtree.c)

16 comprehensive tests covering:
- Tree initialization
- Single and multiple insertions
- Duplicate insertion handling
- Leaf, one-child, and two-children deletion
- Non-existent key deletion
- Search operations
- Minimum and maximum finding
- Inorder, preorder, and postorder traversals
- Red-Black property validation
- Property maintenance after deletions
- Empty tree operations
- Sequential insertions
- Stress test with 1000 random operations

### Google Test Suite (test_rbtree_gtest.cpp)

15 test cases using Google Test framework:
- Initialization
- InsertSingle
- InsertMultiple
- InsertDuplicate
- DeleteLeaf
- DeleteNodeWithOneChild
- DeleteNodeWithTwoChildren
- DeleteNonExistent
- Search
- MinMax
- EmptyTreeOperations
- RedBlackProperties
- PropertiesAfterDeletions
- SequentialInsertions
- StressTest

## Building and Running

### Prerequisites

- GCC compiler with C99 support
- G++ compiler with C++17 support (for gtest)
- GNU Make (optional)

### Compilation

```bash
# Build traditional test
gcc -Wall -Wextra -std=c99 -O2 -c rbtree.c -o rbtree.o
gcc -Wall -Wextra -std=c99 -O2 -c test_rbtree.c -o test_rbtree.o
gcc -Wall -Wextra -std=c99 -O2 -o rbtree_test rbtree.o test_rbtree.o

# Build gtest
cd googletest/build
g++ -std=c++17 -I../googletest/include -I../googletest -c ../googletest/src/gtest-all.cc -o gtest-all.o
g++ -std=c++17 -I../googletest/include -I../googletest -c ../googletest/src/gtest_main.cc -o gtest_main.o
ar -rv libgtest.a gtest-all.o gtest_main.o

# Build gtest test
g++ -std=c++17 -Igoogletest/googletest/include -c test_rbtree_gtest.cpp -o test_rbtree_gtest.o
g++ -std=c++17 -o test_rbtree_gtest test_rbtree_gtest.o rbtree.o googletest/build/libgtest.a -lpthread
```

### Running Tests

```bash
# Run traditional tests
./rbtree_test

# Run gtest
./test_rbtree_gtest
```

### Using Make (if available)

```bash
make          # Build both traditional and gtest tests
make test     # Run traditional tests
make test-gtest # Run gtest
make test-all # Run all tests
make clean    # Clean build files
```

## Performance Characteristics

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Search    | O(log n)       | O(1)             |
| Insert    | O(log n)       | O(1)             |
| Delete    | O(log n)       | O(1)             |
| Traversal | O(n)           | O(1)             |
| Minimum   | O(log n)       | O(1)             |
| Maximum   | O(log n)       | O(1)             |

## Memory Management

- Each node is allocated using `malloc`
- The tree maintains a sentinel node (`nil`) for leaf representation
- `rbtree_destroy` recursively frees all nodes
- No memory leaks are present (verified through testing)

## Error Handling

- Functions return specific error codes:
  - `0`: Success
  - `1`: Key already exists (insert) or not found (delete)
  - `-1`: Memory allocation error
- All functions handle NULL tree pointers gracefully
- Invalid operations on empty trees return appropriate sentinel values

## Testing Results

### Traditional C Tests

```
=== Red-Black Tree Tests ===

Test 1: Tree initialization                     PASSED
Test 2: Single insertion                        PASSED
Test 3: Multiple insertions                     PASSED
Test 4: Duplicate insertion                     PASSED
Test 5: Delete leaf node                        PASSED
Test 6: Delete node with one child              PASSED
Test 7: Delete node with two children           PASSED
Test 8: Delete non-existent key                 PASSED
Test 9: Search operations                       PASSED
Test 10: Min and Max operations                  PASSED
Test 11: Traversals (inorder, preorder, postorder) PASSED
Test 12: Red-black tree properties               PASSED
Test 13: Properties after deletions              PASSED
Test 14: Empty tree operations                   PASSED
Test 15: Sequential insertions                    PASSED
Test 16: Stress test (1000 random operations)    PASSED

=== Test Summary ===
Total tests: 16
Passed: 16
Failed: 0
All tests PASSED!
```

### Google Test Results

```
[==========] Running 15 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 15 tests from RBTreeTest
[ RUN      ] RBTreeTest.Initialization
[       OK ] RBTreeTest.Initialization (0 ms)
[ RUN      ] RBTreeTest.InsertSingle
[       OK ] RBTreeTest.InsertSingle (0 ms)
[ RUN      ] RBTreeTest.InsertMultiple
[       OK ] RBTreeTest.InsertMultiple (0 ms)
[ RUN      ] RBTreeTest.InsertDuplicate
[       OK ] RBTreeTest.InsertDuplicate (0 ms)
[ RUN      ] RBTreeTest.DeleteLeaf
[       OK ] RBTreeTest.DeleteLeaf (0 ms)
[ RUN      ] RBTreeTest.DeleteNodeWithOneChild
[       OK ] RBTreeTest.DeleteNodeWithOneChild (0 ms)
[ RUN      ] RBTreeTest.DeleteNodeWithTwoChildren
[       OK ] RBTreeTest.DeleteNodeWithTwoChildren (0 ms)
[ RUN      ] RBTreeTest.DeleteNonExistent
[       OK ] RBTreeTest.DeleteNonExistent (0 ms)
[ RUN      ] RBTreeTest.Search
[       OK ] RBTreeTest.Search (0 ms)
[ RUN      ] RBTreeTest.MinMax
[       OK ] RBTreeTest.MinMax (0 ms)
[ RUN      ] RBTreeTest.EmptyTreeOperations
[       OK ] RBTreeTest.EmptyTreeOperations (0 ms)
[ RUN      ] RBTreeTest.RedBlackProperties
[       OK ] RBTreeTest.RedBlackProperties (0 ms)
[ RUN      ] RBTreeTest.PropertiesAfterDeletions
[       OK ] RBTreeTest.PropertiesAfterDeletions (0 ms)
[ RUN      ] RBTreeTest.SequentialInsertions
[       OK ] RBTreeTest.SequentialInsertions (0 ms)
[ RUN      ] RBTreeTest.StressTest
[       OK ] RBTreeTest.StressTest (0 ms)
[----------] 15 tests from RBTreeTest (0 ms total)

[----------] Global test environment tear-down.
[==========] 15 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 15 tests.
```

## Conclusion

This implementation provides a complete, well-tested Red-Black Tree in C with both traditional and modern testing frameworks. The code follows best practices for C programming, including proper memory management, clear API design, and comprehensive testing.

The implementation is suitable for educational purposes and can be extended for production use with additional features like:
- Generic key types (void pointers)
- Iterator support
- Thread-safe operations
- Persistence