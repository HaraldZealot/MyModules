#ifndef STACK_H
#define STACK_H

#include <exception>

namespace hzw
{
   class StackVoid;
   class StackImplementation;

   class StackException: public std::exception
   {
         const char *what() const throw()
         {
            return "hzw::read_from_empty_stack";
         }
   };

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
      unsigned char *bufer=new unsigned char[sizeof(Data)];
      pimpl->onBack((void *) bufer);
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

#endif // STACK_H
