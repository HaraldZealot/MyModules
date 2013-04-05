#ifndef QUEUEIMPLEMENTATION_H
#define QUEUEIMPLEMENTATION_H

#include <exception>

namespace hzw
{
   class QueueException: public std::exception
   {
         const char *what() const throw()
         {
            return "hzw::read_from_empty_queue";
         }
   };
   class QueueImplementation
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
}

#endif // QUEUEIMPLEMENTATION_H
