#ifndef ELEMEL_COPYING_VECTOR_HPP
#define ELEMEL_COPYING_VECTOR_HPP

// Copyright (C) 2011 by Mikael Lind
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include <cassert>
#include <iterator>
#include <stdexcept>

namespace elemel {
    template <class T, class Allocator = std::allocator<T> >
    class copying_vector {
    public:
        typedef T value_type;
        typedef Allocator allocator_type;

        typedef value_type *pointer;
        typedef value_type const *const_pointer;
        typedef value_type &reference;
        typedef value_type const &const_reference;
        typedef value_type *iterator;
        typedef value_type const *const_iterator;
        typedef std::reverse_iterator<value_type *> reverse_iterator;
        typedef std::reverse_iterator<value_type const *> const_reverse_iterator;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        explicit copying_vector(allocator_type const &allocator = allocator_type()) :
            begin_(0),
            end_(0),
            capacity_(0),
            allocator_(allocator)
        { }

        explicit copying_vector(size_type n,
                                value_type const &value = value_type(),
                                allocator_type const &allocator = allocator_type()) :
            begin_(0),
            end_(0),
            capacity_(0),
            allocator_(allocator)
        {
            copying_vector temp(allocator_);
            temp.resize(n, value);
            swap(temp);
        }

        copying_vector(copying_vector const &other) :
            begin_(0),
            end_(0),
            capacity_(0),
            allocator_(other.allocator_)
        {
            copying_vector temp(allocator_);
            temp.reserve(other.size());
            temp.insert(temp.end_, other.begin_, other.end_);
            swap(temp);
        }

        // Exception safety: No-throw guarantee.
        ~copying_vector()
        {
            if (begin_) {
                clear();
                allocator_.deallocate(begin_, capacity());
            }
        }

        // Exception safety: Basic guarantee.
        copying_vector &operator=(copying_vector const &other)
        {
            if (capacity() < other.size()) {
                copying_vector temp(other);
                swap(temp);
            } else {
                clear();
                insert(end_, other.begin_, other.end_);
            }
        }

        // Exception safety: No-throw guarantee.
        iterator begin()
        {
            return begin_;
        }

        // Exception safety: No-throw guarantee.
        iterator end()
        {
            return end_;
        }

        // Exception safety: No-throw guarantee.
        const_iterator begin() const
        {
            return begin_;
        }

        // Exception safety: No-throw guarantee.
        const_iterator end() const
        {
            return end_;
        }

        // Exception safety: No-throw guarantee.
        reverse_iterator rbegin()
        {
            return reverse_iterator(end_);
        }

        // Exception safety: No-throw guarantee.
        reverse_iterator rend()
        {
            return reverse_iterator(begin_);
        }

        // Exception safety: No-throw guarantee.
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end_);
        }

        // Exception safety: No-throw guarantee.
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin_);
        }

        // Exception safety: No-throw guarantee.
        size_type size() const
        {
            return end_ - begin_;
        }

        // Exception safety: No-throw guarantee.
        size_type max_size() const
        {
            return std::numeric_limits<size_type>::max() / sizeof(value_type);
        }

        // Exception safety: Basic guarantee.
        void resize(size_type n, value_type const &value)
        {
            if (size() < n) {
                reserve(n);
                do {
                    allocator_.construct(end_, value);
                    ++end_;
                } while (size() < n);
            } else if (size() > n) {
                do {
                    allocator_.destroy(--end_);
                } while (size() > n);
            }
        }

        // Exception safety: No-throw guarantee.
        size_type capacity() const
        {
            return capacity_ - begin_;
        }

        // Exception safety: No-throw guarantee.
        bool empty() const
        {
            return begin_ == end_;
        }

        // Exception safety: Strong guarantee.
        void reserve(size_type n)
        {
            if (capacity() < n) {
                if (begin_) {
                    copying_vector temp(allocator_);
                    temp.reserve(n);
                    temp.insert(temp.end_, begin_, end_);
                    swap(temp);
                } else {
                    begin_ = end_ = allocator_.allocate(n, 0);
                    capacity_ = begin_ + n;
                }
            }
        }

        // Exception safety: Strong guarantee.
        void push_back(value_type const &value)
        {
            auto_reserve(size() + 1);
            allocator_.construct(end_, value);
            ++end_;
        }

        // Exception safety: No-throw guarantee.
        void pop_back()
        {
            assert(!empty());
            allocator_.destroy(--end_);
        }

        // Exception safety: No-throw guarantee.
        void clear()
        {
            while (!empty()) {
                allocator_.destroy(--end_);
            }
        }

        reference front()
        {
            assert(!empty());
            return *begin_;
        }

        const_reference front() const
        {
            assert(!empty());
            return *begin_;
        }

        reference back()
        {
            assert(!empty());
            return *(end_ - 1);
        }

        const_reference back() const
        {
            assert(!empty());
            return *(end_ - 1);
        }

        // Exception safety: Strong guarantee.
        reference at(size_type index)
        {
            if (index < size()) {
                return *(begin_ + index);
            } else {
                throw std::out_of_range("index out of range");
            }
        }

        // Exception safety: Strong guarantee.
        const_reference at(size_type index) const
        {
            if (index < size()) {
                return *(begin_ + index);
            } else {
                throw std::out_of_range("index out of range");
            }
        }

        // Exception safety: No-throw guarantee.
        reference operator[](size_type index)
        {
            assert(index < size());
            return *(begin_ + index);
        }

        // Exception safety: No-throw guarantee.
        const_reference operator[](size_type index) const
        {
            assert(index < size());
            return *(begin_ + index);
        }

        // Exception safety: Basic guarantee.
        iterator insert(iterator position, value_type const &value)
        {
            if (position == end_) {
                push_back(value);
                return end_ - 1;
            } else if (size() == capacity()) {
                copying_vector temp(allocator_);
                temp.auto_reserve(size() + 1);
                temp.insert(temp.end_, begin_, position);
                temp.push_back(value);
                temp.insert(temp.end_, position, end_);
                swap(temp);
                return begin_ + (position - temp.begin_);
            } else {
                iterator j = end_;
                try {
                    do {
                        allocator_.construct(j, *(j - 1));
                        allocator_.destroy(--j);
                    } while (j != position);
                    allocator_.construct(position, value);
                } catch (...) {
                    while (end_ != j) {
                        allocator_.destroy(end_);
                        --end_;
                    }
                    throw;
                }
                ++end_;
                return position;
            }
        }

        // Exception safety: Basic guarantee.
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            difference_type diff = std::distance(first, last);
            if (size() + diff > capacity()) {
                copying_vector temp(allocator_);
                temp.auto_reserve(size() + diff);
                temp.insert(temp.end_, begin_, position);
                temp.insert(temp.end_, first, last);
                temp.insert(temp.end_, position, end_);
                swap(temp);
            } else if (position == end_) {
                for (iterator i = first; i != last; ++i) {
                    allocator_.construct(end_, *i);
                    ++end_;
                }
            } else {
                assert(false);
            }
        };

        // Exception safety: No-throw guarantee.
        void swap(copying_vector &other)
        {
            std::swap(begin_, other.begin_);
            std::swap(end_, other.end_);
            std::swap(capacity_, other.capacity_);
            std::swap(allocator_, other.allocator_);
        }

        // Exception safety: No-throw guarantee.
        allocator_type get_allocator() const
        {
            return allocator_;
        }

    private:
        value_type *begin_;
        value_type *end_;
        value_type *capacity_;
        allocator_type allocator_;

        void auto_reserve(size_type n)
        {
            size_type m = capacity();
            if (m < n) {
                do {
                    // Grow by Golden Ratio.
                    m = m * 233 / 144 + 1;
                } while (m < n);
                reserve(m);
            }
        }
    };
}

namespace std {
    template <class T, class Allocator>
    void swap(elemel::copying_vector<T, Allocator> &first,
              elemel::copying_vector<T, Allocator> &second)
    {
        first.swap(second);
    }
}

#endif // ELEMEL_COPYING_VECTOR_HPP
