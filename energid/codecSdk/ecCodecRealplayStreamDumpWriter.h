#ifndef ecCodecRealplayStreamDumpWriter_H_
#define ecCodecRealplayStreamDumpWriter_H_

#include <codec/codec_config.h>

#include "ecStreamPacketPtr.h"

#include <fstream>
#include <string>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

//---------------------------------------------------------------------------
/// A simple callback that dumps the stream data to file
//---------------------------------------------------------------------------
class EcCodecRealplayStreamDumpWriter
{
public:
   /*!
    \brief Constructor
    \param fileName file name where the stream data is dumped
    */
   explicit EcCodecRealplayStreamDumpWriter
      (
      const std::string& fileName
      );

   /// Destructor
   ~EcCodecRealplayStreamDumpWriter
      (
      );

   /// Returns the file name of the dump file
   const std::string& fileName
      (
      ) const;

   /*!
    \brief Dumps a stream package to file
    \param microseconds arrival time of the package data
    \param rtpFlag whether the data represents an RTP package
    \param packetPtr package data
    */
   void writePackage
      (
      boost::int64_t    microseconds,
      bool              rtpFlag,
      EcStreamPacketPtr packetPtr
      );

private:
   std::string                      m_FileName;
   boost::shared_ptr<std::ofstream> m_OfPtr;
   boost::int64_t                   m_FirstTime;
   bool                             m_WaitingForFirst;
};

#endif // ecCodecRealplayStreamDumpWriter_H_
