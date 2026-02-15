# 🗂️ DS-Foundation-Lab

A comprehensive practice repository for implementing data structures from scratch in C++. This lab is where theory meets practice through hands-on implementation.

## 🎯 Purpose

This repository is dedicated to **building data structures from the ground up**. No STL shortcuts - every structure is implemented manually to understand the internals, time/space complexity, and real-world applications.

## 📚 Data Structures Implemented

### **Linear Structures**
- ✅ **Arrays** - Static arrays, Dynamic arrays
- ✅ **Linked Lists** - Singly, Doubly, Circular
- ✅ **Stacks** - Array-based, Linked-list-based
- ✅ **Queues** - Simple, Circular, Priority, Deque

### **Non-Linear Structures**
- ✅ **Trees**
  - Binary Tree
  - Binary Search Tree (BST)
  - AVL Tree
  - Red-Black Tree
  - B-Tree
  - Trie
- ✅ **Heaps** - Min Heap, Max Heap
- ✅ **Graphs**
  - Adjacency Matrix
  - Adjacency List
  - Weighted Graphs

### **Hash-Based Structures**
- ✅ **Hash Tables** - Separate Chaining, Open Addressing
- ✅ **Hash Sets** - Custom implementation
- ✅ **Hash Maps** - Key-value storage

### **Advanced Structures**
- ✅ **Disjoint Set (Union-Find)**
- ✅ **Segment Tree**
- ✅ **Fenwick Tree (Binary Indexed Tree)**

## 📂 Repository Structure
```
DS-Foundation-Lab/
├── 01-Arrays/
│   ├── dynamic-array/
│   └── exercises/
├── 02-LinkedLists/
│   ├── singly-linked-list/
│   ├── doubly-linked-list/
│   ├── circular-linked-list/
│   └── problems/
├── 03-Stacks/
│   ├── array-stack/
│   ├── linked-stack/
│   └── applications/
├── 04-Queues/
│   ├── simple-queue/
│   ├── circular-queue/
│   ├── priority-queue/
│   └── deque/
├── 05-Trees/
│   ├── binary-tree/
│   ├── bst/
│   ├── avl-tree/
│   └── trie/
├── 06-Graphs/
│   ├── adjacency-matrix/
│   ├── adjacency-list/
│   └── graph-problems/
├── 07-HashTables/
│   ├── separate-chaining/
│   └── open-addressing/
├── 08-Heaps/
│   ├── min-heap/
│   └── max-heap/
└── README.md
```

## 🚀 Each Implementation Includes

- ✅ **Core Operations**: Insert, Delete, Search, Traverse
- ✅ **Time Complexity Analysis**: Big O for all operations
- ✅ **Space Complexity**: Memory usage breakdown
- ✅ **Test Cases**: Comprehensive testing
- ✅ **Use Cases**: Real-world applications
- ✅ **Common Problems**: LeetCode-style practice problems

## ✅ Implementation Progress

| Data Structure | Implementation      | Tests | Problems Solved |
|--------------------|-----------------|-------|-----------------|
| Dynamic Array      | ⏳ Not Started | ⏳    | 0/5             |
| Singly Linked List | ⏳ Not Started | ⏳    | 0/10            |
| Stack              | ⏳ Not Started | ⏳    | 0/8             |
| Queue              | ⏳ Not Started | ⏳    | 0/8             |
| Binary Tree        | ⏳ Not Started | ⏳    | 0/15            |
| BST                | ⏳ Not Started | ⏳    | 0/12            |
| Graph              | ⏳ Not Started | ⏳    | 0/20            |
| Hash Table         | ⏳ Not Started | ⏳    | 0/10            |
| Heap               | ⏳ Not Started | ⏳    | 0/8             |

## 🔨 Building & Testing
```bash
# Compile any implementation
g++ -std=c++17 -Wall -Wextra -o test implementation.cpp

# Run tests
./test
```

## 📊 Complexity Reference

Each implementation includes a complexity table:

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Insert    | O(?)            | O(?)             |
| Delete    | O(?)            | O(?)             |
| Search    | O(?)            | O(?)             |
| Access    | O(?)            | O(?)             |

## 🎓 Learning Path

**Recommended Order:**
1. Arrays → Linked Lists → Stacks → Queues (Linear structures)
2. Binary Trees → BST → AVL Trees (Tree basics to balanced trees)
3. Hash Tables (Understanding hashing)
4. Heaps (Priority-based structure)
5. Graphs (Complex relationships)
6. Advanced structures (Segment Tree, Disjoint Set)

## 🔗 Related Projects

- [Algorithms-Playground](https://github.com/apdalah/Algorithms-Playground) - Algorithms using these data structures
- [Cpp-Evolution-Lab](https://github.com/apdalah/Cpp-Evolution-Lab) - Main C++ project

## 📖 Practice Philosophy

**Build from Scratch**: Every data structure is implemented manually without using STL containers. This builds deep understanding of:
- Memory management
- Pointer manipulation
- Edge case handling
- Performance optimization

---

**Status**: 🔄 Active Development  
**Language**: C++  
**Focus**: Implementation from Scratch
