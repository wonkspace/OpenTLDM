//#include "ecDataBuffer.h"

#include <cstring>

//---------------------------------------------------------------------------
#include <iostream>
template <typename T>
class EcDataBufferCounter
{
public:
   static EcDataBufferCounter& instance
      (
      )
   {
      static EcDataBufferCounter counter;
      return counter;
   }

   void countConstruction
      (
      )
   {
      ++m_Constructions;
   }

   void countResize
      (
      )
   {
      ++m_Resizes;
   }

private:
   EcDataBufferCounter
      (
      ) :
      m_Constructions(0),
      m_Resizes(0)
   {
   }

   ~EcDataBufferCounter
      (
      )
   {
      std::cout << "EcDataBufferCounter constructions : " << m_Constructions << ", resizes : " << m_Resizes << std::endl;
   }

   size_t m_Constructions;
   size_t m_Resizes;
};

//---
// EcDataBuffer constructors
//---

//---------------------------------------------------------------------------
template <typename T>
EcDataBuffer<T>::EcDataBuffer
   (
   size_t numElements
   ) :
   m_Data(),
   m_MaxElements(numElements),
   m_NumElements(0)
{
   EcDataBufferCounter<T>::instance().countConstruction();
   if (numElements > 0)
   {
      EcDataBufferCounter<T>::instance().countResize();
      m_Data.reset(new T[numElements]);
   }
}

//---------------------------------------------------------------------------
template <typename T>
EcDataBuffer<T>::EcDataBuffer
   (
   const T* pData,
   size_t   numElements
   ) :
   m_Data(),
   m_MaxElements(numElements),
   m_NumElements(numElements)
{
   EcDataBufferCounter<T>::instance().countConstruction();
   if (numElements > 0)
   {
      EcDataBufferCounter<T>::instance().countResize();
      m_Data.reset(new T[numElements]);
      memcpy(m_Data.get(), pData, numBytes());
   }
}

//---
// EcDataBuffer public methods
//---

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::appendData
   (
   const T* pData,
   size_t   numElements
   )
{
   if (numElements > 0)
   {
      reserve(m_NumElements + numElements);
      memcpy(m_Data.get() + numBytes(), pData, numElements * sizeof(T));
      m_NumElements += numElements;
   }
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::clear
   (
   )
{
   m_NumElements = 0;
}

//---------------------------------------------------------------------------
template <typename T>
T* EcDataBuffer<T>::data
   (
   )
{
   return m_Data.get();
}

//---------------------------------------------------------------------------
template <typename T>
const T* EcDataBuffer<T>::data
   (
   ) const
{
   if (m_NumElements > 0)
   {
      return m_Data.get();
   }

   return 0;
}

//---------------------------------------------------------------------------
template <typename T>
size_t EcDataBuffer<T>::numBytes
   (
   ) const
{
   return m_NumElements * sizeof(T);
}

//---------------------------------------------------------------------------
template <typename T>
size_t EcDataBuffer<T>::numElements
   (
   ) const
{
   return m_NumElements;
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::pad
   (
   size_t numElements
   )
{
   if (numElements > 0)
   {
      reserve(m_NumElements + numElements);
      memset(m_Data.get() + numBytes(), 0, numElements * sizeof(T));
   }
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::reserve
   (
   size_t numElements
   )
{
   if (m_MaxElements < numElements)
   {
      EcDataBufferCounter<T>::instance().countResize();
      if (m_NumElements > 0)
      {
         boost::scoped_array<T> data(new T[numElements]);
         memcpy(data.get(), m_Data.get(), numBytes());
         m_Data.swap(data);
      }
      else
      {
         m_Data.reset(new T[numElements]);
      }
      m_MaxElements = numElements;
   }
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::setData
   (
   const EcDataBuffer<T>& dataBuffer
   )
{
   clear();
   const size_t numElements = dataBuffer.numElements();
   if (numElements > 0)
   {
      reserve(numElements);
      m_NumElements = numElements;
      memcpy(m_Data.get(), dataBuffer.data(), numBytes());
   }
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::setData
   (
   const T* pData,
   size_t   numElements
   )
{
   clear();
   if (numElements > 0)
   {
      reserve(numElements);
      m_NumElements = numElements;
      memcpy(m_Data.get(), pData, numBytes());
   }
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::setNumBytes
   (
   size_t numBytes
   )
{
   setNumElements(numBytes / sizeof(T));
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBuffer<T>::setNumElements
   (
   size_t numElements
   )
{
   reserve(numElements);
   m_NumElements = numElements;
}
