#ifndef ecCodecRealplayStreamProcessor_H_
#define ecCodecRealplayStreamProcessor_H_

#include <codec/codec_config.h>

#include "ecStreamPacketPtr.h"

#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

// Forward declarations
class EcCodecRealplayStreamDumpWriter;

//---------------------------------------------------------------------------
/// Sends stream data to a callback to process while optionally dumping the stream data to file
//---------------------------------------------------------------------------
class EcCodecRealplayStreamProcessor
{
public:
   /// Type of the callback: void (*callback)(boost::int64_t microseconds, bool rtpFlag, EcStreamPacketPtr packetPtr)
   typedef boost::function3<void, boost::int64_t, bool, EcStreamPacketPtr> CallbackType;

   /*!
    \brief Constructor
    \param callback callback that receives the stream data
    */
   explicit EcCodecRealplayStreamProcessor
      (
      CallbackType callback
      );

   /// Destructor
   ~EcCodecRealplayStreamProcessor
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

   /// Returns the name of the stream dump file
   std::string streamDumpFile
      (
      ) const;

   /// Sets the name of the stream dump file
   void setStreamDumpFile
      (
      const std::string& fileName
      );

private:
   CallbackType                                       m_Callback;

   // Thread safe data members
   mutable boost::mutex                               m_Mutex;
   boost::shared_ptr<EcCodecRealplayStreamDumpWriter> m_WriterPtr;
};

#endif // ecCodecRealplayStreamProcessor_H_
