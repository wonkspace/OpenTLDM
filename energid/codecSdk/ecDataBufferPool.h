#ifndef ecDataBufferPool_H_
#define ecDataBufferPool_H_

#include <codec/codec_config.h>

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <queue>

// Forward declarations
template <typename T> class EcDataBuffer;

//---------------------------------------------------------------------------
/// Generic data buffer pool
//---------------------------------------------------------------------------
template <typename T>
class EcDataBufferPool :
   public boost::enable_shared_from_this< EcDataBufferPool<T> >,
   private boost::noncopyable
{
public:
   typedef typename boost::shared_ptr< EcDataBuffer<T> > BufferPtr;

   /*!
    \brief Constructor
    \param numBufferElements initial size of newly constructed data buffers
    \param numBuffers number of data buffers to initially construct
    */
   EcDataBufferPool
      (
      size_t numBufferElements = 0,
      size_t numBuffers        = 0
      );

   /*!
    \brief Get a data buffer from the pool
    \returns shared pointer to the next available data buffer in the pool
    */
   BufferPtr dataBuffer
      (
      );

   // FIXME: This should not be in the public interface
   /*!
    \brief Called when a data buffer is no longer in use

    This method is automatically called by the destructor of the shared pointer
    returned by the dataBuffer method when the data buffer is no longer in use
    (goes out of scope).

    \param pData The address of the data buffer that is no longer in use
    */
   void recover
      (
      const void* pData
      );

   /*!
    \brief Ensure the pool contains a specified number of data buffers at a minimum
    \param numBuffers minimal number of data buffers in the pool
    */
   void reserve
      (
      size_t numBuffers
      );

private:
   typedef std::map<const void*, BufferPtr> InUseBufferMap;

   const size_t          m_NumBufferElements;
   size_t                m_NumBuffers;
   // Index of the queue to use for holding available buffers
   int                   m_AvailableQueue;
   // 2 queues: 1 for available buffers, 1 for returned (no longer in-use) buffers
   std::queue<BufferPtr> m_BufferPtrQueue[2];
   InUseBufferMap        m_InUseBufferMap;

   class Counter;
   boost::shared_ptr<Counter> m_CounterPtr;
};

#include "ecDataBufferPool.ipp"

#endif // ecDataBufferPool_H_
