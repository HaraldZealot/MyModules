/*!      \file main.cpp

 * Copyright (c) 2013 Alaksiej Piotr Stankievič (Alaksei Stankevich)
 * All rights reserved.
 * *************************
 * Author: Alaksiej Stankievič
 * *************************
 * module: QueueOnList
 * project: MyModules
 *
 * different testcases for class Queue
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
               num = q.onFront();
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

