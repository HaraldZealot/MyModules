#include <cstring>
#include "ring.h"


namespace hzw
{
   class RingVoid::RingImplementation
   {
   public:
      RingImplementation();
      RingImplementation(const void *dataAdress, int dataSize, int count);
      RingImplementation(const RingImplementation &original);
      RingImplementation &operator=(const RingImplementation &rightOperand);
      ~RingImplementation();

      void goForward(int turn);
      void current(void *dataAdress, int dataSize);
      RingImplementation operator+(const RingVoid &rightOperand) const;
      RingImplementation operator-(const RingVoid &rightOperand) const;
      RingImplementation operator*(const RingVoid &rightOperand) const;
      RingImplementation &operator+=(const RingVoid &rightOperand);
      RingImplementation &operator-=(const RingVoid &rightOperand);
      RingImplementation &operator*=(const RingVoid &rightOperand);
      bool isEmpty() const;
      bool hasSingle() const;
      bool contain(const void *sample, int samleSize) const;
   private:
      struct Node
      {
         void *dataAdress_;
         int dataSize_;
         Node *next_, *prev_;
         Node(const void *dataAdress, int dataSize);
         ~Node();
      } *current_;
      void clear();
      void push(const void *dataAdress, int dataSize);
   };

   RingVoid::RingVoid():
      pimpl(0)
   {
      pimpl = new RingImplementation();
   }

   RingVoid::RingVoid(const void *dataAdress, int dataSize, int count):
      pimpl(0)
   {
      pimpl = new RingImplementation(dataAdress, dataSize, count);
   }

//============ RingVoid =============
//======= RingImplementation ========

   RingVoid::RingImplementation::
   RingImplementation():
      current_(0)
   {
   }

   RingVoid::RingImplementation::
   RingImplementation(const void *dataAdress, int dataSize, int count):
      current_(0)
   {
      register const void *p = dataAdress;

      for(register int i = 0; i < count; ++i, p += dataSize)
         push(p, dataSize);
   }

   //copy-swap pattern
   RingVoid::RingImplementation::
   RingImplementation(const RingImplementation &original):
      current_(0)
   {
      if(original.current_)
      {
         register Node *p = original.current_;
         register Node *q = 0, *temp = 0;

         do
         {
            q = new Node(p->dataAdress_, p->dataSize_);

            if(temp)
            {
               q->next_ = temp;
               q->prev_ = current_->prev_;
               temp->prev_->next_ = q;
               temp->prev_ = q;
            }
            else
            {
               q->next_ = q;
               p->prev_ = q;
               temp = q;
            }

            q = 0;

            p = p->next_;
         }
         while(p != original.current_);

         current_ = temp;
         p = 0;
         temp = 0;
      }
   }


   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator=(const RingImplementation &rightOperand)
   {

   }

   RingVoid::RingImplementation::
   ~RingImplementation()
   {
      clear();
      current_ = 0;
   }

   void RingVoid::RingImplementation::
   clear()
   {
      while(current_->next_ != current_)
      {
         Node *p = current_;
         current_ = current_->next_;
         delete p;
      }

      delete current_;
      current_ = 0;
   }

   void RingVoid::RingImplementation::
   push(const void *dataAdress, int dataSize)
   {
      Node *p = 0;
      p = new Node(dataAdress, dataSize);

      if(current_)
      {
         p->next_ = current_;
         p->prev_ = current_->prev_;
         current_->prev_->next_ = p;
         current_->prev_ = p;
      }
      else
      {
         p->next_ = p;
         p->prev_ = p;
         current_ = p;
      }

      p = 0;
   }

//============== Node ===============

   // copy-swap pattern
   RingVoid::RingImplementation::Node::Node(const void *dataAdress, int dataSize):
      dataAdress_(0),
      dataSize_(0),
      next_(0),
      prev_(0)
   {
      void *temp = 0;
      temp = (void *)new unsigned char[dataSize];
      memcpy(temp, dataAdress, dataSize);
      dataSize_ = dataSize;
      dataAdress_ = temp;
      temp = 0;
   }

   // crack-safe destuctor
   RingVoid::RingImplementation::Node::~Node()
   {
      prev_ = 0;
      next_ = 0;
      memset(dataAdress_, 0, dataSize_); //it is being filled zeros
      delete [] dataAdress_;
      dataAdress_ = 0;
      dataSize_ = 0;
   }
}




