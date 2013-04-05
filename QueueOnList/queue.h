#ifndef QUEUE_H
#define QUEUE_H

#include "queueimplementation.h"

namespace hzw
{
   template <typename Data>
   class Queue
   {
      public:
         inline Queue();
         inline ~Queue();
         inline void clear();
         inline void enqueue(const Data &dt);
         inline void onFront(Data &dt) const;
         inline void onBack(Data &dt) const;
         inline void dequeue();
         inline bool isEmpty() const;
      private:
         QueueImplementation *pimpl;
   };

   template<typename Data>
   Queue<Data>::Queue() :
      pimpl(0)
   {
      pimpl = new QueueImplementation;
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
   void Queue<Data>::enqueue(const Data &dt)
   {
      pimpl->enqueue((void *) &dt, sizeof(Data));
   }

   template<typename Data>
   void Queue<Data>::onFront(Data &dt) const
   {
      pimpl->onFront((void *) &dt);
   }

   template<typename Data>
   void Queue<Data>::onBack(Data &dt) const
   {
      pimpl->onBack((void *) &dt);
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
