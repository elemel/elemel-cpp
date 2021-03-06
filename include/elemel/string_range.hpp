#ifndef ELEMEL_STRING_RANGE_HPP
#define ELEMEL_STRING_RANGE_HPP

#include <algorithm>
#include <stdexcept>
#include <string>

namespace elemel {
    template <class Char, class Traits = std::char_traits<Char> >
    class basic_string_range {
    public:
        typedef Char value_type;
        typedef Traits traits_type;
        typedef std::size_t size_type;
        typedef value_type const *const_pointer;
        typedef value_type const &const_reference;
        typedef value_type const *const_iterator;

        basic_string_range() :
            first_(0),
            last_(0)
        { }

        basic_string_range(const_pointer str) :
            first_(str),
            last_(str + Traits::length(str))
        { }

        basic_string_range(const_pointer str, size_type n) :
            first_(str),
            last_(str + n)
        { }

        basic_string_range(const_pointer first, const_pointer last) :
            first_(first),
            last_(last)
        { }

        const_pointer data() const
        {
            return first_;
        }

        size_type size() const
        {
            return last_ - first_;
        }

        bool empty() const
        {
            return first_ != last_;
        }

        const_iterator begin() const
        {
            return first_;
        }

        const_iterator end() const
        {
            return last_;
        }

        const_reference front() const
        {
            assert(!empty());
            return *first_;
        }

        const_reference back() const
        {
            assert(!empty());
            return *(last_ - 1);
        }

        const_reference operator[](size_type index) const
        {
            assert(index < size());
            return first_[index];
        }

        const_reference at(size_type index) const
        {
            if (index >= size()) {
                throw std::out_of_range("index out of range");
            }
            return first_[index];
        }

    private:
        const_pointer first_;
        const_pointer last_;
    };

    template <class C, class T>
    bool operator==(basic_string_range<C, T> const &left,
                    basic_string_range<C, T> const &right)
    {
        return (left.size() == right.size() &&
                std::equal(left.begin(), left.end(), right.begin(), T::eq));
    }

    template <class C, class T>
    bool operator!=(basic_string_range<C, T> const &left,
                    basic_string_range<C, T> const &right)
    {
        return !(left == right);
    }

    template <class C, class T>
    bool operator<(basic_string_range<C, T> const &left,
                   basic_string_range<C, T> const &right)
    {
        return std::lexicographical_compare(left.begin(), left.end(),
                                            right.begin(), right.end(), T::lt);
    }

    template <class C, class T>
    bool operator<=(basic_string_range<C, T> const &left,
                    basic_string_range<C, T> const &right)
    {
        return !(right < left);
    }

    template <class C, class T>
    bool operator>=(basic_string_range<C, T> const &left,
                    basic_string_range<C, T> const &right)
    {
        return !(left < right);
    }

    template <class C, class T>
    bool operator>(basic_string_range<C, T> const &left,
                   basic_string_range<C, T> const &right)
    {
        return right < left;
    }

    template <class C, class T>
    bool operator==(basic_string_range<C, T> const &left, C const *right)
    {
        return left == basic_string_range<C, T>(right);
    }

    template <class C, class T>
    bool operator!=(basic_string_range<C, T> const &left, C const *right)
    {
        return !(left == right);
    }

    template <class C, class T>
    bool operator<(basic_string_range<C, T> const &left, C const *right)
    {
        return left < basic_string_range<C, T>(right);
    }

    template <class C, class T>
    bool operator<=(basic_string_range<C, T> const &left, C const *right)
    {
        return !(right < left);
    }

    template <class C, class T>
    bool operator>=(basic_string_range<C, T> const &left, C const *right)
    {
        return !(left < right);
    }

    template <class C, class T>
    bool operator>(basic_string_range<C, T> const &left, C const *right)
    {
        return right < left;
    }

    template <class C, class T>
    bool operator==(C const *left, basic_string_range<C, T> const &right)
    {
        return basic_string_range<C, T>(left) == right;
    }

    template <class C, class T>
    bool operator!=(C const *left, basic_string_range<C, T> const &right)
    {
        return !(left == right);
    }

    template <class C, class T>
    bool operator<(C const *left, basic_string_range<C, T> const &right)
    {
        return basic_string_range<C, T>(left) < right;
    }

    template <class C, class T>
    bool operator<=(C const *left, basic_string_range<C, T> const &right)
    {
        return !(right < left);
    }

    template <class C, class T>
    bool operator>=(C const *left, basic_string_range<C, T> const &right)
    {
        return !(left < right);
    }

    template <class C, class T>
    bool operator>(C const *left, basic_string_range<C, T> const &right)
    {
        return right < left;
    }

    typedef basic_string_range<char> string_range;
    typedef basic_string_range<wchar_t> wstring_range;
}

#endif // ELEMEL_STRING_RANGE_HPP
