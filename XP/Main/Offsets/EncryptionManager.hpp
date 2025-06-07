#pragma once

#include <Windows.h>
#include <string_view>
#include <cstdint>
#include <string>

template <typename T>
struct unwrap_vmvalue {
    using type = T;
};

template <typename T>
using VMValue0 = typename unwrap_vmvalue<T>::type;

template <typename T>
struct VMValue1
{
private:
    T Storage;
public:
    operator const T() const {
        return (T)((uintptr_t)this->Storage - (uintptr_t)this);
    }

    void operator=(const T& Value) {
        this->Storage = (T)((uintptr_t)Value + (uintptr_t)this);
    }

    const T operator->() const {
        return operator const T();
    }

    T Get() {
        return operator const T();
    }

    void Set(const T& Value) {
        operator=(Value);
    }
};

template <typename T>
struct VMValue2
{
private:
    T Storage;
public:
    operator const T() const {
        return (T)((uintptr_t)this - (uintptr_t)this->Storage);
    }

    void operator=(const T& Value) {
        this->Storage = (T)((uintptr_t)this - (uintptr_t)Value);
    }

    const T operator->() const {
        return operator const T();
    }

    T Get() {
        return operator const T();
    }

    void Set(const T& Value) {
        operator=(Value);
    }
};

template <typename T>
struct VMValue3
{
private:
    T Storage;
public:
    operator const T() const {
        return (T)((uintptr_t)this ^ (uintptr_t)this->Storage);
    }

    void operator=(const T& Value) {
        this->Storage = (T)((uintptr_t)Value ^ (uintptr_t)this);
    }

    const T operator->() const {
        return operator const T();
    }

    T Get() {
        return operator const T();
    }

    void Set(const T& Value) {
        operator=(Value);
    }
};

template <typename T>
struct VMValue4
{
private:
    T Storage;
public:
    operator const T() const {
        return (T)((uintptr_t)this + (uintptr_t)this->Storage);
    }

    void operator=(const T& Value) {
        this->Storage = (T)((uintptr_t)Value - (uintptr_t)this);
    }

    const T operator->() const {
        return operator const T();
    }

    T Get() {
        return operator const T();
    }

    void Set(const T& Value) {
        operator=(Value);
    }
};
