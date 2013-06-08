/**
 * Copyright (c) 2013 Alaksiej Piotr Stankievič (Alaksei Stankevich)
 * All rights reserved.
 * *************************
 * Author: Alaksiej Stankievič
 * *************************
 * module: StackOnList
 * project: MyModules
 *
 * different testcases for class Stack
 * *************************
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Its copy is also available at the root directory of the project.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
