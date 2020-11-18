#include "wgraph.h"

class compare
{
public:
   bool operator() (wedge x, wedge y)
   {
      return x.w > y.w;
   }
};

vector<vector<wedge>> wgraph_in()
{
   ifstream fin;
   fin.open("in_w.txt");
   int V, E;
   fin >> V;
   fin >> E;
   vector<vector<wedge>> wgraph;
   wgraph.resize(V);
   for (int i = 0; i < E; i++)
   {
      int v1, v2, w;
      fin >> v1 >> v2 >> w;
      wedge e;
      e.v1 = --v1;
      e.v2 = --v2;
      e.w = w;
      wgraph[v1].push_back(e);
   }
   fin.close();
   return wgraph;
}

void wgraph_out(vector<vector<wedge>> wgraph)
{
   ofstream fout;
   fout.open("out_w.txt");
   for (int i = 0; i < wgraph.size(); i++)
   {
      fout << i + 1 << ": ";
      for (int j = 0; j < wgraph[i].size(); j++)
         fout << "(" << wgraph[i][j].v2 + 1 << " " << wgraph[i][j].w << ") ";
      fout << endl;
   }
   fout.close();
}


vector<vector<wedge>> min_tree_build(vector<vector<wedge>> wgraph, int v, float *weight)
{
   v--;
   vector<vector<wedge>> tree;
   tree.resize(wgraph.size());

   priority_queue<wedge, vector<wedge>, compare> q;
   for (int i = 0; i < wgraph[v].size(); i++)
   {
      wedge temp;
      temp.v1 = v;
      temp.v2 = wgraph[v][i].v2;
      temp.w = wgraph[v][i].w;
      q.push(temp);
   }

   vector<bool> intree;
   intree.resize(wgraph.size());
   intree[v] = true;

   while (!q.empty())
   {
      wedge e = q.top();
      q.pop();
      if (!intree[e.v2])
      {
         tree[e.v1].push_back(e);

         (*weight) += e.w;
         intree[e.v2] = true;
         for (int i = 0; i < wgraph[e.v2].size(); i++)
            if (!intree[wgraph[e.v2][i].v2])
            {
               wedge temp;
               temp.v1 = e.v2;
               temp.v2 = wgraph[e.v2][i].v2;
               temp.w = wgraph[e.v2][i].w;
               q.push(temp);
            }
      }
   }
   return tree;
}


vector<wedge> min_pathes_tree_build(vector<vector<wedge>> wgraph, int v)
{
   v--;
   vector<wedge> d_tree;
   d_tree.resize(wgraph.size());

   priority_queue<wedge, vector<wedge>, compare> q;
   for (int i = 0; i < wgraph[v].size(); i++)
   {
      wedge temp;
      temp.v1 = v;
      temp.v2 = wgraph[v][i].v2;
      temp.w = wgraph[v][i].w;
      q.push(temp);
   }

   vector<bool> intree;
   intree.resize(wgraph.size());
   intree[v] = true;

   while (!q.empty())
   {
      wedge e = q.top();
      q.pop();
      float weight = e.w;
      if (!intree[e.v2])
      {
         wedge rev_e;
         rev_e.v1 = e.v2;
         rev_e.v2 = e.v1;
         rev_e.w = e.w;

         d_tree[e.v2] = rev_e;

         intree[e.v2] = true;
         for (int i = 0; i < wgraph[e.v2].size(); i++)
            if (!intree[wgraph[e.v2][i].v2])
            {
               wedge temp;
               temp.v1 = e.v2;
               temp.v2 = wgraph[e.v2][i].v2;
               temp.w = wgraph[e.v2][i].w + weight;
               q.push(temp);
            }
      }
   }
   return d_tree;
}

void wgraph_interface()
{
   vector<vector<wedge>> wgraph = wgraph_in();

   enum wgraph_choice { MIN_TREE_BUILD = 1, DIJKSTRA = 2};

   cout << "<1> Построить минимальное остовное дерево" << endl;
   cout << "<2> Найти кратчайшие маршруты между всеми вершинами" << endl;
   cout << "Выберете действие с графом:" << endl;

   int ch;
   cin >> ch;

   bool exit = false;

   do
   {
      switch (ch)
      {
         case MIN_TREE_BUILD:
         {
            cout << "Введите вершину начала:" << endl;
            int v;
            cin >> v;

            float weight = 0;
            vector<vector<wedge>> tree = min_tree_build(wgraph, v, &weight);

            ofstream fout;

            fout.open("min_tree.txt");

            fout << "Вершина начала: " << v << endl;
            for (int i = 0; i < tree.size(); i++)
            {
               fout << i + 1 << ": ";
               for (int j = 0; j < tree[i].size(); j++)
                  fout << "(" << tree[i][j].v2 + 1 << " " << tree[i][j].w << ") ";
               fout << endl;
            }
            fout << "Суммарный вес дерева: " << weight << endl;

            fout.close();

            exit = true;
            break;
         }
         case DIJKSTRA:
         {
            vector<vector<int>> length;
            length.resize(wgraph.size());

            for (int i = 0; i < wgraph.size(); i++)
               length[i].resize(wgraph.size());

            vector<vector<vector<int>>> pathes;
            pathes.resize(wgraph.size());

            for (int i = 0; i < wgraph.size(); i++)
               pathes[i].resize(wgraph.size());

            for (int i = 0; i < wgraph.size(); i++)
            {
               vector<wedge> d_tree = min_pathes_tree_build(wgraph, i + 1);
               for (int j = 0; j < wgraph.size(); j++)
                  if (i != j)
                  {
                     int v = j;
                     length[i][j] = d_tree[j].w;
                     if (length[i][j])
                     {
                        vector<int> path;
                        do
                        {
                           path.push_back(v);
                           v = d_tree[v].v2;
                        } while (v != i);

                        path.push_back(i);

                        pathes[i][j] = path;
                     }
                  }
            }
               
            ofstream fout;
            fout.open("w_pathes.txt");
            for (int i = 0; i < pathes.size(); i++)
            {
               for (int j = 0; j < wgraph.size(); j++)
                  if (i != j)
                  {
                     if (length[i][j] != 0)
                     {
                        fout << "Расстояние между вершинами " << i + 1 << " и " << j + 1 << " = " << length[i][j] << endl;
                        fout << "Путь между вершинами " << i + 1 << " и " << j + 1 << ":" << endl;
                        for (int k = pathes[i][j].size() - 1; k >= 0; k--)
                        {
                           if (k)
                              fout << pathes[i][j][k] + 1 << "-";
                           else
                              fout << pathes[i][j][k] + 1;
                        }
                        fout << endl << endl;
                     }
                     else
                        fout << "Пути между вершинами " << i + 1 << " и " << j + 1 << " нет" << endl << endl;
               }
            }

            fout.close();

            exit = true;
            break;
         }
         default:
         {
            cout << endl << "Неизвестная команда!" << endl << endl;
            cout << "Выберете действие с графом:" << endl;
            cin >> ch;
            exit = false;
            break;
         }
      }
   } while (!exit);

   wgraph_out(wgraph);
}