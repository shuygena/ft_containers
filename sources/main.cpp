#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <deque>

int main(){
    
    std::cout << "=======================================\n";
    std::cout << "\t\tFT STACK\n";
    std::cout << "=======================================\n";

    ft::stack<int > s1;
    s1.push(1);
    std::cout << "Top element: " << s1.top() << std::endl;
    s1.push(2);
    s1.push(4);
    std::cout << "Top element: " << s1.top() << std::endl;
    std::cout << "Size of stack: " << s1.size() << std::endl;

    // std::vector<int> v1;
    // std::deque<int> d1;
    // std::stack<int> s2(d1);
    // s2.push(6);
    // std::cout << "Top element s2: " << s2.top() << std::endl;

    std::cout << "=======================================\n";
    std::cout << "\t\tFT VECTOR\n";
    std::cout << "=======================================\n";

    ft::vector<int> v1; //  не работает с std::string
    std::cout << "capacity: " << v1.capacity()<< std::endl;
    v1.push_back(2);
    std::cout << "capacity: " << v1.capacity()<< std::endl;
    v1.push_back(8);
    std::cout << "capacity: " << v1.capacity()<< std::endl;
    for (int i = 0; i < int(v1.size()); i++)
        std::cout << "v1[" << i << "] = " << v1[i] << std::endl;
    v1.clear();
    std::cout << "capacity after clear: " << v1.capacity()<< std::endl;
    std::cout << "size after clear: " << v1.size()<< std::endl;
    
    std::cout << "=======================================\n";
    std::cout << "\t\tSTD VECTOR\n";
    std::cout << "=======================================\n";

    std::vector<int> v2; //  не работает с std::string
    std::cout << "capacity: " << v2.capacity()<< std::endl;
    v2.push_back(2);
    std::cout << "capacity: " << v2.capacity()<< std::endl;
    v2.push_back(8);
    std::cout << "capacity: " << v2.capacity()<< std::endl;
    for (int i = 0; i < int(v2.size()); i++)
        std::cout << "v2[" << i << "] = " << v2[i] << std::endl;
    v2.clear();
    std::cout << "capacity after clear: " << v2.capacity()<< std::endl;
    std::cout << "size after clear: " << v2.size()<< std::endl;
    
}