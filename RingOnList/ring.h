/*!
 * \file ring.h
 * \brief declaration of classes Ring and RingVoid, implementation of Ring
 *
 * \author Alaksiej Stankievič aka Harald Zealot
 * \copyright (c) 2013 Alaksiej Piotr Stankievič (Alaksei Stankevich).
 * All rights reserved.
 * \copyright Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * \copyright http://www.apache.org/licenses/LICENSE-2.0
 * \copyright Its copy is also available at the root directory of the project.
 * \copyright Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \defgroup RingOnList Ring on list
 * @{
 */

#ifndef RING_H
#define RING_H

#include <exception>

/*!
 * \namespace hzw
 * \brief harald zealot's werke
 * \details Namespace for all classes and function in the MyModules project.
*/
namespace hzw
{
   /*!
    * \class RingException ring.h "hzw/ring.h"
    * \brief Exception it will be thrown while trying to read from empty Ring.
    */
   class RingException: public std::exception
   {
      //! Exception's message.
      const char *what() const throw()
      {
         return "hzw::read_from_empty_ring";
      }
   };

   /*!
    * Pointer to function with typical for compare function signature
    * \param [in] a The memory area contains object a.
    * \param [in] b The memory area contains object b.
    * \return Integer value, that corresponds to some comparability.
    */
   typedef int (*FuncCompare)(const void *, const void *);

   class RingVoid;

   /*!
    * \class Ring ring.h "hzw/ring.h"
    * \brief Container class with current element and operations as on sets.
    *
    * Object which may contain uniform and comparable data-objects,
    * that have copy constructor. The data-objects are arranged in close chain order.
    * In every nonempty Ring exists the special selected element named current.
    * The current selection can be moved up to any nonegative integer number. If
    * the number is greater than count of elements, movement will be continued \a ab \a initio.
    * It looks like the addition in modular ring in the mathematics very much.
    * They may obtain and exclude current element. For two Ring\c s are also defined union,
    * intersection and substraction with the same semantics as on mathematiacal sets.
    *
    * \par Purpose:
    * The main purpose of the Ring is to generate nonrepeated random number
    * from previosly determined set. Ring can be used also as usual set.
    * \tparam Data is any data type with < and == comparsion operators.
    */
   template <typename Data>
   class Ring
   {
   public:
      //! Construct an empty Ring
      inline Ring();

      //! \brief Construct a Ring with the single element
      //!
      //! \param [in] element
      explicit inline Ring(Data element);

      //! \brief Construct a Ring by range of elements.
      //!
      //! The duplicates in the range will be eliminated if exist.
      //! \param [in] elements of the range.
      //! \param [in] count of elements in the range.
      inline Ring(const Data elements[], int count);

      //! Copy constructor.
      inline Ring(const Ring &original);

      //! Assign operator.
      inline Ring &operator=(const Ring &rightOperand);

      //! Destructor.
      inline ~Ring();

      //!  @{
      //!  \brief Move up pointer to the current element.
      //!
      //!  \f$ pointer \equiv turn \bmod{count} \f$
      //!  \param [in] turn is count of step
      inline void goForward(int turn);

      //!  \brief Value of the current element.
      //!
      //!  \exception RingException is thrown while trying to read from empty Ring.
      inline Data current() const;

      //!  Exclude the current element from the Ring
      inline void excludeCurrent();
      //!  @}


      //!@{
      //! \brief Union operator.
      //!
      //! \f$ result = left \cup right \f$
      inline Ring<Data> operator+(const Ring<Data> &rightOperand) const;

      //! \brief Substract operator.
      //!
      //! \f$ result = left \setminus right \f$
      inline Ring<Data> operator-(const Ring<Data> &rightOperand) const;

      //! \brief Intersect operator.
      //!
      //! \f$ result = left \cap right \f$
      inline Ring<Data> operator*(const Ring<Data> &rightOperand) const;

      //! Union assign operatot. \see operator+()
      inline Ring<Data> &operator+=(const Ring<Data> &rightOperand);

      //! Substract assign operatot. \see operator-()
      inline Ring<Data> &operator-=(const Ring<Data> &rightOperand);

      //! Intersect assign operatot. \see operator*()
      inline Ring<Data> &operator*=(const Ring<Data> &rightOperand);
      //!@}

      //!@{
      //! Predicate that is true when the Ring is an empty.
      inline bool isEmpty() const;

      //! Predicate that is true when the Ring has the one element only.
      inline bool hasSingle() const;

      //! Predicate that is true when the Ring contain the sample element.
      //!
      //! \param [in] sample element presence of which will be examinated.
      inline bool contain(Data sample) const;
      //!@}
   private:
      static int cmp(const void *a, const void *b);
      RingVoid *pimpl_;
      inline Ring(const RingVoid &original);
   };

   //! \privatesection
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


/*! @} */
#endif // RING_H
