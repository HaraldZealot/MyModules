#include "stack.h"

namespace hzw
{
   class StackVoid::StackImplementation
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

   StackVoid::StackVoid() :
      pimpl(0)
   {
      pimpl = new StackImplementation;
   }

   StackVoid::StackVoid(const StackVoid &original) :
      pimpl(0)
   {
      pimpl = new StackImplementation(*original.pimpl);
   }

   StackVoid  &StackVoid::operator= (const StackVoid &roperand)
   {
      *pimpl = *roperand.pimpl;
      return *this;
   }

   StackVoid::~StackVoid()
   {
      pimpl->clear();
      delete pimpl;
      pimpl = 0;
   }

   void StackVoid::clear()
   {
      pimpl->clear();
   }

   void StackVoid::push(const void *dtAdress, int dtSize)
   {
      pimpl->push(dtAdress, dtSize);
   }

   void StackVoid::onTop(void *dtAdress) const
   {
      pimpl->onTop(dtAdress);
   }

   void StackVoid::pop()
   {
      pimpl->pop();
   }

   bool StackVoid::isEmpty() const
   {
      return pimpl->isEmpty();
   }

   StackVoid::StackImplementation::
   StackImplementation() :
      top(0)
   {

   }

   StackVoid::StackImplementation::
   StackImplementation(const StackVoid::StackImplementation &original) :
      top(0)
   {
      Node *p = 0, *q = original.top;

      while(q)
      {
         Node *r = 0;
         r = new Node(q->datum, q->size);
         r->link = p;
         p = r;
         q = q->link;
      }

      while(p)
      {
         Node *r = p;
         r = p->link;
         p->link = q;
         q = p;
         p = r;
         r = 0;
      }

      top = q;
      q = 0;
   }

   StackVoid::StackImplementation &StackVoid::StackImplementation::
   operator= (const StackVoid::StackImplementation &roperand)
   {
      if(this == &roperand)return *this;

      clear();
      Node *p = 0, *q = roperand.top;

      while(q)
      {
         Node *r = 0;
         r = new Node(q->datum, q->size);
         r->link = p;
         p = r;
         q = q->link;
      }

      while(p)
      {
         Node *r = p;
         r = p->link;
         p->link = q;
         q = p;
         p = r;
         r = 0;
      }

      top = q;
      q = 0;
      return *this;
   }

   StackVoid::StackImplementation::
   ~StackImplementation()
   {
      clear();
   }

   void StackVoid::StackImplementation::
   push(const void *dtAdress, int dtSize)
   {
      Node *p = 0;
      p = new Node(dtAdress, dtSize);
      p->link = top;
      top = p;
      p = 0;
   }

   void StackVoid::StackImplementation::
   pop()
   {
      Node *p = top;

      if(p)
      {
         top = top->link;
         delete p;
         p = 0;
      }
   }

   void StackVoid::StackImplementation::
   onTop(void *dtAdress) const
   {
      if(top)
      {
         for(int i = 0; i < top->size; ++i)
            *((unsigned char *) dtAdress + i) = *((unsigned char *) top->datum + i);
      }
      else throw StackException();
   }

   bool StackVoid::StackImplementation::
   isEmpty() const
   {
      return 0 == top;
   }

   void StackVoid::StackImplementation::
   clear()
   {
      while(top)
      {
         Node *p = top;
         top = top->link;
         delete p;
         p = 0;
      }
   }

   StackVoid::StackImplementation::Node::
   Node(const void *dtAdress, int dtSize) :
      size(dtSize), datum(0), link(0)
   {
      if(dtAdress && dtSize)
      {
         datum = (void *)(new unsigned char[size]);

         for(int i = 0; i < size; ++i)
            *((unsigned char *) datum + i) = *((unsigned char *) dtAdress + i);
      }
   }

   StackVoid::StackImplementation::Node::
   ~Node()
   {
      if(datum && size)
      {
         for(int i = 0; i < size; ++i)
            *((unsigned char *) datum + i) = 0;

         size = 0;
         link = 0;
         delete [] datum;
         datum = 0;
      }
   }
}
