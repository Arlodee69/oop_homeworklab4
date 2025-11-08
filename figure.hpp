#pragma once

#include <iostream>
#include <memory>
#include "point.hpp"

template <Scalar T>
class Figure {
    protected:
        std::unique_ptr<std::unique_ptr<Point<T>>[]> points;
        size_t amountOfPoints;

    public:
        Figure() : amountOfPoints(0), points(nullptr) {}
        Figure(size_t n, std::unique_ptr<std::unique_ptr<Point<T>>[]>&& inputPoints)
            : amountOfPoints(n), points(std::move(inputPoints)) {}

        virtual ~Figure() = default;

        virtual Point<T> center() const = 0;
        virtual double area() const = 0;
        explicit operator double() const {
            return area();
        }

        virtual void printPoints(std::ostream& os) const {
            for (size_t i = 0; i < amountOfPoints; ++i) {
                os << " " << *(points[i]);
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
            fig.print(os);
            return os;
        }
        friend std::istream& operator>>(std::istream& is, Figure& fig) {
            fig.read(is);
            return is;
        }

        virtual void print(std::ostream& os) const = 0;
        virtual void read(std::istream& is) = 0;
        
        virtual std::unique_ptr<Figure<T>> copy() const = 0;

        virtual bool operator==(const Figure<T>& other) const = 0;
};