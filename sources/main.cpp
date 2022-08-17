#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "rb_tree.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <map>
#include <ctime>
#include <unistd.h>

#define STOP   "\033[0m"
#define GREEN  "\033[32m"
#define BLUE   "\033[36m"     

void test_stack(void)
{ 
    std::cout << "=======================================\n";
    std::cout << "\t\tFT STACK\n";
    std::cout << "=======================================\n";

    clock_t time_start = clock();

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
    
    clock_t time_end = clock();
    std::cout << BLUE << "execution time: " << (time_end - time_start)
            << " mcs" << STOP << std::endl;

    std::cout << "=======================================\n";
    std::cout << "\t\tSTD STACK\n";
    std::cout << "=======================================\n";

    time_start = clock();

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

    time_end = clock();
    std::cout << BLUE << "execution time: " << (time_end - time_start)
            << " mcs" << STOP << std::endl;
}

void test_vector(void)
{
    std::cout << "=======================================\n";
    std::cout << "\t\tFT VECTOR\n";
    std::cout << "=======================================\n";

    clock_t time_start = clock();

    std::cout << GREEN << "capacity(), push_back(), size(), clear()" << STOP << std::endl;
    ft::vector<int> v1; 
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

    std::cout << GREEN << "assign(), resize()" << STOP << std::endl;
    ft::vector<int> vr; 
    vr.assign(783, 1);
    std::cout << "capacity(): assign 783: " << vr.capacity()<< std::endl;
    vr.push_back(vr.capacity());
    std::cout << "capacity(): push_back(): " << vr.capacity()<< std::endl;
    vr.resize(88);
    std::cout << "capacity(): resize 88: " << vr.capacity()<< std::endl;
    std::cout << "size(): resize 88: " << vr.size()<< std::endl;

    std::cout << GREEN << "asign(range), begin(), end()"<< STOP << std::endl;
    std::vector<int> vass; 
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
    v1.clear(); 
    std::vector<int> vre;
    v1.assign(50, 1);
    v1.resize(25);
    v1.reserve(25);
    vre.push_back(v1.size());
    vre.push_back(v1.capacity());
    v1.resize(30);
        std::cout << "v1 resize: " << v1.size() << std::endl;

    std::cout << GREEN << "insert(), insert(range)"<< STOP << std::endl;
    v1.insert(v1.begin(), vre.begin(), vre.end());
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

    clock_t time_end = clock();
    std::cout << BLUE << "execution time: " << (time_end - time_start)
            << " mcs" << STOP << std::endl;

    std::cout << "=======================================\n";
    std::cout << "\t\tSTD VECTOR\n";
    std::cout << "=======================================\n";

    time_start = clock();

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
    time_end = clock();
    std::cout << BLUE << "execution time: " << (time_end - time_start)
            << " mcs" << STOP << std::endl;
}

void test_map(void)
{
    std::cout << "=======================================\n";
    std::cout << "\t\tFT MAP\n";
    std::cout << "=======================================\n";
    /*ft::pair<int, std::string> vk(1, "one");
    std::cout << vk.first << " = " << vk.second << "\n";


    ft::tree< ft::pair<int, std::string> > t;
    ft::node< ft::pair<int, std::string> > n(vk);
    ft::pair<int, std::string> vk1(2, "two");
    ft::node< ft::pair<int, std::string> > n1(vk1);
    ft::pair<int, std::string> vk2(3, "three");
    ft::node< ft::pair<int, std::string> > n2(vk2);
    ft::pair<int, std::string> vk3(4, "four");
    ft::node< ft::pair<int, std::string> > n3(vk3);
    std::cout << "n is " << n.nil << std::endl;
    t.insert(vk, 0);
    t.insert(vk1, 0);
    t.insert(vk2, 0);
    t.insert(vk3, 0);
    // t.test();
    t.printTree();
    // t.rb_delete(&n2);
    // t.printTree();*/

    clock_t time_start = clock();

    std::cout << GREEN << "insert(key_value), map[]" << STOP << std::endl;
    ft::map<int, int> m1;
    ft::map<int, int> m2;
    std::cout << "insert(1, 1): "<< (m1.insert(ft::make_pair(1, 1))).second << std::endl;
    std::cout << "insert(1, 1): "<< (m1.insert(ft::make_pair(1, 1))).second << std::endl;
    std::cout << "insert(1, 2): "<< (m1.insert(ft::make_pair(1, 2))).second << std::endl;
    std::cout << "m1[1] = " << m1[1] << std::endl;
    std::cout << "insert(1, 3): "<< (m1.insert(ft::make_pair(1, 3))).second << std::endl;
    std::cout << "insert(2, 4): "<< (m1.insert(ft::make_pair(2, 4))).second << std::endl;
    std::cout << "mp[1] = " << m1[1] << std::endl;
    std::cout << "mp[333] = " << m1[333] << std::endl;
    
    std::cout << GREEN << "empty(), size(), max_size()" << STOP << std::endl;
    std::cout << "empty(): " << m1.empty() << std::endl;
    std::cout << "size(): " << m1.size() << std::endl;
    std::cout << "max_size(): " << m1.max_size() << std::endl;
    
    std::cout << GREEN << "begin(), end(), ++, --" << STOP << std::endl;
    m2.insert(ft::make_pair(3, 9));
    m2.insert(ft::make_pair(4, 16));
    m2.insert(ft::make_pair(5, 25));
    ft::map<int, int>::iterator first = m2.begin();
    ft::map<int, int>::iterator end = m2.end();
    first++;
    end--;
    std::cout << "begin()++ first: " << first->first << "; second: " << first->second << std::endl;
    std::cout << "end()-- first: " << end->first << "; second: " << end->second << std::endl;

    std::cout << GREEN << "insert(iter1, iter2)" << STOP << std::endl;
    m1.insert(m2.begin(), m2.end());
    for (ft::map<int, int>::iterator it1 = m1.begin(); it1 != m1.end(); it1++)
        std::cout << "m1[" << it1->first<< "] = " << it1->second << std::endl;
    
    std::cout << GREEN << "erase()" << STOP << std::endl;
    m1.erase(4);
    for (ft::map<int, int>::iterator it1 = m1.begin(); it1 != m1.end(); it1++)
        std::cout << "erase(): m1[" << it1->first<< "] = " << it1->second << std::endl;
    std::cout << "size after erase: " << m1.size() << std::endl;

    std::cout << GREEN << "overload operators: ==, !=, <, >, <=, >=" << STOP << std::endl;
    std::cout << "m1 == m1: " << (m1 == m1) << std::endl;
    std::cout << "m1 != m2: " << (m1 != m2) << std::endl;
    std::cout << "m1 < m2: " << (m1 < m2) << std::endl;
    std::cout << "m1 < m2: " << (m1 > m2) << std::endl;
    std::cout << "m1 < m2: " << (m1 <= m2) << std::endl;
    std::cout << "m1 < m2: " << (m1 >= m2) << std::endl;

    std::cout << GREEN << "clear()" << STOP << std::endl;
    m1.clear();
    std::cout << "m1 after clear(): empty(): " << m1.empty() << std::endl;

    clock_t time_end = clock();
    std::cout << BLUE << "execution time: " << (time_end - time_start)
            << " mcs" << STOP << std::endl;

    std::cout << "=======================================\n";
    std::cout << "\t\tSTD MAP\n";
    std::cout << "=======================================\n";
    
    time_start = clock();
    std::cout << GREEN << "insert(key_value), map[]" << STOP << std::endl;
    std::map<int, int> mp;
    std::map<int, int> mp1;
    std::cout << "insert(1, 1): "<< (mp.insert(std::make_pair(1, 1))).second << std::endl;
    std::cout << "insert(1, 1): "<< (mp.insert(std::make_pair(1, 1))).second << std::endl;
    std::cout << "insert(1, 2): "<< (mp.insert(std::make_pair(1, 2))).second << std::endl;
    std::cout << "mp[1] = " << mp[1] << std::endl;
    std::cout << "insert(1, 3): "<< (mp.insert(std::make_pair(1, 3))).second << std::endl;
    std::cout << "insert(2, 4): "<< (mp.insert(std::make_pair(2, 4))).second << std::endl;
    std::cout << "mp[1] = " << mp[1] << std::endl;
    std::cout << "mp[333] = " << mp[333] << std::endl;
    
    std::cout << GREEN << "empty(), size(), max_size()" << STOP << std::endl;
    std::cout << "empty(): " << mp.empty() << std::endl;
    std::cout << "size(): " << mp.size() << std::endl;
    std::cout << "max_size(): " << mp.max_size() << std::endl;
    
    std::cout << GREEN << "begin(), end(), ++, --" << STOP << std::endl;
    mp1.insert(std::make_pair(3, 9));
    mp1.insert(std::make_pair(4, 16));
    mp1.insert(std::make_pair(5, 25));
    std::map<int, int>::iterator first1 = mp1.begin();
    std::map<int, int>::iterator end1 = mp1.end();
    first1++;
    end1--;
    std::cout << "begin()++ first: " << first1->first << "; second: " << first1->second << std::endl;
    std::cout << "end()-- first: " << end1->first << "; second: " << end1->second << std::endl;

    std::cout << GREEN << "insert(iter1, iter2)" << STOP << std::endl;
    mp.insert(mp1.begin(), mp1.end());
    std::map<int, int>::iterator it = mp.begin();
    std::map<int, int>::iterator en = mp.end();
    for (; it != en; it++)
        std::cout << "mp[" << it->first<< "] = " << it->second << std::endl;
    
    std::cout << GREEN << "erase()" << STOP << std::endl;
    mp.erase(4);
    for (std::map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
        std::cout << "erase(): mp[" << it->first<< "] = " << it->second << std::endl;
    std::cout << "size after erase: " << mp.size() << std::endl;

    std::cout << GREEN << "overload operators: ==, !=, <, >, <=, >=" << STOP << std::endl;
    std::cout << "mp == mp: " << (mp == mp) << std::endl;
    std::cout << "mp != mp1: " << (mp != mp1) << std::endl;
    std::cout << "mp < mp1: " << (mp < mp1) << std::endl;
    std::cout << "mp < mp1: " << (mp > mp1) << std::endl;
    std::cout << "mp < mp1: " << (mp <= mp1) << std::endl;
    std::cout << "mp < mp1: " << (mp >= mp1) << std::endl;

    std::cout << GREEN << "clear()" << STOP << std::endl;
    mp.clear();
    std::cout << "mp after clear(): empty(): " << mp.empty() << std::endl;

    time_end = clock();
    std::cout << BLUE << "execution time: " << (time_end - time_start)
            << " mcs" << STOP << std::endl;
}

int main(){
    test_stack();
    test_vector();
    test_map();

    //for leaks
    //usleep(20000000); 
}