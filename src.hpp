#include <iostream>

// Only iostream and cstdio are allowed. We use iostream.

template <typename T>
class LinkedList {
private:
    struct Node {
        T val;
        Node* next;
        Node(const T& v) : val(v), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int n;

public:
    // Default constructor
    LinkedList() : head(nullptr), tail(nullptr), n(0) {}

    // Copy constructor (deep copy)
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), n(0) {
        Node* cur = other.head;
        while (cur) {
            pushBack(cur->val);
            cur = cur->next;
        }
    }

    // Destructor
    ~LinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        n = 0;
    }

    // Insert at front
    void pushFront(const T& val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
        if (!tail) tail = head;
        ++n;
    }

    // Insert at back
    void pushBack(const T& val) {
        Node* node = new Node(val);
        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        ++n;
    }

    // Remove from front; return removed value or default T() if empty
    T popFront() {
        if (!head) return T();
        Node* node = head;
        T ret = node->val;
        head = head->next;
        if (!head) tail = nullptr;
        delete node;
        --n;
        return ret;
    }

    // Remove from back; return removed value or default T() if empty
    T popBack() {
        if (!head) return T();
        if (head == tail) {
            T ret = head->val;
            delete head;
            head = tail = nullptr;
            --n;
            return ret;
        }
        Node* prev = head;
        while (prev->next != tail) prev = prev->next;
        T ret = tail->val;
        delete tail;
        tail = prev;
        tail->next = nullptr;
        --n;
        return ret;
    }

    int size() const { return n; }

    void print() const {
        Node* cur = head;
        bool first = true;
        while (cur) {
            if (!first) std::cout << ' ';
            std::cout << cur->val;
            first = false;
            cur = cur->next;
        }
        std::cout << '\n';
    }

    // Virtual interface; base versions won't be used in tests on LinkedList
    virtual const char* name() { return "LinkedList"; }
    virtual T peak() {
        if (!head) return T();
        return head->val;
    }
    virtual T pop() { return popFront(); }
    virtual void push(T val) { pushBack(val); }
};

// Stack: no member variables; operate via LinkedList interface

template <typename T>
class Stack : public LinkedList<T> {
public:
    const char* name() override { return "Stack"; }
    T peak() override {
        // Guaranteed non-empty when called
        T v = LinkedList<T>::popBack();
        LinkedList<T>::pushBack(v);
        return v;
    }
    T pop() override { return LinkedList<T>::popBack(); }
    void push(T val) override { LinkedList<T>::pushBack(val); }
};

// Queue: no member variables; operate via LinkedList interface

template <typename T>
class Queue : public LinkedList<T> {
public:
    const char* name() override { return "Queue"; }
    T peak() override {
        // Guaranteed non-empty when called
        T v = LinkedList<T>::popFront();
        LinkedList<T>::pushFront(v);
        return v;
    }
    T pop() override { return LinkedList<T>::popFront(); }
    void push(T val) override { LinkedList<T>::pushBack(val); }
};
