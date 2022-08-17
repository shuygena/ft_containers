#ifndef NODE_ITERATOR_HPP
#define NODE_ITERATOR_HPP

#include "rb_tree.hpp"
#include "iterator.hpp"
#include "utils.hpp"

namespace ft{
    template<class T, typename Pair> //deleted class U
    class node_iterator{
    public:
        typedef typename std::bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<Pair*>::difference_type
            difference_type;
        typedef typename ft::iterator_traits<Pair*>::reference
            reference;
        typedef typename ft::iterator_traits<Pair*>::pointer pointer;
        typedef typename ft::iterator_traits<Pair*>::value_type value_type;

    private:
        T current;

        void next(){
            if (current->nil == 0){
                if (current->right->nil == 0){
                    current = current->right;
                    while (current->left->nil == 0)
                        current = current->left;
                }
                else{
                    T parent = current->parent;
                    while(parent->nil == 0 && current == parent->right)
                    {
                        current = parent;
                        parent = parent->parent;
                    }
                    current = parent;
                }
            }
        }

        void prev(){
            if (current->nil){
                current = current->parent;    
                }
            else if (current->left->nil == 0){
                current = current->left;
                while (current->right->nil)
                    current = current->right;
            }
            else {
                T parent = current->parent;
                while (parent->nil == 0 && current == parent->left){
                    current = parent;
                    parent = parent->parent;
                }
                if (parent->nil == 0)
                    current = parent;
            }

        }
    
    public:
        node_iterator(T value = 0): current(value){}

        template<class U>
            node_iterator(const ft::node_iterator<U, Pair>& u):
                current(u.base()){}

        ~node_iterator(){}

        T base() const{
            return current;
        }

        // const node<const T> *c_base(){
        //     std::cout << typeid(current) << std::endl;
        //     return node_iterator();
        // }

        // const node<T> *base() const{
        //     return current;
        // }

        node_iterator& operator=(const node_iterator& u){
            if (this == &u)
                return *this;
            current = u.current;
            return *this;
        }

        reference operator*() const{
            return current->key_value;
        }

        pointer operator->() const{
            return &(current->key_value);
        }
    
        node_iterator& operator++(){
            next();
            return *this;
        }
        node_iterator operator++(int){
            node_iterator tmp = *this;
            next();
            return tmp;
        }
        node_iterator& operator--(){
            prev();
            return *this;
        }
        node_iterator operator--(int){
            node_iterator tmp = *this;
            prev();
            return tmp;
        }

        bool operator!=(node_iterator const &x){
            return (current != x.current);
        }

    };

}

#endif