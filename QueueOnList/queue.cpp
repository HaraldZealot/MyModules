#include "queue.h"

namespace hzw
{
   class QueueVoid::QueueImplementation
   {
      public:
         QueueImplementation();
         ~QueueImplementation();
         void clear();
         void enqueue(const void *dtAdress, int dtSize);
         void onFront(void *dtAdress) const;
         void onBack(void *dtAdress) const;
         void dequeue();
         bool isEmpty() const;
      private:
         struct Node
         {
            int size;
            void *datum;
            Node *link;
            Node(const void *dtAdress, int dtSize);
            ~Node();
         } *beg, *end;
   };

   QueueVoid::QueueVoid() :
      pimpl(0)
   {
      pimpl = new QueueImplementation;
   }

   QueueVoid::~QueueVoid()
   {
      pimpl->clear();
      delete pimpl;
      pimpl = 0;
   }

   void QueueVoid::clear()
   {
      pimpl->clear();
   }

   void QueueVoid::enqueue(const void *dtAdress, int dtSize)
   {
      pimpl->enqueue(dtAdress, dtSize);
   }

   void QueueVoid::onFront(void *dtAdress) const
   {
      pimpl->onFront(dtAdress);
   }

   void QueueVoid::onBack(void *dtAdress) const
   {
      pimpl->onBack(dtAdress);
   }

   void QueueVoid::dequeue()
   {
      pimpl->dequeue();
   }

   bool QueueVoid::isEmpty() const
   {
      return pimpl->isEmpty();
   }

   QueueVoid::QueueImplementation::
   QueueImplementation() :
      beg(0), end(0)
   {

   }

   QueueVoid::QueueImplementation::
   ~QueueImplementation()
   {
      clear();
   }

   void QueueVoid::QueueImplementation::
   enqueue(const void *dtAdress, int dtSize)
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

   void QueueVoid::QueueImplementation::
   dequeue()
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

   void QueueVoid::QueueImplementation::
   onFront(void *dtAdress) const
   {
      if(beg)
      {
         for(int i = 0; i < beg->size; ++i)
            *((unsigned char *) dtAdress + i) = * ((unsigned char *) beg->datum + i);
      }
      else throw QueueException();
   }

   void QueueVoid::QueueImplementation::
   onBack(void *dtAdress) const
   {
      if(end)
      {
         for(int i = 0; i < end->size; ++i)
            *((unsigned char *) dtAdress + i) = * ((unsigned char *) end->datum + i);
      }
      else throw QueueException();
   }

   bool QueueVoid::QueueImplementation::
   isEmpty() const
   {
      return 0 == beg && 0 == end;
   }

   void QueueVoid::QueueImplementation::
   clear()
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

   QueueVoid::QueueImplementation::Node::
   Node(const void *dtAdress, int dtSize) :
      size(dtSize), datum(0), link(0)
   {
      if(dtAdress && dtSize)
      {
         datum = (void *)(new unsigned char[size]);

         for(int i = 0; i < size; ++i)
            *((unsigned char *) datum + i) = * ((unsigned char *) dtAdress + i);
      }
   }

   QueueVoid::QueueImplementation::Node::
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
