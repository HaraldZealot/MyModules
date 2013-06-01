#ifndef RING_H
#define RING_H

#include <exception>

namespace hzw
{
   class RingException: public std::exception
   {
      const char *what() const throw()
      {
         return "hzw::read_from_empty_ring";
      }
   };

   class RingVoid;

   template <typename Data>
   class Ring
   {
   public:
      inline Ring();
      explicit inline Ring(Data element);
      inline Ring(const Data elements[], int count);
      inline Ring(const Ring &original);
      inline Ring &operator=(const Ring &rightOperand);
      inline ~Ring();

      inline void goForward(int turn);
      inline Data current() const;
      inline Ring<Data> operator+(const Ring<Data> &rightOperand) const;
      inline Ring<Data> operator-(const Ring<Data> &rightOperand) const;
      inline Ring<Data> operator*(const Ring<Data> &rightOperand) const;
      inline Ring<Data> &operator+=(const Ring<Data> &rightOperand);
      inline Ring<Data> &operator-=(const Ring<Data> &rightOperand);
      inline Ring<Data> &operator*=(const Ring<Data> &rightOperand);
      inline bool isEmpty() const;
      inline bool hasSingle() const;
      inline bool contain(Data sample) const;
   private:
      RingVoid *pimpl;
      inline Ring(const RingVoid &original);
   };

   class RingVoid
   {
   private:
      template<class T> friend class Ring;
      RingVoid();
      RingVoid(const void *dataAdress, int dataSize, int count = 1);
      RingVoid(const RingVoid &original);
      RingVoid &operator=(const RingVoid &rightOperand);
      ~RingVoid();

      void goForward(int turn);
      void current(void *dataAdress, int dataSize) const;
      RingVoid operator+(const RingVoid &rightOperand) const;
      RingVoid operator-(const RingVoid &rightOperand) const;
      RingVoid operator*(const RingVoid &rightOperand) const;
      RingVoid &operator+=(const RingVoid &rightOperand);
      RingVoid &operator-=(const RingVoid &rightOperand);
      RingVoid &operator*=(const RingVoid &rightOperand);
      bool isEmpty() const;
      bool hasSingle() const;
      bool contain(const void *sample,int samleSize) const;

      class RingImplementation;
      RingVoid(const RingImplementation &original);
      RingImplementation *pimpl;
   };

   template <typename T>
   Ring<T>::Ring():
      pimpl(0)
   {
      pimpl = new RingVoid();
   }

   template <typename T>
   Ring<T>::Ring(T e):
      pimpl(0)
   {
      pimpl = new RingVoid((void *)&e,sizeof(T));
   }

   template <typename T>
   Ring<T>::~Ring()
   {
      //dtor
   }

}

#endif // RING_H
