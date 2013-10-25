//#include "ecDataBufferPool.h"
#include "ecDataBuffer.h"

//---------------------------------------------------------------------------
#include <iostream>
static size_t INSTANCE_COUNT = 0;
template <typename T>
class EcDataBufferPool<T>::Counter
{
public:
   explicit Counter
      (
      size_t instanceNumber
      ) :
      m_InstanceNumber(instanceNumber),
      m_ReservedCount(0),
      m_DynamicCount(0)
   {
   }

   ~Counter
      (
      )
   {
      std::cout << "EcDataBufferPool::Counter (" << m_InstanceNumber << ") reserved : " << m_ReservedCount << ", dynamic : " << m_DynamicCount << std::endl;
   }

   void countReserved
      (
      )
   {
      ++m_ReservedCount;
   }

   void countDynamic
      (
      )
   {
      ++m_DynamicCount;
      std::cout << "EcDataBufferPool::Counter (" << m_InstanceNumber << ") a new buffer was added (" << m_ReservedCount + m_DynamicCount << ")" << std::endl;
   }

private:
   size_t m_InstanceNumber;
   size_t m_ReservedCount;
   size_t m_DynamicCount;
};

//---------------------------------------------------------------------------
template <typename T>
class EcReturnToPool
{
public:
   EcReturnToPool
      (
      boost::shared_ptr< EcDataBufferPool<T> > poolPtr
      ) :
      m_PoolPtr(poolPtr)
   {
   }

   void operator()
      (
      const void* pData
      ) const
   {
      m_PoolPtr->recover(pData);
   }

private:
   boost::shared_ptr< EcDataBufferPool<T> > m_PoolPtr;
};

//---
// EcDataBufferPool constructor
//---

//---------------------------------------------------------------------------
template <typename T>
EcDataBufferPool<T>::EcDataBufferPool
   (
   size_t numBufferElements,
   size_t numBuffers
   ) :
   m_NumBufferElements(numBufferElements),
   m_NumBuffers(0),
   m_AvailableQueue(0),
   m_InUseBufferMap(),
   m_CounterPtr(new Counter(INSTANCE_COUNT++))
{
   reserve(numBuffers);
}

//---
// EcDataBufferPool public methods
//---

//---------------------------------------------------------------------------
template <typename T>
typename EcDataBufferPool<T>::BufferPtr EcDataBufferPool<T>::dataBuffer
   (
   )
{
   const int returnQueue = (m_AvailableQueue == 1) ? 0 : 1;
   if (m_BufferPtrQueue[m_AvailableQueue].empty() && m_BufferPtrQueue[returnQueue].empty())
   {
      m_CounterPtr->countDynamic();
      BufferPtr bufferPtr(new EcDataBuffer<T>(m_NumBufferElements));
      m_InUseBufferMap[bufferPtr.get()] = bufferPtr;
      ++m_NumBuffers;
      return BufferPtr(bufferPtr.get(), EcReturnToPool<T>(this->shared_from_this()));
   }

   if (m_BufferPtrQueue[m_AvailableQueue].empty())
   {
      m_AvailableQueue = returnQueue;
   }

   BufferPtr bufferPtr = m_BufferPtrQueue[m_AvailableQueue].front();
   m_BufferPtrQueue[m_AvailableQueue].pop();
   m_InUseBufferMap[bufferPtr.get()] = bufferPtr;

   return BufferPtr(bufferPtr.get(), EcReturnToPool<T>(this->shared_from_this()));
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBufferPool<T>::recover
   (
   const void* pData
   )
{
   typename InUseBufferMap::iterator ii = m_InUseBufferMap.find(pData);
   if (ii != m_InUseBufferMap.end())
   {
      const int returnQueue = (m_AvailableQueue == 1) ? 0 : 1;
      BufferPtr bufferPtr = (*ii).second;
      bufferPtr->clear();
      m_BufferPtrQueue[returnQueue].push(bufferPtr);
      m_InUseBufferMap.erase(ii);
   }
   else
   {
      std::cerr << "Unable to recover buffer " << pData << std::endl;
   }
}

//---------------------------------------------------------------------------
template <typename T>
void EcDataBufferPool<T>::reserve
   (
   size_t numBuffers
   )
{
   while (m_NumBuffers < numBuffers)
   {
      m_CounterPtr->countReserved();
      m_BufferPtrQueue[m_AvailableQueue].push(BufferPtr(new EcDataBuffer<T>(m_NumBufferElements)));
      ++m_NumBuffers;
   }
}
