#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "vector.hpp"
namespace ft {
    template <bool B, class T = void>
    struct enable_if{};

    template<class T>
    struct enable_if<true, T>{
        typedef T type;
    };

//is_integral
    template <class T, bool v>
        struct integral_constant {
            static const bool value = v;
            typedef T value_type;
            typedef integral_constant type;
            operator value_type() const
            {
                return value;
            }
    };

    template <class T>
        struct is_integral: public ft::integral_constant<T, false> {};
    template <>
        struct is_integral<bool>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<char>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<signed char>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<unsigned char>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<wchar_t>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<char16_t>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<short>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<unsigned short>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<int>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<unsigned int>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<long>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<unsigned long>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<long long>: public ft::integral_constant<bool, true> {};
    template <>
        struct is_integral<unsigned long long>: public ft::integral_constant<bool, true> {};

    template<class InputIterator1, class InputIterator2>
        bool
        lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2){
        for (; first1 != last1 && first2 != last2 && !(*first1 < *first2) && !(*first2 < *first1);
        ++first1, ++first2);
        return first2 == last2 ? false : first1 == last1 || *first1 < *first2;
        };

    template <class T1, class T2>
        struct pair {
            typedef T1 first_type;
            typedef T2 second_type;
            T1 first;
            T2 second;
            pair(): first(T1()), second(T2()) {}
            pair(const T1& x, const T2& y): first(x), second(y) {}
            template<class U, class V>
                pair(const pair<U, V> &p): first(p.first), second(p.second) {}
            };

            template <class T1, class T2>
                bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y){
                    return x.first == y.first && x.second == y.second;
                }
            template <class T1, class T2>
                bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y){
                    return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
                    }
            template <class T1, class T2>
                pair<T1, T2> make_pair(const T1& x, const T2& y){
                    return pair<T1, T2>(x, y);
                    }
        }

#endif