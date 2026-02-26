#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>

/**
* @brief A dynamic array implementation in C++.
* 
* This class mimics the behavior of std::vector but is built from scratch
* to demonstrate the underlying mechanics of a resizable array data structure.
* The DynamicArray class manages its own memory, allowing it to grow as elements
* are added. It provides methods for inserting, deleting, and accessing elements,
* as well as utility functions to check size, capacity, and display contents.
* The internal array is stored on the heap, and the class handles resizing when
* the number of elements exceeds the current capacity. This implementation is
* intended for educational purposes to illustrate how dynamic arrays work under the hood,
* and is not optimized for performance or feature-completeness like std::vector.
* 
* Note: This implementation does not seperate the logic from the container itself (Like std::vector) and is not designed for production use.
*       It focuses on clarity and educational value.
*
* @tparam T  The type of elements stored in the array.
*
* Example usage:
*   DynamicArray<int> arr;
*   arr.pushBack(10);
*   arr.pushBack(20);
*   arr.insert(1, 15); // arr now contains [10, 15, 20]
*/

class DynamicArray {
private:
    int capacity;      // Total allocated space
    int currentSize;   // Current number of elements
    T* data;           // Pointer to heap-allocated array

    /**
    * @brief Doubles the internal array capacity when the array is full.
    *
    * Allocates a new array with twice the current capacity, copies all
    * existing elements into it, frees the old memory, and redirects
    * the internal pointer to the new allocation.
    *
    * This is called automatically by insertion methods — never call it manually.
    *
    * Time Complexity  : O(n)
    * Space Complexity : O(n)
    */
    void resize() {
        capacity *= 2; 
        T* newData = new T[capacity];

        for (int i = 0; i < currentSize; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
    }

public:
    /**
     * @brief Constructs a new DynamicArray with a given initial capacity.
     *
     * Allocates an array on the heap with the specified capacity.
     * The array starts empty (currentSize = 0).
     *
     * @param initialCapacity  The number of elements to pre-allocate space for.
     *                         Defaults to 4 if not specified.
     *
     * Example:
     *   DynamicArray<int> arr;       // capacity = 5
     *   DynamicArray<int> arr(10);   // capacity = 10
     */
    DynamicArray(int initialCapacity = 5) {
        capacity = initialCapacity;
        currentSize = 0;
        data = new T[capacity];
    }

    /**
     * @brief Destructor — frees the heap-allocated array.
     *
     * Called automatically when the object goes out of scope.
     * Releases the memory allocated in the constructor or after any resize(),
     * preventing memory leaks.
     */
    ~DynamicArray() {
        delete[] data;
    }

    /**
     * @brief Copy constructor — creates a deep copy of another DynamicArray.
     *
     * Allocates a brand new array and copies all elements from the source.
     * This ensures both objects own completely separate memory and modifying
     * one won't affect the other (deep copy, not shallow copy).
     *
     * @param other  The DynamicArray to copy from.
     *
     * Example:
     *   DynamicArray<int> arr2 = arr1;  // triggers copy constructor
     */
    DynamicArray(const DynamicArray& other) {
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new T[capacity];

        for (int i = 0; i < currentSize; i++) {
            data[i] = other.data[i];
        }
    }

    /**
     * @brief Copy assignment operator — replaces this array's content with a deep copy.
     *
     * Frees the current array's memory, then allocates a new one and copies
     * all elements from the right-hand side object.
     * Includes a self-assignment guard to handle the case: arr = arr;
     *
     * @param other  The DynamicArray to copy from.
     * @return       A reference to this object (enables chaining: a = b = c).
     *
     * Example:
     *   arr1 = arr2;  // triggers copy assignment operator
     */
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) { 
            delete[] data; 

            capacity = other.capacity;
            currentSize = other.currentSize;
            data = new T[capacity];

            for (int i = 0; i < currentSize; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    /**
     * @brief Inserts an element at the beginning of the array.
     *
     * Shifts all existing elements one position to the right to make room
     * at index 0, then places the new element there.
     * Resizes the array first if it is at full capacity.
     *
     * @param value  The element to insert at the front.
     *
     * Time Complexity  : O(n) — due to shifting all elements right
     * Space Complexity : O(1) — O(n) only if resize is triggered
     *
     * Example:
     *   arr = [10, 20, 30]
     *   arr.push(5)  ->  [5, 10, 20, 30]
     */
    void push(const T& value)
    {
    	if (currentSize == capacity)
    		resize();

    	for (int i = currentSize - 1; i >= 0; i--)
    	{
    		data[i + 1] = data[i];
    	}

    	data[0] = value;

    	currentSize++;
    }

    /**
     * @brief Appends an element to the end of the array.
     *
     * Places the new element at the next available position after the last
     * element. Resizes the array first if it is at full capacity.
     *
     * @param value  The element to append.
     *
     * Time Complexity  : O(1) amortized — O(n) only when resize is triggered
     * Space Complexity : O(1)
     *
     * Example:
     *   arr = [10, 20, 30]
     *   arr.pushBack(40) ->  [10, 20, 30, 40]
     */
    void pushBack(const T& value) {
        if (currentSize == capacity) {
            resize();
        }
        data[currentSize++] = value;
    }
    
    /**
    * @brief Inserts an element at a specific index, shifting subsequent elements right.
    *
    * All elements from the given index onward are shifted one position to
    * the right before placing the new element at the target index.
    * Resizes the array first if it is at full capacity.
    *
    * @param index  The position at which to insert (0-based).
    *               Valid range: [0, currentSize]
    * @param value  The element to insert.
    *
    * @throws std::out_of_range  If index < 0 or index > currentSize.
    *
    * Time Complexity  : O(n) — due to shifting elements right
    * Space Complexity : O(1) — O(n) only if resize is triggered
    *
    * Example:
    *   arr = [10, 20, 30]
    *   arr.insert(1, 99)  ->  [10, 99, 20, 30]
    */
    void insert(int index, const T& value) {
        if (index < 0 || index > currentSize) {
            throw out_of_range("Index out of bounds");
        }

        if (currentSize == capacity) {
            resize();
        }

        for (int i = currentSize; i > index; i--) {
            data[i] = data[i - 1];
        }

        data[index] = value;
        currentSize++;
    }

    /**
     * @brief Removes the first element of the array.
     *
     * Shifts all remaining elements one position to the left to fill the gap
     * left by removing index 0, then decrements currentSize.
     * Does nothing if the array is empty.
     *
     * Time Complexity  : O(n) — due to shifting all elements left
     * Space Complexity : O(1)
     *
     * Example:
     *   arr = [10, 20, 30]
     *   arr.pop()  ->  [20, 30]
     */
    void pop()
    {
	    if (currentSize == 0) return;

	    for (int i = 0; i < currentSize - 1; i++)
		    data[i] = data[i + 1];

        currentSize--;
    }

    /**
     * @brief Removes the last element of the array.
     *
     * Simply decrements currentSize — no shifting needed.
     * The value at the old last index remains in memory but is
     * considered out of bounds and will be overwritten on the next insert.
     * Does nothing if the array is empty.
     *
     * Time Complexity  : O(1)
     * Space Complexity : O(1)
     *
     * Example:
     *   arr = [10, 20, 30]
     *   arr.popBack()  ->  [10, 20]
     */
    void popBack() {
        if (currentSize > 0) {
            currentSize--;
        }
    }

    /**
     * @brief Removes the element at a specific index, shifting subsequent elements left.
     *
     * All elements after the given index are shifted one position to the left
     * to fill the gap, then currentSize is decremented.
     *
     * @param index  The position of the element to remove (0-based).
     *               Valid range: [0, currentSize - 1]
     *
     * @throws std::out_of_range  If index < 0 or index >= currentSize.
     *
     * Time Complexity  : O(n) — due to shifting elements left
     * Space Complexity : O(1)
     *
     * Example:
     *   arr = [10, 20, 30, 40]
     *   arr.removeAt(1)  ->  [10, 30, 40]
     */
    void removeAt(int index) {
        if (index < 0 || index >= currentSize) {
            throw out_of_range("Index out of bounds");
        }

        for (int i = index; i < currentSize - 1; i++) {
            data[i] = data[i + 1];
        }

        currentSize--;
    }

    /**
     * @brief Returns a reference to the element at the given index, with bounds checking.
     *
     * Unlike operator[], this method validates the index before accessing memory.
     * Use this when you want a safe access that throws on invalid input.
     *
     * @param index  The position of the element to access (0-based).
     * @return       A reference to the element at the given index.
     *
     * @throws std::out_of_range  If index < 0 or index >= currentSize.
     *
     * Time Complexity  : O(1)
     *
     * Example:
     *   arr.at(2)  ->  returns reference to element at index 2
     */
    T& at(int index) {
        if (index < 0 || index >= currentSize) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    /**
     * @brief Overloads the [] operator for direct index access without bounds checking (like STL).
     *
     * Mimics the behavior of a raw array or std::vector's operator[].
     * Faster than at() since it skips validation, but accessing an
     * out-of-range index leads to undefined behavior.
     *
     * @param index  The position of the element to access (0-based).
     * @return       A reference to the element at the given index.
     *
     * Time Complexity  : O(1)
     *
     * Example:
     *   arr[2]  ->  returns reference to element at index 2
     */
    T& operator[](int index) {
        return data[index];
    }

    /**
     * @brief Resets the array to its initial empty state.
     *
     * Frees the currently allocated memory, resets currentSize to 0,
     * resets capacity back to the default (5), and allocates a fresh array.
     * After calling clear(), the object is in the same state as a newly constructed one.
     *
     * Time Complexity  : O(1)
     * Space Complexity : O(1)
     *
     * Example:
     *   arr = [10, 20, 30]
     *   arr.clear()  ->  arr is now []
     */
    void clear()
    {
        delete[] data;
        capacity = 5;
        currentSize = 0;
        data = new T[capacity];
    }

    /**
     * @brief Searches for the first occurrence of a value and returns its index.
     *
     * Performs a linear scan from index 0 and returns the index of the first
     * element that matches the given key.
     *
     * @param key  The value to search for.
     * @return     The index of the first matching element.
     *
     * @throws std::out_of_range  If the element is not found.
     *
     * Time Complexity  : O(n)
     * Space Complexity : O(1)
     *
     * Example:
     *   arr = [10, 20, 30]
     *   arr.find(20)  ->  returns 1
     *   arr.find(99)  ->  throws out_of_range
     */
    int find(const T& key) const
    {
        for (int i = 0; i < currentSize; i++)
        {
            if (data[i] == key)
                return i;
        }
        throw out_of_range("Element not found");
    }

    /**
    * @brief Returns the indices of ALL occurrences of a given value.
    *
    * Scans the entire array and collects the index of every element
    * that matches the key into a new DynamicArray<int>, which is returned.
    * Returns an empty array if no match is found.
    *
    * @param key  The value to search for.
    * @return     A DynamicArray<int> containing all matching indices.
    *
    * Time Complexity  : O(n)
    * Space Complexity : O(k) — where k is the number of matches
    *
    * Example:
    *   arr = [10, 20, 10, 30, 10]
    *   arr.findAll(10)  ->  returns [0, 2, 4]
    *   arr.findAll(99)  ->  returns []
    */
    DynamicArray<int> findAll(const T& key) const
    {
        DynamicArray<int> indices;

        for (int i = 0; i < currentSize; i++)
        {
            if (data[i] == key)
                indices.pushBack(i);
        }

        return indices;
    }

    /**
     * @brief Returns the current number of elements in the array.
     *
     * @return  The number of elements currently stored (not the capacity).
     *
     * Example:
     *   arr = [10, 20, 30]  ->  arr.size() returns 3
     */
    int size() const { return currentSize; }

    /**
     * @brief Returns the total allocated capacity of the internal array.
     *
     * Capacity is always >= size. When size reaches capacity, the array
     * automatically resizes and capacity doubles.
     *
     * @return  The total number of elements the array can hold before resizing.
     *
     * Example:
     *   arr = [10, 20, 30], capacity = 4  ->  arr.getCapacity() returns 4
     */
    int getCapacity() const { return capacity; }

    /**
     * @brief Checks whether the array has no elements.
     *
     * @return  true if currentSize == 0, false otherwise.
     *
     * Example:
     *   DynamicArray<int> arr;  ->  arr.isEmpty() returns true
     *   arr.pushBack(1);        ->  arr.isEmpty() returns false
     */
    bool isEmpty() const { return currentSize == 0; }

    /**
     * @brief Prints all elements in the array to standard output.
     *
     * Outputs elements in the format: [e1, e2, e3]
     * Prints [] if the array is empty.
     *
     * Time Complexity  : O(n)
     *
     * Example:
     *   arr = [10, 20, 30]  ->  prints "[10, 20, 30]"
     */
    void display() const {
        cout << "[";
        for (int i = 0; i < currentSize; i++) {
            cout << data[i];
            if (i < currentSize - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    /**
     * @brief Returns a new sorted copy of the array using bubble sort.
     *
     * Does not modify the original array. Creates a copy internally,
     * sorts it in ascending order, and returns it.
     *
     * For numeric types (int, float, double, etc.): sorts by value.
     * For strings: sorts lexicographically (alphabetical order).
     *
     * @return  A new DynamicArray containing all elements in sorted order.
     *
     * Time Complexity  : O(n^2) — bubble sort
     * Space Complexity : O(n)   — due to the copy
     *
     * Example:
     *   arr = [5, 3, 8, 1]
     *   arr.sort()  ->  returns [1, 3, 5, 8], original unchanged
     */
    DynamicArray sort() const
    {
		DynamicArray sorted(*this);

        for (int i = 0; i < currentSize - 1; i++)
        {
            for (int j = 0; j < currentSize - i - 1; j++)
            {
                if (sorted[j] > sorted[j + 1])
                {
					T temp = sorted[j];
					sorted[j] = sorted[j + 1];
					sorted[j + 1] = temp;
                }
            }
        }

        return sorted;
    }

    /**
     * @brief Returns a new array containing all elements of this array followed by all elements of another.
     *
     * Does not modify either original array. Creates a copy of this array
     * and appends every element from the other array to it.
     *
     * @param other  The array whose elements will be appended.
     * @return       A new DynamicArray with combined elements.
     *
     * Time Complexity  : O(n + m) — n = this size, m = other size
     * Space Complexity : O(n + m)
     *
     * Example:
     *   arr1 = [1, 2, 3]
     *   arr2 = [4, 5, 6]
     *   arr1.merge(arr2)  ->  returns [1, 2, 3, 4, 5, 6], both originals unchanged
     */
    DynamicArray merge(const DynamicArray& other) const
    {
		DynamicArray merged(*this);

        for (int i = 0; i < other.size(); i++)
        {
            merged.pushBack(other.data[i]);
        }
		return merged;
    }

    /**
     * @brief Returns a new array with all elements in reverse order.
     *
     * Does not modify the original array. Creates a copy and fills it
     * by reading the original from back to front.
     *
     * @return  A new DynamicArray with elements in reversed order.
     *
     * Time Complexity  : O(n)
     * Space Complexity : O(n) — due to the copy
     *
     * Example:
     *   arr = [1, 2, 3, 4]
     *   arr.reverse()  ->  returns [4, 3, 2, 1], original unchanged
     */
    DynamicArray reverse() const
    {
		DynamicArray reversed(*this);

        for(int i = 0; i < currentSize; i++)
        {
            reversed.data[i] = data[currentSize - i - 1];
		}

		return reversed;
    }

    /**
     * @brief Returns the maximum element in the array.
     *
     * Behavior depends on type T:
     * - Numeric types (int, float, double, etc.): returns the largest value.
     * - std::string: returns the longest string (by character count).
     *
     * @return  The maximum element of type T.
     *
     * @throws std::runtime_error  If the array is empty.
     *
     * Time Complexity  : O(n)
     * Space Complexity : O(1)
     *
     * Example (numeric):
     *   arr = [3, 7, 1, 9, 2]
     *   arr.max()  ->  returns 9
     *
     * Example (string):
     *   arr = ["hi", "hello", "hey"]
     *   arr.max()  ->  returns "hello"  (longest)
     */
    T max() const
    {
        if (isEmpty()) throw std::runtime_error("Array is empty");

        T maxValue = data[0];

        if constexpr (is_arithmetic<T>::value) 
        {
            for (int i = 1; i < currentSize; i++)
            {
                if(data[i] > maxValue)
					maxValue = data[i];
            }
        }
		else if constexpr (is_same<T, string>::value)
        {
            for (int i = 1; i < currentSize; i++)
            {
				if (data[i].length() > maxValue.length())
					maxValue = data[i];
            }
        }

        return maxValue;
    }

    /**
     * @brief Returns the minimum element in the array.
     *
     * Behavior depends on type T:
     * - Numeric types (int, float, double, etc.): returns the smallest value.
     * - std::string: returns the shortest string (by character count).
     *
     * @return  The minimum element of type T.
     *
     * @throws std::runtime_error  If the array is empty.
     *
     * Time Complexity  : O(n)
     * Space Complexity : O(1)
     *
     * Example (numeric):
     *   arr = [3, 7, 1, 9, 2]
     *   arr.min()  ->  returns 1
     *
     * Example (string):
     *   arr = ["hi", "hello", "hey"]
     *   arr.min()  ->  returns "hi"  (shortest)
     */
    T min() const
    {
        if (isEmpty()) throw std::runtime_error("Array is empty");

        T minValue = data[0];

        if constexpr (is_arithmetic<T>::value)
        {
            for (int i = 1; i < currentSize; i++)
            {
                if (data[i] < minValue)
                    minValue = data[i];
            }
        }
        else if constexpr (is_same<T, string>::value)
        {
            for (int i = 1; i < currentSize; i++)
            {
                if (data[i].length() < minValue.length())
                    minValue = data[i];
            }
        }

        return minValue;
    }


};


int main() {

    DynamicArray<int> arr;

    // ---------------------------------------------------------------
    // Test Push & pushBack
    // ---------------------------------------------------------------
    cout << "=== Push & PushBack ===" << endl;
    arr.push(10);
    arr.push(20);
    arr.pushBack(30);
    arr.pushBack(40);
    arr.pushBack(50);
    arr.pushBack(60);
    arr.pushBack(70);
    cout << "Expected : [20, 10, 30, 40, 50, 60, 70]" << endl;
    cout << "Result   : "; arr.display();

    // ---------------------------------------------------------------
    // Test insert
    // ---------------------------------------------------------------
    cout << "\n=== Insert ===" << endl;
    arr.insert(2, 99);
    cout << "Expected : [20, 10, 99, 30, 40, 50, 60, 70]" << endl;
    cout << "Result   : "; arr.display();

    // ---------------------------------------------------------------
    // Test removeAt
    // ---------------------------------------------------------------
    cout << "\n=== RemoveAt ===" << endl;
    arr.removeAt(3);
    cout << "Expected : [20, 10, 99, 40, 50, 60, 70]" << endl;
    cout << "Result   : "; arr.display();

    // ---------------------------------------------------------------
    // Test find
    // ---------------------------------------------------------------
    cout << "\n=== Find ===" << endl;
    cout << "Expected : index 2" << endl;
    cout << "Result   : index " << arr.find(99) << endl;

    try {
        arr.find(999);
    }
    catch (const out_of_range& e) {
        cout << "find(999) correctly threw: " << e.what() << endl;
    }

    // ---------------------------------------------------------------
    // Test findAll
    // ---------------------------------------------------------------
    cout << "\n=== FindAll ===" << endl;
    DynamicArray<int> arr2;
    arr2.pushBack(10);
    arr2.pushBack(20);
    arr2.pushBack(10);
    arr2.pushBack(30);
    arr2.pushBack(10);
    cout << "Array    : "; arr2.display();
    cout << "Expected : [0, 2, 4]" << endl;
    cout << "Result   : "; arr2.findAll(10).display();
    cout << "Expected : []" << endl;
    cout << "Result   : "; arr2.findAll(999).display();

    // ---------------------------------------------------------------
    // Test sort
    // ---------------------------------------------------------------
    cout << "\n=== Sort ===" << endl;
    DynamicArray<int> unsorted;
    unsorted.pushBack(5);
    unsorted.pushBack(3);
    unsorted.pushBack(8);
    unsorted.pushBack(1);
    unsorted.pushBack(4);
    cout << "Original : "; unsorted.display();
    cout << "Expected : [1, 3, 4, 5, 8]" << endl;
    cout << "Result   : "; unsorted.sort().display();
    cout << "Original unchanged: "; unsorted.display();

    // ---------------------------------------------------------------
    // Test merge
    // ---------------------------------------------------------------
    cout << "\n=== Merge ===" << endl;
    DynamicArray<int> a, b;
    a.pushBack(1); a.pushBack(2); a.pushBack(3);
    b.pushBack(4); b.pushBack(5); b.pushBack(6);
    cout << "a        : "; a.display();
    cout << "b        : "; b.display();
    cout << "Expected : [1, 2, 3, 4, 5, 6]" << endl;
    cout << "Result   : "; a.merge(b).display();
    cout << "a unchanged: "; a.display();

    // ---------------------------------------------------------------
    // Test reverse
    // ---------------------------------------------------------------
    cout << "\n=== Reverse ===" << endl;
    DynamicArray<int> toReverse;
    toReverse.pushBack(1);
    toReverse.pushBack(2);
    toReverse.pushBack(3);
    toReverse.pushBack(4);
    cout << "Original : "; toReverse.display();
    cout << "Expected : [4, 3, 2, 1]" << endl;
    cout << "Result   : "; toReverse.reverse().display();
    cout << "Original unchanged: "; toReverse.display();

    // ---------------------------------------------------------------
    // Test max & min (numeric)
    // ---------------------------------------------------------------
    cout << "\n=== Max & Min (int) ===" << endl;
    DynamicArray<int> nums;
    nums.pushBack(3); nums.pushBack(7); nums.pushBack(1); nums.pushBack(9); nums.pushBack(2);
    cout << "Array    : "; nums.display();
    cout << "Expected max : 9  |  Result : " << nums.max() << endl;
    cout << "Expected min : 1  |  Result : " << nums.min() << endl;

    // ---------------------------------------------------------------
    // Test max & min (string)
    // ---------------------------------------------------------------
    cout << "\n=== Max & Min (string) ===" << endl;
    DynamicArray<string> words;
    words.pushBack("hi");
    words.pushBack("hello");
    words.pushBack("hey");
    words.pushBack("howdy");
    cout << "Array    : "; words.display();
    cout << "Expected max (longest) : hello or howdy  |  Result : " << words.max() << endl;
    cout << "Expected min (shortest): hi              |  Result : " << words.min() << endl;

    // ---------------------------------------------------------------
    // Test clear
    // ---------------------------------------------------------------
    cout << "\n=== Clear ===" << endl;
    DynamicArray<int> toClear;
    toClear.pushBack(1); toClear.pushBack(2); toClear.pushBack(3);
    cout << "Before clear : "; toClear.display();
    toClear.clear();
    cout << "After clear  : "; toClear.display();
    cout << "isEmpty      : " << (toClear.isEmpty() ? "true" : "false") << endl;
    cout << "size         : " << toClear.size() << endl;

    // ---------------------------------------------------------------
    // Test size and capacity
    // ---------------------------------------------------------------
    cout << "\n=== Size & Capacity ===" << endl;
    cout << "Size     : " << arr.size() << endl;
    cout << "Capacity : " << arr.getCapacity() << endl;

    return 0;
}