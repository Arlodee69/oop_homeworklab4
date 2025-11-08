#pragma once

#include <iostream>
#include "figure.hpp"
#include <cmath>
#include <memory>
#include <typeinfo>

template <Scalar T>
class Trapezoid : public Figure<T> {
    public:
        Trapezoid() : Figure<T>(4, nullptr) {
            this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
            for (size_t i = 0; i < 4; ++i) {
                this->points[i] = std::make_unique<Point<T>>();
            }
            this->amountOfPoints = 4;
        }

        Trapezoid(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
            this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
            this->points[0] = std::make_unique<Point<T>>(p1);
            this->points[1] = std::make_unique<Point<T>>(p2);
            this->points[2] = std::make_unique<Point<T>>(p3);
            this->points[3] = std::make_unique<Point<T>>(p4);
            this->amountOfPoints = 4;
        }

        Point<T> center() const override {
            T cX = 0;
            T cY = 0;

            for (size_t i = 0; i < 4; ++i) {
                cX += this->points[i]->x;
                cY += this->points[i]->y;
            }

            return Point<T>(cX / (T)4, cY / (T)4);
        }

        double area() const override {
            double area = 0.0;
            for (size_t i = 0; i < 4; ++i) {
                size_t j = (i + 1) % 4;
                area += (this->points[i]->x * this->points[j]->y - this->points[j]->x * this->points[i]->y);
            }
            return std::abs(area) / 2.0;
        }

        std::unique_ptr<Figure<T>> copy() const override {
            return std::make_unique<Trapezoid<T>>(*this->points[0], *this->points[1], *this->points[2], *this->points[3]);
        }

        bool operator==(const Figure<T>& other) const override {
            if (typeid(*this) != typeid(other)) {
                return false;
            }

            const Trapezoid<T>* otherFig = dynamic_cast<const Trapezoid<T>*>(&other);
            
            if (!otherFig) {
                return false;
            } 

            return std::abs(this->area() - otherFig->area()) < 1e-16;
        }

        void read(std::istream& is) override {
            for (size_t i = 0; i < 4; ++i) {
                is >> *(this->points[i]);
            }
        }

        void print(std::ostream& os) const override {
            os << "Трапеция ";
            os << "Центр: " << center() << ", площадь: " << area() << ", точки:";
            this->printPoints(os);
        }
};