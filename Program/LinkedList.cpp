#include <iostream> 
using namespace std;

// 템플릿 Node 구조체
template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(T value) : data(value), next(nullptr) {}
};

// 템플릿 List 클래스
template <typename T>
class List
{
private:
    Node<T>* head = nullptr;
    int size = 0;

public:
    // 생성자
    List() {}
    // 소멸자
    ~List()
    {
        while (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 앞에 노드 추가
    void push_front(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head != nullptr)
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            head = newNode;
            newNode->next = nullptr;
        }
        size++;
    }

    bool empty()
    {
        bool temp = true;
        if (head != nullptr)
            temp = false;
        return temp;
    }

    // 리스트 끝에 노드 추가 
    void push_back(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head != nullptr)
        {
            Node<T>* current = head;
            // current->next가 nullptr이면 while 바로 벗어남 
            // 즉 맨 끝 노드로 이동하는 방법임 
            while (current->next != nullptr)
            {
                current = current->next;
            }
            // 맨 끝 노드의 다음에 새로운 노드를 할당함 
            current->next = newNode;
        }
        else
        {
            head = newNode;
        }

        size++;
    }

    // pop_front
    T pop_front()
    {
        if (!head) throw runtime_error("empty");
        Node<T>* tmp = head;
        T ret = std::move(tmp->data);  // 복사 대신 이동 가능
        head = head->next;
        delete tmp;
        --size;
        return ret;
    }

    // pop_back
    T pop_back() {
        if (!head) throw runtime_error("empty");
        if (!head->next) {
            T ret = std::move(head->data);
            delete head;
            head = nullptr;
            --size;
            return ret;
        }
        Node<T>* cur = head;
        while (cur->next->next) cur = cur->next;
        T ret = std::move(cur->next->data);
        delete cur->next;
        cur->next = nullptr;
        --size;
        return ret;
    }

    // 리스트 출력
    void print() const
    {
        Node<T>* current = head;
        while (current)
        {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // 리스트 크기 반환
    int get_size() const
    {
        return size;
    }

    void reverse()
    {
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        Node<T>* next = nullptr;

        while (curr)
        {
            next = curr->next;   // 다음 노드 백업 
            curr->next = prev;   // 링크 방향 뒤집기 
            prev = curr;         // prev, curr 한 칸씩 이동 
            curr = next;
        }

        head = prev;
    }

    void remove(T value)
    {
        // 1) head부터 연속으로 value와 일치하는 노드 삭제
        while (head && head->data == value)
        {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
            --size;
        }

        // 2) 중간 및 끝 노드 처리
        Node<T>* curr = head;
        while (curr && curr->next)
        {
            if (curr->next->data == value)
            {
                Node<T>* toDelete = curr->next;
                curr->next = curr->next->next;
                delete toDelete;
                --size;
            }
            else
            {
                curr = curr->next;
            }
        }
    }
};


int main()
{
    List<int> myList;

    myList.push_front(10);
    myList.push_front(20);
    myList.push_back(55);
    myList.push_front(30);
    myList.pop_front();
    myList.push_back(77);
    myList.remove(55);

    myList.print();  // 출력: 30 -> 20 -> 10 -> nullptr 
    cout << "Size: " << myList.get_size() << endl;  // 출력: Size: 3 
    cout << myList.empty() << endl;
    myList.reverse();

    myList.print();

    return 0;
}
