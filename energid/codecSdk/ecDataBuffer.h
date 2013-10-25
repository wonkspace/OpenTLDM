#ifndef ecDataBuffer_H_
#define ecDataBuffer_H_

#include <codec/codec_config.h>

#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>

//---------------------------------------------------------------------------
/// Generic data buffer
//---------------------------------------------------------------------------
template <typename T>
class EcDataBuffer : private boost::noncopyable
{
public:
   /*!
    \brief Constructor
    \param numElements initial size of data buffer in elements
    */
   EcDataBuffer
      (
      size_t numElements = 0
      );

   /*!
    \brief Constructor
    \param pData initial data to fill the buffer
    \param numElements number of elements in the initial data
    */
   EcDataBuffer
      (
      const T* pData,
      size_t   numElements
      );

   /*!
    \brief Appends data to the end of the buffer
    \param pData data to append to the buffer
    \param numElements number of elements in the append data
    */
   void appendData
      (
      const T* pData,
      size_t   numElements
      );

   /// Clears the buffer
   void clear
      (
      );

   /// Returns the address of the data
   T* data
      (
      );

   /// Returns the address of the data
   const T* data
      (
      ) const;

   /// Returns the size of the data in bytes
   size_t numBytes
      (
      ) const;

   /// Returns the size of the data in elements
   size_t numElements
      (
      ) const;

   /*!
    \brief Add zero padding at the end of the data
    \param numElements number of data elements to pad at the end of the data
    */
   void pad
      (
      size_t numElements
      );

   /*!
    \brief Ensure the buffer contains a specified number of elements at a minimum
    \param numElements minimal number of data elements in the buffer
    */
   void reserve
      (
      size_t numElements
      );

   /*!
    \brief Sets the current contents of the buffer
    \param dataBuffer data to set in the buffer
    */
   void setData
      (
      const EcDataBuffer& dataBuffer
      );

   /*!
    \brief Sets the current contents of the buffer
    \param pData data to set in the buffer
    \param numElements number of elements in the data
    */
   void setData
      (
      const T* pData,
      size_t   numElements
      );

   /// Sets the size of the data in bytes
   void setNumBytes
      (
      size_t numBytes
      );

   /// Sets the size of the data in elements
   void setNumElements
      (
      size_t numElements
      );

private:
   boost::scoped_array<T> m_Data;
   size_t                 m_MaxElements;
   size_t                 m_NumElements;
};

#include "ecDataBuffer.ipp"

#endif // ecDataBuffer_H_
