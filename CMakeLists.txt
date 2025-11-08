cmake_minimum_required(VERSION 3.10)
project(lab_oop_4 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл main (если он нужен)

# Подключаем модуль FetchContent
include(FetchContent)

# Объявляем источник для GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0 # или последний стабильный тег
)

# Загружаем и настраиваем GoogleTest
# Это делает googletest доступным как внешний проект
FetchContent_MakeAvailable(googletest)

# Теперь можно использовать цель, созданную googletest
add_executable(tests tests.cpp)

# Связываем тесты с библиотекой gtest_main из FetchContent
# FetchContent_MakeAvailable создает цель gtest, gtest_main, gmock, gmock_main
target_link_libraries(tests gtest_main)