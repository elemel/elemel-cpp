#ifndef ELEMEL_STRING_PTR_HPP
#define ELEMEL_STRING_PTR_HPP

#include <elemel/find_terminator.hpp>
#include <elemel/raw_allocator.hpp>
#include <elemel/ref_ptr.hpp>

#include <algorithm>
#include <cassert>

namespace elemel {
    namespace detail {
        template <class T, class RefCount, class RawAllocator>
        class string_header {
        public:
            typedef T value_type;
            typedef std::size_t size_type;
            typedef RefCount ref_count_type;
            typedef RawAllocator raw_allocator_type;
    
            static ref_ptr<string_header>
            create(value_type const *str, size_type n,
                   raw_allocator_type const &alloc)
            {
                size_type alloc_n = (sizeof(string_header) +
                                     sizeof(value_type) * (n + 1));
                string_header *p =
                    reinterpret_cast<string_header *>(alloc.allocate(alloc_n));
                return ref_ptr<string_header>(new (p)
                                              string_header(str, n, alloc));
            }
    
            void add_ref()
            {
                ++ref_count_;
            }
    
            void release()
            {
                if (--ref_count_ == 0) {
                    raw_allocator_type alloc(alloc_);
                    this->~string_header();
                    alloc.deallocate(reinterpret_cast<void *>(this));
                }
            }
    
            size_type size()
            {
                return size_;
            }
    
            value_type *data()
            {
                return reinterpret_cast<value_type *>(reinterpret_cast<unsigned char *>(this) +
                                                      sizeof(string_header));
            }
    
        private:
            size_type size_;
            raw_allocator_type alloc_;
            ref_count_type ref_count_;
    
            string_header(value_type const *str, size_type n,
                          raw_allocator_type const &alloc) :
                size_(n),
                alloc_(alloc),
                ref_count_(0)
            {
                std::copy(str, str + n, data());
                data()[n] = value_type(0);
            }
        };
    }

    template <
        class T,
        class RefCount = int,
        class RawAllocator = raw_new_allocator
    >
    class basic_string_ptr {
    public:
        typedef T value_type;
        typedef RefCount ref_count_type;
        typedef RawAllocator raw_allocator_type;
        typedef detail::string_header<value_type, ref_count_type, raw_allocator_type>
            header_type;
        typedef std::size_t size_type;
        typedef value_type *const_iterator;

        basic_string_ptr()
        { }

        explicit basic_string_ptr(raw_allocator_type const &alloc =
                                  raw_allocator_type())
        {
            header_ = header_type::create(0, 0, alloc);
        }

        explicit basic_string_ptr(value_type const *str,
                                  raw_allocator_type const &alloc =
                                  raw_allocator_type())
        {
            assert(str);
            size_type n = find_terminator(str) - str;
            header_ = header_type::create(str, n, alloc);
        }

        basic_string_ptr(value_type const *str, size_type n,
                         raw_allocator_type const &alloc =
                         raw_allocator_type())
        {
            assert(str);
            header_ = header_type::create(str, n, alloc);
        }

        size_type size() const
        {
            return header_ ? header_->size() : 0;
        }

        value_type const *data() const
        {
            return header_ ? header_->data() : 0;
        }

        value_type const *c_str() const
        {
            if (header_.get() == 0) {
                header_ = header_type::create(0, 0, raw_allocator_type());
            }
            return header_->data();
        }

        const_iterator begin() const
        {
            return header_ ? header_->data() : 0;
        }

        const_iterator end() const
        {
            return header_ ? header_->data() + header_->size() : 0;
        }

    private:
        mutable ref_ptr<header_type> header_;
    };

    template <class T, class C, class A>
    bool operator==(basic_string_ptr<T, C, A> const &left,
                    basic_string_ptr<T, C, A> const &right)
    {
        return (left.size() == right.size() &&
                std::equal(left.begin(), left.end(), right.begin()));
    }

    template <class T, class C, class A>
    bool operator!=(basic_string_ptr<T, C, A> const &left,
                    basic_string_ptr<T, C, A> const &right)
    {
        return !(left == right);
    }

    template <class T, class C, class A>
    bool operator==(basic_string_ptr<T, C, A> const &left, T const *right)
    {
        std::size_t n = find_terminator(right) - right;
        return left.size() == n && std::equal(left.begin(), left.end(), right);
    }

    template <class T, class C, class A>
    bool operator!=(basic_string_ptr<T, C, A> const &left, T const *right)
    {
        return !(left == right);
    }

    template <class T, class C, class A>
    bool operator==(T const *left, basic_string_ptr<T, C, A> const &right)
    {
        std::size_t n = find_terminator(left) - left;
        return n == right.size() && std::equal(left, left + n, right.begin());
    }

    template <class T, class C, class A>
    bool operator!=(T const *left, basic_string_ptr<T, C, A> const &right)
    {
        return !(left == right);
    }

    typedef basic_string_ptr<char> string_ptr;
    typedef basic_string_ptr<wchar_t> wstring_ptr;
}

#endif // ELEMEL_STRING_PTR_HPP