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

//������� ���� � ������ ��� �� ����� "in.txt"
vector<vector<int>> graph_in();

//������� ���� � ���� "out.txt"
void graph_out(vector<vector<int>> graph);

//����� � ������ (���������� ������ � ��������� ������)
vector<int> BFS(vector<vector<int>> graph, int v);

//����� � ������� (���������� ������ � ��������� ������)
vector<int> DFS(vector<vector<int>> graph, int v);

//�������� ������� �� ���� (���������� ���������� ���������� ������ ��� -1 ���� ��� ������� ��������)
int is_passed(vector<bool> marks);

//����� ���� ��������� ��������� (���������� ��������� ������ � ���������� ������ ���� ��������� ��������� � �������)
vector<vector<int>> comp_search(vector<vector<int>> graph);

//����� ������������ ���������� ����� ����� ��������� (���������� ���������� ������� ����� ����� ��������� ��� 0 ���� ��� ���)
vector<int> is_connected(vector<vector<int>> graph, int v1, int v2, int *length);

//���������� ��������� ������
vector<vector<edge>> tree_build(vector<vector<int>> graph, int v);

//��������� ������ � ������
void graph_interface();
