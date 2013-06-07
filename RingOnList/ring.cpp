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
      void unionRing(const RingImplementation &a, const RingImplementation &b, Node *&resultH) const;
      void intersectRing(const RingImplementation &a, const RingImplementation &b, Node *&resultH) const;
      void substractRing(const RingImplementation &a, const RingImplementation &b, Node *&resultH) const;
      void clear();
      void copy(Node *&temp, const RingImplementation &original) const;
      void distinctify();
      //void sort();
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

   RingVoid::RingVoid(const RingVoid &original)
   {
      //TODO
   }

   RingVoid &RingVoid::operator=(const RingVoid &rightOperand)
   {
      //TODO
   }

   RingVoid::~RingVoid()
   {
      //TODO
   }

   void RingVoid::goForward(int turn)
   {
      //TODO
   }

   void RingVoid::current(void *dataAdress, int dataSize) const
   {
      //TODO
   }

   void RingVoid::excludeCurrent()
   {
      //TODO
   }

   RingVoid RingVoid::operator+(const RingVoid &rightOperand) const
   {
      //TODO
   }

   RingVoid RingVoid::operator-(const RingVoid &rightOperand) const
   {
      //TODO
   }

   RingVoid RingVoid::operator*(const RingVoid &rightOperand) const
   {
      //TODO
   }

   RingVoid &RingVoid::operator+=(const RingVoid &rightOperand)
   {
      //TODO
   }

   RingVoid &RingVoid::operator-=(const RingVoid &rightOperand)
   {
      //TODO
   }

   RingVoid &RingVoid::operator*=(const RingVoid &rightOperand)
   {
      //TODO
   }

   bool RingVoid::isEmpty() const
   {
      //TODO
   }

   bool RingVoid::hasSingle() const
   {
      //TODO
   }

   bool RingVoid::contain(const void *sample, int samleSize) const
   {
      //TODO
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
      for(register const void *p = 0, *end = dataAdress + count * dataSize;
            p < end; p += dataSize)
         push(p, dataSize);

      Node *head = current_,
            *tail = 0;
      breakRing(head, tail);
      sort(head, tail);
      closeRing(head, tail);
      current_ = head;
      distinctify();
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
      Node *preResult = 0;

      unionRing(*this, rightOperand, preResult);
      RingImplementation result;
      result.current_ = preResult;
      preResult = 0;
      return result;
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator-(const RingImplementation &rightOperand) const
   {
      Node *preResult = 0;

      substractRing(*this, rightOperand, preResult);
      RingImplementation result;
      result.current_ = preResult;
      preResult = 0;
      return result;
   }

   RingVoid::RingImplementation RingVoid::RingImplementation::
   operator*(const RingImplementation &rightOperand) const
   {
      Node *preResult = 0;

      intersectRing(*this, rightOperand, preResult);
      RingImplementation result;
      result.current_ = preResult;
      preResult = 0;
      return result;
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator+=(const RingImplementation &rightOperand)
   {
      Node *preResult = 0;

      unionRing(*this, rightOperand, preResult);
      this->clear();
      this->current_ = preResult;
      preResult = 0;
      return *this;
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator-=(const RingImplementation &rightOperand)
   {
      Node *preResult = 0;

      substractRing(*this, rightOperand, preResult);
      this->clear();
      this->current_ = preResult;
      preResult = 0;
      return *this;
   }

   RingVoid::RingImplementation &RingVoid::RingImplementation::
   operator*=(const RingImplementation &rightOperand)
   {
      Node *preResult = 0;

      intersectRing(*this, rightOperand, preResult);
      this->clear();
      this->current_ = preResult;
      preResult = 0;
      return *this;
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
   unionRing(const RingImplementation &a, const RingImplementation &b, Node *&head) const
   {
      Node *leftHead = 0,
            *leftTail = 0,
             *rightHead = 0,
              *rightTail = 0,
               *tail = 0;

      copy(leftHead, a);
      breakRing(leftHead, leftTail);
      sort(leftHead, leftTail);

      copy(rightHead, b);
      breakRing(rightHead, rightTail);
      sort(rightHead, rightTail);

      while(leftHead && rightHead)
      {
         Node *node = cmp_(leftHead->dataAdress_, rightHead->dataAdress_) < 0
                      ? pop(leftHead, leftTail) : pop(rightHead, rightTail);

         if(!head || cmp_(tail->dataAdress_, node->dataAdress_) != 0)
            push(head, tail, node);
         else
            delete node;
      }

      while(leftHead)
      {
         Node *node = pop(leftHead, leftTail);

         if(!head || cmp_(tail->dataAdress_, node->dataAdress_) != 0)
            push(head, tail, node);
         else
            delete node;
      }

      while(rightHead)
      {
         Node *node = pop(rightHead, rightTail);

         if(!head || cmp_(tail->dataAdress_, node->dataAdress_) != 0)
            push(head, tail, node);
         else
            delete node;
      }

      closeRing(head, tail);
   }

   void RingVoid::RingImplementation::
   intersectRing(const RingImplementation &a, const RingImplementation &b, Node *&head) const
   {
      Node *leftHead = 0,
            *leftTail = 0,
             *rightHead = 0,
              *rightTail = 0,
               *tail = 0;

      copy(leftHead, a);
      breakRing(leftHead, leftTail);
      sort(leftHead, leftTail);

      copy(rightHead, b);
      breakRing(rightHead, rightTail);
      sort(rightHead, rightTail);

      while(leftHead && rightHead)
      {
         Node *node = 0;

         if(cmp_(leftHead->dataAdress_, rightHead->dataAdress_) < 0)
            delete pop(leftHead, leftTail);
         else if(cmp_(leftHead->dataAdress_, rightHead->dataAdress_) > 0)
            delete pop(rightHead, rightTail);
         else
         {
            delete pop(leftHead, leftTail);
            push(head, tail, pop(rightHead, rightTail));
         }
      }

      while(leftHead)
         delete pop(leftHead, leftTail);

      while(rightHead)
         delete pop(rightHead, rightTail);

      closeRing(head, tail);
   }

   void RingVoid::RingImplementation::
   substractRing(const RingImplementation &a, const RingImplementation &b, Node *&head) const
   {
      Node *leftHead = 0,
            *leftTail = 0,
             *rightHead = 0,
              *rightTail = 0,
               *tail = 0;

      copy(leftHead, a);
      breakRing(leftHead, leftTail);
      sort(leftHead, leftTail);

      copy(rightHead, b);
      breakRing(rightHead, rightTail);
      sort(rightHead, rightTail);

      while(leftHead && rightHead)
      {
         Node *node = 0;

         if(cmp_(leftHead->dataAdress_, rightHead->dataAdress_) < 0)
            push(head, tail, pop(leftHead, leftTail));
         else if(cmp_(leftHead->dataAdress_, rightHead->dataAdress_) > 0)
            delete pop(rightHead, rightTail);
         else
         {
            delete pop(leftHead, leftTail);
            delete pop(rightHead, rightTail);
         }
      }

      if(leftHead)
         connect(head, tail, leftHead, leftTail);

      while(rightHead)
         delete pop(rightHead, rightTail);

      closeRing(head, tail);
   }

   void RingVoid::RingImplementation::
   clear()
   {
      if(current_)
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
   }

   void RingVoid::RingImplementation::
   copy(Node *&copied, const RingImplementation &original) const
   {
      copied = 0;

      if(original.current_)
      {
         register Node *p = original.current_;
         register Node *q = 0;

         do
         {
            q = new Node(p->dataAdress_, p->dataSize_);

            if(copied)
            {
               q->next_ = copied;
               q->prev_ = current_->prev_;
               copied->prev_->next_ = q;
               copied->prev_ = q;
            }
            else
            {
               q->next_ = q;
               p->prev_ = q;
               copied = q;
            }

            q = 0;

            p = p->next_;
         }
         while(p != original.current_);
      }
   }

   void RingVoid::RingImplementation::
   distinctify()
   {
      if(current_) {
         Node *p = current_->next_;

         while(p != current_ && p->next_ != p)
         {
            Node *q = p->next_;

            if(cmp_(p->dataAdress_, p->prev_->dataAdress_) == 0)
            {
               p->next_->prev_ = p->prev_;
               p->prev_->next_ = p->next_;
               delete p;
            }

            p = q;
         }
      }
   }

   void RingVoid::RingImplementation::
   sort(Node *&head, Node *&tail) const
   {
      if(head && tail) {
         Node *leftHead = head,
               *leftTail = head,
                *rightHead = tail,
                 *rightTail = tail;
         split(leftHead, leftTail, rightHead, rightTail);

         if(leftHead != leftTail)
            sort(leftHead, leftTail);

         if(rightHead != rightTail)
            sort(rightHead, rightTail);

         merge(leftHead, leftTail, rightHead, rightTail);
         head = leftHead;
         tail = leftTail;
         leftHead = 0;
         leftTail = 0;
         rightHead = 0;
         rightTail = 0;
      }
   }

   void RingVoid::RingImplementation::
   split(Node *&leftHead, Node *&leftTail, Node *&rightHead, Node *&rightTail) const
   {
      bool phase = false;

      while(leftTail->next_ != rightHead)
      {
         if(phase)
            leftTail = leftTail->next_;
         else
            rightHead = rightHead->prev_;

         phase = !phase;
      }

      leftTail->next_ = 0;
      rightHead->prev_ = 0;
   }

   void RingVoid::RingImplementation::
   merge(Node *&leftHead, Node *&leftTail, Node *&rightHead, Node *&rightTail) const
   {
      Node *head = 0, *tail = 0;

      while(leftHead && rightHead)
      {
         if(cmp_(leftHead->dataAdress_, rightHead->dataAdress_) < 0)
            push(head, tail, pop(leftHead, leftTail));
         else
            push(head, tail, pop(rightHead, rightTail));
      }

      if(leftHead)
         connect(head, tail, leftHead, leftTail);

      if(rightHead)
         connect(head, tail, rightHead, rightTail);

      leftHead = head;
      leftTail = tail;
      head = 0;
      tail = 0;
   }

   void RingVoid::RingImplementation::
   connect(Node *&leftHead, Node *&leftTail, Node *&rightHead, Node *&rightTail) const
   {
      leftTail->next_ = rightHead;
      rightHead->prev_ = leftTail;
      leftTail = rightTail;
      rightHead = 0;
      rightTail = 0;
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
