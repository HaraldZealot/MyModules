#include "stackimplementation.h"

namespace hzw
{
   StackImplementation::StackImplementation() :
      top(0)
   {

   }

   StackImplementation::StackImplementation(const StackImplementation &original) :
      top(0)
   {
      Node *p=0, *q=original.top;
      while(q)
      {
         Node *r=0;
         r=new Node(q->datum,q->size);
         r->link=p;
         p=r;
         q=q->link;
      }
      q=0;
      while(p)
      {
         Node *r=p;
         r=p->link;
         p->link=q;
         q=p;
         p=r;
         r=0;
      }
      top=q;
      p=q=0;
   }

   StackImplementation &StackImplementation::operator= (const StackImplementation &roperand)
   {
      if(this==&roperand)return *this;
      clear();
      Node *p=0, *q=roperand.top;
      while(q)
      {
         Node *r=0;
         r=new Node(q->datum,q->size);
         r->link=p;
         p=r;
         q=q->link;
      }
      q=0;
      while(p)
      {
         Node *r=p;
         r=p->link;
         p->link=q;
         q=p;
         p=r;
         r=0;
      }
      top=q;
      p=q=0;
      return *this;
   }

   StackImplementation::~StackImplementation()
   {
      clear();
   }

   void StackImplementation::push(const void *dtAdress, int dtSize)
   {
      Node *p = 0;
      p = new Node(dtAdress, dtSize);
      p->link = top;
      top = p;
      p = 0;
   }

   void StackImplementation::pop()
   {
      Node *p = top;

      if(p)
      {
         top = top->link;
         delete p;
         p = 0;
      }
   }

   void StackImplementation::onTop(void *dtAdress) const
   {
      if(top)
      {
         for(int i = 0; i < top->size; ++i)
            *((unsigned char *) dtAdress + i) = *((unsigned char *) top->datum + i);
      }
      else throw StackException();
   }

   bool StackImplementation::isEmpty() const
   {
      return 0 == top;
   }

   void StackImplementation::clear()
   {
      while(top)
      {
         Node *p = top;
         top = top->link;
         delete p;
         p = 0;
      }
   }

   StackImplementation::Node::Node(const void *dtAdress, int dtSize) :
      size(dtSize), datum(0), link(0)
   {
      if(dtAdress && dtSize)
      {
         datum = (void *)(new unsigned char[size]);

         for(int i = 0; i < size; ++i)
            *((unsigned char *) datum + i) = *((unsigned char *) dtAdress + i);
      }
   }

   StackImplementation::Node::~Node()
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


