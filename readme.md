# A2_SimpleNavigator
Graph algorithms library with console interface \
Библиотека алгоритмов на графах с консольным интерфейсом

## Overview / Обзор
This project implements a C++20 library for working with graphs represented as adjacency matrices. It provides basic graph operations, traversal algorithms (DFS, BFS), shortest path algorithms (Dijkstra, Floyd-Warshall), minimum spanning tree (Prim's algorithm), and traveling salesman problem solution (ant algorithm). \
Данный проект реализует библиотеку на C++20 для работы с графами, представленными в виде матриц смежности. Он предоставляет базовые операции с графами, алгоритмы обхода (DFS, BFS), алгоритмы поиска кратчайших путей (Дейкстра, Флойд-Уоршелл), построение минимального остовного дерева (алгоритм Прима) и решение задачи коммивояжера (муравьиный алгоритм).

## Features / Возможности
Graph representation using adjacency matrix with dynamic size \
Представление графа с помощью матрицы смежности с динамическим размером

Graph traversal: Depth-First Search (non-recursive) and Breadth-First Search \
Обход графа: поиск в глубину (нерекурсивный) и поиск в ширину

Shortest path algorithms: Dijkstra (between two vertices) and Floyd-Warshall (all pairs) \
Алгоритмы поиска кратчайших путей: Дейкстра (между двумя вершинами) и Флойд-Уоршелл (все пары)

Minimum spanning tree: Prim's algorithm \
Минимальное остовное дерево: алгоритм Прима

Traveling Salesman Problem: Ant algorithm \
Задача коммивояжера: муравьиный алгоритм

Console interface for testing all algorithms \
Консольный интерфейс для тестирования всех алгоритмов

Performance comparison of different TSP algorithms (bonus part) \
Сравнение производительности различных алгоритмов для задачи коммивояжера (бонусная часть)

## Project Structure / Структура проекта
```text
├── algos_lib/           # Graph algorithms implementation / Реализация алгоритмов на графах
├── containers/          # Custom data structures (Stack, Queue, MinHeap) /
|                        # Собственные структуры данных (стек, очередь, мин-куча)
├── controller/          # Controller for connecting UI and algorithms /
|                        # Контроллер для связи UI и алгоритмов
├── graph_lib/           # Graph class with adjacency matrix / Класс графа с матрицей смежности
├── tests/               # Unit tests with GTest / Модульные тесты с GTest
├── ui/                  # Console user interface / Консольный пользовательский интерфейс
├── main.cc              # Entry point / Точка входа
└── Makefile             # Build automation / Автоматизация сборки
```
## Requirements / Требования
C++20 compiler (g++ recommended) \
Компилятор с поддержкой C++20 (рекомендуется g++)

Google Test framework (for tests) \
Фреймворк Google Test (для тестов)

Make build system \
Система сборки Make

## Installation and Build / Установка и сборка
```bash
# Clone the repository / Клонируйте репозиторий
git clone <repository-url>
cd A2_SimpleNavigator_v1.0-0/src
```

# Build all libraries and executable / Соберите все библиотеки и исполняемый файл
make all

# The executable will be created as 'graph' in the src directory
# Исполняемый файл 'graph' будет создан в директории src
Makefile targets / Цели Makefile
Target / Цель	Description / Описание
all	Build everything / Собрать всё
s21_graph.a	Build graph library / Собрать библиотеку графа
s21_graph_algorithms.a	Build algorithms library / Собрать библиотеку алгоритмов
containers.a	Build containers library / Собрать библиотеку контейнеров
graph	Build console application / Собрать консольное приложение
test	Run unit tests / Запустить модульные тесты
gcov_report	Generate coverage report / Сгенерировать отчет о покрытии
valgrind	Check for memory leaks / Проверить утечки памяти
clean	Clean build files / Очистить файлы сборки
cl	Format code with clang-format / Форматировать код с помощью clang-format
Usage / Использование
Console Application / Консольное приложение
After building, run the executable:
После сборки запустите исполняемый файл:

bash
./graph
The console interface provides the following options:
Консольный интерфейс предоставляет следующие возможности:

Load graph from file / Загрузить граф из файла
Loads a graph in adjacency matrix format from a text file.
Загружает граф в формате матрицы смежности из текстового файла.

Breadth-First Search / Поиск в ширину
Performs BFS from a starting vertex and displays the traversal order.
Выполняет обход в ширину от начальной вершины и отображает порядок обхода.

Depth-First Search / Поиск в глубину
Performs non-recursive DFS from a starting vertex and displays the traversal order.
Выполняет нерекурсивный обход в глубину от начальной вершины и отображает порядок обхода.

Shortest path between two vertices / Кратчайший путь между двумя вершинами
Finds the shortest path using Dijkstra's algorithm.
Находит кратчайший путь с использованием алгоритма Дейкстры.

Shortest paths between all vertices / Кратчайшие пути между всеми вершинами
Computes all-pairs shortest paths using Floyd-Warshall algorithm.
Вычисляет кратчайшие пути между всеми парами вершин с использованием алгоритма Флойда-Уоршелла.

Minimum spanning tree / Минимальное остовное дерево
Finds the MST using Prim's algorithm and displays its adjacency matrix.
Находит минимальное остовное дерево с использованием алгоритма Прима и отображает его матрицу смежности.

Traveling Salesman Problem / Задача коммивояжера
Solves TSP using ant colony algorithm.
Решает задачу коммивояжера с помощью муравьиного алгоритма.

Compare TSP algorithms (bonus) / Сравнение алгоритмов для задачи коммивояжера (бонус)
Compares performance of ant algorithm with two other algorithms over multiple iterations.
Сравнивает производительность муравьиного алгоритма с двумя другими алгоритмами за несколько итераций.

Exit / Выход

Graph File Format / Формат файла графа
The graph file should contain an adjacency matrix in the following format:
Файл графа должен содержать матрицу смежности в следующем формате:

text
3
0 1 2
1 0 3
2 3 0
First line: number of vertices (n) / Первая строка: количество вершин (n)

Next n lines: adjacency matrix (n x n) with integer weights / Следующие n строк: матрица смежности (n x n) с целочисленными весами

0 indicates no edge (or loop with weight 0) / 0 означает отсутствие ребра (или петля с весом 0)

Testing / Тестирование
The project includes comprehensive unit tests using Google Test framework.
Проект включает комплексные модульные тесты с использованием фреймворка Google Test.

bash
# Run all tests / Запустить все тесты
make test

# Generate coverage report / Сгенерировать отчет о покрытии
make gcov_report

# Check for memory leaks / Проверить утечки памяти
make valgrind
Implementation Details / Детали реализации
Graph class uses adjacency matrix for graph representation
Класс Graph использует матрицу смежности для представления графа

Custom data structures: Stack (for DFS), Queue (for BFS), MinHeap (for Dijkstra)
Собственные структуры данных: стек (для DFS), очередь (для BFS), мин-куча (для Дейкстры)

Algorithms are implemented in a separate class GraphAlgorithms that interacts with Graph only through its public interface
Алгоритмы реализованы в отдельном классе GraphAlgorithms, который взаимодействует с Graph только через его публичный интерфейс

Console interface uses a simple menu-driven approach with input validation
Консольный интерфейс использует простой подход с меню и валидацией ввода

Bonus Part / Бонусная часть
The bonus part implements comparison of three different algorithms for solving the Traveling Salesman Problem:
В бонусной части реализовано сравнение трех различных алгоритмов для решения задачи коммивояжера:

Ant Colony Algorithm (main implementation) / Муравьиный алгоритм (основная реализация)

Branch and Bound (additional algorithm) / Метод ветвей и границ (дополнительный алгоритм)

Simulated Annealing (additional algorithm) / Имитация отжига (дополнительный алгоритм)

The comparison measures execution time for solving the problem N times with each algorithm.
Сравнение измеряет время выполнения для решения задачи N раз каждым алгоритмом.

License / Лицензия
This project is part of the educational program at School 21 (Ecole 42).
Данный проект является частью образовательной программы Школы 21 (Ecole 42).