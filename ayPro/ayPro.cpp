
#include <iostream> 
using namespace std; 

template <typename T>
class Vector 
{
private:
    T*  data = nullptr;
    int capacity = 0;
    int length = 0;

public: 
    Vector() {} 

    // 이동 생성자
    Vector(Vector&& other) noexcept
    {
        data = other.data;
        capacity = other.capacity;
        length = other.length;

        // 원본 객체를 초기 상태로
        other.data = nullptr;
        other.capacity = 0;
        other.length = 0;
    }

    // 복사 생성자
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
        // new_capacity는 최소한 현재 length 이상이어야 함
        if (new_capacity < length)
            throw std::runtime_error("new_capacity must be >= length");

        T* new_data = new T[new_capacity];

        // 새로 할당한 메모리 공간을 초기화         
        std::fill(new_data, new_data + new_capacity, T());

        for (int i = 0; i < length; ++i)
        {
            new_data[i] = data[i];
        }

        // data가 nullptr이 아닌 경우 
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
        // length 값이 마지막 요소 다음 index를 나타낸다. 
        // 마지막 요소 다음 칸에 값을 대입하고 length 값을 증가시킨다. 
        data[length++] = value;
    }

    void pop_back() 
    {
        if (length > 0) 
        {
            --length; 
        }
    } 

    // 이동 대입 연산자
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

    // 대입 연산자
    Vector& operator=(const Vector& other)
    {
        if (this == &other) return *this; // 자기 자신 대입 방지

        // 기존 자원 정리
        delete[] data;

        // 새로 복사
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

    // 값 10개 넣기
    for (int i = 1; i <= 10; ++i) 
    {
        vec.push_back(i * 10);  // 예: 10, 20, ..., 100
    }

    // 출력
    cout << "Vector contents:\n";
    for (int i = 0; i < vec.size(); ++i) 
    {
        cout << vec[i] << " ";
    }

    cout << "\nSize: " << vec.size() << endl; 
    cout << "Capacity: " << vec.get_capacity() << endl;

    return 0;
    
}
