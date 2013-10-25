#ifndef ecFrameManager_H
#define ecFrameManager_H

#include <codec/codec_config.h>

#include "ecFrameManagerStatistics.h"
#include "ecFramePtr.h"
#include "ecStreamPacketPtr.h"

#include <boost/cstdint.hpp>

#include <list>
#include <map>

//---------------------------------------------------------------------------
/// Container for managing complete and incomplete frames
//---------------------------------------------------------------------------
class EcFrameManager
{
public:
   /// Frame type
   enum TypeEnum
   {
      VideoFrames=0,
      AudioFrames
   };

   /*!
    \brief Constructor
    \param type type of frames to manage (audio, video)
    */
   explicit EcFrameManager
      (
      TypeEnum type
      );

   /*!
    \brief Add a RTP package
    \param microseconds arrival time of the package
    \param packetPtr RTP package data
    \returns true upon successfully adding the package
    */
   bool addRtpPackage
      (
      boost::int64_t    microseconds,
      EcStreamPacketPtr packetPtr
      );

   /// Returns a shared pointer to the next complete frame for processing
   EcFramePtr nextFrame
      (
      );

   /// Resets
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

   /// Returns the type
   TypeEnum type
      (
      ) const;

private:
   void discardExpiredFrames
      (
      boost::int64_t microseconds
      );

   void discardUpToFrameId
      (
      unsigned int frameId
      );

   typedef std::list<unsigned int>            FrameIdListType;
   typedef std::map<unsigned int, EcFramePtr> FrameMapType;

   TypeEnum                 m_Type;
   FrameMapType             m_FramesMap;
   FrameIdListType          m_FramesList;
   unsigned int             m_ExpectedFrameId;
   unsigned int             m_LatestFrameId;
   EcFrameManagerStatistics m_Statistics;
};

#endif // ecFrameManager_H
