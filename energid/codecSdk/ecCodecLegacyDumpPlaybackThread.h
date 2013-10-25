#ifndef ecCodecLegacyDumpPlaybackThread_H_
#define ecCodecLegacyDumpPlaybackThread_H_

#include <codec/codec_config.h>

#include "ecStreamTimer.h"

#include <string>

#include <boost/function.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/shared_ptr.hpp>

// Forward declarations
class EcCodecRealplayStreamProcessor;

//---------------------------------------------------------------------------
/// Thread functor for UDP realplay thread
//---------------------------------------------------------------------------
class EcCodecLegacyDumpPlaybackThread
{
public:
   /// Type of the lost connection callback: void (*callback)(void)
   typedef boost::function0<void> PlaybackCompleteCallbackType;

   /// Type of the lost connection callback: void (*callback)(int percent)
   typedef boost::function1<void, int> PlaybackProgressCallbackType;

   /// Constructor
   EcCodecLegacyDumpPlaybackThread
      (
      bool realtime = true
      );

   /// Destructor
   ~EcCodecLegacyDumpPlaybackThread
      (
      );

   /*!
    \brief Initialization method

    This method is called prior to starting the thread.

    \param fileName the stream dump file to read
    \param procPtr processor that receives all of the stream data
    */
   bool init
      (
      const std::string& fileName,
      boost::shared_ptr<EcCodecRealplayStreamProcessor> procPtr
      );

   /*!
    \brief Thread function

    This methods defines the thread tasks.  The init method must be called prior to starting the thread.
    */
   void operator()
      (
      PlaybackCompleteCallbackType playbackCompleteCallback,
      PlaybackProgressCallbackType playbackProgressCallback = 0
      );

private:
   void playbackFinish
      (
      );

   bool playbackInit
      (
      );

   bool playbackUpdate
      (
      );

   bool                                                 m_Realtime;
   EcStreamTimer                                        m_Timer;
   boost::int64_t                                       m_MicrosecondsPlayed;
   boost::shared_ptr<boost::iostreams::file_descriptor> m_FilePtr;
   boost::shared_ptr<EcCodecRealplayStreamProcessor>    m_StreamProcessorPtr;
};

#endif // ecCodecLegacyDumpPlaybackThread_H_
