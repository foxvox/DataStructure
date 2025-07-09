#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;

    Node(T value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List {
private:
    int size = 0;
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

public:
    List() {}
    ~List() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_front(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
        ++size;
    }

    void push_back(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->prev = tail;
        if (tail) tail->next = newNode;
        tail = newNode;
        if (!head) head = newNode;
        ++size;
    }

    T pop_front() {
        if (!head) throw runtime_error("empty");
        Node<T>* temp = head;
        T ret = move(temp->data);
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        --size;
        return ret;
    }

    T pop_back() {
        if (!tail) throw runtime_error("empty");
        Node<T>* temp = tail;
        T ret = move(temp->data);
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        --size;
        return ret;
    }

    void print() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " <-> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    void reverse() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp) {
            temp = temp->prev;
            swap(head, tail);
        }
    }

    void remove(T value) {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                Node<T>* toDelete = current;
                if (current->prev) current->prev->next = current->next;
                else head = current->next;
                if (current->next) current->next->prev = current->prev;
                else tail = current->prev;
                current = current->next;
                delete toDelete;
                --size;
            }
            else {
                current = current->next;
            }
        }
    }

    bool empty() const {
        return size == 0;
    }

    int get_size() const {
        return size;
    }
};

int main() {
    List<int> myList;

    myList.push_front(10);
    myList.push_front(20);
    myList.push_back(55);
    myList.push_front(30);
    myList.pop_front();
    myList.push_back(77);
    myList.remove(55);

    myList.print();  // 출력: 20 <-> 10 <-> 77 <-> nullptr
    cout << "Size: " << myList.get_size() << endl;
    cout << "Empty: " << myList.empty() << endl;

    myList.reverse();
    myList.print();  // 출력: 77 <-> 10 <-> 20 <-> nullptr

    return 0;
}
