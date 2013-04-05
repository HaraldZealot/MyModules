#ifndef STACKIMPLEMENTATION_H
#define STACKIMPLEMENTATION_H

#include <exception>

namespace hzw
{
   class StackException: public std::exception
   {
         const char *what() const throw()
         {
            return "hzw::read_from_empty_stack";
         }
   };
   class StackImplementation
   {
      public:
         StackImplementation();
         StackImplementation(const StackImplementation &original);
         StackImplementation &operator= (const StackImplementation &roperand);
         ~StackImplementation();
         void push(const void *dtAdress, int dtSize);
         void pop();
         void onTop(void *dtAdress) const;
         bool isEmpty() const;
         void clear();
      private:
         struct Node
         {
            int size;
            void *datum;
            Node *link;
            Node(const void *dtAdress, int dtSize);
            ~Node();
         } *top;
   };
}

#endif // STACKIMPLEMENTATION_H

