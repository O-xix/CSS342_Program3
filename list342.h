#ifndef LIST342_H_
#define LIST342_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <class T>
struct Node {
    T *data;
    Node *next;
};

template <class T>
class List342 {
    public:
        //constructors
        List342();
        ~List342();
        List342(const List342& source);

        //action-verbs
        bool BuildList(string file_name);
        //bool Insert(T obj);
        bool Insert(T* obj);
        bool Remove(T target, T& result);
        bool Peek(T target, T& result);
        int Size() const;
        void DeleteList();
        bool Merge(List342& list1);

        //operators
        List342 operator+(List342 rhs);
        List342& operator+=(List342 rhs);   //remember to return reference
        template <class U> //need to add templatization here for the List342 rhs?
        friend ostream& operator<<(ostream& os, const List342<U>& rhs); //templatization here?
        bool operator==(const List342& rhs) const;
        bool operator!=(const List342& rhs) const;
        List342& operator=(const List342& rhs);

    private:
        Node<T>* head_; //need templatization here as well
};

template <class T>
List342<T>::List342() {
    head_ = nullptr;
}

template <class T>
List342<T>::List342(const List342& source) {
    head_ = nullptr;
    *this = source;
}

template <class T>
List342<T>::~List342() {
    DeleteList();
}

template <class T>
bool List342<T>::BuildList(string file_name) {
    ifstream f(file_name);
    if (!f.is_open()) {
        cerr << "Error opening the file: " << file_name << endl;
        return false;
    }

    T object;
    while (f >> object) {
        Insert(new T(object));
    }
    f.close();
    return true;
}

//Used for testing primitives
/*
template <class T>
bool List342<T>::Insert(T obj) {
    return Insert(&obj);
}
*/

template <class T>
bool List342<T>::Insert(T* obj) {
    if (obj == nullptr) {
        return false;
    }

    Node<T>* node_to_insert = new Node<T>();
    node_to_insert->data = new T(*obj);

    //if the list is empty
    if (head_ == nullptr) {
        node_to_insert->next = nullptr;
        head_ = node_to_insert;
        return true;
    }

    //special case for the head end
    if (*(node_to_insert->data) <= *(head_->data)) {
        if (*(node_to_insert->data) == *(head_->data)) {
            delete node_to_insert->data;  //cleanup
            delete node_to_insert;
            return false;
        }
        node_to_insert->next = head_;
        head_ = node_to_insert;
        return true;
    }

    //find the position to insert
    Node<T>* current = head_;
    while (current->next != nullptr && *(current->next->data) < *(node_to_insert->data)) {
        current = current->next;
    }

    //check for duplicates
    if (current->next != nullptr && *(current->next->data) == *(node_to_insert->data)) {
        delete node_to_insert->data;  //cleanup
        delete node_to_insert;
        return false;
    }

    node_to_insert->next = current->next;
    current->next = node_to_insert;
    return true;
}

template <class T>
bool List342<T>::Remove(T target, T& result) {
    if (head_ == nullptr) {
        return false;
    }

    Node<T>* current = head_;
    Node<T>* previous = nullptr;

    while (current != nullptr && *(current->data) != target) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    result = *(current->data);

    if (previous == nullptr) {  //removing the head node
        head_ = head_->next;
    } 
    else {
        previous->next = current->next;
    }

    delete current->data;
    delete current;

    return true;
}

template <class T>
bool List342<T>::Peek(T target, T& result) {
    Node<T>* current = head_;
    while (current != nullptr) {
        if (*(current->data) == target) {
            result = *(current->data);
            return true;
        }
        current = current->next;
    }
    return false;
}

template <class T>
int List342<T>::Size() const {
    int count = 0;
    Node<T>* current = head_;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

template <class T>
void List342<T>::DeleteList() {
    T dummy;
    while (head_ != nullptr) {
        Remove(*(head_->data), dummy);
    }
}


template <class T>
bool List342<T>::Merge(List342& list1) {
    if (this == &list1 || list1.head_ == nullptr) {
        return true;
    }

    //ff current list is empty, transfer contents of list1
    if (this->head_ == nullptr) {  
        this->head_ = list1.head_;
        list1.head_ = nullptr;
        return true;
    }

    //points to the last node of the merged list
    Node<T>* tail = nullptr; 
    Node<T>* current1 = this->head_;
    Node<T>* current2 = list1.head_;

    //initialize the head of the merged list and handle duplicates at the start
    if (*(current1->data) < *(current2->data)) {
        this->head_ = current1;
        current1 = current1->next;
    } else if (*(current2->data) < *(current1->data)) {
        this->head_ = current2;
        current2 = current2->next;
    } else { 
        this->head_ = current1;
        current1 = current1->next;
        Node<T>* temp = current2;
        current2 = current2->next;
        delete temp->data;
        delete temp;
    }
    tail = this->head_;

    //iterate through both lists and merge them, removing duplicates
    while (current1 != nullptr && current2 != nullptr) {
        if (*(current1->data) < *(current2->data)) {
            if (tail->data != current1->data) { 
                tail->next = current1;
                tail = tail->next;
            }
            current1 = current1->next;
        } else if (*(current2->data) < *(current1->data)) {
            if (tail->data != current2->data) { 
                tail->next = current2;
                tail = tail->next;
            }
            current2 = current2->next;
        } else { 
            if (tail->data != current1->data) { 
                tail->next = current1;
                tail = tail->next;
            }
            Node<T>* temp = current2;
            current2 = current2->next;
            current1 = current1->next;
            delete temp->data;
            delete temp;
        }
    }

    //attach remaining nodes from either list, avoiding duplicates
    while (current1 != nullptr) {
        if (tail->data != current1->data) {  
            tail->next = current1;
            tail = tail->next;
        }
        current1 = current1->next;
    }

    while (current2 != nullptr) {
        if (tail->data != current2->data) {  
            tail->next = current2;
            tail = tail->next;
        }
        current2 = current2->next;
    }

    tail->next = nullptr;  
    list1.head_ = nullptr; 

    return true;
}

template <class T>
List342<T> List342<T>::operator+(List342 rhs) {
    List342<T> newList(*this);
    newList.Merge(rhs);
    return newList;
}

template <class T>
List342<T>& List342<T>::operator+=(List342 rhs) {
    this->Merge(rhs);
    return *this;
}

template <class T>
ostream& operator<<(ostream& os, const List342<T>& rhs) {
    Node<T>* current = rhs.head_;
    while (current != nullptr) {
        os << *(current->data);
        current = current->next;
    }
    return os;
}

template <class T>
bool List342<T>::operator==(const List342& rhs) const {
    if (this->Size() != rhs.Size()) {
        return false;
    }

    Node<T>* current = head_;
    Node<T>* rhs_current = rhs.head_;
    while (current != nullptr && rhs_current != nullptr) {
        if (*(current->data) != *(rhs_current->data)) {
            return false;
        }
        current = current->next;
        rhs_current = rhs_current->next;
    }
    return true;
}

template <class T>
bool List342<T>::operator!=(const List342& rhs) const {
    return !(*this == rhs);
}

template <class T>
List342<T>& List342<T>::operator=(const List342& rhs) {
    if (this == &rhs) {
        return *this;
    }

    this->DeleteList();

    if (rhs.head_ == nullptr) {
        return *this;
    }

    Node<T>* d_node = new Node<T>();
    d_node->data = new T(*(rhs.head_->data));
    head_ = d_node;
    Node<T>* s_node = rhs.head_->next;

    while (s_node != nullptr) {
        d_node->next = new Node<T>();
        d_node = d_node->next;
        d_node->data = new T(*(s_node->data));
        s_node = s_node->next;
    }

    return *this;
}


#endif