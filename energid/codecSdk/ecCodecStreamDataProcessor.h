#ifndef ecCodecStreamDataProcessor_H_
#define ecCodecStreamDataProcessor_H_

#include <codec/codec_config.h>

#include "ecFrameManager.h"

#include <boost/cstdint.hpp>

#include <queue>

//---------------------------------------------------------------------------
/// Processes stream data into complete frames
//---------------------------------------------------------------------------
class EcCodecStreamDataProcessor
{
public:
   /*!
    \brief Constructor
    \param type type of data to process (audio, video)
    */
   explicit EcCodecStreamDataProcessor
      (
      EcFrameManager::TypeEnum type
      );

   /// Destructor
   ~EcCodecStreamDataProcessor
      (
      );

   /*!
    \brief Process a package
    \param microseconds arrival time of the package data
    \param rtpFlag whether the data represents an RTP package
    \param packetPtr package data
    */
   void processPackage
      (
      boost::int64_t    microseconds,
      bool              rtpFlag,
      EcStreamPacketPtr packetPtr
      );

   /*!
    \brief Returns the next available data buffer
    \returns next available data buffer
    */
   EcStreamPacketPtr nextBuffer
      (
      );

   /*!
    \brief Returns the next complete frame
    \param microseconds arrival time of the frame
    \param isMarked flag indicating if the returned frame is a marked frame
    \returns next complete frame
    */
   EcStreamPacketPtr nextFrame
      (
      boost::int64_t& microseconds,
      bool&           isMarked
      );

   /// Resets the frame manager
   void reset
      (
      );

   /// Resets the statistics
   void resetStatistics
      (
      );

   /// Returns the statistics
   const EcFrameManagerStatistics& statistics
      (
      ) const;

private:
   void processData
      (
      const char* pBuffer,
      size_t      length
      );

   void processPackageImpl
      (
      boost::int64_t    microseconds,
      EcStreamPacketPtr packetPtr
      );

   struct DataType
   {
      boost::int64_t    microseconds;
      bool              isMarked;
      EcStreamPacketPtr framePtr;
   };

   typedef std::queue<DataType> DataQueueType;

   EcFrameManager    m_FrameManager;
   EcStreamPacketPtr m_IncompletePacketPtr;
   unsigned int      m_RemainderLength;
   bool              m_WaitingForFrame;
   bool              m_WaitingForHeader;
   bool              m_IsMarked;
   boost::int64_t    m_ArrivalTime;
   DataQueueType     m_FrameQueue;
};

#endif // ecCodecStreamDataProcessor_H_
