#include "stack.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <deque>

int main(){
    ft::stack<int > s1;
    s1.push(1);
    std::cout << "Top element: " << s1.top() << std::endl;
    s1.push(2);
    s1.push(4);
    std::cout << "Top element: " << s1.top() << std::endl;
    std::cout << "Size of stack: " << s1.size() << std::endl;

    std::vector<int> v1;
    std::deque<int> d1;
    std::stack<int> s2(d1);
    s2.push(6);
    std::cout << "Top element s2: " << s2.top() << std::endl;
}