#include "queueimplementation.h"

namespace hzw
{
   QueueImplementation::QueueImplementation() :
      beg(0), end(0)
   {

   }

   QueueImplementation::~QueueImplementation()
   {
      clear();
   }

   void QueueImplementation::enqueue(const void *dtAdress, int dtSize)
   {
      Node *p = 0;
      p = new Node(dtAdress, dtSize);

      if(end)
         end->link = p;
      else
         beg = p;

      end = p;
      p = 0;
   }

   void QueueImplementation::dequeue()
   {
      Node *p = beg;

      if(p)
      {
         beg = beg->link;

         if(!beg)
            end = 0;

         delete p;
         p = 0;
      }
   }

   void QueueImplementation::onFront(void *dtAdress) const
   {
      if(beg)
      {
         for(int i = 0; i < beg->size; ++i)
            *((unsigned char *) dtAdress + i) = * ((unsigned char *) beg->datum + i);
      }
      else throw QueueException();
   }

   void QueueImplementation::onBack(void *dtAdress) const
   {
      if(end)
      {
         for(int i = 0; i < end->size; ++i)
            *((unsigned char *) dtAdress + i) = * ((unsigned char *) end->datum + i);
      }
      else throw QueueException();
   }

   bool QueueImplementation::isEmpty() const
   {
      return 0 == beg && 0 == end;
   }

   void QueueImplementation::clear()
   {
      while(beg)
      {
         Node *p = beg;
         beg = beg->link;
         delete p;
         p = 0;
      }

      end = 0;
   }

   QueueImplementation::Node::Node(const void *dtAdress, int dtSize) :
      size(dtSize), datum(0), link(0)
   {
      if(dtAdress && dtSize)
      {
         datum = (void *)(new unsigned char[size]);

         for(int i = 0; i < size; ++i)
            *((unsigned char *) datum + i) = * ((unsigned char *) dtAdress + i);
      }
   }

   QueueImplementation::Node::~Node()
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
