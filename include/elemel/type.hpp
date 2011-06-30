#ifndef ELEMEL_TYPE_HPP
#define ELEMEL_TYPE_HPP

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

#include <elemel/hash_string.hpp>

#include <typeinfo>
#include <tr1/functional>

namespace elemel {
    class type {
    public:
        type(std::type_info const &info = typeid(void)) :
            info_(&info)
        { }
    
        std::type_info const &info() const
        {
            return *info_;
        }
    
    private:
        std::type_info const *info_;
    };

    inline bool operator==(type const &a, type const &b)
    {
        return a.info() == b.info();
    }
    
    inline bool operator!=(type const &a, type const &b)
    {
        return !(a == b);
    }
    
    inline bool operator<(type const &a, type const &b)
    {
        return a.info().before(b.info());
    }
    
    inline bool operator>(type const &a, type const &b)
    {
        return b < a;
    }
    
    inline bool operator<=(type const &a, type const &b)
    {
        return !(b < a);
    }
    
    inline bool operator>=(type const &a, type const &b)
    {
        return !(a < b);
    }
}

namespace std {
    namespace tr1 {
        template <>
        struct hash<elemel::type> :
            unary_function<elemel::type, size_t>
        {
            size_t operator()(elemel::type const &arg) const
            {
                return elemel::hash_string(arg.name());
            }
        };
    }
}

#endif // ELEMEL_TYPE_HPP
