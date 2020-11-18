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

//������� ���������� ���� � ������ ��� �� ����� "in_w.txt"
vector<vector<wedge>> wgraph_in();

//������� ���������� ���� � ���� "out_w.txt"
void wgraph_out(vector<vector<wedge>> wgraph);

//���������� ��������� ������ ������������ ����
vector<vector<wedge>> min_tree_build(vector<vector<wedge>> wgraph, int v, float *weight);

//���������� ������ ���������� ����� (�������� ��������)
vector<wedge> min_pathes_tree_build(vector<vector<wedge>> wgraph, int v);

//��������� ������ � ������
void wgraph_interface();
