#include <iostream> 
using namespace std;

// ���ø� Node ����ü
template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(T value) : data(value), next(nullptr) {}
};

// ���ø� List Ŭ����
template <typename T>
class List
{
private:
    Node<T>* head = nullptr;
    int size = 0;

public:
    // ������
    List() {}
    // �Ҹ���
    ~List()
    {
        while (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // �տ� ��� �߰�
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

    // ����Ʈ ���� ��� �߰� 
    void push_back(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head != nullptr)
        {
            Node<T>* current = head;
            // current->next�� nullptr�̸� while �ٷ� ��� 
            // �� �� �� ���� �̵��ϴ� ����� 
            while (current->next != nullptr)
            {
                current = current->next;
            }
            // �� �� ����� ������ ���ο� ��带 �Ҵ��� 
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
        T ret = std::move(tmp->data);  // ���� ��� �̵� ����
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

    // ����Ʈ ���
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

    // ����Ʈ ũ�� ��ȯ
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
            next = curr->next;   // ���� ��� ��� 
            curr->next = prev;   // ��ũ ���� ������ 
            prev = curr;         // prev, curr �� ĭ�� �̵� 
            curr = next;
        }

        head = prev;
    }

    void remove(T value)
    {
        // 1) head���� �������� value�� ��ġ�ϴ� ��� ����
        while (head && head->data == value)
        {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;
            --size;
        }

        // 2) �߰� �� �� ��� ó��
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

    myList.print();  // ���: 30 -> 20 -> 10 -> nullptr 
    cout << "Size: " << myList.get_size() << endl;  // ���: Size: 3 
    cout << myList.empty() << endl;
    myList.reverse();

    myList.print();

    return 0;
}
