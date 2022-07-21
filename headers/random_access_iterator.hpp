#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

#include "iterator.hpp"

namespace ft {
    template <typename T>
    class random_access_iterator{
    public:
        typedef typename ft::iterator_traits<T*>::difference_type
            difference_type;
        typedef typename ft::iterator_traits<T*>::reference
            reference;
        typedef typename ft::iterator_traits<T*>::pointer pointer;
        typedef typename std::random_access_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<T*>::value_type value_type;
    protected:
        pointer current;
    public:
        random_access_iterator(pointer current = 0):current(current){}
        template<class U>
            random_access_iterator(const ft::random_access_iterator<U>& u):
                current(u.base()){}
        virtual ~random_access_iterator(){}

        pointer base() const{
            return current;
        }

        random_access_iterator& operator=(const random_access_iterator& u){
            if (this == &u)
                return *this;
            current = u.current;
            return *this;
        }

        reference operator*() const{
        return *current;
        }
        pointer operator->() const{
            return current;
        }
    
        random_access_iterator& operator++(){
            ++current;
            return *this;
        }
        random_access_iterator operator++(int){
            random_access_iterator tmp = *this;
            ++current;
            return tmp;
        }
        random_access_iterator& operator--(){
            --current;
            return *this;
        }
        random_access_iterator operator--(int){
            random_access_iterator tmp = *this;
            --current;
            return tmp;
        }
    
        random_access_iterator operator+(difference_type n) const{
            return random_access_iterator(current + n);
        }

        random_access_iterator& operator+=(difference_type n){
            current += n;
            return *this;
        }
        random_access_iterator operator- (difference_type n) const{
            return random_access_iterator(current - n);
        }
        random_access_iterator& operator-=(difference_type n){
            current -= n;
            return *this;
        }

        reference operator[](difference_type n) const{
            return current[n];
        }
        // template <typename T>
        //     ptrdiff_t operator-(const random_access_iterator<T>& x){ 
        //         return base() - x.base(); }
    };
    template <class T> bool operator==(
        const random_access_iterator<T>& x,
        const random_access_iterator<T>& y){
            return &(*x) == &(*y);
        }
    template <class T> bool operator<(
        const random_access_iterator<T>& x,
        const random_access_iterator<T>& y){
            return &(*x) < &(*y);
        }
    template <class T> bool operator!=(
        const random_access_iterator<T>& x,
        const random_access_iterator<T>& y){
            return &(*x) != &(*y);
        }
    template <class T> bool operator>(
        const random_access_iterator<T>& x,
        const random_access_iterator<T>& y){
           return &(*x) > &(*y); 
        }
    template <class T> bool operator>=(
        const random_access_iterator<T>& x,
        const random_access_iterator<T>& y){
            return &(*x) >= &(*y);
        }

    template <class T> bool operator<=(
        const random_access_iterator<T>& x,
        const random_access_iterator<T>& y){
            return &(*x) <= &(*y);
        }
    template <class T>
        typename random_access_iterator<T>::difference_type operator-(
            const random_access_iterator<T>& x,
            const random_access_iterator<T>& y){
            return &(*x) - &(*y);   
            }
    template <class T>
        random_access_iterator<T> operator+(
            typename random_access_iterator<T>::difference_type n,
            const random_access_iterator<T>& x ){
            return random_access_iterator<T> (&(*x) + n);
            }
}

#endif