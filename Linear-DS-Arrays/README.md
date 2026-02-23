# 📐 Linear-DS-Arrays

A foundational reference for understanding how static arrays work in C++ — memory layout, indexing mechanics, and core operations with full complexity analysis.

---

## 🎯 What This Covers

- How arrays are laid out in contiguous memory
- Why index access is O(1) (address calculation formula)
- Linear search, insertion with right-shifting, and deletion with left-shifting
- When to use arrays vs other data structures

---

## ⚙️ Operations

| Operation | Time Complexity | Why |
|---|---|---|
| Access by index | O(1) | Direct address calculation: `base + (index × size)` |
| Search (linear) | O(n) | May need to check every element |
| Insert at index | O(n) | Requires shifting elements right |
| Delete at index | O(n) | Requires shifting elements left |
| Insert at end | O(1) | No shifting needed |
| Delete at end | O(1) | Just decrement size |

---

## 🧠 Key Concept — Why O(1) Access?

Arrays store elements in contiguous memory. The CPU computes the address of any element directly:

```
address = base_address + (index × sizeof(T))
```

No loops, no searching — just a single calculation. That's what makes array access instant regardless of size.

---

## ✅ Use Arrays When

- You need fast random access (O(1))
- Size is known in advance
- Sequential processing / iteration
- Memory locality and cache performance matter

## ❌ Avoid Arrays When

- Size changes dynamically → use `std::vector`
- Frequent insertions/deletions in the middle → use a linked list
- Storing mixed types → use `std::tuple` or `std::variant`

---

## 🔨 Build & Run

```bash
g++ -std=c++17 -o arrays Linear-DS-Arrays.cpp
./arrays
```

---

## 📁 Part of

[DS-Foundation-Lab](https://github.com/apdalah/DS-Foundation-Lab) — a repository for building data structures from scratch in C++.
