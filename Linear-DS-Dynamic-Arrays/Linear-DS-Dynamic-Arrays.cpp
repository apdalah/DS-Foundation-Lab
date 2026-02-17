#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class DynamicArray {
private:
    T* data;           // Pointer to heap-allocated array
    int capacity;      // Total allocated space
    int currentSize;   // Current number of elements

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
	    if (size == 0) return;

	    for (int i = 0; i < size - 1; i++)
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
};


int main() {

    DynamicArray<int> arr;

    // Test Push & push_back
    cout << "Pushing elements..." << endl;
    arr.push(10);
    arr.push(20);
    arr.pushBack(30);
    arr.pushBack(40);
    arr.pushBack(50);
    arr.pushBack(60);
    arr.pushBack(70);
    arr.display();

    // Test insert
    cout << "\nInserting 99 at index 2..." << endl;
    arr.insert(2, 99);
    arr.display();

    // Test removeAt
    cout << "\nRemoving element at index 3..." << endl;
    arr.removeAt(3);
    arr.display();

    // Test access
    cout << "\nElement at index 2: " << arr[2] << endl;

    // Test size and capacity
    cout << "\nSize: " << arr.size() << endl;
    cout << "Capacity: " << arr.getCapacity() << endl;

    return 0;
}