#ifndef ecCodecRealplayUdpThread_H_
#define ecCodecRealplayUdpThread_H_

#include <codec/codec_config.h>

#include "ecCodecLoginParameters.h"

#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

// Forward declarations
class EcCodecRealplayStreamProcessor;
class EcCodecUdpSocket;
class EcStreamTimer;

//---------------------------------------------------------------------------
/// Thread functor for UDP realplay thread
//---------------------------------------------------------------------------
class EcCodecRealplayUdpThread
{
public:
   /// Type of the lost connection callback: void (*callback)(void)
   typedef boost::function0<void> LostConnectionCallbackType;

   /*!
    \brief Constructor
    \param channel realplay channel
    \param lparams login parameters
    \param codecUserID user ID of the login session
    \param callback callback that receives the realplay frame data
    */
   EcCodecRealplayUdpThread
      (
      int                           channel,
      const EcCodecLoginParameters& lparams,
      unsigned long                 codecUserID
      );

   /// Destructor
   ~EcCodecRealplayUdpThread
      (
      );

   /*!
    \brief Initialization method

    This method is called prior to starting the thread.

    \param procPtr processor that receives all of the stream data
    */
   bool init
      (
      boost::shared_ptr<EcCodecRealplayStreamProcessor> procPtr
      );

   /*!
    \brief Thread function

    This methods defines the thread tasks.  The init method must be called prior to starting the thread.

    \param lostConnectionCallback called when the connection is lost
    */
   void operator()
      (
      LostConnectionCallbackType lostConnectionCallback
      );

private:
   enum StartStopRequestType
   {
      STOP = 0,
      START,
      REPLY
   };

   void realplayFinish
      (
      );

   bool realplayInit
      (
      );

   bool realplayUpdate
      (
      EcStreamTimer& timer
      );

   bool sendStartStopRequest
      (
      StartStopRequestType type
      );

   int                                               m_Channel;
   EcCodecLoginParameters                            m_LParams;
   unsigned long                                     m_CodecUserID;
   boost::shared_ptr<EcCodecUdpSocket>               m_SocketPtr;
   boost::shared_ptr<EcCodecRealplayStreamProcessor> m_StreamProcessorPtr;
   boost::int64_t                                    m_LastReplyMicroseconds;
};

#endif // ecCodecRealplayUdpThread_H_
