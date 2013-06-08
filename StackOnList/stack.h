/*!
 * \file stack.h
 * \brief declaration of classes Stack and StackVoid, implementation of Stack
 *
 * \author Alaksiej Stankievič aka Harald Zealot
 * \copyright (c) 2013 Alaksiej Piotr Stankievič (Alaksei Stankevich).
 * All rights reserved.
 * \copyright Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * \copyright http://www.apache.org/licenses/LICENSE-2.0
 * \copyright Its copy is also available at the root directory of the project.
 * \copyright Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \defgroup StackOnList Stack on list
 * @{
 *
 *
 *
 */

#ifndef STACK_H
#define STACK_H

#include <exception>

/*!
 * \namespace hzw
 * \brief harald zealot's werke
 * \details Namespace for all classes and function in the MyModules project.
*/
namespace hzw
{
   class StackException: public std::exception
   {
         const char *what() const throw()
         {
            return "hzw::read_from_empty_stack";
         }
   };

   class StackVoid;


   template <typename Data>
   class Stack
   {
      public:
         inline Stack();
         inline Stack(const Stack<Data> &original);
         inline Stack<Data> &operator= (const Stack<Data> &roperand);
         inline ~Stack();
         inline void clear();
         inline void push(Data dt);
         inline Data onTop() const;
         inline void pop();
         inline bool isEmpty() const;
      private:
         StackVoid *pimpl;
   };

   class StackVoid
   {
      public:
         StackVoid();
         StackVoid(const StackVoid &original);
         StackVoid &operator= (const StackVoid &roperand);
         ~StackVoid();
         void push(const void *dtAdress, int dtSize);
         void pop();
         void onTop(void *dtAdress) const;
         bool isEmpty() const;
         void clear();
      private:
         class StackImplementation;
         StackImplementation *pimpl;
   };

   template<typename Data>
   Stack<Data>::Stack() :
      pimpl(0)
   {
      pimpl = new StackVoid;
   }

   template<typename Data>
   Stack<Data>::Stack(const Stack<Data> &original) :
      pimpl(0)
   {
      pimpl = new StackVoid(*original.pimpl);
   }

   template<typename Data>
   Stack<Data>  &Stack<Data>::operator= (const Stack<Data> &roperand)
   {
      *pimpl = *roperand.pimpl;
      return *this;
   }

   template<typename Data>
   Stack<Data>::~Stack()
   {
      pimpl->clear();
      delete pimpl;
      pimpl = 0;
   }

   template<typename Data>
   void Stack<Data>::clear()
   {
      pimpl->clear();
   }

   template<typename Data>
   void Stack<Data>::push(Data dt)
   {
      pimpl->push((void *) &dt, sizeof(Data));
   }

   template<typename Data>
   Data Stack<Data>::onTop() const
   {
      unsigned char *bufer = new unsigned char[sizeof(Data)];
      pimpl->onTop((void *) bufer);
      return *((Data *)bufer);
   }

   template<typename Data>
   void Stack<Data>::pop()
   {
      pimpl->pop();
   }

   template<typename Data>
   bool Stack<Data>::isEmpty() const
   {
      return pimpl->isEmpty();
   }
}

/*! @} */
#endif // STACK_H
