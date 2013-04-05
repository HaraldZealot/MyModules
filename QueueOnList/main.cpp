#include <iostream>
#include <fstream>
#include "queue.h"
using namespace std;
using namespace hzw;

class Proba
{
      int n;
      double *coord;
     // Proba();
   public:
      Proba(int nn);
      Proba(const Proba &original);
      Proba &operator= (const Proba &roperand);
      ~Proba();
      friend ostream &operator<<(ostream &out, const Proba &b);
};

int main()
{
   Queue<Proba> q;
   Proba a(3);
   cout << "\n\na:\n" << a;
   q.enqueue(a);
   cout << "on back\n" << q.onBack();
   cout << "after onBack\n";
   cout << "\n\na:\n" << a;
   cout << "on front\n" << q.onFront();
   cout << "after onFront\n";
   cout << "\n\na:\n" << a;
   cout << "before return\n";

   /*ifstream fin("test.in");
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
               num=q.onFront();
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

   */
   return 0;
}

Proba::Proba():
   n(3),
   coord(0)
{
   coord = new double[n];
   coord[0] = 1.1;
   coord[1] = 1.2;
   coord[2] = 1.3;
   cout << "empty constructor\n";
}

Proba::Proba(int nn):
   n(nn),
   coord(0)
{
   coord = new double[n];
   for(int i=0;i<n;++i)
      coord[i]=2.0+0.1*(i+1);
   cout << "empty constructor\n";
}

Proba::Proba(const Proba &original):
   n(original.n),
   coord(0)
{
   coord = new double[n];

   for(int i = 0; i < n; ++i)
      coord[i] = original.coord[i];

   cout << "copy constructor\n";
}
Proba &Proba::operator= (const Proba &roperand)
{
   if(this == &roperand)return *this;

   if(n != roperand.n)
   {
      delete [] coord;
      cout << "coord adress:\n";
      cout << (long)coord << endl;
      coord = 0;
      cout << (long)coord << endl;
      n = roperand.n;
      coord = new double[n];
      cout << (long)coord << endl;
   }

   for(int i = 0; i < n; ++i)
      coord[i] = roperand.coord[i];

   cout << "assign operator\n";
   return *this;
}

Proba::~Proba()
{
   cout << "in destructor\n";
   cout << "n=" << n << endl;

   for(int i = 0; i < n; ++i)
      cout << coord[i] << endl;

   delete [] coord;
   coord = 0;
   n = 0;
   cout << "n=" << n << endl;

   for(int i = 0; i < n; ++i)
      cout << coord[i] << endl;

   cout << "destructor\n";
}


ostream &operator<<(ostream &out, const Proba &b)
{
   out << "Proba instance:\n";

   for(int i = 0; i < b.n; ++i)
   {
      out << b.coord[i] << endl;
   }

   out << endl;
   return out;
}


