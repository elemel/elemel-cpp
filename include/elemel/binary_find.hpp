#ifndef ELEMEL_BINARY_FIND_HPP
#define ELEMEL_BINARY_FIND_HPP

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

#include <algorithm>

namespace elemel {
    template <class ForwardIterator, class T>
    ForwardIterator binary_find(ForwardIterator first, ForwardIterator last, T const &value)
    {
        std::pair<ForwardIterator, ForwardIterator> i = std::equal_range(first, last, value);
        return (i.first != i.second) ? i.first : last;
    }

    template <class ForwardIterator, class T, class Compare>
    ForwardIterator binary_find(ForwardIterator first, ForwardIterator last, T const &value, Compare comp)
    {
        std::pair<ForwardIterator, ForwardIterator> i = std::equal_range(first, last, value, comp);
        return (i.first != i.second) ? i.first : last;
    }
}

#endif // ELEMEL_BINARY_FIND_HPP
