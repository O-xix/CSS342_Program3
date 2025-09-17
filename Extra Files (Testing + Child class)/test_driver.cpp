#include "list342.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void testInsert() {
    List342<int> list;
    assert(list.Insert(10) == true);
    assert(list.Insert(5) == true);
    assert(list.Insert(15) == true);
    assert(list.Insert(5) == false); // Duplicate, should return false
    cout << "Insert test passed!" << endl;
}

void testRemove() {
    List342<int> list;
    list.Insert(10);
    list.Insert(20);
    list.Insert(30);
    
    int removedValue;
    assert(list.Remove(20, removedValue) == true);
    assert(removedValue == 20);
    assert(list.Remove(100, removedValue) == false); // Element not present
    assert(list.Size() == 2);
    cout << "Remove test passed!" << endl;
}

void testPeek() {
    List342<string> list;
    list.Insert("apple");
    list.Insert("banana");
    list.Insert("cherry");

    string result;
    assert(list.Peek("banana", result) == true);
    assert(result == "banana");
    assert(list.Peek("mango", result) == false); // Element not present
    cout << "Peek test passed!" << endl;
}

void testSize() {
    List342<char> list;
    assert(list.Size() == 0);
    list.Insert('A');
    list.Insert('B');
    assert(list.Size() == 2);
    list.Insert('A'); // Duplicate, should not increase size
    assert(list.Size() == 2);
    cout << "Size test passed!" << endl;
}

void testMerge() {
    List342<int> list1;
    List342<int> list2;

    list1.Insert(1);
    list1.Insert(3);
    list1.Insert(5);

    list2.Insert(2);
    list2.Insert(4);
    list2.Insert(6);

    list1.Merge(list2);
    assert(list1.Size() == 6);
    assert(list2.Size() == 0);
    cout << "Merge test passed!" << endl;
}

void testOperatorPlus() {
    List342<int> list1;
    List342<int> list2;

    list1.Insert(1);
    list1.Insert(3);
    list1.Insert(5);

    list2.Insert(2);
    list2.Insert(4);
    list2.Insert(6);

    List342<int> list3 = list1 + list2;
    assert(list3.Size() == 6);
    assert(list1.Size() == 3);
    assert(list2.Size() == 3);
    cout << "Operator+ test passed!" << endl;
}

void testOperatorEquals() {
    List342<int> list1;
    List342<int> list2;

    list1.Insert(1);
    list1.Insert(2);
    list1.Insert(3);

    list2.Insert(1);
    list2.Insert(2);
    list2.Insert(3);

    assert(list1 == list2);
    list2.Insert(4);
    assert(list1 != list2);
    cout << "Equality operators test passed!" << endl;
}

void testAssignmentOperator() {
    List342<int> list1;
    list1.Insert(10);
    list1.Insert(20);

    List342<int> list2 = list1; // Test copy constructor
    assert(list1 == list2);

    List342<int> list3;
    list3.Insert(30);
    list3 = list1; // Test assignment operator
    assert(list1 == list3);
    cout << "Assignment operator test passed!" << endl;
}

int main() {
    testInsert();
    testRemove();
    testPeek();
    testSize();
    testMerge();
    testOperatorPlus();
    testOperatorEquals();
    testAssignmentOperator();
    cout << "All tests passed successfully!" << endl;
    return 0;
}
