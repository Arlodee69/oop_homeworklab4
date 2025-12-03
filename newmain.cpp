#include <iostream>
#include <memory>
#include <string>
#include "point.hpp"
#include "figure.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "array.hpp"

using FigurePtr = std::shared_ptr<Figure<double>>;
using IntFigurePtr = std::shared_ptr<Figure<int>>;

FigurePtr createFigureFromInput() {
    std::cout << "Выберите тип фигуры:\n";
    std::cout << "1. Квадрат\n";
    std::cout << "2. Прямоугольник\n";
    std::cout << "3. Трапеция\n";
    std::cout << "> ";
    
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1: {
            auto fig = std::make_shared<Square<double>>();
            std::cout << "Введите 4 точки квадрата (x y):\n";
            std::cin >> *fig;
            return fig;
        }
        case 2: {
            auto fig = std::make_shared<Rectangle<double>>();
            std::cout << "Введите 4 точки прямоугольника (x y):\n";
            std::cin >> *fig;
            return fig;
        }
        case 3: {
            auto fig = std::make_shared<Trapezoid<double>>();
            std::cout << "Введите 4 точки трапеции (x y):\n";
            std::cin >> *fig;
            return fig;
        }
        default:
            std::cout << "Неверный выбор. Квадрат по умолчанию.\n";
            return std::make_shared<Square<double>>(
                Point<double>(0, 0), Point<double>(1, 0), Point<double>(1, 1), Point<double>(0, 1)
            );
    }
}

int main() {
    Array<FigurePtr> figureArray;

    char command;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "a - Добавить фигуру\n";
        std::cout << "r - Удалить фигуру по индексу\n";
        std::cout << "p - Показать все фигуры\n";
        std::cout << "s - Показать общую площадь\n";
        std::cout << "q - Выход\n";
        std::cout << "> ";
        std::cin >> command;

        switch (command) {
            case 'a': {
                FigurePtr newFig = createFigureFromInput();
                figureArray.add(std::move(newFig));
                std::cout << "Фигура добавлена.\n";
                break;
            }

            case 'r': {
                if (figureArray.getSize() == 0) {
                    std::cout << "Массив пуст. Нечего удалять.\n";
                    break;
                }

                size_t index;
                std::cout << "Введите индекс фигуры для удаления (0-" << figureArray.getSize()-1 << "): ";
                std::cin >> index;

                if (index < figureArray.getSize()) {
                    figureArray.remove(index);
                    std::cout << "Фигура удалена.\n";
                } else {
                    std::cout << "Неверный индекс.\n";
                }
                break;
            }

            case 'p': {
                if (figureArray.getSize() == 0) {
                    std::cout << "Массив пуст.\n";
                } else {
                    std::cout << "\nСписок фигур\n";
                    std::cout << figureArray;
                    std::cout << "\nДетали каждой фигуры\n";
                    for (size_t i = 0; i < figureArray.getSize(); ++i) {
                        const auto& fig = figureArray.get(i);
                        std::cout << "Фигура " << i << ":\n";
                        std::cout << "  Центр: " << fig->center() << "\n";
                        std::cout << "  Площадь: " << static_cast<double>(*fig) << "\n";
                        std::cout << "\n";
                    }
                }
                break;
            }

            case 's': {
                double totalArea = figureArray.allArea();
                std::cout << "Общая площадь всех фигур: " << totalArea << "\n";
                break;
            }

            case 'q':
                std::cout << "Выход из программы.\n";
                break;

            default:
                std::cout << "Неизвестная команда.\n";
                break;
        }

    } while (command != 'q');

    return 0;
}