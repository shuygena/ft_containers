#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <deque>

void test_stack(void)
{
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
    s1.pop();
    std::cout << "Top element: " << s1.top() << std::endl;
    std::cout << "Size of stack: " << s1.size() << std::endl;
    

    std::cout << "=======================================\n";
    std::cout << "\t\tSTD STACK\n";
    std::cout << "=======================================\n";

    std::stack<int > s2;
    s2.push(1);
    std::cout << "Top element: " << s2.top() << std::endl;
    s2.push(2);
    s2.push(4);
    std::cout << "Top element: " << s2.top() << std::endl;
    std::cout << "Size of stack: " << s2.size() << std::endl;
    s2.pop();
    std::cout << "Top element: " << s2.top() << std::endl;
    std::cout << "Size of stack: " << s2.size() << std::endl;

}

void test_vector(void)
{
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
    std::cout << "begin() = " << *(v1.begin()) << std::endl;
    ft::vector<int> vr;
    vr.assign(783, 1);
    std::cout << "capacity(): assign 783: " << vr.capacity()<< std::endl;
    vr.push_back(vr.capacity());
    std::cout << "capacity(): push_back(): " << vr.capacity()<< std::endl;
    vr.resize(88);
    std::cout << "capacity(): resize 88: " << vr.capacity()<< std::endl;
    std::cout << "size(): resize 88: " << vr.size()<< std::endl;

    //ATENTION THERE IS CONSTRUCTOR TESTS
    std::vector<int> v;
    ft::vector<int> vector(3, 3);
	std::vector<int> tmp(1000, 4);
	ft::vector<int> tmp2(tmp.begin(), tmp.end());
	v.push_back(tmp2.size());
	v.push_back(tmp2.capacity());
    

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
    std::cout << "begin() = " << *(v2.begin()) << std::endl;

    std::vector<int> vstd;
    vstd.assign(783, 1);
    std::cout << "capacity(): assign 783: " << vstd.capacity()<< std::endl;
    vstd.push_back(vstd.capacity());
    std::cout << "capacity(): push_back(): " << vstd.capacity()<< std::endl;
    vstd.resize(88);
    std::cout << "capacity(): resize 88: " << vstd.capacity()<< std::endl;
    std::cout << "size(): resize 88: " << vstd.size()<< std::endl;
}

int main(){
    
    test_stack();
    test_vector();
    
}