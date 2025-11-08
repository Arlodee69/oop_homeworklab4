#include "gtest/gtest.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <sstream>

#include "point.hpp"
#include "figure.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "array.hpp"

using FigurePtr = std::shared_ptr<Figure<double>>;

// Вспомогательная функция для создания фигур
template <template <class> class FigureType>
FigurePtr create_square() {
    // Квадрат 1x1 с вершинами (0,0), (1,0), (1,1), (0,1)
    // Площадь = 1
    return std::make_shared<FigureType<double>>(
        Point<double>(0, 0), Point<double>(1, 0), Point<double>(1, 1), Point<double>(0, 1)
    );
}

template <template <class> class FigureType>
FigurePtr create_rectangle() {
    // Прямоугольник 2x3 с вершинами (0,0), (2,0), (2,3), (0,3)
    // Площадь = 6
    return std::make_shared<FigureType<double>>(
        Point<double>(0, 0), Point<double>(2, 0), Point<double>(2, 3), Point<double>(0, 3)
    );
}

template <template <class> class FigureType>
FigurePtr create_trapezoid() {
    // Трапеция с вершинами (0,0), (2,0), (1,2), (0,2)
    // Площадь = 0.5 * (сумма оснований) * высота = 0.5 * (2 + 1) * 2 = 3
    return std::make_shared<FigureType<double>>(
        Point<double>(0, 0), Point<double>(2, 0), Point<double>(1, 2), Point<double>(0, 2)
    );
}

TEST(FigureTest, SquareAreaAndCenter) {
    FigurePtr square = create_square<Square>();
    ASSERT_NE(square, nullptr);
    ASSERT_NEAR(square->area(), 1.0, 1e-10); // Площадь квадрата 1x1
    // Центр квадрата (0,0), (1,0), (1,1), (0,1) должен быть (0.5, 0.5)
    ASSERT_NEAR(square->center().x, 0.5, 1e-10);
    ASSERT_NEAR(square->center().y, 0.5, 1e-10);
}

TEST(FigureTest, RectangleAreaAndCenter) {
    FigurePtr rectangle = create_rectangle<Rectangle>();
    ASSERT_NEAR(rectangle->area(), 6.0, 1e-10); // Площадь прямоугольника 2x3
    // Центр прямоугольника (0,0), (2,0), (2,3), (0,3) должен быть (1, 1.5)
    ASSERT_NEAR(rectangle->center().x, 1.0, 1e-10);
    ASSERT_NEAR(rectangle->center().y, 1.5, 1e-10);
}

TEST(FigureTest, TrapezoidAreaAndCenter) {
    FigurePtr trapezoid = create_trapezoid<Trapezoid>();
    ASSERT_NEAR(trapezoid->area(), 3.0, 1e-10); // Площадь трапеции
    // Центр трапеции (0,0), (2,0), (1,2), (0,2) должен быть (0.75, 1)
    ASSERT_NEAR(trapezoid->center().x, 0.75, 1e-10);
    ASSERT_NEAR(trapezoid->center().y, 1.0, 1e-10);
}

TEST(FigureTest, SquareEquality) {
    FigurePtr s1 = create_square<Square>();
    FigurePtr s2 = create_square<Square>();

    ASSERT_TRUE(*s1 == *s2);
}

TEST(FigureTest, RectangleInequality) {
    FigurePtr rect = create_rectangle<Rectangle>();
    FigurePtr square = create_square<Square>();

    ASSERT_FALSE(*rect == *square); // Площади разные
}

TEST(ArrayTest, AddSquareToDynamicArray) {
    Array<FigurePtr> arr;
    arr.add(create_square<Square>());

    ASSERT_EQ(arr.getSize(), 1);
    ASSERT_NEAR(arr.allArea(), 1.0, 1e-10);
}

TEST(ArrayTest, AddRectangleAndTrapezoid) {
    Array<FigurePtr> arr;
    arr.add(create_rectangle<Rectangle>());
    arr.add(create_trapezoid<Trapezoid>());
    
    // Общая площадь: 6 + 3 = 9
    ASSERT_NEAR(arr.allArea(), 9.0, 1e-10);
    ASSERT_EQ(arr.getSize(), 2);
}

TEST(ArrayTest, MixedFiguresTotalArea) {
    Array<FigurePtr> arr;
    arr.add(create_square<Square>());      // 1.0
    arr.add(create_rectangle<Rectangle>()); // 6.0
    arr.add(create_trapezoid<Trapezoid>()); // 3.0
    
    // Общая площадь: 1 + 6 + 3 = 10
    ASSERT_NEAR(arr.allArea(), 10.0, 1e-10);
    ASSERT_EQ(arr.getSize(), 3);
}