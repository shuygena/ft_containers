#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

namespace ft {
    template <class T, class Allocator = std::allocator<T> >
    class vector {
    public:
        // types:
        typedef typename Allocator::const_reference const_reference;
        typedef typename Allocator::reference reference;
        // typedef implementation defined iterator; // See 23.1
        // typedef implementation defined const_iterator; // See 23.1
        // typedef implementation defined size_t; // See 23.1
        // typedef implementation defined difference_type;// See 23.1
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        // typedef std::reverse_iterator<iterator> reverse_iterator;
        // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
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
        // template <class InputIterator> //как сделать проверку на int?
        //     vector(InputIterator first, InputIterator last,
        //         const Allocator& = Allocator()): _all(alloc){
        //             bool is_valid;
        //             if (first > last)
        //                 throw std::length_error("vector");
        //             _sz = last - first;
        //             _cap = _sz;
        //             _arr = _all.allocate(_cap);

        //     }

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
        
        // template <class InputIterator>
        //     void assign(InputIterator first, InputIterator last);
        
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

        // iterator begin();
        // const_iterator begin() const;
        // iterator end();
        // const_iterator end() const;
        // reverse_iterator rbegin();
        // const_reverse_iterator rbegin() const;
        // reverse_iterator rend();
        // const_reverse_iterator rend() const;
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

        // iterator insert(iterator position, const T& x);
        // void insert(iterator position, size_t n, const T& x)
        // {
        //     size_t i = 0;
        //     size_t j = 0;
        //     pointer *arr = _all.allocate(n + _sz);
        //     while (i++ < position)
        //         _all.construct(arr + i, *(_arr + i));
        //     while (j++ < n)
        //         _all.construct(arr + i - 1 + j, x);
        //     while (i++ < _sz)
        //         _all.construct(arr + i + j, *(_arr + i));
        //     for (i = 0; i < _sz; i++)
        //         _all.destroy(_arr + i);
        //     if (_cap)
        //         _all.deallocate(_arr, _cap);
        //     _arr = arr;
        //     _cap = n + _sz;
        //     _sz += n;
        // }
        // template <class InputIterator>
        //     void insert(iterator position,
        //     InputIterator first, InputIterator last);
        // iterator erase(iterator position);
        // iterator erase(iterator first, iterator last);
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
    const vector<T,Allocator>& y);
template <class T, class Allocator>
    bool operator!=(const vector<T,Allocator>& x,
    const vector<T,Allocator>& y){
            return !(x == y);
        }

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


#endif