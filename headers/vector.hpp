#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace ft {
    template <class T, class Allocator = allocator<T> >
    class vector {
    public:
        // types:
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::reference reference;
        typedef implementation defined iterator; // See 23.1
        typedef implementation defined const_iterator; // See 23.1
        typedef implementation defined size_type; // See 23.1
        typedef implementation defined difference_type;// See 23.1
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        pointer         _arr;
        size_t          _sz;
        size_t          _cap;
        allocator_type  _all;

        // construct/copy/destroy:
        /* Constructs an empty container with the given 
        allocator alloc.*/
        explicit vector(const Allocator& = Allocator()):
            _arr(0), _sz(0), _cap(0), _all(alloc){}
        
        /* Constructs the container with count copies of 
        elements with value value.*/
        explicit vector(size_type n, const T& value = T(),
            const Allocator& = Allocator()):
            _sz(n), _cap(n), _all(alloc){
                _arr = _all.allocate(n);
                for (size_type i = 0; i < n; i ++)
                    _all.construct(_arr + i, value);
            }

        // Constructs the container with the contents of the range [first, last]    
        template <class InputIterator> //как сделать проверку на int?
            vector(InputIterator first, InputIterator last,
                const Allocator& = Allocator()): _all(alloc){
                    bool is_valid;
                    if (first > last)
                        throw std::length_error("vector");
                    _sz = last - first;
                    _cap = _sz;
                    _arr = _all.allocate(_cap);
                    
                
            }


        //Copy constructor. Constructs the container with the copy of the contents of other.         
        vector(const vector<T,Allocator>& x){ // надо ли здесь указывать sz, cap? перегрузка опертора должна случиться раньше
            *this = x;
        }

        ~vector()
        {
            for (size_t i = 0; i < _sz; i++)
                _all.destroy(_arr + i);
            if (_cap)
                _all.deallocate(_arr, _cap);
        }
        //
        
        vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
        template <class InputIterator>
            void assign(InputIterator first, InputIterator last);
        void assign(size_type n, const T& u);
        allocator_type get_allocator() const;

        // iterators:
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
        // 23.2.4.2 capacity:
        size_type size() const;
        size_type max_size() const;
        void resize(size_type sz, T c = T());
        size_type capacity() const;
        bool empty() const;
        void reserve(size_type n);
        // element access:
        reference operator[](size_type n);
        const_reference operator[](size_type n) const;
        const_reference at(size_type n) const;
        reference at(size_type n);
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
        // 23.2.4.3 modifiers:
        void push_back(const T& x);
        void pop_back();
        iterator insert(iterator position, const T& x);
        void insert(iterator position, size_type n, const T& x);
        template <class InputIterator>
        void insert(iterator position,
        InputIterator first, InputIterator last);
        iterator erase(iterator position);
        iterator erase(iterator first, iterator last);
        void swap(vector<T,Allocator>&);
        void clear();
        };
template <class T, class Allocator>
bool operator==(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator< (const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator!=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator> (const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator>=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator<=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
// specialized algorithms:
template <class T, class Allocator>
void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
}


#endif VECTOR_HPP