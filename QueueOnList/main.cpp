#include <iostream>
#include <fstream>
#include "queue.h"
using namespace std;
using namespace hzw;

int main()
{
   ifstream fin("test.in");
   Queue<int> q;

   while(!fin.eof())
   {
      char ch;
      int num;
      fin >> ch;

      switch(ch)
      {
         case 'i':
            fin >> num;
            q.enqueue(num);
            break;
         case 'o':

            if(q.isEmpty())
            {
               cout << "error ";
            }
            else
            {
               q.onFront(num);
               q.dequeue();
               cout << num << ' ';
            }

            break;
      }
   }

   cout << (q.isEmpty() ? "empty " : "nonempty ");
   q.clear();
   cout << (q.isEmpty() ? "empty " : "nonempty ");
   cout << endl;


   return 0;
}

