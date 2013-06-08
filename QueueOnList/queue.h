/**
 * Copyright (c) 2013 Alaksiej Piotr Stankievič (Alaksei Stankevich)
 * All rights reserved.
 * *************************
 * Author: Alaksiej Stankievič
 * *************************
 * module: QueueOnList
 * project: MyModules
 *
 * declaration of classes Queue and QueueVoid, implementation of Queue
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

#ifndef QUEUE_H
#define QUEUE_H

#include <exception>

namespace hzw
{
   class QueueException: public std::exception
   {
         const char *what() const throw()
         {
            return "hzw::read_from_empty_queue";
         }
   };

   class QueueVoid;

   template <typename Data>
   class Queue
   {
      public:
         inline Queue();
         inline Queue(const Queue &original);
         inline Queue &operator=(const Queue &roperand);
         inline ~Queue();
         inline void clear();
         inline void enqueue(Data dt);
         inline Data onFront() const;
         inline Data onBack() const;
         inline void dequeue();
         inline bool isEmpty() const;
      private:
         QueueVoid *pimpl;
   };

   class QueueVoid
   {
      public:
         QueueVoid();
         QueueVoid(const QueueVoid &original);
         QueueVoid &operator=(const QueueVoid &roperand);
         ~QueueVoid();
         void clear();
         void enqueue(const void *dtAdress, int dtSize);
         void onFront(void *dtAdress) const;
         void onBack(void *dtAdress) const;
         void dequeue();
         bool isEmpty() const;
      private:
         class QueueImplementation;
         QueueImplementation *pimpl;
   };

   template<typename Data>
   Queue<Data>::Queue() :
      pimpl(0)
   {
      pimpl = new QueueVoid;
   }

   template<typename Data>
   Queue<Data>::Queue(const Queue<Data> &original):
      pimpl(0)
   {
      pimpl = new QueueVoid(*original.pimpl);
   }

   template<typename Data>
   Queue<Data> &Queue<Data>::operator=(const Queue<Data> &roperand)
   {
      *pimpl = *roperand.pimpl;
      return *this;
   }

   template<typename Data>
   Queue<Data>::~Queue()
   {
      pimpl->clear();
      delete pimpl;
      pimpl = 0;
   }

   template<typename Data>
   void Queue<Data>::clear()
   {
      pimpl->clear();
   }

   template<typename Data>
   void Queue<Data>::enqueue(Data dt)
   {
      pimpl->enqueue((void *) &dt, sizeof(Data));
   }

   template<typename Data>
   Data Queue<Data>::onFront() const
   {
      unsigned char *bufer = new unsigned char[sizeof(Data)];
      pimpl->onFront((void *) bufer);
      return *((Data *)bufer);
   }

   template<typename Data>
   Data Queue<Data>::onBack() const
   {
      unsigned char *bufer = new unsigned char[sizeof(Data)];
      pimpl->onBack((void *) bufer);
      return *((Data *)bufer);
   }

   template<typename Data>
   void Queue<Data>::dequeue()
   {
      pimpl->dequeue();
   }

   template<typename Data>
   bool Queue<Data>::isEmpty() const
   {
      return pimpl->isEmpty();
   }

}

#endif // QUEUE_H
