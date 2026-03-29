# AGENTS.md

This file provides guidelines for AI agents working in this repository.

## Project Overview

This repository contains a Red-Black Tree implementation. Red-Black Trees are self-balancing binary search trees with O(log n) time complexity for insertion, deletion, and lookup operations.

## Build & Test Commands

### Running Tests
```bash
# Run all tests (adjust based on your language/framework)
cargo test              # Rust
npm test                # Node.js
pytest                  # Python
go test ./...           # Go
make test               # C/C++

# Run a single test
cargo test test_name    # Rust
npm test -- --grep "test_name"  # Node.js
pytest test_file.py::test_name  # Python
go test -run TestName   # Go
make test TEST=test_name # C/C++
```

### Linting & Formatting
```bash
# Linting
cargo clippy            # Rust
npm run lint            # Node.js
flake8                  # Python
golint ./...            # Go

# Formatting
cargo fmt               # Rust
npm run format          # Node.js
black .                 # Python
gofmt -w .              # Go
```

### Building
```bash
cargo build --release   # Rust
npm run build           # Node.js
go build                # Go
make                    # C/C++
```

## Code Style Guidelines

### General Principles
- Write clean, readable, and maintainable code
- Follow language-specific conventions and idioms
- Keep functions small and focused (single responsibility)
- Use meaningful names that describe intent
- Add comments only when code isn't self-explanatory

### Naming Conventions
- **Variables**: Use descriptive names (e.g., `root_node`, `parent_pointer`)
- **Functions**: Use verb phrases (e.g., `insert_node`, `rotate_left`, `balance_tree`)
- **Constants**: Use UPPER_SNAKE_CASE
- **Types/Classes**: Use PascalCase (e.g., `RedBlackTree`, `TreeNode`)
- **Files**: Use snake_case or kebab-case based on language conventions

### Imports
- Group imports by category: standard library, external dependencies, internal modules
- Sort imports alphabetically within each group
- Remove unused imports
- Use absolute imports over relative imports when possible

### Error Handling
- Always handle edge cases (null/None pointers, empty trees)
- Return Result/Option types instead of using exceptions where appropriate
- Validate inputs at function boundaries
- Provide meaningful error messages

### Documentation
- Document public APIs with clear descriptions of parameters and return values
- Include examples for complex operations
- Document invariants (e.g., red-black tree properties)

### Testing
- Write unit tests for all public methods
- Include edge cases: empty tree, single node, rotations
- Test balance property maintenance after operations
- Use descriptive test names that explain the scenario

## Red-Black Tree Specific Rules

### Invariants to Maintain
1. Every node is either red or black
2. Root is always black
3. Every leaf (NIL) is black
4. If a node is red, both its children are black
5. All paths from a node to its descendant leaves contain the same number of black nodes

### Implementation Notes
- Always validate tree properties after modifications
- Handle edge cases: empty tree, root operations, sibling operations
- Use sentinel nodes for NIL values if appropriate
- Consider iterative vs recursive approaches based on performance needs

## Pull Request Guidelines
- Run all tests before submitting
- Include test coverage for new features
- Update documentation if adding public APIs
- Keep PRs focused on single concerns