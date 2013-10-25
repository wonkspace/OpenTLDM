#ifndef ecFrame_H
#define ecFrame_H

#include <codec/codec_config.h>

#include "ecRtpPackagePtr.h"
#include "ecStreamPacketPtr.h"

#include <boost/cstdint.hpp>

#include <list>

//---------------------------------------------------------------------------
/// Container for holding a single frame
//---------------------------------------------------------------------------
class EcFrame
{
public:
   /// Frame type
   enum TypeEnum
   {
      EC_VFRAME=0,
      EC_AFRAME,
      EC_OSDLOGO,
      EC_EMPTY
   };

   /// Constructor
   EcFrame
      (
      );

   /*!
    \brief Add a RTP package to this frame
    \param microseconds arrival time of the package
    \param packagePtr shared pointer to the package to add
    \param testId frame id used to determine if this frame is complete
    \returns true upon successfully adding the package to this frame
    */
   bool addRtpPackage
      (
      boost::int64_t  microseconds,
      EcRtpPackagePtr packagePtr,
      unsigned int    testId
      );

   /*!
    \brief Get the full frame of data
    \param packetPtr buffer for storing the frame of data
    \returns true upon successfully fetching a complete frame
    */
   bool fetchData
      (
      EcStreamPacketPtr packetPtr
      ) const;

   /// Returns the number of RTP packages in this frame
   unsigned int numPackages
      (
      ) const;

   /// Returns the ID of this frame
   unsigned int id
      (
      ) const;

   /// Returns the type of this frame
   TypeEnum type
      (
      ) const;

   /// Returns a flag indicating if this frame is complete
   bool isComplete
      (
      ) const;

   /// Returns a flag indicating if this frame is marked
   bool isMarked
      (
      ) const;

   /// Returns a flag indicating if this frame is missing packets
   bool isMissingPackets
      (
      ) const;

   /// Returns the arrival time for the earliest RTP package
   boost::int64_t arrivalTime
      (
      ) const;

private:
   typedef std::list<EcRtpPackagePtr> ListType;

   ListType       m_List;
   unsigned int   m_Id;
   TypeEnum       m_Type;
   bool           m_IsMarked;
   bool           m_IsComplete;
   bool           m_GotLastPackage;
   unsigned int   m_ExpectedLength;
   unsigned int   m_CurrentLength;
   boost::int64_t m_ArrivalTime;
   const char*    m_pFirstPayload;
};

#endif // ecFrame_H
