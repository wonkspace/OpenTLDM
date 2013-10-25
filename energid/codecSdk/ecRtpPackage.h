#ifndef ecRtpPackage_H
#define ecRtpPackage_H

#include <codec/codec_config.h>

#include "ecStreamPacketPtr.h"

#include <boost/cstdint.hpp>

//---------------------------------------------------------------------------
/// Container for holding a RTP package
//---------------------------------------------------------------------------
class EcRtpPackage
{
public:
   /// Constructor
   EcRtpPackage
      (
      );

   /// Destructor
   ~EcRtpPackage
      (
      );

   /*!
    \brief Initializes the data for this package
    \param packetPtr package data
    \returns true upon successful initialization of this package
    */
   bool initial
      (
      EcStreamPacketPtr packetPtr
      );

   /// Returns the length of this package payload in bytes
   unsigned int payloadLength
      (
      ) const;

   /// Returns the address of this package payload
   const char* payloadPointer
      (
      ) const;

   /// Returns the frame ID of this package
   unsigned int frameId
      (
      ) const;

   /// Returns the frame offset of this package inside a frame
   unsigned int frameOffset
      (
      ) const;

   /// Returns a flag indicating if this package is the last package of a complete frame
   bool isLastPackage
      (
      ) const;

private:
   bool isValid
      (
      EcStreamPacketPtr packetPtr
      ) const;

   unsigned int      m_FrameId;
   unsigned int      m_FrameOffset;
   bool              m_IsLastPackage;
   unsigned int      m_PayloadLength;
   EcStreamPacketPtr m_PacketPtr;
};

#endif // ecRtpPackage_H
