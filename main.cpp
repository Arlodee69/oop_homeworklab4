#include <iostream>
#include "figure.hpp"
#include "square.hpp"

int main() {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(2.0, 0.0);
    Point<double> p3(2.0, 2.0);
    Point<double> p4(0.0, 2.0);

    Square<double> square(p1, p2, p3, p4);

    std::cout << "Квадрат" << std::endl;
    std::cout << square << std::endl;

    std::cout << "\nВведите 4 точки квадрата (x y для каждой точки):" << std::endl;
    Square<double> inputSquare;
    std::cin >> inputSquare;

    std::cout << "\nВы ввели:" << std::endl;
    std::cout << inputSquare << std::endl;

    std::cout << "\nКвадрат по умолчанию равен введённому? " << (square == inputSquare ? "Да" : "Нет") << std::endl;

    auto copiedInputSquare = inputSquare.copy();
    std::cout << "\nКопия введённого квадрата:" << std::endl;
    std::cout << *copiedInputSquare << std::endl;

    return 0;
}