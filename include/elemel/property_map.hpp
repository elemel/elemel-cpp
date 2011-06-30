#ifndef ELEMEL_PROPERTY_MAP_HPP
#define ELEMEL_PROPERTY_MAP_HPP

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

#include <elemel/flat_map.hpp>

#include <iostream>
#include <stdexcept>

namespace elemel {
    template <
        class Key,
        class Data,
        class Storage = flat_map<Key, Data>,
        class Cache = flat_map<Key, Data const *>
    >
    class property_map {
    public:
        typedef Key key_type;
        typedef Data data_type;
        typedef Storage storage_type;
        typedef Cache cache_type;

        typedef typename storage_type::size_type size_type;
        typedef typename storage_type::iterator iterator;
        typedef typename storage_type::const_iterator const_iterator;

        explicit property_map(property_map *prototype = 0) :
            prototype_(prototype),
            first_instance_(0),
            next_instance_(0),
            previous_instance_(0)
        { }

        property_map(property_map const &other) :
            properties_(other.properties_),
            prototype_(other.prototype_),
            first_instance_(0),
            next_instance_(0),
            previous_instance_(0)
        { }

        ~property_map()
        {
            unlink();
        }

        property_map *prototype()
        {
            return prototype_;
        }

        property_map const *prototype() const
        {
            return prototype_;
        }

        void prototype(property_map *prototype)
        {
            unlink();
            prototype_ = prototype;
        }

        data_type const *get_ptr(key_type const &key) const
        {
            const_iterator i = properties_.find(key);
            if (i != properties_.end()) {
                return &i->second;
            } else if (prototype_) {
                return prototype_->inherit(key);
            } else {
                return 0;
            }
        }

        data_type *get_local_ptr(key_type const &key)
        {
            iterator i = properties_.find(key);
            return (i != properties_.end()) ? &i->second : 0;
        }

        data_type const *get_local_ptr(key_type const &key) const
        {
            const_iterator i = properties_.find(key);
            return (i != properties_.end()) ? &i->second : 0;
        }

        data_type const &get(key_type const &key) const
        {
            data_type const *result = get_ptr(key);
            if (result == 0) {
                throw std::out_of_range("no such key");
            }
            return *result;
        }

        data_type &get_local(key_type const &key)
        {
            data_type *result = get_local_ptr(key);
            if (result == 0) {
                throw std::out_of_range("no such key");
            }
            return *result;
        }

        data_type const &get_local(key_type const &key) const
        {
            data_type const *result = get_local_ptr(key);
            if (result == 0) {
                throw std::out_of_range("no such key");
            }
            return *result;
        }

        void set(key_type const &key, data_type const &value)
        {
            iterator i = properties_.find(key);
            if (i == properties_.end()) {
                unlink();
                properties_.insert(std::make_pair(key, value));
            } else {
                i->second = value;
            }
        }

        size_type erase(key_type const &key)
        {
            iterator i = properties_.find(key);
            if (i == properties_.end()) {
                return 0;
            } else {
                unlink();
                properties_.erase(i);
                return 1;
            }
        }

        bool empty() const
        {
            return properties_.empty();
        }

        size_type size() const
        {
            return properties_.size();
        }

        iterator begin()
        {
            return properties_.begin();
        }

        iterator end()
        {
            return properties_.end();
        }

        const_iterator begin() const
        {
            return properties_.begin();
        }

        const_iterator end() const
        {
            return properties_.end();
        }

    private:
        storage_type properties_;
        property_map *prototype_;

        property_map *first_instance_;
        property_map *next_instance_;
        property_map *previous_instance_;
        cache_type cache_;

        void link()
        {
            if (prototype_ && next_instance_ == 0) {
                if (prototype_->first_instance_ == 0) {
                    prototype_->first_instance_ = this;
                    next_instance_ = this;
                    previous_instance_ = this;
                } else {
                    previous_instance_ = prototype_->first_instance_->previous_instance_;
                    next_instance_ = prototype_->first_instance_;
                    prototype_->first_instance_->previous_instance_->next_instance_ = this;
                    prototype_->first_instance_->previous_instance_ = this;
                }
            }
        }

        void unlink()
        {
            while (first_instance_) {
                first_instance_->previous_instance_->unlink();
            }

            cache_.clear();

            if (next_instance_) {
                if (next_instance_ == this) {
                    prototype_->first_instance_ = 0;
                } else {
                    if (prototype_->first_instance_ = this) {
                        prototype_->first_instance_ = next_instance_;
                    }
                    next_instance_->previous_instance_ = previous_instance_;
                    previous_instance_->next_instance_ = next_instance_;
                }
                next_instance_ = 0;
                previous_instance_ = 0;
            }
        }

        data_type const *inherit(key_type const &key)
        {
            typename cache_type::const_iterator i = cache_.find(key);
            if (i != cache_.end()) {
                return i->second;
            }

            data_type const *result = 0;
            const_iterator j = properties_.find(key);
            if (j != properties_.end()) {
                result = &j->second;
            } else if (prototype_) {
                link();
                result = prototype_->inherit(key);
            }
            cache_.insert(std::make_pair(key, result));
            return result;
        }
    };
}

#endif // ELEMEL_PROPERTY_MAP_HPP
