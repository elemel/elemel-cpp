#ifndef ELEMEL_CONST_STRING_HPP
#define ELEMEL_CONST_STRING_HPP

#include <elemel/raw_allocator.hpp>
#include <elemel/ref_ptr.hpp>
#include <elemel/string_range.hpp>
#include <elemel/detail/string_impl.hpp>

#include <cassert>
#include <string>

namespace elemel {
    enum by_ref_tag { by_ref };

    template <
        class Char,
        class Traits = std::char_traits<Char>,
        class RefCount = long,
        class RawAllocator = raw_new_allocator
    >
    class basic_const_string {
    public:
        typedef Char value_type;
        typedef Traits traits_type;
        typedef RefCount ref_count_type;
        typedef RawAllocator raw_allocator_type;
        typedef detail::string_impl<value_type, ref_count_type, raw_allocator_type>
            impl_type;
        typedef basic_string_range<value_type, traits_type> range_type;
        typedef std::size_t size_type;
        typedef value_type const *const_pointer;
        typedef value_type const *const_iterator;

        explicit basic_const_string(by_ref_tag = by_ref) :
            range_(range_type(0, 0))
        { }

        explicit basic_const_string(const_pointer str,
                                    raw_allocator_type const &alloc =
                                    raw_allocator_type()) :
            impl_(impl_type::create(str, traits_type::length(str), alloc)),
            range_(impl_->data(), impl_->data() + impl_->size())
        { }

        basic_const_string(const_pointer str, size_type n,
                           raw_allocator_type const &alloc =
                           raw_allocator_type()) :
            impl_(impl_type::create(str, n, alloc)),
            range_(impl_->data(), impl_->data() + impl_->size())
        { }

        basic_const_string(const_pointer first, const_pointer last,
                           raw_allocator_type const &alloc =
                           raw_allocator_type()) :
            impl_(impl_type::create(first, last - first, alloc)),
            range_(impl_->data(), impl_->data() + impl_->size())
        { }

        basic_const_string(const_pointer str, by_ref_tag) :
            range_(str, traits_type::length(str))
        { }

        basic_const_string(const_pointer str, size_type n, by_ref_tag) :
            range_(str, n)
        { }

        basic_const_string(const_pointer first, const_pointer last, by_ref_tag)
            : range_(first, last - first)
        { }

        const_pointer data() const
        {
            return range_.data();
        }

        size_type size() const
        {
            return range_.size();
        }

        bool empty() const
        {
            return range_.empty();
        }

        const_iterator begin() const
        {
            return range_.begin();
        }

        const_iterator end() const
        {
            return range_.end();
        }

    private:
        ref_ptr<impl_type> impl_;
        range_type range_;
    };

    template <class C, class T, class N, class A>
    bool operator==(basic_const_string<C, T, N, A> const &left,
                    basic_const_string<C, T, N, A> const &right)
    {
        return (left.size() == right.size() &&
                std::equal(left.begin(), left.end(), right.begin(), T::eq));
    }

    template <class C, class T, class N, class A>
    bool operator!=(basic_const_string<C, T, N, A> const &left,
                    basic_const_string<C, T, N, A> const &right)
    {
        return !(left == right);
    }

    template <class C, class T, class N, class A>
    bool operator<(basic_const_string<C, T, N, A> const &left,
                   basic_const_string<C, T, N, A> const &right)
    {
        return std::lexicographical_compare(left.begin(), left.end(),
                                            right.begin(), right.end(), T::lt);
    }

    template <class C, class T, class N, class A>
    bool operator<=(basic_const_string<C, T, N, A> const &left,
                    basic_const_string<C, T, N, A> const &right)
    {
        return !(right < left);
    }

    template <class C, class T, class N, class A>
    bool operator>=(basic_const_string<C, T, N, A> const &left,
                    basic_const_string<C, T, N, A> const &right)
    {
        return !(left < right);
    }

    template <class C, class T, class N, class A>
    bool operator>(basic_const_string<C, T, N, A> const &left,
                   basic_const_string<C, T, N, A> const &right)
    {
        return right < left;
    }

    template <class C, class T, class N, class A>
    bool operator==(basic_const_string<C, T, N, A> const &left, C const *right)
    {
        assert(right);
        std::size_t n = T::length(right);
        return left.size() == n && std::equal(left.begin(), left.end(), right);
    }

    template <class C, class T, class N, class A>
    bool operator!=(basic_const_string<C, T, N, A> const &left, C const *right)
    {
        return !(left == right);
    }

    template <class C, class T, class N, class A>
    bool operator<(basic_const_string<C, T, N, A> const &left, C const *right)
    {
        assert(right);
        return std::lexicographical_compare(left.begin(), left.end(),
                                            right, right + T::length(right),
                                            T::lt);
    }

    template <class C, class T, class N, class A>
    bool operator<=(basic_const_string<C, T, N, A> const &left, C const *right)
    {
        return !(right < left);
    }

    template <class C, class T, class N, class A>
    bool operator>=(basic_const_string<C, T, N, A> const &left, C const *right)
    {
        return !(left < right);
    }

    template <class C, class T, class N, class A>
    bool operator>(basic_const_string<C, T, N, A> const &left, C const *right)
    {
        return right < left;
    }

    template <class C, class T, class N, class A>
    bool operator==(C const *left, basic_const_string<C, T, N, A> const &right)
    {
        assert(left);
        std::size_t n = T::length(left);
        return n == right.size() && std::equal(left, left + n, right.begin());
    }

    template <class C, class T, class N, class A>
    bool operator!=(C const *left, basic_const_string<C, T, N, A> const &right)
    {
        return !(left == right);
    }

    template <class C, class T, class N, class A>
    bool operator<(C const *left, basic_const_string<C, T, N, A> const &right)
    {
        assert(left);
        return std::lexicographical_compare(left, left + T::length(left),
                                            right.begin(), right.end(),
                                            T::lt);
    }

    template <class C, class T, class N, class A>
    bool operator<=(C const *left, basic_const_string<C, T, N, A> const &right)
    {
        return !(right < left);
    }

    template <class C, class T, class N, class A>
    bool operator>=(C const *left, basic_const_string<C, T, N, A> const &right)
    {
        return !(left < right);
    }

    template <class C, class T, class N, class A>
    bool operator>(C const *left, basic_const_string<C, T, N, A> const &right)
    {
        return right < left;
    }

    typedef basic_const_string<char> const_string;
    typedef basic_const_string<wchar_t> const_wstring;
}

#endif // ELEMEL_CONST_STRING_HPP
