#include "graph.h"
#include "wgraph.h"

using namespace std;

int main()
{
   setlocale(LC_CTYPE, "RUS");



   enum main_choice {GRAPH = 1, WGRAPH = 2};

   cout << "<1> ����" << endl;
   cout << "<2> ���������� ������" << endl;
   cout << "�������� ����:" << endl;


   int ch;
   cin >> ch;

   bool exit = false;

   do
   {
      switch (ch)
      {
         case GRAPH:
         {
            cout << endl << "�������� ��� ������:" << endl << endl;
            graph_interface();
            exit = true;
            break;
         }
         case WGRAPH:
         {
            cout << endl << "�������� ��� ��������� ��������:" << endl << endl;
            wgraph_interface();
            exit = true;
            break;
         }
         default:
         {
            cout << endl << "����������� �������!" << endl << endl;
            cout << "�������� ����:" << endl;
            cin >> ch;
            exit = false;
            break;
         }
      }
   } while (!exit);

   int p;
   cin >> p;
}