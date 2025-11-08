#pragma once

#include <iostream>
#include "figure.hpp"
#include <cmath>
#include <memory>
#include <typeinfo>

template <Scalar T>
class Square : public Figure<T> {
    public:
        Square() : Figure<T>(4, nullptr) {
            this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
            for (size_t i = 0; i < 4; ++i) {
                this->points[i] = std::make_unique<Point<T>>();
            }
            this->amountOfPoints = 4;
        }

        Square(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
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
            double dx = this->points[1]->x - this->points[0]->x;
            double dy = this->points[1]->y - this->points[0]->y;
            double side_length = std::sqrt(dx*dx + dy*dy);
            return side_length * side_length;
        }

        std::unique_ptr<Figure<T>> copy() const override {
            return std::make_unique<Square<T>>(*this->points[0], *this->points[1], *this->points[2], *this->points[3]);
        }

        bool operator==(const Figure<T>& other) const override {
            if (typeid(*this) != typeid(other)) {
                return false;
            }

            const Square<T>* otherFig = dynamic_cast<const Square<T>*>(&other);
            
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
            os << "Квадрат ";
            os << "Центр: " << center() << ", площадь: " << area() << ", точки:";
            this->printPoints(os);
        }
};