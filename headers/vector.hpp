#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {
    template <class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        typedef T value_type;
        typedef Allocator allocator_type;        
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef ft::random_access_iterator<pointer> iterator;
        typedef ft::random_access_iterator<const pointer> const_iterator;
        typedef typename Allocator::size_t size_t;
        typedef typename Allocator::difference_type difference_type;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        pointer         *_arr;
        size_t          _sz;
        size_t          _cap;
        allocator_type  _all;

// ? ***************************************************************************
// ? *                       construct/copy/destroy:                           *
// ? ***************************************************************************
        /* Constructs an empty container with the given 
        allocator alloc.*/
        explicit vector(const Allocator& = Allocator()):
            _arr(0), _sz(0), _cap(0), _all(Allocator()){}
        
        /* Constructs the container with count copies of 
        elements with value value.*/
        explicit vector(size_t n, const T& value = T(),
            const Allocator& = Allocator()):
            _sz(n), _cap(n), _all(Allocator()){
                _arr = _all.allocate(n);
                for (size_t i = 0; i < n; i ++)
                    _all.construct(_arr + i, value);
        }

        // Constructs the container with the contents of the range [first, last]    
        template <class InputIterator> //как сделать проверку на int?
            vector(InputIterator first, InputIterator last, const Allocator& = Allocator(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0): _all(Allocator()){
                    if (first > last)
                        throw std::length_error("vector");
                    _sz = last - first;
                    _cap = _sz;
                    _arr = _all.allocate(_cap);
                    for (difference_type i = 0; i < static_cast<difference_type>(_sz); i++)
                        _all.construct(_arr + i, *(first + i));

            }

        vector<T,Allocator>& operator=(const vector<T,Allocator>& x){
            if (this == &x)
                return *this;
            for (size_t i = 0; i < _sz; i++)
                _all.destroy(_arr + i);
            if (_cap)
                _all.deallocate(_arr, _cap);
            _arr = _all.allocate(x._cap);
            _sz = x._sz;
            _cap = x._cap;
            for (size_t i = 0; i < _sz; i++)
                _all.construct(_arr + i, *(x + i));
            return *this;     
        }

        //Copy constructor. Constructs the container with the copy of the contents of other.         
        vector(const vector<T,Allocator>& x){ // надо ли здесь указывать sz, cap? перегрузка опертора должна случиться раньше
            *this = x;
        }

        ~vector()
        {
            for (size_t i = 0; i < _sz; i++)
                _all.destroy(_arr + i);
            _all.deallocate(_arr, _cap); 
        }
        
        template <class InputIterator>
            void assign(InputIterator first, InputIterator last,
             typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
                if (first > last)
                    throw std::logic_error("vector");
                difference_type counter = last - first;
                for (size_t i = 0; i < _sz; i++)
                    _all.destroy(_arr + i);
                if (counter > static_cast<difference_type>(_cap)){
                    _all.deallocate(_arr, _cap);
                    _arr = _all.allocate(counter);
                    _cap = counter;
                }
                iterator it = begin();
                while (first < last)
                {
                    _all.construct(&(*it), *first);
                    it++;
                    first++;
                }
                _sz = counter;
            }
        
        void assign(size_t n, const T& u){
            for (size_t i = 0; i < _sz; i++)
                _all.destroy(_arr + i);
            if (n > _cap){
                _all.deallocate(_arr, _cap);
                while (_cap < n)
                    _cap *= 2;
                _arr = _all.allocate(_cap);  
            }
            for (size_t i = 0; i < n; i++)
                _all.construct(_arr + i, u);
            _sz = n;            
        }

        allocator_type get_allocator() const{
            return(_all);
        }
// ? ***************************************************************************
// ? *                       iterators:                                        *
// ? ***************************************************************************

        iterator begin(){
            return iterator(_arr);
        }
        const_iterator begin() const{
            return const_terator(_arr);
        }
        
        iterator end(){
            return iterator(_arr + _sz);
        }
        
        const_iterator end() const{
            return const_iterator(_arr + _sz);
        }
        reverse_iterator rbegin(){
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const{
            return const_reverse_iterator(end());
        }
        reverse_iterator rend(){
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const{
            return const_reverse_iterator(begin());
        }
// ? ***************************************************************************
// ? *                       capacity:                                         *
// ? ***************************************************************************
        size_t size() const{
            return _sz;
        }

        size_t max_size() const{
            return _all.max_size();
        }

        void reserve(size_t n){
            if (n > _cap)
            {
                size_t i;
                pointer *arr = _all.allocate(n);
                for (i = 0; i < _sz; i++)
                    _all.construct(arr + i, *(_arr + i));
                for (i = 0; i < _sz; i++)
                    _all.destroy(_arr + i);
                if (_cap)
                    _all.deallocate(_arr, _cap);
                _arr = arr;
                _cap = n;
            }
        }

        void resize(size_t sz, T c = T()){ //what if (_cap < sz) ?
            if (sz < _sz){
                for (size_t i = sz; i < _sz; i++)
                _all.destroy(_arr + i);
                _sz = sz;
            }
            else{
                size_t ncap = _cap;
                while(ncap < sz)
                    ncap *= 2;
                reserve(ncap);
                for (size_t i = _sz; i < sz; i++)
                    _all.construct(_arr + i, c);
                    _sz++;
            }
        }

        size_t capacity() const{
            return _cap;
        }

        bool empty() const{
            if (_sz == 0)
                return true;
            return false;
        }

// ? ***************************************************************************
// ? *                       element access:                                   *
// ? ***************************************************************************
        reference operator[](size_t n){
            return *(_arr + n);
        }

        const_reference operator[](size_t n) const{
            return static_cast<const_reference>(*(_arr + n));
        }

        const_reference at(size_t n) const{
            if (n > _cap)
                throw std::out_of_range("vector at out of range");
            return static_cast<const_reference>(*(_arr + n));
        }

        reference at(size_t n){
            if (n > _cap)
                throw std::out_of_range("vector at out of range");
            return *(_arr + n);
        }

        reference front(){
            return *_arr;
        }

        const_reference front() const{
            return static_cast<const_reference>(*_arr);
        }

        reference back(){
            return *(_arr + _sz - 1);
        }

        const_reference back() const{
            return static_cast<const_reference>(*(_arr + _sz - 1));
        }
// ? ***************************************************************************
// ? *                       modifiers:                                        *
// ? ***************************************************************************

        void clear(){
            for (size_t i = 0; i < _sz; i++)
                _all.destroy(_arr + i);
            _sz = 0;
        }

        void push_back(const T& x){
            if (_cap <= _sz)
                reserve(_cap * 2 + (_cap == 0));
            _all.construct(_arr + _sz, x);
            _sz++;
        }

        void pop_back(){
            _sz--;
            _all.destroy(_arr + _sz);
        }

        iterator insert(iterator position, const T& x){
            insert(position, 1, x);
            return ++position;
        }

        void insert(iterator position, size_t n, const T& x)
        {
            size_t i = 0;
            size_t j = 0;
            pointer *arr = _all.allocate(n + _sz);
            while (i++ < position)
                _all.construct(arr + i, *(_arr + i));
            while (j++ < n)
                _all.construct(arr + i - 1 + j, x);
            while (i++ < _sz)
                _all.construct(arr + i + j, *(_arr + i));
            for (i = 0; i < _sz; i++)
                _all.destroy(_arr + i);
            if (_cap)
                _all.deallocate(_arr, _cap);
            _arr = arr;
            _cap = n + _sz;
            _sz += n;
        }

        template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
                if (position < begin() || position > end() || first > last)
                    throw std::logic_error("vector");
                size_t start = static_cast<size_t>(position - begin());
                size_t counter = static_cast<size_t>(last - first);
                if (_sz + counter > _cap)
                {
                    size_t cap = _cap * 2;
                    while (cap < _sz + counter)
                        cap = _cap * 2;
                    pointer *arr = _all.allocate(cap);
                    size_t i = 0;
                    size_t j = 0;
                    while (i++ < position)
                        _all.construct(arr + i, *(_arr + i));
                    while (j++ < counter)
                        _all.construct(arr + i - 1 + j, *(first++));
                    while (i++ < _sz)
                        _all.construct(arr + i + j, *(_arr + i));
                    for (i = 0; i < _sz; i++)
                        _all.destroy(_arr + i);
                    if (_cap)
                         _all.deallocate(_arr, _cap);
                    _arr = arr;
                    _cap = cap;
                    _sz += counter;
                }
                else{
                    for (size_t i = _sz; i > static_cast<size_t>(start); i--){
                        _all.destroy(_arr + i + counter - 1);
                        _all.construct(_arr + i + counter - 1, *(_arr + i - 1));
                    }
                    for (size_t i = 0; i < static_cast<size_t>(counter); i++){
                        _all.destroy(_arr + i + counter);
                        _all.construct(_arr + start + i, *(first++));
                    }
                    _sz += counter;
                }
            }

        iterator erase(iterator position){
            return erase(position, position + 1);
        }

        iterator erase(iterator first, iterator last){
            size_t n = std::distance(first, last);
            for (size_t i = 0; i < n; i++)
                _all.destroy(first.base() + 1);
            size_t counter = std::distance(last, end());
            for (size_t i = 0; i < counter; i++)
            first.base()[i] = last.base()[i];
            _sz -= n;
            return first;
        }

        void swap(ft::vector<T,Allocator>& x){
            std::swap(_arr, x._arr);
            std::swap(_sz, x._sz);
            std::swap(_cap, x._cap);
            std::swap(_all, x._all);
        }
};
    template <class T, class Allocator>
        bool operator==(const vector<T,Allocator>& x,
        const vector<T,Allocator>& y){
            if (x._sz != y._sz)
                return false;
            for (size_t i = 0; i < x._sz; i++)
                if (x[i] != y[i])
                    return false;
            return true;
        }

    template <class T, class Allocator>
        bool operator< (const vector<T,Allocator>& x,
        const vector<T,Allocator>& y){
            return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
        }

    template <class T, class Allocator>
        bool operator!=(const vector<T,Allocator>& x,
        const vector<T,Allocator>& y){
            return !(x == y);
        }

    template <class T, class Allocator>
        bool operator> (const vector<T,Allocator>& x,
        const vector<T,Allocator>& y){
            return y < x;
        }

    template <class T, class Allocator>
    bool operator>=(const vector<T,Allocator>& x,
    const vector<T,Allocator>& y){
        return !(x < y);
    }

    template <class T, class Allocator>
        bool operator<=(const vector<T,Allocator>& x,
        const vector<T,Allocator>& y){
            return !(x > y);
        }
    // specialized algorithms:
    template <class T, class Allocator>
    void swap(vector<T,Allocator>& x, vector<T,Allocator>& y){
        x.swap(y);
    }
}


#endif