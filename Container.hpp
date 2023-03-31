/// @file Container.hpp
/// @author Sujin Lee
/// @date 3/9/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief HPP file for pa14.cpp
/// @note 20hr
/// 2022-03-02: Created by Sujin Lee
/// REVISION HISTORY:
/// 2022-03-08: Sujin Lee submmitted
/// 2022-03-09: Revised prize logic. Added clarification that operator[]() and at() are member functions.
/// 2022-03-11: Changed name of unit test file to match class it tests.
/// 2022-03-12: Corrected lottery draw to five digits.

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <utility>


template <class T>
class Container{
public:
    /// Member types.
    using value_type = T;
    using size_type = std::size_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    /// Default ctor
    Container(size_type count = 0)
    : capacity(count), used(0), data(new value_type[count]) {}

    /// Copy ctor
    Container(const Container& other);

    /// Move ctor
    Container(Container&& other);

    /// Initializer List ctor
    Container(const std::initializer_list<value_type>& init);

    /// Destructor
    ~Container();

    // Copy assigment
    Container& operator=(const Container& rhs);

    // Move assignment
    Container& operator=(Container&& rhs);

    // Append another container to this
    Container& operator+=(const Container& rhs);

    /// Check if the container has no element, || begin() == end()
    /// @return true if the container is empty, false otherwise.
    bool empty() const { return begin() == end(); }

    /// Return the number of elements in the container
    size_type size() const { return used; }

    /// Return a pointer to the first element
    pointer begin() { return data; }
    const_pointer begin() const { return data; }

    /// Returns a pointer to the end
    /// the element following the last element
    pointer end() { return begin() + size(); }
    const_pointer end() const { return begin() + size(); }

    /// Adds an element to the end
    void push_back(const value_type& value);

    /// Removes a signle item from the container
    void erase(pointer pos);

    /// After this call, size() return ZERO
    /// The capacity remains unchanged
    void clear() { used = 0; }

    /// Exchanges the contents of the container with those of other.
    void swap(Container& other);

    /// Find the first element equal to the given target.
    /// Search begins ar pos
    /// @return pointer to the element if found, or end() if no found
    pointer find(const value_type& target, pointer pos = nullptr);

    /// const and non-const versions of member functions at()
    /// @return T
    T& at(size_type pos);

    /// const and non-const versions of member functions at()
    /// @return const T
    const T& at(size_type pos) const;

    /// const and non-const versions of member operator[]
    /// @return T
    T& operator[](size_type pos) {
        return data[pos];
    }

    /// const and non-const versions of member operator[]
    /// @return const T
    const T& operator[](size_type pos) const {
        return data[pos];
    }

private:
    size_type capacity;
    size_type used;
    pointer data;
};

// related non-member functions
/// Equality comparison operators
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs);

template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs);

/// Concatenation operator
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs);

/// Stream insertion operator
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset);

// ABOVE COPIED FROM CONTAINER_H

// ===========================================================================================================//
// --------------------------------------------------------------
template <class T>
Container<T>::Container(const Container<T>& other)
: Container<T>(other.size()) {
    std::copy(other.begin(), other.end(), begin());  // ::is scope resolution for static function
    used = other.size();
}

// move Copy constructor(&&)
// template <class T>
// Container<T>::Container(Container<T>&& other)
// : capacity(other.capacity), used(other.used), data(other.data) {
    // leave other in a stable state
//    other.data = nullptr;
//    other.capacity = other.used = 0;
// }

// move Copy constructor(&&) using std::exchange
template <class T>
Container<T>::Container(Container<T>&& other){
    data = std::exchange(other.data, nullptr);
    used = std::move(other.used);
    capacity = std::move(other.capacity);
}

template <class T>
Container<T>::Container(const std::initializer_list<value_type>& init)
: Container<T>(init.size()) {
    std::copy(init.begin(), init.end(), begin());
    used = init.size();
}
template <class T>
Container<T>::~Container() {
    delete [] data;
    data = nullptr;
    used = capacity = 0;
}
template <class T>
void Container<T>::push_back(const value_type& value) {
    if (size() == capacity) {
        pointer copy_of_data = new value_type[capacity +=8] ;  // can use auto instead of pointer
        // auto copy_of_data { new value_type[capacity += 8] };  // this is modern way to do 1
        // auto copy_of_data { new value_type[capacity += 8] {} };  // this is modern way to do 2
        // auto copy_of_data new value_type[capacity += 8] {} ;  // this is modern way to do 3
        std::copy(begin(), end(), copy_of_data);
        delete [] data;
        data = copy_of_data;
    }

    *(data + used++) = value;
}
template <class T>
void Container<T>::erase(pointer pos) {
    try {
        if (pos != nullptr) {
            if ((pos < begin()) || (pos > end())){
                throw std::out_of_range("std::out_of_range(erase)");
            }
            std::copy(pos + 1, end(), pos);
            --used;
        }
    }
    catch (const std::out_of_range& error) {
        std::cout << error.what() << std::endl;
        throw error;
    }
}
template <class T>
void Container<T>::swap(Container<T>& other) {
    std::swap(capacity, other.capacity);
    std::swap(data, other.data);
    std::swap(used, other.used);
}
template <class T>
typename Container<T>::pointer
Container<T>::find(const value_type& target, pointer pos) {
    auto first = pos == nullptr ? begin() : pos;
    return std::find(first, end(), target);
}

// --------------------------------------------------------------
template <class T>
Container<T>& Container<T>::operator=(const Container<T>& rhs) {
    if (this != &rhs) {
        delete [] data;
        data = new value_type[rhs.size()];
        std::copy(rhs.begin(), rhs.end(), begin());
        used = capacity = rhs.size();
    }
    return *this;
}

/// move assignment operator uses R-Value(&&)
template <class T>
Container<T>& Container<T>::operator=(Container<T>&& rhs) {
    capacity = std::move(rhs.capacity);
    data = std::move(rhs.data);
    used = std::move(rhs.used);
    rhs.data = nullptr;

    return *this;
}
template <class T>
Container<T>& Container<T>::operator+=(const Container<T>& rhs) {
    const auto reqd_size = size() +rhs.size();

    if(capacity < reqd_size) {
        auto copy_of_data = new value_type[reqd_size];
        std::copy(begin(), end(), copy_of_data);
        delete [] data;
        data = copy_of_data;
        capacity = reqd_size;
    }

    std::copy(rhs.begin(), rhs.end(), end()); // append rhs

    used = reqd_size;
    return *this;
}
template <class T>
bool operator==(const Container<T>& lhs, const Container<T>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class T>
bool operator!=(const Container<T>& lhs, const Container<T>& rhs) {
    return !(std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}
template <class T>
Container<T> operator+(const Container<T>& lhs, const Container<T>& rhs) {
    return Container<T>(lhs) += rhs;
}
template <class T>
std::ostream& operator<<(std::ostream& output, const Container<T>& oset) {
    char separator[2] {};

    output << '{';

    for (auto& item : oset) {
        output << separator << item;
        *separator = ',';
    }

    return output << '}';
}

/// const and non-const versions of member functions at()
/// @return T
template <class T>
T& Container<T>::at(size_type pos) {
    auto val = data[pos];
    try {
        find(val, nullptr);
    }
    catch(const std::out_of_range& error) {
        std::cout << error.what() << std::endl;
    }
    return data[pos];
}

/// const and non-const versions of member functions at()
/// @return const T
template <class T>
const T& Container<T>::at(size_type pos) const {
    auto val = data[pos];
    try {
        find(val, nullptr);
    }
    catch(const std::out_of_range& error) {
        std::cout << error.what() << std::endl;
    }
    return data[pos];
}


#endif // CONTAINER_H

// EOF
