#pragma once

#include <iostream>
#include "figure.hpp"
#include <cmath>
#include <memory>
#include <typeinfo>

template <Scalar T>
class Rectangle : public Figure<T> {
    public:
        Rectangle() : Figure<T>(4, nullptr) {
            this->points = std::make_unique<std::unique_ptr<Point<T>>[]>(4);
            for (size_t i = 0; i < 4; ++i) {
                this->points[i] = std::make_unique<Point<T>>();
            }
            this->amountOfPoints = 4;
        }

        Rectangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4) {
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
            double dx1 = this->points[1]->x - this->points[0]->x;
            double dy1 = this->points[1]->y - this->points[0]->y;
            double side1 = std::sqrt(dx1*dx1 + dy1*dy1);

            double dx2 = this->points[3]->x - this->points[0]->x;
            double dy2 = this->points[3]->y - this->points[0]->y;
            double side2 = std::sqrt(dx2*dx2 + dy2*dy2);

            return side1 * side2;
        }

        std::unique_ptr<Figure<T>> copy() const override {
            return std::make_unique<Rectangle<T>>(*this->points[0], *this->points[1], *this->points[2], *this->points[3]);
        }

        bool operator==(const Figure<T>& other) const override {
            if (typeid(*this) != typeid(other)) {
                return false;
            }

            const Rectangle<T>* otherFig = dynamic_cast<const Rectangle<T>*>(&other);
            
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
            os << "Прямоугольник ";
            os << "Центр: " << center() << ", площадь: " << area() << ", точки:";
            this->printPoints(os);
        }
};