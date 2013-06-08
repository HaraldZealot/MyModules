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

   typedef int (*FuncCompare)(const void *, const void *);

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
      inline void excludeCurrent();
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
      static int cmp(const void *a, const void *b);
      RingVoid *pimpl_;
      inline Ring(const RingVoid &original);
   };

   class RingVoid
   {
   private:
      template<class T> friend class Ring;
      RingVoid(FuncCompare cmp);
      RingVoid(FuncCompare cmp, const void *dataAdress, int dataSize, int count = 1);
      RingVoid(const RingVoid &original);
      RingVoid &operator=(const RingVoid &rightOperand);
      ~RingVoid();

      void goForward(int turn);
      void current(void *dataAdress, int dataSize) const;
      void excludeCurrent();
      RingVoid operator+(const RingVoid &rightOperand) const;
      RingVoid operator-(const RingVoid &rightOperand) const;
      RingVoid operator*(const RingVoid &rightOperand) const;
      RingVoid &operator+=(const RingVoid &rightOperand);
      RingVoid &operator-=(const RingVoid &rightOperand);
      RingVoid &operator*=(const RingVoid &rightOperand);
      bool isEmpty() const;
      bool hasSingle() const;
      bool contain(const void *sample, int samleSize) const;

      class RingImplementation;
      RingVoid(const RingImplementation &original);
      RingImplementation *pimpl_;
      FuncCompare cmp_;
   };

   template <typename T>
   Ring<T>::Ring():
      pimpl_(0)
   {
      pimpl_ = new RingVoid((FuncCompare)&hzw::Ring<T>::cmp);
   }

   template <typename T>
   Ring<T>::Ring(T element):
      pimpl_(0)
   {
      pimpl_ = new RingVoid((FuncCompare)hzw::Ring<T>::cmp, (void *)&element, sizeof(T));
   }

   template <typename T>
   Ring<T>::Ring(const T elements[], int count):
      pimpl_(0)
   {
      pimpl_ = new RingVoid((FuncCompare)&hzw::Ring<T>::cmp, (void *)elements, sizeof(T), count);
   }


   template <typename T>
   Ring<T>::Ring(const Ring<T> &original):
      pimpl_(0)
   {
      pimpl_ = new RingVoid(*original.pimpl_);
   }

   template <typename T>
   Ring<T>::Ring(const RingVoid &original):
      pimpl_(0)
   {
      pimpl_ = new RingVoid(original);
   }

   template <typename T>
   Ring<T> &Ring<T>::operator=(const Ring<T> &rightOperand)
   {
      *pimpl_ = *rightOperand.pimpl_;
      return *this;
   }

   template <typename T>
   Ring<T>::~Ring()
   {
      delete pimpl_;
      pimpl_ = 0;
   }

   template <typename T>
   void Ring<T>::goForward(int turn)
   {
      pimpl_->goForward(turn);
   }

   template <typename T>
   T Ring<T>::current() const
   {
      unsigned char *bufer = new unsigned char[sizeof(T)];
      pimpl_->current((void *) bufer, sizeof(T));
      return *((T *)bufer);
   }

   template <typename T>
   void Ring<T>::excludeCurrent()
   {
      pimpl_->excludeCurrent();
   }

   template <typename T>
   Ring<T> Ring<T>::operator+(const Ring<T> &rightOperand) const
   {
      return Ring(*pimpl_ + *rightOperand.pimpl_);
   }

   template <typename T>
   Ring<T> Ring<T>::operator-(const Ring<T> &rightOperand) const
   {
      return Ring(*pimpl_ - *rightOperand.pimpl_);
   }

   template <typename T>
   Ring<T> Ring<T>::operator*(const Ring<T> &rightOperand) const
   {
      return Ring(*pimpl_ * *rightOperand.pimpl_);
   }

   template <typename T>
   Ring<T> &Ring<T>::operator+=(const Ring<T> &rightOperand)
   {
      *pimpl_ += *rightOperand.pimpl_;
      return *this;
   }

   template <typename T>
   Ring<T> &Ring<T>::operator-=(const Ring<T> &rightOperand)
   {
      *pimpl_ -= *rightOperand.pimpl_;
      return *this;
   }

   template <typename T>
   Ring<T> &Ring<T>::operator*=(const Ring<T> &rightOperand)
   {
      *pimpl_ *= *rightOperand.pimpl_;
      return *this;
   }

   template <typename T>
   bool Ring<T>::isEmpty() const
   {
      return pimpl_->isEmpty();
   }

   template <typename T>
   bool Ring<T>::hasSingle() const
   {
      return pimpl_->hasSingle();
   }

   template <typename T>
   bool Ring<T>::contain(T sample) const
   {
      return pimpl_->contain((const void *)&sample, sizeof(T));
   }

   template <typename T>
   int Ring<T>::cmp(const void *a, const void *b)
   {
      return *((T *)a) == *((T *)b) ? 0 : (*((T *)a) < * ((T *)b) ? -1 : 1);
   }
}

#endif // RING_H
