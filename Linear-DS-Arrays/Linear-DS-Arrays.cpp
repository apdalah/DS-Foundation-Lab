/**
* 
* Why Do Arrays Exist?
* Imagine you need to store 100 variables. You could create 100 individual variables.
* 
* int var1, var2, var3, ..., var100;  // Nightmare!
* 
* Arrays solve this by giving you:
*
* * Contiguous memory - all elements stored side-by-side in one block
* * Index-based access - access any element instantly using its position
* * Type safety - all elements must be the same type
* * Predictable memory layout - you know exactly where each element lives
* 
* Use Arrays When:
* ✅ You need fast random [[ access (O(1) ]] to get element at any index)
* ✅ You know the approximate size beforehand
* ✅ You're doing sequential processing (iterating through all elements)
* ✅ Memory locality matters (cache-friendly for performance)
* ✅ You need simple, straightforward code
* 
* Don't Use Arrays When:
* ❌ You need dynamic resizing (consider std::vector instead)
* ❌ You need to insert/delete elements frequently (arrays require shifting)
* ❌ You need to store different types of data (consider std::tuple or std::variant)
* ❌ Size changes dramatically and unpredictably
* 
* In summary, arrays are a fundamental data structure that provide efficient storage and access for homogeneous data. 
* They are ideal for scenarios where you need fast access and know the size in advance, 
* but they can be inflexible when it comes to resizing and managing dynamic data.
* 
* **MEMORY LAYOUT - HOW ARRAYS REALLY WORK IN MEMORY**
* 
*   int arr[5] = {10, 20, 30, 40, 50};
    
*   cout << "Array name (address of first element): " << arr << endl;
*   cout << "Address of arr[0]: " << &arr[0] << endl;
*   cout << "Address of arr[1]: " << &arr[1] << endl;
*   cout << "Address of arr[2]: " << &arr[2] << endl;
*    
*   // Output might look like:
*   // 0x7ffc8b4e7a40
*   // 0x7ffc8b4e7a40
*   // 0x7ffc8b4e7a44  (4 bytes later for int)
*   // 0x7ffc8b4e7a48  (4 bytes later again)
*
* **Memory Diagram:**
*
* Memory Address:  0x1000   0x1004   0x1008   0x100C   0x1010
*                    ↓        ↓        ↓        ↓        ↓
* Array:           [ 10  ] [ 20  ] [ 30  ] [ 40  ] [ 50  ]
* Index:             0        1        2        3        4
* 
*/

/**
* **OPERATIONS & COMPLEXITY ANALYSIS**
* 
* * * 1- Access (Read/Write): O(1) - Direct access to any index
* 
*   Why O(1) Access?
* *   - Direct memory address calculation, no loops needed.
* *   - Arrays are stored in contiguous memory, so the address of any element can be calculated directly:
* *       address_of_element = base_address + (index * size_of_element)
* *       = 0x1000 + (3 * 4) = 0x100C
* *       Then directly jumps to that address!
* 
* * * 2- Search (Linear) - O(n)
* *   - You have to go through loop -> means O(n).
* *   - If you need to find an element by value, you may have to check each element until you find it.
* *   - Worst case: must check all n elements. Best case: O(1) if found at index 0.
* 
* * * 3- Insertion/Deletion - O(n)
* *   - Why O(n)? Must shift up to n elements. [Shifting to right]
* *   - Inserting at the end is O(1), but worst case (inserting at index 0) requires shifting all elements.
* *   - See the implementation below for details on how shifting works during insertion.
* 
* * * 4- Delete - O(n)
*  - Why O(n)? Must shift up to n elements. [Shifting to left]
*  - Similar to insertion, deleting an element requires shifting elements to fill the gap, 
*  - which can take O(n) time in the worst case.
*  - See the implementation below for details on how shifting works during deletion.
* 
* 
*/

#include <iostream>
using namespace std;

// ***************  OPERATIONS & COMPLEXITY ANALYSIS  ****************

// 1- Access (Read/Write): O(1) - implementation
void demonstrateAccess() {
    int data[5] = { 100, 200, 300, 400, 500 };

    // Read - O(1)
    int value = data[2];  // Instant access to index 2
    cout << "Element at index 2: " << value << endl;  // 300

    // Write - O(1)
    data[2] = 999;  // Instant modification
    cout << "After modification: " << data[2] << endl;  // 999
}

// 2- Search for a value in unsorted array
int linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {  // Must check each element
        if (arr[i] == target) {
            return i;  // Found at index i
        }
    }
    return -1;  // Not found
}

// 3- Insert element at specific index
void insertAt(int arr[], int& size, int capacity, int index, int value) {
    // Check if array is full
    if (size >= capacity) {
        cout << "Array is full!" << endl;
        return;
    }

    // Check if index is valid
    // 
    // Index:  0     1    2    3    4   5
    // Array: [10] [20] [30] [40] [50] [ ]
    //         ↑                   ↑
    //      index 0            index 5 (= size)
    // 
    // **Valid insertion indices : 0, 1, 2, 3, 4, 5 * *
	//   - index = 0: Insert at beginning [number of shifts = size (shifting all elements)] **worst case**
    //   - index = 1, 2, 3, 4: Insert in middle [Number of shifts = size - index]
	//   - index = 5: Insert at end(after last element) [No shifts neded] **best case**
    
    if (index < 0 || index > size) {
        cout << "Invalid index!" << endl;
        return;
    }

    // Shift elements to the right
    // Index:             0    1    2    3   4
    // Array :          [10] [20] [30] [40] [50] [ ] [ ] [ ] [ ] [ ]
    //                             ↑
	//              Want to insert a value [99] here at index 2
    // 
    // After shifting:  [10] [20] [30] [30] [40] [50] [ ] [ ] [ ] [ ]
    // Then the result: [10] [20] [99] [30] [40] [50] [ ] [ ] [ ] [ ]

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert new element
    arr[index] = value;
    size++;
}

// 4- Delete element at specific index
void deleteAt(int arr[], int& size, int index) {

    // Check if index is valid
    if (index < 0 || index >= size) {
        cout << "Invalid index!" << endl;
        return;
    }

    
    // 
    // Explaination:
    // 
    // Index:           0    1    2    3    4    5
    // Array :         [10] [20] [30] [40] [50] [60]
    // size = 6                   ↑
    //                       Delete this (30)
    // Shift elements to the left
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    // After shifting: [10] [20] [40] [50] [60] [60]
    // Then we just decrease the size to ignore the last duplicate element:
    size--;
}

int main() {
    // Static array - size fixed at compile time
    int scores[5];  // Uninitialized (garbage values)

    int ages[10] = { 21, 25, 30, 19, 45 };  // Initialized [ Capacity 10, size 5 ]

    int temps[5] = { 32, 45 };  // Partially initialized
    // temps = {32, 45, 0, 0, 0}

    int numbers[] = { 10, 20, 30 };  // Size inferred (3 elements)

    // Access elements
    cout << ages[0] << endl;  // 21 (first element)
    cout << ages[4] << endl;  // 45 (last element)

    // Modify elements
    ages[2] = 31;

    // Get size (only works for static arrays in same scope)
    int size = sizeof(ages) / sizeof(ages[0]);  // 5

    return 0;
}