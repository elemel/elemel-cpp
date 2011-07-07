#ifndef ELEMEL_RAW_ALLOCATOR_HPP
#define ELEMEL_RAW_ALLOCATOR_HPP

#include <cstddef>
#include <cstdlib>

namespace elemel {
    class raw_new_allocator {
    public:
        typedef std::size_t size_type;

        void *allocate(size_type n) const
        {
            return reinterpret_cast<void *>(new unsigned char[n]);
        }

        void deallocate(void *p) const
        {
            delete[] reinterpret_cast<unsigned char *>(p);
        }
    };

    class raw_malloc_allocator {
    public:
        typedef std::size_t size_type;

        void *allocate(size_type n) const
        {
            return std::malloc(n);
        }

        void deallocate(void *p) const
        {
            std::free(p);
        }
    };
}

#endif // ELEMEL_RAW_ALLOCATOR_HPP
