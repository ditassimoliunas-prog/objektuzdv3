#pragma once

#include <iostream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <limits>
#include <vector>

template <typename T>
class Vector;

// Forward declaration
template <typename T>
class VectorIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

private:
    T* _ptr;

public:
    VectorIterator(T* ptr = nullptr) : _ptr(ptr) {}

    reference operator*() const { return *_ptr; }
    pointer operator->() const { return _ptr; }

    VectorIterator& operator++() {
        ++_ptr;
        return *this;
    }
    VectorIterator operator++(int) {
        VectorIterator temp = *this;
        ++_ptr;
        return temp;
    }

    VectorIterator& operator--() {
        --_ptr;
        return *this;
    }
    VectorIterator operator--(int) {
        VectorIterator temp = *this;
        --_ptr;
        return temp;
    }

    VectorIterator operator+(difference_type n) const {
        return VectorIterator(_ptr + n);
    }
    VectorIterator operator-(difference_type n) const {
        return VectorIterator(_ptr - n);
    }

    VectorIterator& operator+=(difference_type n) {
        _ptr += n;
        return *this;
    }
    VectorIterator& operator-=(difference_type n) {
        _ptr -= n;
        return *this;
    }

    reference operator[](difference_type n) const {
        return _ptr[n];
    }

    bool operator==(const VectorIterator& other) const { return _ptr == other._ptr; }
    bool operator!=(const VectorIterator& other) const { return _ptr != other._ptr; }
    bool operator<(const VectorIterator& other) const { return _ptr < other._ptr; }
    bool operator>(const VectorIterator& other) const { return _ptr > other._ptr; }
    bool operator<=(const VectorIterator& other) const { return _ptr <= other._ptr; }
    bool operator>=(const VectorIterator& other) const { return _ptr >= other._ptr; }

    difference_type operator-(const VectorIterator& other) const {
        return _ptr - other._ptr;
    }
};

template <typename T>
class Vector {
private:
    T* _data;
    size_t _size;
    size_t _capacity;
    size_t _realloc_count;

    void reallocate(size_t new_capacity) {
        if (new_capacity < _size) {
            throw std::invalid_argument("New capacity must be >= current size");
        }
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
        ++_realloc_count;
    }

public:
    Vector() : _data(nullptr), _size(0), _capacity(0), _realloc_count(0) {}
    explicit Vector(size_t capacity) : _size(0), _capacity(capacity), _realloc_count(0) {
        _data = capacity > 0 ? new T[capacity] : nullptr;
    }
    Vector(size_t size, const T& value) : _size(size), _capacity(size), _realloc_count(0) {
        _data = size > 0 ? new T[size] : nullptr;
        for (size_t i = 0; i < size; ++i) _data[i] = value;
    }

    // Conversion constructor from std::vector
    Vector(const std::vector<T>& other) : _size(other.size()), _capacity(other.size()), _realloc_count(0) {
        _data = _size > 0 ? new T[_size] : nullptr;
        for (size_t i = 0; i < _size; ++i) _data[i] = other[i];
    }

    ~Vector() { delete[] _data; _data = nullptr; _size = 0; _capacity = 0; }
    
    Vector(const Vector& other) : _size(other._size), _capacity(other._capacity), _realloc_count(0) {
        _data = _capacity > 0 ? new T[_capacity] : nullptr;
        for (size_t i = 0; i < _size; ++i) _data[i] = other._data[i];
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._capacity;
            _realloc_count = 0;
            _data = _capacity > 0 ? new T[_capacity] : nullptr;
            for (size_t i = 0; i < _size; ++i) _data[i] = other._data[i];
        }
        return *this;
    }
    
    Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), 
          _capacity(other._capacity), _realloc_count(other._realloc_count) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
        other._realloc_count = 0;
    }
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            _realloc_count = other._realloc_count;
            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
            other._realloc_count = 0;
        }
        return *this;
    }

    inline size_t size() const { return _size; }
    inline size_t capacity() const { return _capacity; }
    inline bool empty() const { return _size == 0; }

    inline T& operator[](size_t index) { return _data[index]; }
    inline const T& operator[](size_t index) const { return _data[index]; }

    T& at(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Vector index out of range");
        }
        return _data[index];
    }
    
    const T& at(size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Vector index out of range");
        }
        return _data[index];
    }
    
    void clear() {
        _size = 0;
    }

    T& front() {
        if (_size == 0) {
            throw std::out_of_range("Vector is empty: cannot access front()");
        }
        return _data[0];
    }

    const T& front() const {
        if (_size == 0) {
            throw std::out_of_range("Vector is empty: cannot access front()");
        }
        return _data[0];
    }

    T& back() {
        if (_size == 0) {
            throw std::out_of_range("Vector is empty: cannot access back()");
        }
        return _data[_size - 1];
    }

    const T& back() const {
        if (_size == 0) {
            throw std::out_of_range("Vector is empty: cannot access back()");
        }
        return _data[_size - 1];
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > _capacity) {
            reallocate(new_capacity);
        }
    }

    void shrink_to_fit() {
        if (_capacity > _size) {
            if (_size == 0) {
                delete[] _data;
                _data = nullptr;
                _capacity = 0;
            } else {
                reallocate(_size);
            }
        }
    }

    void resize(size_t new_size) {
        if (new_size > _capacity) {
            reallocate(new_size);
        }
        _size = new_size;
    }

    void resize(size_t new_size, const T& value) {
        if (new_size > _capacity) {
            reallocate(new_size);
        }
        if (new_size > _size) {
            for (size_t i = _size; i < new_size; ++i) {
                _data[i] = value;
            }
        }
        _size = new_size;
    }

    void swap(Vector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_realloc_count, other._realloc_count);
    }

    bool operator==(const Vector& other) const {
        if (_size != other._size) return false;
        for (size_t i = 0; i < _size; ++i) {
            if (_data[i] != other._data[i]) return false;
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    bool operator<(const Vector& other) const {
        for (size_t i = 0; i < _size && i < other._size; ++i) {
            if (_data[i] < other._data[i]) return true;
            if (_data[i] > other._data[i]) return false;
        }
        return _size < other._size;
    }

    bool operator>(const Vector& other) const {
        return other < *this;
    }

    bool operator<=(const Vector& other) const {
        return !(other < *this);
    }

    bool operator>=(const Vector& other) const {
        return !(*this < other);
    }

    using iterator = VectorIterator<T>;
    using const_iterator = VectorIterator<const T>;

    iterator begin() { return iterator(_data); }
    iterator end() { return iterator(_data + _size); }

    const_iterator begin() const { return const_iterator(_data); }
    const_iterator end() const { return const_iterator(_data + _size); }

    const_iterator cbegin() const { return const_iterator(_data); }
    const_iterator cend() const { return const_iterator(_data + _size); }

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    void assign(size_t count, const T& value) {
        clear();
        if (count > _capacity) {
            reallocate(count);
        }
        for (size_t i = 0; i < count; ++i) {
            _data[i] = value;
        }
        _size = count;
    }

    template<typename InputIt>
    void assign(InputIt first, InputIt last) {
        // This is a specialized version - only works with Vector iterators
        // For general case, user should use clear() + for loop
    }


    iterator insert(const_iterator pos, const T& value) {
        size_t index = std::distance(cbegin(), pos);
        if (index > _size) {
            throw std::out_of_range("Iterator out of range");
        }

        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            reallocate(new_capacity);
        }

        for (size_t i = _size; i > index; --i) {
            _data[i] = _data[i - 1];
        }
        _data[index] = value;
        ++_size;

        return iterator(_data + index);
    }

    // Non-const overload for insert (accepts non-const iterator, treats as const_iterator)
    iterator insert(iterator pos, const T& value) {
        // pos is a mutable iterator, but we just use it as a position
        // Convert to size_t using cbegin()
        size_t index = std::distance(begin(), pos);
        if (index > _size) {
            throw std::out_of_range("Iterator out of range");
        }

        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            reallocate(new_capacity);
        }

        for (size_t i = _size; i > index; --i) {
            _data[i] = _data[i - 1];
        }
        _data[index] = value;
        ++_size;

        return iterator(_data + index);
    }

    // Range insert overload with three arguments
    template<typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        size_t index = std::distance(cbegin(), pos);
        if (index > _size) {
            throw std::out_of_range("Iterator out of range");
        }

        // Count elements manually
        size_t count = 0;
        for (InputIt it = first; it != last; ++it) {
            ++count;
        }

        if (_size + count > _capacity) {
            reallocate(std::max(_size + count, _capacity * 2));
        }

        // Shift elements to the right
        for (size_t i = _size; i > index; --i) {
            _data[i + count - 1] = _data[i - 1];
        }

        // Insert new elements
        size_t i = index;
        for (InputIt it = first; it != last; ++it, ++i) {
            _data[i] = *it;
        }
        _size += count;

        return iterator(_data + index);
    }

    // Range insert overload with non-const iterator
    template<typename InputIt>
    iterator insert(iterator pos, InputIt first, InputIt last) {
        size_t index = std::distance(begin(), pos);
        if (index > _size) {
            throw std::out_of_range("Iterator out of range");
        }

        // Count elements manually
        size_t count = 0;
        for (InputIt it = first; it != last; ++it) {
            ++count;
        }

        if (_size + count > _capacity) {
            reallocate(std::max(_size + count, _capacity * 2));
        }

        // Shift elements to the right
        for (size_t i = _size; i > index; --i) {
            _data[i + count - 1] = _data[i - 1];
        }

        // Insert new elements
        size_t i = index;
        for (InputIt it = first; it != last; ++it, ++i) {
            _data[i] = *it;
        }
        _size += count;

        return iterator(_data + index);
    }

    iterator erase(const_iterator pos) {
        size_t index = std::distance(cbegin(), pos);
        if (index >= _size) {
            throw std::out_of_range("Iterator out of range");
        }

        for (size_t i = index; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
        }
        --_size;

        return iterator(_data + index);
    }

     iterator erase(const_iterator first, const_iterator last) {
        size_t first_index = std::distance(cbegin(), first);
        size_t last_index = std::distance(cbegin(), last);

        if (first_index > _size || last_index > _size || first_index > last_index) {
            throw std::out_of_range("Invalid range");
        }

        size_t count = last_index - first_index;
        for (size_t i = first_index; i < _size - count; ++i) {
            _data[i] = _data[i + count];
        }
        _size -= count;

        return iterator(_data + first_index);
    }

    // Non-const overload for erase (single element)
    iterator erase(iterator pos) {
        size_t index = std::distance(begin(), pos);
        if (index >= _size) {
            throw std::out_of_range("Iterator out of range");
        }

        for (size_t i = index; i < _size - 1; ++i) {
            _data[i] = _data[i + 1];
        }
        --_size;

        return iterator(_data + index);
    }

    // Non-const overload for erase (range)
    iterator erase(iterator first, iterator last) {
        size_t first_index = std::distance(begin(), first);
        size_t last_index = std::distance(begin(), last);

        if (first_index > _size || last_index > _size || first_index > last_index) {
            throw std::out_of_range("Invalid range");
        }

        size_t count = last_index - first_index;
        for (size_t i = first_index; i < _size - count; ++i) {
            _data[i] = _data[i + count];
        }
        _size -= count;

        return iterator(_data + first_index);
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            reallocate(new_capacity);
        }
        new (_data + _size) T(std::forward<Args>(args)...);
        ++_size;
    }

    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        size_t index = std::distance(cbegin(), pos);
        if (index > _size) {
            throw std::out_of_range("Iterator out of range");
        }

        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            reallocate(new_capacity);
        }

        for (size_t i = _size; i > index; --i) {
            _data[i] = _data[i - 1];
        }
        new (_data + index) T(std::forward<Args>(args)...);
        ++_size;

        return iterator(_data + index);
    }

    size_t max_size() const {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    inline T* data() { return _data; }
    inline const T* data() const { return _data; }

    inline size_t get_reallocation_count() const { return _realloc_count; }
    inline void reset_reallocation_count() { _realloc_count = 0; }

    void push_back(const T& value) {
        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            reallocate(new_capacity);
        }
        _data[_size] = value;
        ++_size;
    }
    
    void push_back(T&& value) {
        if (_size >= _capacity) {
            size_t new_capacity = (_capacity == 0) ? 1 : _capacity * 2;
            reallocate(new_capacity);
        }
        _data[_size] = std::move(value);
        ++_size;
    }

    void pop_back() {
        if (_size > 0) {
            --_size;
        }
    }
};



