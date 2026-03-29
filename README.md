# Red-Black Tree Implementation in C

A complete Red-Black Tree implementation in C with comprehensive testing using Google Test.

## Features

- **Full Red-Black Tree Implementation**: Insert, delete, search, and traversal operations
- **Self-Balancing**: Maintains O(log n) time complexity for all operations
- **Comprehensive Testing**: 15 test cases using Google Test framework
- **Cross-Platform**: Works on Windows, Linux, and macOS
- **Well-Documented**: Complete API documentation and development guide

## Quick Start

### Prerequisites

- GCC compiler with C99 support
- G++ compiler with C++17 support (for gtest)
- GNU Make
- Google Test library (pre-compiled at `D:\app\googletest`)

### Build and Test

```bash
# Build the project
make all

# Run tests
make test

# Clean build files
make clean
```

## API Reference

### Core Functions

```c
// Initialize and destroy
void rbtree_init(rbtree_t *tree);
void rbtree_destroy(rbtree_t *tree);

// Operations
int rbtree_insert(rbtree_t *tree, int key);
int rbtree_delete(rbtree_t *tree, int key);
rbtree_node_t* rbtree_search(rbtree_t *tree, int key);

// Utilities
rbtree_node_t* rbtree_min(rbtree_t *tree);
rbtree_node_t* rbtree_max(rbtree_t *tree);
int rbtree_is_valid(rbtree_t *tree);
int rbtree_height(rbtree_t *tree);
```

## Project Structure

```
rbtree/
├── rbtree.h              # Header file
├── rbtree.c              # Implementation
├── test_rbtree_gtest.cpp # Test suite
├── Makefile              # Build configuration
├── DEVELOPMENT.md        # Detailed documentation
└── README.md             # This file
```

## Performance

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Search    | O(log n)       | O(1)             |
| Insert    | O(log n)       | O(1)             |
| Delete    | O(log n)       | O(1)             |
| Traversal | O(n)           | O(1)             |

## Testing

The project includes 15 comprehensive test cases covering:

- Tree initialization
- Insertion (single, multiple, duplicate)
- Deletion (leaf, one child, two children)
- Search operations
- Minimum/maximum finding
- Red-Black property validation
- Stress testing with 1000 random operations

## Documentation

For detailed documentation, see [DEVELOPMENT.md](DEVELOPMENT.md).

## License

This project is open source and available under the MIT License.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## GitHub Repository

https://github.com/felacebo/ai_rbtree