#pragma once

#include <cmath>
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <ostream>
#include <utility>

namespace vector_detail {
    template<size_t N, typename T> struct VectorComponents {};
    template<typename T> struct VectorComponents<1, T> { T& x; VectorComponents(T* data) : x(data[0]) {} };
    template<typename T> struct VectorComponents<2, T> { T& x; T& y; VectorComponents(T* data) : x(data[0]), y(data[1]) {} };
    template<typename T> struct VectorComponents<3, T> { T& x; T& y; T& z; VectorComponents(T* data) : x(data[0]), y(data[1]), z(data[2]) {} };
    template<typename T> struct VectorComponents<4, T> { T& x; T& y; T& z; T& w; VectorComponents(T* data) : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {} };
}

template<size_t N, typename T = float>
class Vector : public vector_detail::VectorComponents<N, T> {
    static_assert(N >= 1, "Vector dimension (N) must be greater than 0");

    public:

    using Components = vector_detail::VectorComponents<N, T>;

    constexpr Vector() : Components(data_) {}

    template<typename... TArgs, typename = std::enable_if_t<sizeof...(TArgs) == N>>
    constexpr Vector(TArgs&&... values) : Components(data_), data_{ static_cast<T>(std::forward<TArgs>(values))... } {}

    constexpr Vector(const Vector<N, T>& other) : Components(data_) {
        for (size_t i = 0;i < N; i++) {
            data_[i] = other[i];
        }
    }

    template<typename U>
    constexpr Vector(const Vector<N, U>& other) : Components(data_) {
        for (size_t i = 0;i < N; i++) {
            data_[i] = static_cast<T>(other[i]);
        }
    }

    constexpr Vector(std::initializer_list<T> list) : Components(data_) {
        size_t i = 0;

        for (const T& value : list) {
            data_[i++] = value;
        }
    }

    constexpr size_t size() const { return N; }

    T* data() { return data_; }
    const T* data() const { return data_; }

    inline T& operator[](const size_t i) { return data_[i]; }
    inline const T& operator[](const size_t i) const { return data_[i]; }

    inline T& at(const size_t i) {
        if (i >= size()) {
            throw new std::runtime_error("vector index out of bounds.");
        }
        return data_[i];
    }

    inline const T& at(const size_t i) const {
        if (i >= size()) {
            throw new std::runtime_error("vector index out of bounds.");
        }
        return data_[i];
    }

    float magnitude() const {
        float sum = 0.0f;
        for (size_t i = 0; i < N; i++) {
            sum += data_[i] * data_[i];
        }
        return std::sqrt(sum);
    }

    template<typename U>
    inline Vector<N, T>& operator=(const Vector<N, U>& other) {
        for (size_t i = 0; i < N; i++) {
            data_[i] = static_cast<T>(other[i]);
        }
        return *this;
    }

    inline Vector<N, T>& operator=(const Vector<N, T>& other) {
        for (size_t i = 0; i < N; i++) {
            data_[i] = other[i];
        }
        return *this;
    }

    template<typename U>
    inline bool operator==(const Vector<N, U>& other) {
        using TCommon = typename std::common_type<T, U>::type;
        for (size_t i = 0; i < N; i++) {
            if (static_cast<TCommon>(data_[i]) != static_cast<TCommon>(other[i])) return false;
        }
        return true;
    }

    inline bool operator!=(const Vector<N, T>& other) {
        return !(*this == other);
    }

    Vector<N, T> operator-() {
        Vector<N, T> result;
        for (size_t i = 0; i < N; i++) {
            result[i] = -data_[i];
        }
        return result;
    }

    template<typename K>
    inline Vector<N, T>& operator*=(const K k) {
        for (size_t i = 0; i < N; i++) {
            data_[i] *= static_cast<T>(k);
        }
        return *this;
    }

    template<typename K>
    inline Vector<N, T>& operator/=(const K k) {
        for (size_t i = 0; i < N; i++) {
            data_[i] /= static_cast<T>(k);
        }
        return *this;
    }

    inline Vector<N, T>& operator+=(const Vector<N, T>& other) {
        for (size_t i = 0; i < N; i++) {
            data_[i] += other[i];
        }
        return *this;
    }

    inline Vector<N, T>& operator-=(const Vector<N, T>& other) {
        for (size_t i = 0; i < N; i++) {
            data_[i] -= other[i];
        }
        return *this;
    }

    private:

    T data_[N] {};
};

template<size_t N, typename T, typename U>
inline auto operator*(const Vector<N, T>& v, const U k) {
    using TCommon = typename std::common_type<T, U>::type;
    Vector<N, TCommon> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = static_cast<TCommon>(v[i]) * static_cast<TCommon>(k);
    }
    return result;
}

template<size_t N, typename T, typename U>
inline auto operator*(const U k, const Vector<N, T>& v) {
    return v * k;
}

template<size_t N, typename T, typename U>
inline auto operator*(const Vector<N, T>& a, const Vector<N, U>& b) {
    using TCommon = typename std::common_type<T, U>::type;
    Vector<N, TCommon> result;
    return result;
}

template<size_t N, typename T, typename U>
inline auto operator/(const Vector<N, T>& v, const U k) {
    using TCommon = typename std::common_type<T, U>::type;
    Vector<N, TCommon> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = static_cast<TCommon>(v[i]) / static_cast<TCommon>(k);
    }
    return result;
}

template<size_t N, typename T, typename U>
inline auto operator/(const U k, const Vector<N, T>& v) {
    using TCommon = typename std::common_type<T, U>::type;
    Vector<N, TCommon> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = static_cast<TCommon>(k) / static_cast<TCommon>(v[i]);
    }
    return result;
}

template<size_t N, typename T, typename U>
inline Vector<N, T> operator/(const Vector<N, T>& a, const Vector<N, U>& b) {
    using TCommon = typename std::common_type<T, U>::type;
    Vector<N, TCommon> result;
    return result;
}

template<size_t N, typename T, typename U>
inline auto operator+(const Vector<N, T>& a, const Vector<N, U>& b) {
    using TCommon = typename std::common_type<T, U>::type;
    Vector<N, TCommon> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = static_cast<TCommon>(a[i]) + static_cast<TCommon>(b[i]);
    }
    return result;
}

template<size_t N, typename T, typename U>
inline auto operator-(const Vector<N, T>& a, const Vector<N, U>& b) {
    using TCommon = typename std::common_type<T, U>::type;
    Vector<N, TCommon> result;
    for (size_t i = 0; i < N; i++) {
        result[i] = static_cast<TCommon>(a[i]) - static_cast<TCommon>(b[i]);
    }
    return result;
}

template<size_t N, typename T>
std::ostream& operator<<(std::ostream& os, const Vector<N, T>& v) {
    static_assert(N > 0, "Vector dimension (N) must be greater than 0");

    os << "(" << v[0];
    for (size_t i = 1; i < N; i++) {
        os << ", " << v[i];
    }
    os << ")";
    return os;
}

using Vector2 = Vector<2, float>;
using Vector2f = Vector<2, float>;
using Vector2int = Vector<2, int>;

using Vector3 = Vector<3, float>;
using Vector3f = Vector<3, float>;
using Vector3int = Vector<3, int>;

using Vector4 = Vector<4, float>;
using Vector4f = Vector<4, float>;
using Vector4int = Vector<4, int>;