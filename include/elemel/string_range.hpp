#ifndef ELEMEL_STRING_RANGE_HPP
#define ELEMEL_STRING_RANGE_HPP

#include <elemel/find_terminator.hpp>

#include <algorithm>
#include <string>

namespace elemel {
    template <class T, class Traits = std::char_traits<T> >
    class basic_string_range {
    public:
        typedef T value_type;
        typedef Traits traits_type;
        typedef std::size_t size_type;
        typedef value_type const *const_pointer;
        typedef value_type const *const_iterator;

        basic_string_range() :
            first_(0),
            last_(0)
        { }

        basic_string_range(const_pointer str) :
            first_(str),
            last_(find_terminator(str))
        { }

        basic_string_range(const_pointer first, const_pointer last) :
            first_(first),
            last_(last)
        { }

        size_type size() const
        {
            return last_ - first_;
        }

        const_pointer data() const
        {
            return first_;
        }

        const_iterator begin() const
        {
            return first_;
        }

        const_iterator end() const
        {
            return last_;
        }

    private:
        const_pointer first_;
        const_pointer last_;
    };

    template <class T, class Traits>
    bool operator==(basic_string_range<T, Traits> const &left,
                    basic_string_range<T, Traits> const &right)
    {
        return (left.size() == right.size() &&
                std::equal(left.begin(), left.end(), right.begin(),
                           Traits::eq));
    }

    template <class T, class Traits>
    bool operator!=(basic_string_range<T, Traits> const &left,
                    basic_string_range<T, Traits> const &right)
    {
        return !(left == right);
    }

    template <class T, class Traits>
    bool operator<(basic_string_range<T, Traits> const &left,
                   basic_string_range<T, Traits> const &right)
    {
        return std::lexicographical_compare(left.begin(), left.end(),
                                            right.begin(), right.end(),
                                            Traits::lt);
    }

    template <class T, class Traits>
    bool operator<=(basic_string_range<T, Traits> const &left,
                    basic_string_range<T, Traits> const &right)
    {
        return !(right < left);
    }

    template <class T, class Traits>
    bool operator>=(basic_string_range<T, Traits> const &left,
                    basic_string_range<T, Traits> const &right)
    {
        return !(left < right);
    }

    template <class T, class Traits>
    bool operator>(basic_string_range<T, Traits> const &left,
                   basic_string_range<T, Traits> const &right)
    {
        return right < left;
    }

    template <class T, class Traits>
    bool operator==(basic_string_range<T, Traits> const &left, T const *right)
    {
        return left == basic_string_range<T, Traits>(right);
    }

    template <class T, class Traits>
    bool operator!=(basic_string_range<T, Traits> const &left, T const *right)
    {
        return !(left == right);
    }

    template <class T, class Traits>
    bool operator<(basic_string_range<T, Traits> const &left, T const *right)
    {
        return left < basic_string_range<T, Traits>(right);
    }

    template <class T, class Traits>
    bool operator<=(basic_string_range<T, Traits> const &left, T const *right)
    {
        return !(right < left);
    }

    template <class T, class Traits>
    bool operator>=(basic_string_range<T, Traits> const &left, T const *right)
    {
        return !(left < right);
    }

    template <class T, class Traits>
    bool operator>(basic_string_range<T, Traits> const &left, T const *right)
    {
        return right < left;
    }

    template <class T, class Traits>
    bool operator==(T const *left, basic_string_range<T, Traits> const &right)
    {
        return basic_string_range<T, Traits>(left) == right;
    }

    template <class T, class Traits>
    bool operator!=(T const *left, basic_string_range<T, Traits> const &right)
    {
        return !(left == right);
    }

    template <class T, class Traits>
    bool operator<(T const *left, basic_string_range<T, Traits> const &right)
    {
        return basic_string_range<T, Traits>(left) < right;
    }

    template <class T, class Traits>
    bool operator<=(T const *left, basic_string_range<T, Traits> const &right)
    {
        return !(right < left);
    }

    template <class T, class Traits>
    bool operator>=(T const *left, basic_string_range<T, Traits> const &right)
    {
        return !(left < right);
    }

    template <class T, class Traits>
    bool operator>(T const *left, basic_string_range<T, Traits> const &right)
    {
        return right < left;
    }

    typedef basic_string_range<char> string_range;
    typedef basic_string_range<wchar_t> wstring_range;
}

#endif // ELEMEL_STRING_RANGE_HPP
