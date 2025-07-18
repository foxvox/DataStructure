
#include <iostream> 
using namespace std;

template <typename T>
class Vector
{
private:
    T* data = nullptr;
    int capacity = 0;
    int length = 0;

public:
    Vector() {}

    // �̵� ������
    Vector(Vector&& other) noexcept
    {
        data = other.data;
        capacity = other.capacity;
        length = other.length;

        // ���� ��ü�� �ʱ� ���·�
        other.data = nullptr;
        other.capacity = 0;
        other.length = 0;
    }

    // ���� ������
    Vector(const Vector& other)
    {
        capacity = other.capacity;
        length = other.length;
        data = new T[capacity];

        for (int i = 0; i < length; ++i)
        {
            data[i] = other.data[i];
        }
    }

    ~Vector()
    {
        delete[] data;
    }

    void resize(int new_capacity)
    {
        // new_capacity�� �ּ��� ���� length �̻��̾�� ��
        if (new_capacity < length)
            throw std::runtime_error("new_capacity must be >= length");

        T* new_data = new T[new_capacity];

        // ���� �Ҵ��� �޸� ������ �ʱ�ȭ         
        std::fill(new_data, new_data + new_capacity, T());

        for (int i = 0; i < length; ++i)
        {
            new_data[i] = data[i];
        }

        // data�� nullptr�� �ƴ� ��� 
        if (data)
        {
            delete[] data;
        }

        data = new_data;
        capacity = new_capacity;
    }

    void push_back(const T& value)
    {
        if (length >= capacity)
        {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        // length ���� ������ ��� ���� index�� ��Ÿ����. 
        // ������ ��� ���� ĭ�� ���� �����ϰ� length ���� ������Ų��. 
        data[length++] = value;
    }

    T pop_back()
    {
        if (length == 0)
            throw std::out_of_range("Vector is empty");

        // ������ ��Ҹ� ������ �ξ��ٰ�
        T value = data[length - 1];

        // length ����
        --length;

        // ��ȯ
        return value;
    }

    // �̵� ���� ������
    Vector& operator=(Vector&& other) noexcept
    {
        if (this == &other) return *this;

        delete[] data;

        data = other.data;
        capacity = other.capacity;
        length = other.length;

        other.data = nullptr;
        other.capacity = 0;
        other.length = 0;

        return *this;
    }

    // ���� ������
    Vector& operator=(const Vector& other)
    {
        if (this == &other) return *this; // �ڱ� �ڽ� ���� ����

        // ���� �ڿ� ����
        delete[] data;

        // ���� ����
        capacity = other.capacity;
        length = other.length;
        data = new T[capacity];

        for (int i = 0; i < length; ++i)
        {
            data[i] = other.data[i];
        }

        return *this;
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of bounds");

        return data[index];
    }

    int size() const
    {
        return length;
    }

    int get_capacity() const
    {
        return capacity;
    }
};


int main()
{
    Vector<int> vec;

    // �� 10�� �ֱ�
    for (int i = 1; i <= 10; ++i)
    {
        vec.push_back(i * 10);  // ��: 10, 20, ..., 100
    }

    cout << vec.pop_back() << endl;

    // ���
    cout << "Vector contents:\n";
    for (int i = 0; i < vec.size(); ++i)
    {
        cout << vec[i] << " ";
    }

    cout << "\nSize: " << vec.size() << endl;
    cout << "Capacity: " << vec.get_capacity() << endl;

    return 0;

}
