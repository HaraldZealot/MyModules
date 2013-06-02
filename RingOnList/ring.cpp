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
      void excludeCurrent();
      RingImplementation operator+(const RingImplementation &rightOperand) const;
      RingImplementation operator-(const RingImplementation &rightOperand) const;
      RingImplementation operator*(const RingImplementation &rightOperand) const;
      RingImplementation &operator+=(const RingImplementation &rightOperand);
      RingImplementation &operator-=(const RingImplementation &rightOperand);
      RingImplementation &operator*=(const RingImplementation &rightOperand);
      bool isEmpty() const;
      bool hasSingle() const;
      bool contain(const void *sample, int samleSize) const;
      void setCmp(FuncCompare cmp) {cmp_ = cmp;}
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
      void sort(Node *&head, Node *&tail) const;
      void split(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2) const;
      void merge(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2) const;
      void connect(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2) const;
      void push(const void *dataAdress, int dataSize);
      static void push(Node *&head, Node *&tail, Node *node);
      static Node *pop(Node *&head, Node *&tail);
      inline void breakRing(Node *&head, Node *&tail) const;
      inline void closeRing(Node *&head, Node *&tail) const;
      FuncCompare cmp_;
   };

//============ RingVoid =============

   RingVoid::RingVoid():
      pimpl(0)
   {
      pimpl = new RingImplementation();
      pimpl->setCmp(cmp_);
   }

   RingVoid::RingVoid(const void *dataAdress, int dataSize, int count):
      pimpl(0)
   {
      pimpl = new RingImplementation(dataAdress, dataSize, count);
      pimpl->setCmp(cmp_);
   }

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

   void RingVoid::RingImplementation::
   excludeCurrent()
   {
      if(current_)
      {
         Node *p = 0;

         if(current_ != current_->next_)
         {
            p = current_->prev_;
            p->next_ = current_->next_;
            current_->next_->prev_ = p;
         }

         delete current_;
         current_ = p;
      }
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator+(const RingImplementation &rightOperand) const
   {
      Node *leftH = 0,
            *leftT = 0,
             *rightH = 0,
              *rightT = 0,
               *resultH = 0,
                *resultT = 0;

      copy(leftH, *this);
      breakRing(leftH, leftT);
      sort(leftH, leftT);

      copy(rightH, rightOperand);
      breakRing(rightH, rightT);
      sort(rightH, rightT);

      while(leftH && rightH)
      {
         Node *node = cmp_(leftH->dataAdress_, rightH->dataAdress_) < 0
                      ? pop(leftH, leftT) : pop(rightH, rightT);

         if(!resultH || cmp_(resultT->dataAdress_, node->dataAdress_) != 0)
            push(resultH, resultT, node);
      }

      while(leftH)
      {
         Node *node = pop(leftH, leftT);

         if(!resultH || cmp_(resultT->dataAdress_, node->dataAdress_) != 0)
            push(resultH, resultT, node);
      }

      while(leftH)
      {
         Node *node = pop(rightH, rightT);

         if(!resultH || cmp_(resultT->dataAdress_, node->dataAdress_) != 0)
            push(resultH, resultT, node);
      }

      closeRing(resultH, resultT);
      RingImplementation result;
      result.current_ = resultH;
      resultH = 0;
      return result;
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator-(const RingImplementation &rightOperand) const
   {
      // TODO
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator*(const RingImplementation &rightOperand) const
   {
      // TODO
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator+=(const RingImplementation &rightOperand)
   {
      // TODO
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator-=(const RingImplementation &rightOperand)
   {
      // TODO
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator*=(const RingImplementation &rightOperand)
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

   bool RingVoid::RingImplementation::contain(const void *sample, int sampleSize) const
   {
      bool find = true;

      if(current_)
      {
         Node *p = current_;

         do
         {
            find = find || 0 == cmp_(sample, p->dataAdress_);
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
         Node *head = current_, *tail = 0;
         breakRing(head, tail);
         sort(head, tail);
         closeRing(head, tail);
         current_ = head;
         head = 0;
      }
   }

   void RingVoid::RingImplementation::
   sort(Node *&head, Node *&tail) const
   {
      if(head && tail) {
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
   }

   void RingVoid::RingImplementation::
   split(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2) const
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
   merge(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2) const
   {
      register Node *head = 0, *tail = 0;

      while(head1 && head2)
      {
         if(cmp_(head1->dataAdress_, head2->dataAdress_) < 0)
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
   connect(Node *&head1, Node *&tail1, Node *&head2, Node *&tail2) const
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
      if(node) {
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

   void RingVoid::RingImplementation::
   breakRing(Node *&head, Node *&tail) const
   {
      if(head)
      {
         if(head != head->next_)
            tail = head->prev_;
         else
            tail = head;

         tail->next_ = 0;
         head->prev_ = 0;
      }
   }

   void RingVoid::RingImplementation::
   closeRing(Node *&head, Node *&tail) const
   {
      if(head && tail)
      {
         head->prev_ = tail;
         tail->next_ = head;
         tail = 0;
      }
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
