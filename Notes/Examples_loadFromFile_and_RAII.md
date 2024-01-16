```c++
void loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    std::string first, last;
    int id;
    float avg;
    
    while (fin >> first) {
        fin >> last >> id >> avg;
        
        addStudent(Student(first, last, id, avg));
    }
}
```



```c++
template <typename T>
class DynamicArray {
    private:
	    size_t m_size;
    	T * m_arr;
    
    public:
    	DynamicArray(size_t size)
            : m_size(size)
            , m_arr(new T[size]) {
        	std::cout << "Array Constructor\n";
        }
    
    	~DynamicArray() {
            delete [] m_arr;
        }
}
```

# setVerticalSyncEnabled 不起作用
很可能是因为在图形驱动程序设置中垂直同步被强制“关闭”。需要手动将其设置为“由应用程序控制”。

# 找到当前工作路径
```c++
#include <iostream>
#include <filesystem>

int main() {
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl
}
```
