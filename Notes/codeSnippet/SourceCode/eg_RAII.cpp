#include <iostream>

template <typename T>
class DynamicArray {
private:
    size_t m_size;
    T * m_arr;
public:
    DynamicArray(size_t size)
        : m_size(size)
        , m_arr(new T[size]) {
        std::cout << "Array Constructor!" << std::endl;
    }

    ~DynamicArray() {
        delete [] m_arr;
        std::cout << "Array Destructor!" << std::endl;
    }

    T get(size_t index) const {
        return m_arr[index];
    }

    void set(size_t index, T value) {
        m_arr[index] = value;
    }

    void print() const {
        for (size_t i = 0; i < m_size; i++) {
            std::cout << i << " " << m_arr[i] << std::endl;
        }
    }

    T & operator [] (size_t index) {
        return m_arr[index];
    }

    const T & operator [] (size_t index) const {
        return m_arr[index];
    }
};

int main(int argc, char** argv) {
    DynamicArray<float> myArray(10);

    myArray[3] = 3.1415926;
    myArray[2] = 1.54;

    myArray.print();

    return 0;
}