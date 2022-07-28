#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <map.hpp>

#define STOP   "\033[0m"
#define GREEN   "\033[32m"     

void test_stack(void)
{
    std::cout << "=======================================\n";
    std::cout << "\t\tFT STACK\n";
    std::cout << "=======================================\n";

    std::cout << GREEN << "push(), top(), pop()" << STOP << std::endl;
    ft::stack<int > s1;
    s1.push(1);
    std::cout << "top element: push 1: " << s1.top() << std::endl;
    s1.push(2);
    s1.push(4);
    std::cout << "top element: push 4: " << s1.top() << std::endl;
    std::cout << "size of stack: " << s1.size() << std::endl;
    s1.pop();
    std::cout << "top element: pop: " << s1.top() << std::endl;
    std::cout << "size of stack: " << s1.size() << std::endl;
    

    std::cout << "=======================================\n";
    std::cout << "\t\tSTD STACK\n";
    std::cout << "=======================================\n";

    std::cout << GREEN << "push(), top(), pop()" << STOP << std::endl;
    std::stack<int > s2;
    s2.push(1);
    std::cout << "top element: push 1: " << s2.top() << std::endl;
    s2.push(2);
    s2.push(4);
    std::cout << "top element: push 4: " << s2.top() << std::endl;
    std::cout << "size of stack: " << s2.size() << std::endl;
    s2.pop();
    std::cout << "top element: pop: " << s2.top() << std::endl;
    std::cout << "size of stack: " << s2.size() << std::endl;

}

void test_vector(void)
{
    std::cout << "=======================================\n";
    std::cout << "\t\tFT VECTOR\n";
    std::cout << "=======================================\n";

    std::cout << GREEN << "capacity(), push_back(), size(), clear()" << STOP << std::endl;
    ft::vector<int> v1; //  capacity(), push_back(), size(), clear() 
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
    //добавить empty()

    std::cout << GREEN << "assign(), resize()" << STOP << std::endl;
    ft::vector<int> vr; //assign(), resize()
    vr.assign(783, 1);
    std::cout << "capacity(): assign 783: " << vr.capacity()<< std::endl;
    vr.push_back(vr.capacity());
    std::cout << "capacity(): push_back(): " << vr.capacity()<< std::endl;
    vr.resize(88);
    std::cout << "capacity(): resize 88: " << vr.capacity()<< std::endl;
    std::cout << "size(): resize 88: " << vr.size()<< std::endl;

    std::cout << GREEN << "asign(range), begin(), end()"<< STOP << std::endl;
    std::vector<int> vass; //asign(iterator first, iterator end), begin(), end()
    ft::vector<int> tmp11, tmp22;
    v1.assign(3, 3);
    tmp11.assign(40, 1);
    tmp22.assign(4, 1);
    v1.assign(tmp11.begin(), tmp11.end());
    vass.push_back(v1[1]);
    size_t nvass = vass.size();
    std::cout << "assign size = " << nvass << std::endl;
    std::cout << "assign capacity = " << vass.capacity() << std::endl;

    std::cout << GREEN << "resize(), reverse()"<< STOP << std::endl;
    v1.clear(); //resize(), reverse()
    std::vector<int> vre;
    v1.assign(50, 1);
    v1.resize(25);
    v1.reserve(25);
    vre.push_back(v1.size());
    vre.push_back(v1.capacity());
    v1.resize(30);
        std::cout << "v1 resize: " << v1.size() << std::endl;

    std::cout << GREEN << "insert(), insert(range)"<< STOP << std::endl;
    v1.insert(v1.begin(), vre.begin(), vre.end());//insert(iterator first, iterator end)
    std::cout << "insert: size: " << v1.size() << " capacity: " << v1.capacity() << std::endl; 
    v1.insert(v1.end() - 8, 5, 44);
    std::cout << "insert(value): value: " << v1[24] <<
    " size: " << v1.size() << " capacity: " << v1.capacity() << std::endl;
    // for (int i = 0; i < int(v1.size()); i++)
    //     std::cout << "[" << v1[i] << "]";
    // std::cout << "\n";
    v1.clear();
    v1.assign(1000, 1);
    v1.insert(v1.end() - 50, 4200, 2);
    std::cout << "insert(fill): size = " << v1.size() << "; capacity = " << v1.capacity() << std::endl;
    v1.insert(v1.end() - 50, 8);
    std::cout << "insert(value): size = " << v1.size() << "; capacity = " << v1.capacity() << std::endl;
    // for (int i = 0; i < int(v1.size()); i++)
    //     std::cout << "[" << v1[i] << "]";
    // std::cout << "\n";

    std::cout << GREEN << "erase()"<< STOP << std::endl;
    std::cout << "value before erase = " << v1[v1.size() - 50]<< "; size = " << v1.size()<< std::endl;
    v1.erase(v1.end() - 50);
    std::cout << "value after erase = " << v1[v1.size() - 50]<< "; size = " << v1.size()<< std::endl;

    std::cout << "=======================================\n";
    std::cout << "\t\tSTD VECTOR\n";
    std::cout << "=======================================\n";

    std::cout << GREEN << "capacity(), push_back(), size(), clear()" << STOP << std::endl;
    std::vector<int> v2;
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

    std::cout << GREEN << "assign(), resize()" << STOP << std::endl;
    std::vector<int> vstd;
    vstd.assign(783, 1);
    std::cout << "capacity(): assign 783: " << vstd.capacity()<< std::endl;
    vstd.push_back(vstd.capacity());
    std::cout << "capacity(): push_back(): " << vstd.capacity()<< std::endl;
    vstd.resize(88);
    std::cout << "capacity(): resize 88: " << vstd.capacity()<< std::endl;
    std::cout << "size(): resize 88: " << vstd.size()<< std::endl;

    std::cout << GREEN << "asign(range), begin(), end()"<< STOP << std::endl;
    std::vector<int> vas;
    std::vector<int> tmp1, tmp12;
    v2.assign(3, 3);
    tmp1.assign(40, 1);
    tmp12.assign(4, 1);
    v2.assign(tmp1.begin(), tmp1.end());
    vas.push_back(v2[1]);
    size_t nvas = vas.size();
    std::cout << "assign size = " << nvas << std::endl;
    std::cout << "assign capacity = " << vas.capacity() << std::endl;

    std::cout << GREEN << "resize(), reverse()"<< STOP << std::endl;
    v2.clear();
    std::vector<int> vres;
    v2.assign(50, 1);
    v2.resize(25);
    v2.reserve(25);
    vres.push_back(v2.size());
    vres.push_back(v2.capacity());
    v2.resize(30);
    std::cout << "v2 resize: " << v2.size() << std::endl;

    std::cout << GREEN << "insert(range), insert(fill), insert(value)"<< STOP << std::endl;
    v2.insert(v2.begin(), vres.begin(), vres.end());
    std::cout << "insert: size: " << v2.size() << " capacity: " << v2.capacity() << std::endl;
    v2.insert(v2.end() - 8, 5, 44);
    std::cout << "insert(fill): value: " << v2[24] <<
    " size: " << v2.size() << " capacity: " << v2.capacity() << std::endl;
    // for (int i = 0; i < int(v2.size()); i++)
    //     std::cout << "index = " << i << " value = " << v2[i] << std::endl;
    v2.clear();
    v2.assign(1000, 1);
    v2.insert(v2.end() - 50, 4200, 2);
    std::cout << "insert(fill): size = " << v2.size() << "; capacity = " << v2.capacity() << std::endl;
    v2.insert(v2.end() - 50, 8);
    std::cout << "insert(value): size = " << v2.size() << "; capacity = " << v2.capacity() << std::endl;

    std::cout << GREEN << "erase()"<< STOP << std::endl;
    std::cout << "value before erase = " << v2[v2.size() - 50]<< "; size = " << v2.size() << std::endl;
    v2.erase(v2.end() - 50);
    std::cout << "value after erase = " << v2[v2.size() - 50]<< "; size = " << v2.size() << std::endl;
    // for (int i = 0; i < int(v2.size()); i++)
    //     std::cout << "[" << v2[i] << "]";
    // std::cout << "\n";
    //std::cout<< "assign(range) compare: " << (vas == vass) << std::endl;
    // std::cout<< "resize/reverse compare: " << (vre == vres) << std::endl;
}

void test_map(void)
{
    std::cout << "=======================================\n";
    std::cout << "\t\tFT MAP\n";
    std::cout << "=======================================\n";

    ft::map<int, int> m1;
}

int main(){
    test_stack();
    test_vector();
    test_map();
}