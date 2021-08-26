#ifndef SLICE_HEADER_INCLUDED
#define SLICE_HEADER_INCLUDED

#include <vector>
#include <algorithm>

#include <cstddef>
#include <exception>

template<typename T>
class Slice{
public:
    using value_type = T;
    using iterator = typename std::vector<T>::const_iterator;

    Slice() = delete;
    Slice(const std::vector<value_type> &v) : slice_begin(v.cbegin()), slice_end(v.cend()) {}
    Slice(iterator b, iterator e) : slice_begin(b), slice_end(e) {}
    
    Slice(const Slice &) = default;
    Slice(Slice &&) = default;

    Slice &operator=(const Slice &) = default;
    Slice &operator=(Slice &&) = default;
    
    ~Slice() = default;

    const value_type &operator[](std::size_t n) const {
        iterator elem = slice_begin + n;
        if (elem >= slice_end)
            throw std::out_of_range("Element out of Range");
        return *elem;
    }

    const value_type &front() const {
        return *slice_begin;
    }

    const value_type &back() const {
        return *(slice_end - 1);
    }

    bool empty() const {
        return !size();
    }

    size_t size() const {
        return slice_end - slice_begin;
    }

    iterator begin() const {
        return slice_begin;
    }

    iterator end() const {
        return slice_end;
    }

private:
    iterator slice_begin;
    iterator slice_end;
};

#endif
