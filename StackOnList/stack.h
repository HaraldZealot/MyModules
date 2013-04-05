#ifndef STACK_H
#define STACK_H

#include "stackimplementation.h"

namespace hzw
{
   template <typename Data>
   class Stack
   {
      public:
         inline Stack();
         inline Stack(const Stack<Data> &original);
         inline Stack<Data> &operator= (const Stack<Data> &roperand);
         inline ~Stack();
         inline void clear();
         inline void push(const Data &dt);
         inline void onTop(Data &dt) const;
         inline void pop();
         inline bool isEmpty() const;
      private:
         StackImplementation *pimpl;
   };

   template<typename Data>
   Stack<Data>::Stack() :
      pimpl(0)
   {
      pimpl = new StackImplementation;
   }

   template<typename Data>
   Stack<Data>::Stack(const Stack<Data> &original) :
      pimpl(0)
   {
      pimpl = new StackImplementation(*original.pimpl);
   }

   template<typename Data>
   Stack<Data>  &Stack<Data>::operator= (const Stack<Data> &roperand)
   {
      *pimpl = *roperand.pimpl;
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
   void Stack<Data>::push(const Data &dt)
   {
      pimpl->push((void *) &dt, sizeof(Data));
   }

   template<typename Data>
   void Stack<Data>::onTop(Data &dt) const
   {
      pimpl->onTop((void *) &dt);
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

#endif // STACK_H
