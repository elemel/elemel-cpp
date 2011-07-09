#ifndef ELEMEL_STRING_IMPL_HPP
#define ELEMEL_STRING_IMPL_HPP

namespace elemel {
    namespace detail {
        template <class Char, class RefCount, class RawAllocator>
        class string_impl {
        public:
            typedef Char value_type;
            typedef std::size_t size_type;
            typedef RefCount ref_count_type;
            typedef RawAllocator raw_allocator_type;
    
            static string_impl *create(value_type const *str, size_type n,
                                       raw_allocator_type const &alloc)
            {
                size_type alloc_n = (sizeof(string_impl) +
                                     sizeof(value_type) * (n + 1));
                string_impl *impl =
                    reinterpret_cast<string_impl *>(alloc.allocate(alloc_n));
                return new (impl) string_impl(str, n, alloc);
            }
    
            void add_ref()
            {
                ++ref_count_;
            }
    
            void release()
            {
                if (--ref_count_ == 0) {
                    raw_allocator_type alloc(alloc_);
                    this->~string_impl();
                    alloc.deallocate(reinterpret_cast<void *>(this));
                }
            }
    
            value_type *data()
            {
                return reinterpret_cast<value_type *>(reinterpret_cast<unsigned char *>(this) +
                                                      sizeof(string_impl));
            }

            size_type size()
            {
                return size_;
            }

        private:
            size_type size_;
            raw_allocator_type alloc_;
            ref_count_type ref_count_;
    
            string_impl(value_type const *str, size_type n,
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
}

#endif // ELEMEL_STRING_IMPL_HPP
