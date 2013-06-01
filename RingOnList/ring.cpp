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
      void current(void *dataAdress, int dataSize) const;
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
      void copy(Node *&temp, const RingImplementation &original) const;
      void sort();
      static void sort(Node *&head, Node *&tail);
      static void split(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2);
      static void merge(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2);
      static void connect(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2);
      void push(const void *dataAdress, int dataSize);
      static void push(Node *&head, Node *&tail, Node *node);
      static Node *pop(Node *&head, Node *&tail);
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
      Node *temp = 0;
      copy(temp, original);
      current_ = temp;
      temp = 0;
   }

   //copy-swap pattern
   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator=(const RingImplementation &rightOperand)
   {
      if(this != &rightOperand)
      {
         Node *temp = 0;
         copy(temp, rightOperand);

         if(temp)
         {
            clear();
            current_ = temp;
         }
      }

      return *this;
   }

   RingVoid::RingImplementation::
   ~RingImplementation()
   {
      clear();
      current_ = 0;
   }

   void RingVoid::RingImplementation::
   goForward(int turn)
   {
      if(current_)
      {
         for(int i = 0; i < turn; ++i)
            current_ = current_->next_;
      }
   }

   void RingVoid::RingImplementation::
   current(void *dataAdress, int dataSize) const
   {
      if(current_)
      {
         if(dataSize == current_->dataSize_)
            memcpy(dataAdress, current_->dataAdress_, dataSize);
         else
         {
            // !!! it must be never happend
            char *p = 0;
            *p = 0;
         }
      }
      else
         throw RingException();
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator+(const RingVoid &rightOperand) const
   {
      RingImplementation result,
                         left(*this),
                         right(*rightOperand.pimpl);
      left.sort();
      right.sort();
      register Node *head = 0, *tail = 0;

      // TODO
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator-(const RingVoid &rightOperand) const
   {
      // TODO
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator*(const RingVoid &rightOperand) const
   {
      // TODO
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator+=(const RingVoid &rightOperand)
   {
      // TODO
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator-=(const RingVoid &rightOperand)
   {
      // TODO
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator*=(const RingVoid &rightOperand)
   {
      // TODO
   }

   bool RingVoid::RingImplementation::
   isEmpty() const
   {
      return 0 == current_;
   }

   bool RingVoid::RingImplementation::hasSingle() const
   {
      return 0 != current_ && current_ == current_->next_;
   }

   // TODO:
   // use Data comparsion predicate, not the memory comparsion
   bool RingVoid::RingImplementation::contain(const void *sample, int sampleSize) const
   {
      bool find = true;

      if(current_)
      {
         Node *p = current_;

         do
         {
            find = find || 0 == memcmp(sample, p->dataAdress_, sampleSize);
         }
         while(!find && p != current_);

         p = 0;
      }

      return find;
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
   copy(Node *&temp, const RingImplementation &original) const
   {
      temp = 0;

      if(original.current_)
      {
         register Node *p = original.current_;
         register Node *q = 0;

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
      }
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

   void RingVoid::RingImplementation::sort()
   {
      if(0 != current_ && current_ != current_->next_)
      {
         Node *tail = current_, *head = current_->prev_;
         tail->prev_ = 0;
         head->next_ = 0;
         sort(head, tail);
         tail->prev_ = head;
         head->next_ = tail;
         current_ = head;
         head = 0;
         tail = 0;
      }
   }
   void RingVoid::RingImplementation::sort(Node *&head, Node *&tail)
   {
      register Node *head1 = head,
                     *tail1 = head,
                      *head2 = tail,
                       *tail2 = tail;
      split(head1, tail1, head2, tail2);

      if(head1 != tail1)
         sort(head1, tail1);

      if(head2 != tail2)
         sort(head2, tail2);

      merge(head1, tail1, head2, tail2);
      head = head1;
      tail = tail1;
      head1 = 0;
      tail1 = 0;
      head2 = 0;
      tail2 = 0;
   }

   void RingVoid::RingImplementation::
   split(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2)
   {
      bool phase = false;

      while(tail1->next_ != head2)
      {
         if(phase)
            tail1 = tail1->next_;
         else
            head2 = head2->prev_;

         phase = !phase;
      }

      tail1->next_ = 0;
      head2->prev_ = 0;
   }

   void RingVoid::RingImplementation::
   merge(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2)
   {
      register Node *head = 0, *tail = 0;

      while(head1 && head2)
      {
         if(memcmp(head1->dataAdress_, head2->dataAdress_, head1->dataSize_) < 0)
            push(head, tail, pop(head1, tail1));
         else
            push(head, tail, pop(head2, tail2));
      }

      if(head1)
         connect(head, tail, head1, tail1);

      if(head2)
         connect(head, tail, head2, tail2);

      head1 = head;
      tail1 = tail;
      head = 0;
      tail = 0;
   }
   void RingVoid::RingImplementation::
   connect(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2)
   {
      tail1->next_ = head2;
      head2->prev_ = tail1;
      tail1 = tail2;
      head2 = 0;
      tail2 = 0;
   }

   void RingVoid::RingImplementation::
   push(Node *&head, Node *&tail, Node *node)
   {
      if(!head)
      {
         head = node;
      }
      else
      {
         tail->next_ = node;
         node->prev_ = tail;
      }

      tail = node;
      tail->next_ = 0;
   }

   RingVoid::RingImplementation::Node *RingVoid::RingImplementation::
   pop(Node *&head, Node *&tail)
   {
      Node *result = head;

      if(head)
      {
         head = head->next_;
         result->next_ = 0;
         (head ? head->prev_ : tail) = 0;
      }

      return result;
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
