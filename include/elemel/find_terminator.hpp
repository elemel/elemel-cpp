#ifndef ELEMEL_FIND_TERMINATOR_HPP
#define ELEMEL_FIND_TERMINATOR_HPP

#include <iterator>

namespace elemel {
    template <class ForwardIterator, class T>
    ForwardIterator find_terminator(ForwardIterator i, T const &terminator)
    {
        while (*i != terminator) {
            ++i;
        }
        return i;
    }

    template <class ForwardIterator>
    ForwardIterator find_terminator(ForwardIterator i)
    {
        typedef typename std::iterator_traits<ForwardIterator>::value_type
            value_type;

        return find_terminator(i, value_type());
    }
}

#endif // ELEMEL_FIND_TERMINATOR_HPP
