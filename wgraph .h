#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include <locale.h>

using namespace std;

struct wedge
{
   int v1;
   int v2;
   double w;
};

//Создает взвешенный граф и вводит его из файла "in_w.txt"
vector<vector<wedge>> wgraph_in();

//Выводит взвешенный граф в файл "out_w.txt"
void wgraph_out(vector<vector<wedge>> wgraph);

//Построение остовного дерева минимального веса
vector<vector<wedge>> min_tree_build(vector<vector<wedge>> wgraph, int v, float *weight);

//Построение дерева кратчайших путей (алгоритм Дейкстры)
vector<wedge> min_pathes_tree_build(vector<vector<wedge>> wgraph, int v);

//Интерфейс работы с графом
void wgraph_interface();
