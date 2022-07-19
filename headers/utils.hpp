#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
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
        }
}

#endif