#ifndef NODE_ITERATOR_HPP
#define NODE_ITERATOR_HPP

#include "rb_tree.hpp"
#include "iterator.hpp"
#include "utils.hpp"

namespace ft{
    template<class T> //deleted class U
    class node_iterator{
    public:
        typedef typename std::bidirectional_iterator_tag iterator_category;
        typedef typename ft::iterator_traits<T*>::difference_type
            difference_type;
        typedef typename ft::iterator_traits<T*>::reference
            reference;
        typedef typename ft::iterator_traits<T*>::pointer pointer;
        typedef typename ft::iterator_traits<T*>::value_type value_type;

    private:
        node<T> *current;

        void next(){
            if (current->nil == 0){
                if (current->right->nil == 0){
                    current = current->right;
                    while (current->left->nil == 0)
                        current = current->left;
                }
                else{
                    node<T> *parent = current->parent;
                    while(parent->nil == 0 && current == parent->right)
                    {
                        current = parent;
                        parent = parent->parent;
                    }
                    current = parent; //mistake?
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
                node<T> *parent = current->parent;
                while (parent->nil == 0 && current == parent->left){
                    current = parent;
                    parent = parent->parent;
                }
                if (parent->nil == 0)
                    current = parent;
            }

        }
    
    public:
        node_iterator(node<T> *value = 0): current(value){}

        template<class U>
            node_iterator(const ft::node_iterator<U>& u):
                current(u.base()){}
        

        ~node_iterator(){}

        node<T> *base() const{
            return current;
        }

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