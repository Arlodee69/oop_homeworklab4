#pragma once

#include <iostream>
#include <memory>

template <class T>
class Array {
    private:
        std::unique_ptr<T[]> data;
        size_t size;
        size_t maxSize;

        void resize(size_t newSize) {
            if (newSize <= maxSize) {
                return;
            }

            auto newData = std::make_unique<T[]>(newSize);

            for (size_t i = 0; i < size; ++i) {   
                newData[i] = std::move(data[i]);
            }

            data = std::move(newData);
            maxSize = newSize;
        }
    
    public:
        const T& get(size_t index) const {
            return data[index];
        }
        
        size_t getSize() const {
            return size;
        }

        Array() : size(0), maxSize(8), data(std::make_unique<T[]>(8)) {}
        ~Array() = default;

        Array(const Array& other) : size(other.size), maxSize(other.maxSize) {
            data = std::make_unique<T[]>(maxSize);
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }

        Array& operator=(const Array& other) {
            if (this != &other) {
                Array temp(other);
                *this = std::move(temp);
            }

            return *this;
        }

        Array(Array&& other)
            : data(std::move(other.data)), size(other.size), maxSize(other.maxSize) {
                other.size = 0;
                other.maxSize = 0;
        }

        Array& operator=(Array&& other) {
            if (this != &other) {
                data = std::move(other.data);
                size = other.size;
                maxSize = other.maxSize;

                other.size = 0;
                other.maxSize = 0;
            }

            return *this;
        }

        void add(T&& element) {
            if (size >= maxSize) {
                resize(maxSize * 2);
            }

            data[size++] = std::move(element);
        }

        void remove(size_t index) {
            for (size_t i = index; i < size - 1; ++i) {
                data[i] = std::move(data[i + 1]);
            }

            data[size - 1] = nullptr;
            size--;
        }

        double allArea() const {
            double otv = 0.0;
            for (size_t i = 0; i < size; ++i) {
                otv += (double)*(data[i]);
            }
            return otv;
        }

        template <typename FigureType>
        void readFigure() {
            std::shared_ptr<FigureType> newFig = std::make_shared<FigureType>();

            std::cin >> *newFig;

            add(std::move(newFig));
        }

        friend std::ostream& operator<<(std::ostream& os, const Array& list) {
            os << "Массив (Размер массива: " << list.size << ", максимальный размер: " << list.maxSize << ")" << std::endl;
            for (size_t i = 0; i < list.size; ++i) {
                os << "[Фигура №" << i << "]: " << *list.data[i] << std::endl;
            }

            return os;
        }
};