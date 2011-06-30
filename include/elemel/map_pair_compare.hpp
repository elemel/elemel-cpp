#ifndef ELEMEL_MAP_PAIR_COMPARE_HPP
#define ELEMEL_MAP_PAIR_COMPARE_HPP

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

#include <functional>

namespace elemel {
    template <class Key, class Compare>
    class map_pair_compare {
    public:
        explicit map_pair_compare(Compare const &comp = Compare()) :
            comp_(comp)
        { }

        template <typename Left, typename Right>
        bool operator()(Left const &left, Right const &right) const
        {
            return comp_(get_key(left), get_key(right));
        }

    private:
        Compare comp_;

        Key const &get_key(Key const &key) const
        {
            return key;
        }

        template <typename Data>
        Key const &get_key(std::pair<Key, Data> const &value) const
        {
            return value.first;
        }

        template <typename Data>
        Key const &get_key(std::pair<Key const, Data> const &value) const
        {
            return value.first;
        }
    };
}

#endif // ELEMEL_MAP_PAIR_COMPARE_HPP
