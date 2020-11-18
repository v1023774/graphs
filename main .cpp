#include "graph.h"
#include "wgraph.h"

using namespace std;

int main()
{
   setlocale(LC_CTYPE, "RUS");



   enum main_choice {GRAPH = 1, WGRAPH = 2};

   cout << "<1> Граф" << endl;
   cout << "<2> Взвешенный орграф" << endl;
   cout << "Выберете граф:" << endl;


   int ch;
   cin >> ch;

   bool exit = false;

   do
   {
      switch (ch)
      {
         case GRAPH:
         {
            cout << endl << "Действия над графом:" << endl << endl;
            graph_interface();
            exit = true;
            break;
         }
         case WGRAPH:
         {
            cout << endl << "Действия над взешенным орграфом:" << endl << endl;
            wgraph_interface();
            exit = true;
            break;
         }
         default:
         {
            cout << endl << "Неизвестная команда!" << endl << endl;
            cout << "Выберете граф:" << endl;
            cin >> ch;
            exit = false;
            break;
         }
      }
   } while (!exit);

   int p;
   cin >> p;
}