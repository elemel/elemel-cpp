#ifndef ELEMEL_REF_PTR_HPP
#define ELEMEL_REF_PTR_HPP

#include <algorithm>
#include <cassert>

namespace elemel {
    template <class T>
    class ref_ptr {
    public:
        typedef T element_type;

        explicit ref_ptr(element_type *p = 0) :
            ptr_(p)
        {
            if (ptr_) {
                ptr_->add_ref();
            }
        }

        ref_ptr(ref_ptr const &other) :
            ptr_(other.ptr_)
        {
            if (ptr_) {
                ptr_->add_ref();
            }
        }

        ~ref_ptr()
        {
            if (ptr_) {
                ptr_->release();
            }
        }

        ref_ptr &operator=(ref_ptr const &other)
        {
            ref_ptr(other).swap(*this);
        }

        element_type &operator*() const
        {
            assert(ptr_);
            return *ptr_;
        }

        element_type *operator->() const
        {
            assert(ptr_);
            return ptr_;
        }

        element_type *get() const
        {
            return ptr_;
        }

        void reset(element_type *p = 0)
        {
            ref_ptr(p).swap(*this);
        }

        void swap(ref_ptr &other)
        {
            std::swap(ptr_, other.ptr_);
        }

        operator bool() const
        {
            return ptr_ != 0;
        }

    private:
        element_type *ptr_;
    };
}

#endif // ELEMEL_REF_PTR_HPP
