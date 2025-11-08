#pragma once

#include <type_traits>
#include <memory>
#include <iostream>
#include <concepts>

template <typename T>
concept Scalar = std::is_scalar<T>::value;

template <Scalar T>
class Point {
    public:
        T x;
        T y;

        Point() : x(T()), y(T()) {}

        Point(T nx, T ny) : x(nx), y(ny) {}

        bool operator==(const Point<T>& other) const {
            return (x == other.x && y == other.y);
        }

        friend std::istream& operator>>(std::istream& is, Point<T>& p) {
            is >> p.x >> p.y;
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
            os << "(" << p.x << ", " << p.y << ")";
            return os;
        }
};