#pragma once

#include <iostream>
#include <stdexcept>

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

    inline size_t get_reallocation_count() const { return _realloc_count; }
    inline void reset_reallocation_count() { _realloc_count = 0; }
    void pop_back() {
        if (_size > 0) {
            --_size;
        }
    }

    inline T* data() { return _data; }
    inline const T* data() const { return _data; }
};

