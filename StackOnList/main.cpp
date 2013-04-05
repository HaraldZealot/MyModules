#include <iostream>
#include <fstream>
#include "stack.h"
using namespace std;
using namespace hzw;

int main()
{
   ifstream fin("test.in");
   Stack<int> s,s1;

   while(!fin.eof())
   {
      char ch;
      int num;
      fin >> ch;

      switch(ch)
      {
         case 'i':
            fin >> num;
            s.push(num);
            break;
         case 'o':

            if(s.isEmpty())
            {
               cout << "error ";
            }
            else
            {
               num=s.onTop();
               s.pop();
               cout << num << ' ';
            }

            break;
      }
   }

   cout << (s.isEmpty() ? "empty " : "nonempty ");
   s.clear();
   cout << (s.isEmpty() ? "empty " : "nonempty ");
   cout << endl;
   return 0;
}
