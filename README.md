# 🗂️ DS-Foundation-Lab

> Building every data structure from scratch in C++ — no STL shortcuts, no black boxes.

A comprehensive hands-on repository where every data structure is implemented manually to understand the internals: how memory is managed, why certain operations are fast or slow, and when to choose one structure over another.

**Language:** C++17 &nbsp;|&nbsp; **Compiler:** `g++ -std=c++17` &nbsp;|&nbsp; **Focus:** Implementation from Scratch

---

## 📌 Table of Contents

- [What Are Data Structures?](#-what-are-data-structures)
- [Repository Structure](#-repository-structure)
- [Linear Data Structures](#-linear-data-structures)
  - [Arrays](#1-arrays)
  - [Dynamic Arrays](#2-dynamic-arrays)
  - [Linked Lists](#3-linked-lists)
  - [Stacks](#4-stacks)
  - [Queues](#5-queues)
  - [Deques](#6-deques)
- [Non-Linear Data Structures](#-non-linear-data-structures)
  - [Trees](#7-trees)
  - [Hash Tables](#8-hash-tables)
  - [Graphs](#9-graphs)
- [Complexity Quick Reference](#-complexity-quick-reference)
- [Build & Run](#-build--run)
- [Philosophy](#-philosophy)
- [Related Projects](#-related-projects)

---

## 💡 What Are Data Structures?

A **data structure** is a way of organizing and storing data in memory so that it can be accessed and modified efficiently. Choosing the right data structure is one of the most important decisions in software — it directly impacts the speed and memory usage of your program.

Think of it this way:

> If your data is a collection of books, an **array** is a shelf where you can grab any book instantly by position. A **linked list** is a treasure hunt where each book points to the next. A **hash table** is a librarian who instantly tells you exactly which shelf to go to.

Every structure has tradeoffs. This repository explores each one by building it from the ground up.

---

## 📂 Repository Structure

```
DS-Foundation-Lab/
│
├── Linear-DS-Arrays/               # Static arrays — memory layout & operations
├── Linear-DS-Dynamic-Arrays/       # Resizable arrays built with templates
├── Linear-DS-Linked-Lists/         # Singly, Doubly, and Circular linked lists
├── Linear-DS-Stacks/               # LIFO structure — array & linked list based
├── Linear-DS-Queues/               # FIFO structure — simple, circular, priority
├── Linear-DS-Deques/               # Double-ended queue
│
├── Non-Linear-DS-Trees/            # Binary Tree, BST, AVL, Heap, Trie
├── Non-Linear-DS-Hash-Tables/      # Hash Tables, Hash Sets, Hash Maps
├── Non-Linear-DS-Graphs/           # Adjacency Matrix, List, Weighted Graphs
│
└── README.md
```

Each folder contains:
- Implementation file with full inline documentation
- Complexity analysis for every operation
- Test cases covering normal use, edge cases, and exceptions

---

## 🔷 Linear Data Structures

Linear structures store elements **sequentially** — each element has a previous and a next (except the first and last). They differ in how they store elements in memory and which operations they optimize.

---

### 1. Arrays

The most fundamental data structure. Elements are stored in **contiguous memory** — side by side — which gives them their signature O(1) access speed.

```
Memory:  [ 10 ][ 20 ][ 30 ][ 40 ][ 50 ]
Address:  1000   1004   1008   100C   1010
Index:      0      1      2      3      4
```

**Why O(1) access?** The CPU doesn't search for an element — it calculates the address directly:
```
address = base_address + (index × sizeof(element))
```

| Operation | Complexity | Why |
|---|---|---|
| Access by index | O(1) | Direct address calculation |
| Search (unsorted) | O(n) | Must scan each element |
| Insert at end | O(1) | No shifting needed |
| Insert at index | O(n) | Must shift elements right |
| Delete at end | O(1) | Just decrement size |
| Delete at index | O(n) | Must shift elements left |

**✅ Use when:** Size is fixed and known, fast random access is needed, sequential iteration matters.  
**❌ Avoid when:** Frequent insertions/deletions in the middle, or size is unpredictable.

---

### 2. Dynamic Arrays

A dynamic array behaves like a regular array but **grows automatically** when it runs out of space. Internally it allocates a larger block of memory, copies all elements, and frees the old block — a process called **resizing**.

```
Initial:    [ 10 ][ 20 ][ 30 ][ 40 ]         capacity = 4, size = 4

After push: [ 10 ][ 20 ][ 30 ][ 40 ][ 50 ][ __ ][ __ ][ __ ]
                                             capacity = 8, size = 5
```

**Capacity doubling strategy:** When full, capacity doubles. This means resize is rare — over many insertions, the average cost per insert is still **O(1) amortized**.

This implementation uses **C++ templates** (`template <typename T>`) so the array works with any type — `int`, `double`, `string`, or custom classes. Type-specific behavior (like `max()` and `min()`) is handled at compile time using `if constexpr`.

| Operation | Average | Worst Case |
|---|---|---|
| Access by index | O(1) | O(1) |
| Push back | O(1) amortized | O(n) on resize |
| Push front | O(n) | O(n) |
| Insert at index | O(n) | O(n) |
| Remove at index | O(n) | O(n) |
| Find | O(n) | O(n) |
| Sort (bubble) | O(n²) | O(n²) |

**Design principle:** Manipulation methods (`sort`, `reverse`, `merge`) are **non-mutating** — they return a new array and leave the original unchanged.

---

### 3. Linked Lists

A linked list stores elements in **nodes** scattered anywhere in memory. Each node holds a value and a pointer to the next node. There is no index, no contiguous memory — you navigate by following pointers.

```
Singly Linked:
[10 | •]──▶[20 | •]──▶[30 | •]──▶[40 | null]

Doubly Linked:
null◀─[• | 10 | •]⟷[• | 20 | •]⟷[• | 30 | •]──▶null

Circular:
[10 | •]──▶[20 | •]──▶[30 | •]──▶(back to 10)
```

**Three variants implemented:**

- **Singly Linked List** — each node points only forward. Simple, memory-efficient.
- **Doubly Linked List** — each node points both forward and backward. Enables O(1) deletion when you have the node.
- **Circular Linked List** — the last node points back to the first. Useful for round-robin scheduling and cyclic data.

| Operation | Array | Linked List |
|---|---|---|
| Access by index | O(1) ✅ | O(n) |
| Insert at front | O(n) | O(1) ✅ |
| Insert at end | O(1) | O(1) with tail pointer ✅ |
| Insert at middle | O(n) | O(n) |
| Delete (with pointer) | O(n) | O(1) ✅ |
| Memory layout | Contiguous | Scattered |

**✅ Use when:** Frequent insertions/deletions at the front or end, size changes frequently.  
**❌ Avoid when:** You need fast random access by index.

---

### 4. Stacks

A stack is a **LIFO** (Last In, First Out) structure. Think of a stack of plates — you can only add or remove from the top. The last plate placed is the first one taken.

```
Push 10 → Push 20 → Push 30

     [30]  ← top
     [20]
     [10]
     ────

Pop → returns 30
```

**Implemented two ways:**
- **Array-based** — fast, cache-friendly, fixed capacity.
- **Linked list-based** — dynamic size, grows as needed.

| Operation | Complexity |
|---|---|
| Push (add to top) | O(1) |
| Pop (remove from top) | O(1) |
| Peek (view top) | O(1) |
| Search | O(n) |

**Real-world uses:** Function call management (the call stack), undo/redo systems, expression parsing, backtracking algorithms (DFS).

---

### 5. Queues

A queue is a **FIFO** (First In, First Out) structure. Like a line at a store — the first person in is the first person served. New elements join at the back; elements leave from the front.

```
Enqueue 10 → Enqueue 20 → Enqueue 30

Front → [10][20][30] ← Back

Dequeue → returns 10
          [20][30]
```

**Variants implemented:**
- **Simple Queue** — basic FIFO, array or linked list backed.
- **Circular Queue** — reuses freed space at the front by wrapping around. Eliminates the "false full" problem of linear queues.
- **Priority Queue** — elements are dequeued by priority, not arrival order. Backed by a heap.

| Operation | Complexity |
|---|---|
| Enqueue (add to back) | O(1) |
| Dequeue (remove from front) | O(1) |
| Peek (view front) | O(1) |
| Search | O(n) |

**Real-world uses:** Task scheduling, print spoolers, BFS graph traversal, request handling in servers.

---

### 6. Deques

A **deque** (Double-Ended Queue) is a generalization of both stacks and queues. Elements can be added or removed from **either end** in O(1) time.

```
PushFront(5) → PushBack(10) → PushFront(1)

Front → [1][5][10] ← Back

PopFront → returns 1
PopBack  → returns 10
```

| Operation | Complexity |
|---|---|
| Push / Pop front | O(1) |
| Push / Pop back | O(1) |
| Access front / back | O(1) |
| Access middle | O(n) |

**Real-world uses:** Sliding window algorithms, browser history (back and forward), palindrome checking.

---

## 🔶 Non-Linear Data Structures

Non-linear structures organize data in **hierarchical or networked relationships** rather than a sequence. They are essential for representing real-world relationships like file systems, social networks, and maps.

---

### 7. Trees

A tree is a hierarchical structure where each element (called a **node**) has a parent and zero or more children. The topmost node is the **root**. Nodes with no children are **leaves**.

```
          [10]          ← root
         /    \
       [5]    [15]
      /   \      \
    [2]   [7]   [20]   ← leaves
```

**Variants implemented:**

**Binary Tree** — each node has at most 2 children (left and right). The foundation of all tree variants.

**Binary Search Tree (BST)** — a binary tree with one rule: every left child is smaller than the parent and every right child is larger. This makes search efficient — at each node, you eliminate half the remaining tree.

```
Search for 7:
Root 10 → go left  (7 < 10)
Node 5  → go right (7 > 5)
Node 7  → found! ✅   (3 steps, not 7)
```

**AVL Tree** — a self-balancing BST. After every insert or delete, it automatically **rotates** nodes to keep the tree balanced. This guarantees O(log n) worst case, unlike a regular BST which degrades to O(n) when data is inserted in sorted order.

**Heap (Min/Max)** — a complete binary tree where every parent is smaller (min-heap) or larger (max-heap) than its children. Used to always efficiently access the minimum or maximum element.

**Trie** — a tree optimized for string storage and prefix lookup. Each path from root to a node represents a prefix. Used in autocomplete, spell checkers, and IP routing.

| Structure | Search | Insert | Delete | Best For |
|---|---|---|---|---|
| Binary Tree | O(n) | O(n) | O(n) | Hierarchical data |
| BST (balanced) | O(log n) | O(log n) | O(log n) | Sorted dynamic data |
| AVL Tree | O(log n) | O(log n) | O(log n) | Guaranteed balance |
| Min/Max Heap | O(n) | O(log n) | O(log n) | Priority access |
| Trie | O(m) | O(m) | O(m) | String prefix search |

*m = length of the string*

---

### 8. Hash Tables

A hash table provides **near-instant** access to any element using a key. It uses a **hash function** to convert a key into an array index, then stores the value at that index.

```
key: "name"  →  hash("name") = 42  →  table[42] = "Abdullah"
key: "age"   →  hash("age")  = 17  →  table[17] = 21

Lookup "name":  hash("name") = 42  →  return table[42]   O(1) ✅
```

**The collision problem:** Two different keys can hash to the same index. Two strategies implemented:

- **Separate Chaining** — each slot holds a linked list of all keys that hashed there. Simple and handles high load factors well.
- **Open Addressing** — when a collision occurs, probe for the next available slot. More cache-friendly since everything stays in the array.

| Operation | Average | Worst Case |
|---|---|---|
| Insert | O(1) | O(n) |
| Search | O(1) | O(n) |
| Delete | O(1) | O(n) |

Worst case occurs when many keys collide. A good hash function and a proper **load factor** (ratio of elements to capacity) keep collisions rare and average case close to O(1).

**Real-world uses:** Database indexing, caching (key-value stores), symbol tables in compilers, counting frequencies.

---

### 9. Graphs

A graph is a collection of **nodes (vertices)** connected by **edges**. Unlike trees, graphs have no root and edges can form cycles, point in both directions, or carry weights (costs).

```
Undirected Graph:          Directed Graph:           Weighted Graph:
  A ── B                    A ──▶ B                   A ──5── B
  |    |                    ▲     |                   |       |
  C ── D                    |     ▼                   3       2
                             D ◀── C                   |       |
                                                       C ──8── D
```

**Two representation strategies implemented:**

- **Adjacency Matrix** — a 2D array where `matrix[i][j] = 1` if an edge exists between node i and j. O(1) edge lookup, but O(V²) memory even for sparse graphs.
- **Adjacency List** — each node stores a list of its neighbors. Memory-efficient for sparse graphs (most real-world graphs).

| Feature | Adjacency Matrix | Adjacency List |
|---|---|---|
| Space | O(V²) | O(V + E) |
| Check if edge exists | O(1) | O(degree) |
| Iterate all edges | O(V²) | O(V + E) |
| Best for | Dense graphs | Sparse graphs |

**Real-world uses:** Social networks (friendship connections), maps and navigation (weighted edges = distances), dependency resolution, network routing.

---

## 📊 Complexity Quick Reference

| Data Structure | Access | Search | Insert | Delete |
|---|---|---|---|---|
| Static Array | O(1) | O(n) | O(n) | O(n) |
| Dynamic Array | O(1) | O(n) | O(1)* | O(n) |
| Singly Linked List | O(n) | O(n) | O(1)** | O(1)** |
| Doubly Linked List | O(n) | O(n) | O(1)** | O(1)** |
| Stack | O(n) | O(n) | O(1) | O(1) |
| Queue | O(n) | O(n) | O(1) | O(1) |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) |
| AVL Tree | O(log n) | O(log n) | O(log n) | O(log n) |
| Heap | O(n) | O(n) | O(log n) | O(log n) |
| Hash Table | O(1) | O(1) | O(1) | O(1) |

*amortized &nbsp;|&nbsp; **at known position*

---

## 🔨 Build & Run

All implementations are single-file C++17 programs. Compile and run any file directly:

```bash
# Compile
g++ -std=c++17 -Wall -Wextra -o output filename.cpp

# Run
./output
```

---

## 📖 Philosophy

Every implementation in this repo follows these principles:

**No STL containers.** `std::vector`, `std::list`, `std::map` — none of these are used internally. Every node, pointer, and memory allocation is written by hand. The goal is to understand what those containers are doing, not just use them.

**Memory management by hand.** Every `new` has a matching `delete[]`. Copy constructors and assignment operators are implemented manually to ensure deep copies and prevent memory leaks.

**Complexity explained, not just stated.** Each method documents not just *what* the complexity is, but *why* — what causes the cost.

**Exceptions over silent failures.** When an operation is invalid (empty structure, out-of-bounds index), the code throws a descriptive exception rather than returning a magic value like `-1`.

**Non-mutating where it makes sense.** Operations like `sort()`, `reverse()`, and `merge()` return new structures rather than modifying the original. This prevents unexpected side effects.

---

## 🔗 Related Projects

- [Algorithms-Playground](https://github.com/apdalah/Algorithms-Playground) — sorting, searching, and graph algorithms built on top of these structures
- [Cpp-Evolution-Lab](https://github.com/apdalah/Cpp-Evolution-Lab) — C++ progression from procedural to production-ready OOP

---

> *"Bad programmers worry about the code. Good programmers worry about data structures and their relationships."*  
> — Linus Torvalds
