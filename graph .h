#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include <locale.h>
#include <time.h>

using namespace std;

struct edge
{
   int v1;
   int v2;
};

//Создает граф и вводит его из файла "in.txt"
vector<vector<int>> graph_in();

//Выводит граф в файл "out.txt"
void graph_out(vector<vector<int>> graph);

//Обход в ширину (возвращает вектор с маршрутом обхода)
vector<int> BFS(vector<vector<int>> graph, int v);

//Обход в глубину (возвращает вектор с маршрутом обхода)
vector<int> DFS(vector<vector<int>> graph, int v);

//Проверка пройден ли граф (возвращает количество посещенных вершин или -1 если все вершины посещены)
int is_passed(vector<bool> marks);

//Поиск всех компонент связности (возвращает двумерный вектор с маршрутами обхода всех компонент связности в глубину)
vector<vector<int>> comp_search(vector<vector<int>> graph);

//Поиск минимального расстояния между двумя вершинами (возвращает кратчайший маршрут между двумя вершинами или 0 если его нет)
vector<int> is_connected(vector<vector<int>> graph, int v1, int v2, int *length);

//Построение остовного дерева
vector<vector<edge>> tree_build(vector<vector<int>> graph, int v);

//Интерфейс работы с графом
void graph_interface();
