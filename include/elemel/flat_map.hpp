#ifndef ELEMEL_FLAT_MAP_HPP
#define ELEMEL_FLAT_MAP_HPP

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

#include <elemel/binary_find.hpp>
#include <elemel/copying_vector.hpp>
#include <elemel/map_pair_compare.hpp>

namespace elemel {
    template <
        class Key,
        class Data,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<Key, Data> >
    >
    class flat_map {
    public:
        typedef Key key_type;
        typedef Data data_type;
        typedef std::pair<key_type, data_type> value_type;
        typedef Compare key_compare;
        typedef map_pair_compare<Key, key_compare> compare;
        typedef Allocator allocator_type;
        typedef copying_vector<value_type, allocator_type> vector_type;

        typedef typename vector_type::pointer pointer;
        typedef typename vector_type::reference reference;
        typedef typename vector_type::const_reference const_reference;
        typedef typename vector_type::size_type size_type;
        typedef typename vector_type::iterator iterator;
        typedef typename vector_type::const_iterator const_iterator;
        typedef typename vector_type::reverse_iterator reverse_iterator;
        typedef typename vector_type::const_reverse_iterator
            const_reverse_iterator;

        explicit flat_map(key_compare const &comp = key_compare(),
                          allocator_type const &allocator = allocator_type()) :
            comp_(comp),
            values_(allocator)
        { }

        template <class InputIterator>
        flat_map(InputIterator first, InputIterator last,
                 key_compare const &comp = key_compare(),
                 allocator_type const &allocator = allocator_type()) :
            comp_(comp),
            values_(first, last, allocator)
        {
            std::sort(values_.begin(), values_.end(), comp_);
        }

        flat_map &operator=(flat_map const &other)
        {
            comp_ = other.comp_;
            values_ = other.values_;
        }

        iterator begin()
        {
            return values_.begin();
        }

        iterator end()
        {
            return values_.end();
        }

        const_iterator begin() const
        {
            return values_.begin();
        }

        const_iterator end() const
        {
            return values_.end();
        }

        reverse_iterator rbegin()
        {
            return values_.rbegin();
        }

        reverse_iterator rend()
        {
            return values_.rend();
        }
        
        const_reverse_iterator rbegin() const
        {
            return values_.rbegin();
        }

        const_reverse_iterator rend() const
        {
            return values_.rend();
        }

        bool empty() const
        {
            return values_.empty();
        }

        size_type size() const
        {
            return values_.size();
        }

        size_type max_size() const
        {
            return values_.max_size();
        }

        value_type &operator[](key_type const &key)
        {
            return insert(value_type(key, data_type())).first->second;
        }

        std::pair<iterator, bool> insert(value_type const &value)
        {
            std::pair<iterator, iterator> i =
                std::equal_range(values_.begin(), values_.end(), value, comp_);
            if (i.first != i.second) {
                return std::make_pair(i.first, false);
            } else {
                return std::make_pair(values_.insert(i.first, value), true);
            }
        }

        void erase(iterator position)
        {
            values_.erase(position);
        }

        size_type erase(key_type const &key)
        {
            iterator i = find(key);
            if (i != values_.end()) {
                values_.erase(i);
                return 1;
            } else {
                return 0;
            }
        }

        void erase(iterator first, iterator last)
        {
            values_.erase(first, last);
        }

        void swap(flat_map &other)
        {
            std::swap(comp_, other.comp_);
            values_.swap(other.values_);
        }

        void clear()
        {
            values_.clear();
        }

        iterator find(key_type const &key)
        {
            return binary_find(values_.begin(), values_.end(), key, comp_);
        }

        const_iterator find(key_type const &key) const
        {
            return binary_find(values_.begin(), values_.end(), key, comp_);
        }

        allocator_type get_allocator() const
        {
            return values_.get_allocator();
        }

    private:
        compare comp_;
        vector_type values_;
    };
}

namespace std {
    template <class Key, class Data, class Compare, class Allocator>
    void swap(elemel::flat_map<Key, Data, Compare, Allocator> &first,
              elemel::flat_map<Key, Data, Compare, Allocator> &second)
    {
        first.swap(second);
    }
}

#endif // ELEMEL_PROPERTY_MAP_HPP
