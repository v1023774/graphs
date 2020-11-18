#include "graph.h"

vector<vector<int>> graph_in()
{
   ifstream fin;
   fin.open("in.txt");
   int E, V;
   fin >> V;
   fin >> E;
   vector<vector<int>> graph;
   graph.resize(V);
   for (int i = 0; i < E; i++)
   {
      int v1, v2;
      fin >> v1 >> v2;
      graph[v1 - 1].push_back(v2 - 1);
      graph[v2 - 1].push_back(v1 - 1);
   }
   fin.close();
   return graph;
}


void graph_out(vector<vector<int>> graph)
{
   ofstream fout;
   fout.open("out.txt");
   for (int i = 0; i < graph.size(); i++)
   {
      fout << i + 1 << ": ";
      for (int j = 0; j < graph[i].size(); j++)
         fout << graph[i][j] + 1 << " ";
      fout << endl;
   }
   fout.close();
}


vector<int> BFS(vector<vector<int>> graph, int v)
{
   v--;
   queue<int> q;
   q.push(v);

   vector<bool> marks;
   marks.resize(graph.size());
   marks[v] = true;

   vector<int> path;

   do
   {
      v = q.front();
      q.pop();
      path.push_back(v);

      for (int i = 0; i < graph[v].size(); i++)
         if (!marks[graph[v][i]])
         {
            marks[graph[v][i]] = true;
            q.push(graph[v][i]);
         }
   } while (!q.empty());

   return path;
}

int is_passed(vector<bool> marks)
{
   bool exit = false;
   int k = 0;
   while (k < marks.size() && !exit)
      if (!marks[k])
         exit = true;
      else
         k++;
   if (exit)
      return k;
   else
      return -1;
}

vector<int> DFS(vector<vector<int>> graph, int v)
{
   v--;

   stack<int> s;
   s.push(v);

   vector<bool> marks;
   marks.resize(graph.size());
   marks[v] = true;

   vector<int> path;

   do
   {
      path.push_back(v);
      for (int i = 0; i < graph[v].size(); i++)
         if (!marks[graph[v][i]])
         {
            marks[graph[v][i]] = true;
            s.push(graph[v][i]);
         }
      if (!s.empty())
      {
         v = s.top();
         s.pop();
      }
   } while (!s.empty());

   return path;
}

vector<vector<int>> comp_search(vector<vector<int>> graph)
{
   int k = 0;
   bool exit = false;
   int v = graph[0][0];

   vector<bool> marks;
   marks.resize(graph.size());

   vector<vector<int>> pathes;

   for (int i = 0; !exit; i++)
   {
      pathes.resize(i + 1);
      marks[v] = true;
      stack<int> s;
      s.push(v);
      do
      {
         pathes[i].push_back(v);
         for (int j = 0; j < graph[v].size(); j++)
            if (!marks[graph[v][j]])
            {
               marks[graph[v][j]] = true;
               s.push(graph[v][j]);
            }
         if (!s.empty())
         {
            v = s.top();
            s.pop();
         }
      } while (!s.empty());
      cout << endl;

      int k = is_passed(marks);

      if (k != -1)
         v = k;
      else
         exit = true;
   }

   return pathes;
}

vector<int> is_connected(vector<vector<int>> graph, int v1, int v2, int *length)
{
   v1--;
   v2--;
   *length = 1;

   int v = v1;

   queue<int> q;
   q.push(v);

   vector<int> marks_tree;
   marks_tree.resize(graph.size());
   marks_tree[v] = 1;

   int t;

   vector<int> tree;
   tree.resize(graph.size());

   bool exit = false;

   for (int i = 0; !q.empty() && !exit; i++)
   {
      v = q.front();
      q.pop();
      t = v;
      *length = marks_tree[v] + 1;

      for (int j = 0; j < graph[v].size() && !exit; j++)
      {
         int n = graph[v][j];

         if (!marks_tree[n])
         {
            if (n == v2)
               exit = true;
            marks_tree[n] = *length;
            q.push(n);
            tree[n] = t;
         }
      }
   }

   vector<int> path;

   if (exit)
   {
      path.resize(*length);

      for (int i = *length - 1; i > 0; i--)
      {
         path[i] = v2;
         v2 = tree[v2];
      }
      path[0] = v1;

      (*length)--;
   }
   else
      *length = 0;
   return path;
}

vector<vector<edge>>  tree_build(vector<vector<int>> graph, int v)
{
   v--;
   vector<vector<edge>>  tree;
   tree.resize(graph.size());

   queue<edge> q;
   for (int i = 0; i < graph[v].size(); i++)
   {
      edge temp;
      temp.v1 = v;
      temp.v2 = graph[v][i];
      q.push(temp);
   }

   vector<bool> intree;
   intree.resize(graph.size());
   intree[v] = true;

   while (!q.empty())
   {
      edge e = q.front();
      q.pop();
      if (!intree[e.v2])
      {
         tree[e.v1].push_back(e);
         intree[e.v2] = true;
         for (int i = 0; i < graph[e.v2].size(); i++)
            if (!intree[graph[e.v2][i]])
            {
               edge temp;
               temp.v1 = e.v2;
               temp.v2 = graph[e.v2][i];
               q.push(temp);
            }
      }
   }
   return tree;
}

void graph_interface()
{
   vector<vector<int>> graph = graph_in();
   enum graph_choice {_DFS = 1, _BFS = 2, COMP_SEARCH = 3, IS_CONNECTED = 4, IS_CONNECTED_FOR_ALL = 5,
                      TREE_BUILD = 6};

   cout << "<1> Обойти граф в глубину" << endl;
   cout << "<2> Обойти граф в ширину" << endl;
   cout << "<3> Найти все компоненты связаности" << endl;
   cout << "<4> Найти кратчайший путь между двумя вершинами" << endl;
   cout << "<5> Найти кратчайший путь между всеми вершинами" << endl;
   cout << "<6> Построить остовное дерево" << endl;
   cout << "Выберете действие с графом:" << endl;

   int ch;
   cin >> ch;

   bool exit = false;

   do
   {
      switch (ch)
      {
         case _DFS:
         {
            cout << endl << "Введите вершину начала обхода:" << endl;
            int v;
            cin >> v;

            vector<int> path = DFS(graph, v);

            cout << endl;
            for (int i = 0; i < path.size(); i++)
               cout << path[i] + 1 << " ";

            exit = true;
            break;
         }
         case _BFS:
         {
            cout << endl << "Введите вершину начала обхода:" << endl;
            int v;
            cin >> v;

            vector<int> path = BFS(graph, v);

            cout << endl;
            for (int i = 0; i < path.size(); i++)
               cout << path[i] + 1 << " ";
            exit = true;
            break;
         }
         case COMP_SEARCH:
         {
            vector<vector<int>> pathes = comp_search(graph);

            for (int i = 0; i < pathes.size(); i++)
            {
               for (int j = 0; j < pathes[i].size(); j++)
               {
                  cout << pathes[i][j] + 1 << " ";
               }
               cout << endl;
            }

            exit = true;
            break;
         }
         case IS_CONNECTED:
         {
            cout << endl << "Введите вершину начала:" << endl;
            int v1;
            cin >> v1;

            cout << endl << "Введите вершину конца:" << endl;
            int v2;
            cin >> v2;

            int length = 0;
            vector<int> path = is_connected(graph, v1, v2, &length);

            if (length)
            {
               cout << endl;
               for (int i = 0; i < path.size(); i++)
                  cout << path[i] + 1 << " ";
            }
            else
               cout << "Пути нет" << endl;

            exit = true;
            break;
         }
         case IS_CONNECTED_FOR_ALL:
         {
            vector<vector<int>> length;
            length.resize(graph.size());

            for (int i = 0; i < graph.size(); i++)
               length[i].resize(graph.size());

            vector<vector<vector<int>>> pathes;
            pathes.resize(graph.size());

            for (int i = 0; i < graph.size(); i++)
               pathes[i].resize(graph.size());

            for (int i = 0; i < graph.size(); i++)
               for (int j = i + 1; j < graph.size(); j++)
                  pathes[i][j] = is_connected(graph, i + 1, j + 1, &length[i][j]);


            ofstream fout;
            fout.open("pathes.txt");

            for (int i = 0; i < pathes.size(); i++)
            {
               for (int j = i + 1; j < graph.size(); j++)
               {
                  if (length[i][j] != 0)
                  {
                     fout << "Расстояние между вершинами " << i + 1 << " и " << j + 1 << " = " << length[i][j] << endl;
                     fout << "Путь между вершинами " << i + 1 << " и " << j + 1 << ":" << endl;
                     for (int k = 0; k < pathes[i][j].size(); k++)
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
         case TREE_BUILD:
         {
            cout << "Введите вершину начала:" << endl;
            int v;
            cin >> v;

            vector<vector<edge>>  tree = tree_build(graph, v);

            ofstream fout;

            fout.open("tree.txt");
            fout << "Вершина начала: " << v << endl;
            for (int i = 0; i < tree.size(); i++)
            {
               fout << i + 1 << ": ";
               for (int j = 0; j < tree[i].size(); j++)
                  fout << "(" << tree[i][j].v2 + 1 << ") ";
               fout << endl;
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

   graph_out(graph);
}