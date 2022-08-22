#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <memory>
#include "iterator.hpp"
#include "node_iterator.hpp"
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
        typedef ft::node_iterator<ft::node<value_type>*, value_type> iterator;
        typedef ft::node_iterator<const ft::node<value_type>*, value_type> const_iterator;
        typedef typename Allocator::size_type size_type;
        typedef typename Allocator::difference_type difference_type;
        typedef typename Allocator::pointer pointer;
        typedef typename Allocator::const_pointer const_pointer;
        typedef typename Allocator::template rebind< node <T> >::other  allocator_node;
        typedef typename Allocator::template rebind< tree <T> >::other  allocator_tree;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        
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
        allocator_node                  _all_node;
        Compare                         _cmp;
        tree<value_type>                _tree;           
        
    public:
// ? ***************************************************************************
// ? *                       construct/copy/destroy:                           *
// ? ***************************************************************************
        explicit map(const Compare& comp = Compare(),
        const Allocator& alloc= Allocator()):
         _all(alloc), _cmp(comp){}

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
        const Compare& comp = Compare(), const Allocator& alloc = Allocator()){
            _all = alloc;
            _cmp = comp;
            for (; first != last; first++)
                insert(*first);
        }

        map(const map<Key,T,Compare,Allocator>& x): _all(x._all), _cmp(x._cmp){
            iterator first = x.begin();
            iterator last = x.end();
            for (; first != last; first++)
                insert(*first);
        } //после итератора перегрузить равно для дерева

        ~map(){
            _tree.clear();
        }

        map<Key,T,Compare,Allocator>&
        operator=(const map<Key,T,Compare,Allocator>& x){
        if (this != &x){
            _tree.clear();
            _cmp = x._cmp;
            _all = x._all;
        //     _tree = x._tree;
            }
        return *this;    
        }
// ? ***************************************************************************
// ? *                       iterators:                                        *
// ? ***************************************************************************
        iterator begin(){
            return iterator(_tree.begin());
        }

        const_iterator begin() const{
            return const_iterator(_tree.begin());
        }
        iterator end(){
            return (iterator(_tree.end()));
        }
        const_iterator end() const{
            return (_tree.end());
        }
        reverse_iterator rbegin(){
            return reverse_iterator(iterator(_tree.last()));
        }
        const_reverse_iterator rbegin() const{
            return const_reverse_iterator(const_iterator(_tree.last()));
        }
        reverse_iterator rend(){
            return reverse_iterator((iterator(_tree.end())));
        }
        const_reverse_iterator rend() const{
            return const_reverse_iterator((const_iterator(_tree.end())));
        }
// ? ***************************************************************************
// ? *                       capacity:                                         *
// ? ***************************************************************************
        bool empty() const{
            return (size() == 0);
        }
        size_type size() const{
            return _tree.size();
        }
        size_type max_size() const{
                return _all_node.max_size();
        }
// ? ***************************************************************************
// ? *                       element access:                                   *
// ? ***************************************************************************
        T& operator[](const key_type& x){
            node<value_type> *tmp = _tree.search(x);
            if (tmp->nil){
                _tree.insert(ft::make_pair(x, mapped_type()), 0);
                tmp = _tree.search(x);
            }
            return tmp->key_value.second;
                
        }
// ? ***************************************************************************
// ? *                       modifiers:                                        *
// ? ***************************************************************************
        pair<iterator, bool> insert(const value_type& x){
            node<value_type> *tmp = _tree.search(x.first);
            bool not_finded = 0;
            if (tmp->nil){
                _tree.insert(x, 0);
                tmp = _tree.search(x.first);
                not_finded = 1;
            }
            return pair<iterator, bool>(iterator(tmp), not_finded);
            // return ft::make_pair( )  
        }

        iterator insert(iterator position, const value_type& x){
            node<value_type> *tmp = _tree.search(x.first);
            key_type z = x.first;
            if (tmp->nil){
                _tree.insert(position.base(), x);                    
            }
            return iterator(_tree.search(z));
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last){
            for (; first != last; first++)
                insert(ft::make_pair(first->first, first->second));
        }

        void erase(iterator position){
            _tree.rb_delete(position.base());
        }

        size_type erase(const key_type& x){
            node<value_type> *tmp = _tree.search(x);
            if (tmp->nil == 0)
            {
                _tree.rb_delete(tmp);
                return 1;
            }
            return 0;
        }

        void erase(iterator first, iterator last){
            for (; first != last; first++)
                _tree.rb_delete(first.base());
        }

        void swap(map<Key,T,Compare,Allocator>&x){
            std::swap(*this, x);
        }

        void clear(){
            _tree.clear();
        }
// ? ***************************************************************************
// ? *                       observers:                                        *
// ? ***************************************************************************
        key_compare key_comp() const{
            return _cmp;
        }

        value_compare value_comp() const{
            return value_compare(key_comp());
        }
// ? ***************************************************************************
// ? *                       map operations:                                   *
// ? ***************************************************************************
        iterator find(const key_type& x){
            key_type z = x;
            node<value_type> *tmp = _tree.search(z);
            if (tmp->nil)
                return iterator();
            return iterator(tmp);
        }

        const_iterator find(const key_type& x) const
        {
            key_type z = x;
            return const_iterator(_tree.search(z));
        }

        size_type count(const key_type& x) const{
            key_type z = x;
            node<value_type> *tmp = _tree.search(z);
            if (tmp->nil)
                return 0;
            return 1;
        }

        iterator lower_bound(const key_type& x){
            iterator last = end();
            for (iterator first = begin(); first != last; ++first){
                if (first->first >= x)
                    return first;
            }
            return (last);
        }

        const_iterator lower_bound(const key_type& x) const{
            iterator last = end();
            for (iterator first = begin(); first != last; ++first){
                if (first->first >= x)
                    return const_iterator(first);
            }
            return const_iterator(last);
        }

        iterator upper_bound(const key_type& x){
            iterator last = end();
            for (iterator first = begin(); first != last; ++first){
                if (first->first > x)
                    return first;
            }
            return (last);
        }

        const_iterator upper_bound(const key_type& x) const{
            iterator last = end();
            for (iterator first = begin(); first != last; ++first){
                if (first->first > x)
                    return const_iterator(first);
            }
            return const_iterator(last);
        }

        pair<iterator,iterator>
            equal_range(const key_type& x){
                return (ft::make_pair(lower_bound(x), upper_bound(x)));
            }

        pair<const_iterator,const_iterator>
            equal_range(const key_type& x) const{
                return (ft::make_pair(lower_bound(x), upper_bound(x)));
            }

    template<class _Key, class _T, class _Compare, class _Alloc>
    friend bool operator==(const map<_Key, _T, _Compare, _Alloc> &x, const map& y){
        return (x._tree == y._tree);
    }

    template<class _Key, class _T, class _Compare, class _Alloc>
    friend bool operator<(const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y){
         return (x._tree < y._tree);
     }

    template<class _Key, class _T, class _Compare, class _Alloc>
    friend bool operator!=(const map<_Key, _T, _Compare, _Alloc> &x,
    const map<_Key, _T, _Compare, _Alloc> &y);

    template<class _Key, class _T, class _Compare, class _Alloc>
    friend bool operator> (const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y);

    template<class _Key, class _T, class _Compare, class _Alloc>
    friend bool operator>=(const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y);

    template<class _Key, class _T, class _Compare, class _Alloc>
    friend bool operator<=(const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y);

    };
        // void test(){ 
        //     _tree.printTree();
        // }

// ? ***************************************************************************
// ? *                       specialized algorithms:                           *
// ? ***************************************************************************


    template<class _Key, class _T, class _Compare, class _Alloc>
    bool operator!=(const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y)
    {
        return !(x == y);
    }

    template<class _Key, class _T, class _Compare, class _Alloc>
    bool operator> (const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y)
    {
        if (x == y)
            return false;
        return !(x < y);
    }

    template<class _Key, class _T, class _Compare, class _Alloc>
    bool operator>=(const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y)
    {
        return !(x < y);
    }

    template<class _Key, class _T, class _Compare, class _Alloc>
    bool operator<=(const map<_Key, _T, _Compare, _Alloc> &x,
     const map<_Key, _T, _Compare, _Alloc> &y)
    {
        return !(x > y);
    }

    template <class Key, class T, class Compare, class Allocator>
    void swap(map<Key,T,Compare,Allocator>& x,
            map<Key,T,Compare,Allocator>& y);
}

#endif