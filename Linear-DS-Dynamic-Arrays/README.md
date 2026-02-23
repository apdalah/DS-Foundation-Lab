# 📦 Linear-DS-Dynamic-Arrays

A dynamic array implementation built from scratch in C++ using templates.
This is a hands-on deep dive into how resizable arrays work under the hood — memory management, heap allocation, resizing strategy, and type-safe operations — without relying on `std::vector`.

---

## 🎯 What This Covers

- Manual heap memory management (`new`, `delete[]`)
- Automatic resizing (capacity doubling strategy)
- Deep copy via copy constructor and assignment operator
- Template programming with type-specific behavior using `if constexpr`
- Exception handling for out-of-bounds and empty-array cases
- Non-mutating operations that return new arrays (safe by design)

---

## 🧱 Class Overview

```cpp
template <typename T>
class DynamicArray
```

Works with any type. Type-specific methods (`max`, `min`) use `std::is_arithmetic` and `std::is_same` to branch behavior at compile time.

---

## ⚙️ Methods

### Insertion

| Method | Description | Time Complexity |
|---|---|---|
| `push(value)` | Insert at the front | O(n) |
| `pushBack(value)` | Append to the end | O(1) amortized |
| `insert(index, value)` | Insert at a specific index | O(n) |

### Removal

| Method | Description | Time Complexity |
|---|---|---|
| `pop()` | Remove the first element | O(n) |
| `popBack()` | Remove the last element | O(1) |
| `removeAt(index)` | Remove element at a specific index | O(n) |
| `clear()` | Reset array to initial empty state | O(1) |

### Access

| Method | Description | Time Complexity |
|---|---|---|
| `at(index)` | Safe access with bounds checking | O(1) |
| `operator[](index)` | Direct access without bounds checking | O(1) |

### Search

| Method | Description | Returns |
|---|---|---|
| `find(key)` | Index of first match | `int` — throws if not found |
| `findAll(key)` | Indices of all matches | `DynamicArray<int>` — empty if not found |

### Utility

| Method | Description |
|---|---|
| `size()` | Number of elements currently stored |
| `getCapacity()` | Total allocated space |
| `isEmpty()` | Returns true if array has no elements |
| `display()` | Prints array in format `[e1, e2, e3]` |

### Manipulation (Non-Mutating — originals unchanged)

| Method | Description | Works With |
|---|---|---|
| `sort()` | Returns new sorted copy (bubble sort) | Any type with `>` operator |
| `reverse()` | Returns new reversed copy | Any type |
| `merge(other)` | Returns new combined array | Any type |
| `max()` | Largest value / longest string | `arithmetic` or `string` |
| `min()` | Smallest value / shortest string | `arithmetic` or `string` |

---

## 💡 Design Decisions

**Non-mutating manipulation methods**
`sort()`, `reverse()`, and `merge()` all return a new `DynamicArray` instead of modifying the original. This means calling them never changes your data unexpectedly.

```cpp
DynamicArray<int> sorted = arr.sort();  // arr is untouched
```

**Type-aware methods with `if constexpr`**
`max()` and `min()` behave differently depending on `T`:
- Numeric types → compare by value
- `std::string` → compare by length

```cpp
DynamicArray<int>    nums;   nums.max();  // returns largest number
DynamicArray<string> words;  words.max(); // returns longest string
```

**Exceptions over magic values**
`find()` throws `std::out_of_range` instead of returning `-1`. This enforces that the caller handles the not-found case explicitly, and it works cleanly for any type `T` (not just `int`).

**`findAll()` returns empty instead of throwing**
Unlike `find()`, finding zero matches in `findAll()` is a valid result — not an error. An empty return is more natural than forcing the caller to use try/catch just to check existence.

---

## 🔨 Build & Run

```bash
g++ -std=c++17 -Wall -Wextra -o dynamic_array Linear-DS-Dynamic-Arrays.cpp
./dynamic_array
```

Requires C++17 for `if constexpr`.

---

## 📊 Complexity Summary

| Operation | Average | Worst Case |
|---|---|---|
| Access by index | O(1) | O(1) |
| Insert at end | O(1) amortized | O(n) on resize |
| Insert at front/middle | O(n) | O(n) |
| Remove at end | O(1) | O(1) |
| Remove at front/middle | O(n) | O(n) |
| Search (find) | O(n) | O(n) |
| Sort | O(n²) | O(n²) |
| Resize (internal) | O(n) | O(n) |

---

## 📁 Part of

[DS-Foundation-Lab](https://github.com/apdalah/DS-Foundation-Lab) — a repository for building data structures from scratch in C++.
