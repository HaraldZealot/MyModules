#include <cstring>
#include "ring.h"


namespace hzw
{
   class RingVoid::RingImplementation
   {
   public:
      RingImplementation();
      RingImplementation(const void *dataAdress, int dataSize, int count = 1);
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
   private:
      struct Node
      {
         void *dataAdress_;
         int dataSize_;
         Node *next_, *prev_;
         Node(const void *dataAdress, int dataSize);
         ~Node();
      } *current_;
   };

   RingVoid::RingVoid():
      pimpl(0)
   {

   }

//============ RingVoid =============
//======= RingImplementation ========
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
      prev_=0;
      next_=0;
      memset(dataAdress_,0,dataSize_);//it is being filled zeros
      delete [] dataAdress_;
      dataAdress_=0;
      dataSize_=0;
   }
}




