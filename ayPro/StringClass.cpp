#include <iostream>
#include <cstring>  
using namespace std;

class String
{
private:
    char* data = nullptr;
    int   length = 0;

public:
    String() = default;

    // 생성자
    String(const char* str)
    {
        if (str)
        {
            length = strlen(str);
            data = new char[length + 1];
            strcpy_s(data, length + 1, str);
        }
    }

    // 복사 생성자
    String(const String& other)
    {
        length = other.length; 
        data = new char[length + 1];
        strcpy_s(data, length + 1, other.data);
    }

    // 이동 생성자
    String(String&& other) noexcept
    {
        data = other.data;
        length = other.length;

        other.data = nullptr;
        other.length = 0;
    }

    // 대입 연산자
    String& operator=(const String& other)
    {
        if (this == &other) return *this;

        delete[] data; 
        length = other.length; 
        data = new char[length + 1];
        strcpy_s(data, length + 1, other.data);

        return *this;
    } 

    // 이동 대입 연산자
    String& operator=(String&& other) noexcept
    {
        if (this == &other) return *this;

        delete[] data;
        data = other.data;
        length = other.length;

        other.data = nullptr;
        other.length = 0;

        return *this;
    } 

    // String + String
    String operator+(const String& other) const
    {
        int new_length = length + other.length;
        char* new_data = new char[new_length + 1];

        strcpy_s(new_data, new_length + 1, data);
        strcat_s(new_data, new_length + 1, other.data);

        String result(new_data);
        delete[] new_data; // 임시 복사본 정리
        return result;
    }

    // String + const char*
    String operator+(const char* str) const
    {
        if (!str) return *this;

        int str_length = strlen(str);
        int new_length = length + str_length;

        char* new_data = new char[new_length + 1]; 
        strcpy_s(new_data, new_length + 1, data); 
        strcat_s(new_data, new_length + 1, str);

        String result(new_data);
        delete[] new_data;
        return result;
    }

    ~String()
    {
        delete[] data;
    }

    const char* c_str() const 
    {
        return data; 
    }

    int size() const
    {
        return length;
    }

    char& operator[](int index)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of bounds"); 

        return data[index];
    }
};


int main()
{
    String str("Hello, World!");
    cout << "Original: " << str.c_str() << endl;

    String copy = str;
    cout << "Copy: " << copy.c_str() << endl;

    String moved = std::move(str);
    cout << "Moved: " << moved.c_str() << endl; 
    
    // String(const char* str) 생성자가 먼저 호출되어 rValue가 생성된 후 
    // String(String&& other) noexcept 이동 대입 연산자 사용 
    str = "Adidas"; 

    cout << str.c_str() << endl; 

    copy[7] = 'C'; 
    cout << "Modified Copy: " << copy.c_str() << endl; 
    cout << "Length: " << copy.size() << endl; 

    return 0; 
}
