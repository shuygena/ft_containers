#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "iterator.hpp"
//iterator
#include "rb_tree.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map {
    public:
    // types:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type; //ft
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename Allocator::reference reference;
        typedef typename Allocator::const_reference const_reference;
        // typedef implementation defined iterator; // See 23.1
        // typedef implementation defined const_iterator; // See 23.1
        typedef typename Allocator::size_type size_type; // See 23.1
        typedef typename Allocator::difference_type difference_type;// See 23.1
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::template rebind< node <T> >::other  allocator_node;
        typedef typename Allocator::template rebind< tree <T> >::other  allocator_tree;
        // typedef ft::reverse_iterator<iterator> reverse_iterator;
        // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        
        class value_compare: public std::binary_function<value_type,value_type,bool> {
            friend class map;
            protected:
                Compare comp;
                value_compare(Compare c) : comp(c) {}
                public:
                bool operator()(const value_type& x, const value_type& y) const {
                return comp(x.first, y.first);
                }
            };
        
    private:
        Allocator                       _all;
        allocator_tree                  _all_tree;
        allocator_node                  _all_node;
        Compare                         _cmp;
        tree<value_type>   _tree;           
        
    public:
// ? ***************************************************************************
// ? *                       construct/copy/destroy:                           *
// ? ***************************************************************************
        explicit map(const Compare& comp = Compare(),
        const Allocator& alloc= Allocator()):
        // :
         _all(alloc), _cmp(comp)//, _tree(tree<value_type>())
        {
                // _tree = _all_tree.allocate(sizeof(tree<value_type>));
                // _all_tree.construct(_tree);
        }
        // template <class InputIterator>
        // map(InputIterator first, InputIterator last,
        // const Compare& comp = Compare(), const Allocator& = Allocator());
        // map(const map<Key,T,Compare,Allocator>& x): _all(x._all), _cmp(x._cmp){
        //     _tree = _all_tree.allocate(sizeof(tree<value_type>));
        //     _all_tree.construct(_tree, *x._tree);
        // } //после итератора перегрузить равно для дерева

        ~map(){}

        map<Key,T,Compare,Allocator>&
        operator=(const map<Key,T,Compare,Allocator>& x){
        if (this != &x){
        //     _tree.clear();
            _cmp = x._cmp;
            _all = x._all;
        //     _tree = x._tree;
            }
        return *this;    
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
        bool empty() const{
            return size() == 0;
        }
        size_type size() const{
            return _tree->size();
        }
        size_type max_size() const{
                return _all_node.max_size();
        }
// ? ***************************************************************************
// ? *                       element access:                                   *
// ? ***************************************************************************
        // T& operator[](const key_type& x){

        // }
// ? ***************************************************************************
// ? *                       modifiers:                                        *
// ? ***************************************************************************
        // pair<iterator, bool> insert(const value_type& x);
        // iterator insert(iterator position, const value_type& x);
        // template <class InputIterator>
        // void insert(InputIterator first, InputIterator last);
        // void erase(iterator position);
        size_type erase(const key_type& x);
        // void erase(iterator first, iterator last);
        void swap(map<Key,T,Compare,Allocator>&);
        void clear();
// ? ***************************************************************************
// ? *                       observers:                                        *
// ? ***************************************************************************
        key_compare key_comp() const;
        value_compare value_comp() const;
// ? ***************************************************************************
// ? *                       map operations:                                   *
// ? ***************************************************************************
        // iterator find(const key_type& x);
        // const_iterator find(const key_type& x) const;
        size_type count(const key_type& x) const;
        // iterator lower_bound(const key_type& x);

        // const_iterator lower_bound(const key_type& x) const;

        // iterator upper_bound(const key_type& x);
        // const_iterator upper_bound(const key_type& x) const;

        // pair<iterator,iterator>
        // equal_range(const key_type& x);

        // pair<const_iterator,const_iterator>
        // equal_range(const key_type& x) const;
};
    template <class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key,T,Compare,Allocator>& x,
    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator< (const map<Key,T,Compare,Allocator>& x,
    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator!=(const map<Key,T,Compare,Allocator>& x,
    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator> (const map<Key,T,Compare,Allocator>& x,
    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator>=(const map<Key,T,Compare,Allocator>& x,
    const map<Key,T,Compare,Allocator>& y);
    template <class Key, class T, class Compare, class Allocator>
    bool operator<=(const map<Key,T,Compare,Allocator>& x,
    const map<Key,T,Compare,Allocator>& y);
// ? ***************************************************************************
// ? *                       specialized algorithms:                           *
// ? ***************************************************************************
    template <class Key, class T, class Compare, class Allocator>
    void swap(map<Key,T,Compare,Allocator>& x,
    
    map<Key,T,Compare,Allocator>& y);
}

#endif