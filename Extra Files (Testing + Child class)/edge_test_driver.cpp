#include <iostream>
#include "list342.h" 

using namespace std;

int main() {
    // Edge Case 1: Creating an empty list and printing it
    List342<int> list1;
    cout << "Test 1 - Initial empty list: " << endl;
    cout << list1 << endl; // Expected output: nothing or indication of an empty list

    // Edge Case 2: Inserting a single element
    list1.Insert(42);
    cout << "Test 2 - Inserted one element (42): " << endl;
    cout << list1 << endl; // Expected output: 42

    // Edge Case 3: Attempting to insert a duplicate element
    list1.Insert(42);
    cout << "Test 3 - Attempting to insert duplicate (42): " << endl;
    cout << list1 << endl; // Expected output: 42 (no change)

    // Edge Case 4: Inserting multiple unique elements
    list1.Insert(7);
    list1.Insert(19);
    list1.Insert(3);
    cout << "Test 4 - Inserted multiple elements (7, 19, 3): " << endl;
    cout << list1 << endl; // Expected output: 42 7 19 3 (order may vary based on implementation)

    // Edge Case 5: Merging with another list containing overlapping elements
    List342<int> list2;
    list2.Insert(19); // Overlapping element
    list2.Insert(8);
    list2.Insert(1);
    cout << "Test 5 - Second list before merge: " << endl;
    cout << list2 << endl; // Expected output: 19 8 1

    list1.Merge(list2);
    cout << "Test 5 - After merging lists (no duplicates): " << endl;
    cout << list1 << endl; // Expected output: 42 7 19 3 8 1 (order may vary)

    // Edge Case 6: Merging an empty list with a non-empty list
    List342<int> list3;
    list1.Merge(list3);
    cout << "Test 6 - After merging with an empty list: " << endl;
    cout << list1 << endl; // Expected output: 42 7 19 3 8 1 (no change)

    // Edge Case 7: Merging two empty lists
    list3.Merge(list2);
    cout << "Test 7 - Merging two empty lists: " << endl;
    cout << list3 << endl; // Expected output: nothing or indication of an empty list

    // Edge Case 8: Inserting elements in descending order (testing order behavior)
    List342<int> list4;
    list4.Insert(10);
    list4.Insert(5);
    list4.Insert(1);
    cout << "Test 8 - Inserted elements in descending order (10, 5, 1): " << endl;
    cout << list4 << endl; // Expected output: 10 5 1

    // Edge Case 9: Removing an element from the list
    int x;
    list4.Remove(5, x);
    cout << "Test 9 - Removed element (5): " << endl;
    cout << list4 << endl; // Expected output: 10 1

    // Edge Case 10: Attempting to remove an element not in the list
    int y;
    list4.Remove(42, y);
    cout << "Test 10 - Attempting to remove non-existent element (42): " << endl;
    cout << list4 << endl; // Expected output: 10 1 (no change)

    // Edge Case 11: Merging lists of different types (if supported by template)
    List342<double> list5;
    list5.Insert(3.14);
    list5.Insert(2.71);
    cout << "Test 11 - List of doubles: " << endl;
    cout << list5 << endl; // Expected output: 3.14 2.71
}
