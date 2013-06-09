/*!   \file main.h
 *    \brief different testcases for Ring
 *
 *    \author Alaksiej Stankievič aka Harald Zealot
 *    \copyright (c) 2013 Alaksiej Piotr Stankievič (Alaksei Stankevich).
 * All rights reserved.
 *    \copyright Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *    \copyright http://www.apache.org/licenses/LICENSE-2.0
 *    \copyright Its copy is also available at the root directory of the project.
 *    \copyright Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "ring.h"

using namespace std;
using namespace hzw;

template<typename T>
ostream &operator<<(ostream &out, Ring<T> &ring);

int main()
{
   try {
      Ring<int> a(5);
      cout << "ring a: " << a << endl;
      int elements1[4] = {5, 5 , 1, 2};
      Ring<int> b(elements1, 4);
      cout << "ring b: " << b << endl;
      Ring<int> c;
      cout << "ring c: " << c << endl;
      c = a + b;
      cout << "ring a + b: " << c << endl;
      c = a - b;
      cout << "ring a - b: " << c << endl;
      c = b - a;
      cout << "ring b - a: " << c << endl;
      c = a * b;
      cout << "ring a * b: " << c << endl;
      a += Ring<int>(7);
      cout << "ring a: " << a << endl;
      int elements2[6] = {7, 4, 10, 7, 4, 8};
      a += Ring<int>(elements2, 6);
      cout << "ring a: " << a << endl;
      a += Ring<int>();
      cout << "ring a: " << a << endl;
      a -= Ring<int>();
      cout << "ring a: " << a << endl;
      a *= Ring<int>();
      cout << "ring a: " << a << endl;
      a += a;
      cout << "ring a: " << a << endl;
      a -= b;
      cout << "ring a: " << a << endl;
      a -= a;
      cout << "ring a: " << a << endl;
      a *= a;
      cout << "ring a: " << a << endl;
      a *= b;
      cout << "ring a: " << a << endl;
      a += b;
      cout << "ring a: " << a << endl;

      cout << endl;
      a -= Ring<int>(1);
      a += Ring<int>(7);
      cout << "ring a: " << a << endl;
      b += Ring<int>(-1);
      cout << "ring b: " << b << endl;
      c = a + b;
      cout << "ring a + b: " << c << endl;
      c = a - b;
      cout << "ring a - b: " << c << endl;
      c = b - a;
      cout << "ring b - a: " << c << endl;
      c = a * b;
      cout << "ring a * b: " << c << endl;

      cout << "\n\n=======================\n\n";
      a += b + Ring<int>(elements2, 6);

      while(!a.isEmpty()) {
         cout << "ring a: " << a << endl;
         cout << "has ring a single element? " << boolalpha << a.hasSingle() << endl;
         cout << "has ring a element '1'?    " << boolalpha << a.contain(1) << endl;
         cout << "has ring a element '7'?    " << boolalpha << a.contain(7) << endl;
         int turn = rand() % 16;
         cout << "the " << setw(2) << turn + 1 << " element has been selected" << endl;
         a.goForward(turn);
         cout << "it's " << a.current() << endl << endl;
         a.excludeCurrent();
      }

      cout << "ring a: " << a << endl;
   }
   catch(exception &e)
   {
      cerr << "\n\nAn exception has been occured.\n";
      cerr << e.what() << endl;
   }

   return 0;
}

template<typename T>
ostream &operator<<(ostream &out, Ring<T> &ring)
{
   if(ring.isEmpty())
      out << "\342\210\205"; // UTF-8 for empty set sign. In non unicode console try: out<<"%";
   else
   {
      T temp;
      out << '{' << (temp = ring.current());
      ring.goForward(1);

      for(; temp != ring.current(); ring.goForward(1))
         out << ", " << ring.current();

      out << '}';
   }

   return out;
}
