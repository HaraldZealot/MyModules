#ifndef QUEUE_H
#define QUEUE_H

#include <exception>

namespace hzw
{
   class QueueVoid;
   class QueueImplementation;

   class QueueException: public std::exception
   {
         const char *what() const throw()
         {
            return "hzw::read_from_empty_queue";
         }
   };

   template <typename Data>
   class Queue
   {
      public:
         inline Queue();
         inline ~Queue();
         inline void clear();
         inline void enqueue(const Data &dt);
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
         ~QueueVoid();
         void clear();
         void enqueue(const void *dtAdress, int dtSize);
         void onFront(void *dtAdress) const;
         void onBack(void *dtAdress) const;
         void dequeue();
         bool isEmpty() const;
      private:
         QueueImplementation *pimpl;
   };

   template<typename Data>
   Queue<Data>::Queue() :
      pimpl(0)
   {
      pimpl = new QueueVoid;
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
   Data Queue<Data>::onFront() const
   {
      unsigned char *bufer=new unsigned char[sizeof(Data)];
      pimpl->onBack((void *) bufer);
      return *((Data *)bufer);
   }

   template<typename Data>
   Data Queue<Data>::onBack() const
   {
      unsigned char *bufer=new unsigned char[sizeof(Data)];
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
