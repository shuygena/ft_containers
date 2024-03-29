#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "vector.hpp"
// #include <vector>

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef typename Container::value_type value_type;
            typedef typename Container::size_type size_type;
            typedef Container container_type;

        protected:
            Container c;
        
        public:
// ***************************************************************************
// *                       construct/copy/destroy:                           *
// ***************************************************************************
            explicit stack( const Container& cont = Container() ): c(cont){}
// ***************************************************************************
// *                       capacity:                                         *
// ***************************************************************************
            bool                empty() const               { return c.empty(); }
            size_type           size() const                { return c.size(); }
// ***************************************************************************
// *                       element access:                                   *
// ***************************************************************************
            value_type&         top()                       { return c.back(); }
            const value_type&   top() const                 { return c.back(); }
// ***************************************************************************
// *                       modifiers:                                        *
// ***************************************************************************
            void                push(const value_type& x)   { c.push_back(x); }
            void                pop()                       { c.pop_back(); }

            template <class T1, class Cnt>
                friend bool operator==(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y);
            template <class T1, class Cnt>
                friend bool operator< (const stack<T1, Cnt>& x, const stack<T1, Cnt>& y);
            template <class T1, class Cnt>
                friend bool operator!=(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y);
            template <class T1, class Cnt>
                friend bool operator> (const stack<T1, Cnt>& x, const stack<T1, Cnt>& y);
            template <class T1, class Cnt>
                friend bool operator>=(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y);
            template <class T1, class Cnt>
                friend bool operator<=(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y);
    };
    template <class T1, class Cnt>
        bool operator==(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y)
    {
        return (x.c == y.c);
    }

    template <class T1, class Cnt>
        bool operator< (const stack<T1, Cnt>& x, const stack<T1, Cnt>& y)
    {
        return (x.c < y.c);
    }

    template <class T1, class Cnt>
        bool operator!=(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y)
    {
        return (x.c != y.c);
    }

    template <class T1, class Cnt>
        bool operator> (const stack<T1, Cnt>& x, const stack<T1, Cnt>& y)
    {
        return (x.c > y.c);
    }

    template <class T1, class Cnt>
        bool operator>=(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y)
    {
        return (x.c >= y.c);
    }
    template <class T1, class Cnt>
        bool operator<=(const stack<T1, Cnt>& x, const stack<T1, Cnt>& y)
    {
        return (x.c <= y.c);
    }
}
#endif