#ifndef ecCodecUser_H_
#define ecCodecUser_H_

#include <codec/codec_config.h>

#include "ecCodecLoginParameters.h"
#include "ecCodecRealplayMode.h"
#include "ecCodecSdk.h"
#include "ecCodecThrottleTable.h"

#include <boost/array.hpp>
#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

//static const int MAX_CHANNUM = 8;
static const int MAX_CHANNUM = 1;

// Forward declarations
class EcCodecRealplayStreamProcessor;
class EcCodecTcpSocket;

namespace boost
{
   class thread;
}

//---------------------------------------------------------------------------
/*!
 \brief Primary class for interfacing with CODEC encoder hardware

 There are two primary interfaces for interfacing with CODEC encoder
 hardware: EcCodecUser and EcPersistentCodecUser.  EcCodecUser will block
 during calls to connect.  EcPersistentCodecUser will use a background thread
 to connect to the hardware and will automatically attempt to reestablish a
 connection when it is lost.
 */
//---------------------------------------------------------------------------
class EcCodecUser
{
public:
   /// Type of the lost connection callback: void (*callback)(void)
   typedef boost::function0<void> LostConnectionCallbackType;

   /// Constructor
   EcCodecUser
      (
      );

   /// Destructor
   ~EcCodecUser
      (
      );


   /*!
    \brief Attempt to connect to the CODEC encoder hardware
    \param lparams login parameters
    \returns true upon successfully connecting to the hardware
    */
   bool connect
      (
      const EcCodecLoginParameters& lparams
      );

   /*!
    \brief Disconnect from the CODEC encoder hardware
    \param bgFlag flag indicating if the disconnect should be done in the background

    Client can specify whether the disconnect should be done in the background or not.
    If the client lifetime is guaranteed to exceed the timeline required for the
    disconnect, then it is safe to disconnect in the background.  Otherwise, it is not
    safe to disconnect in the background.  If disconnect is called at application
    exit, then bgFlag should be set to false.  Alternately, the destructor will
    automatically call disconnect(false).
    */
   void disconnect
      (
      bool bgFlag = true
      );

   /// Returns a flag indicating if realplay is currently active for the specified channel
   bool isRealplayOn
      (
      int channel
      ) const;

   /*!
    \brief Attempt to start realplay
    \param channel channel to start realplay on
    \param mode realplay mode (TCP, UDP)
    \param procPtr processor that receives all of the stream data
    \returns true if realplay is successfully started
    */
   bool startRealplay
      (
      int                                               channel,
      EcCodecRealplayMode::Enum                         mode,
      boost::shared_ptr<EcCodecRealplayStreamProcessor> procPtr
      );

   /*!
    \brief Attempt to stop realplay
    \param channel channel to stop realplay on
    \returns true if realplay is successfully stopped
    */
   bool stopRealplay
      (
      int channel
      );

   /*!
    \brief Set the callback that is called when the connection is lost
    \param callback called when the connection is lost
    */
   void setLostConnectionCallback
      (
      LostConnectionCallbackType callback
      );

   /*!
    \brief Get the audio parameters from the CODEC encoder hardware
    \param channel channel of the desired audio parameters
    \param aparams audio parameters
    \returns true upon successfully getting the audio parameters from the hardware
    */
   bool getAudioParameters
      (
      int channel,
      EcCodecAudioParameters& aparams
      ) const;

   /*!
    \brief Set the audio parameters on the CODEC encoder hardware
    \param channel channel of the desired audio parameters to set
    \param aparams audio parameters to set
    \returns true upon successfully setting the audio parameters on the hardware
    */
   bool setAudioParameters
      (
      int channel,
      const EcCodecAudioParameters& aparams
      ) const;

   /*!
    \brief Save the audio parameters on the CODEC encoder hardware
    \returns true upon successfully saving the audio parameters on the hardware
    */
   bool saveAudioParameters
      (
      ) const;

   /*!
    \brief Get the motion detect parameters from the CODEC repeater
    \param mparams motion detect parameters
    \returns true upon successfully getting the motion detect parameters from the repeater
    */
   bool getMotionDetectParameters
      (
      EcCodecMotionDetectParameters& mparams
      ) const;

   /*!
    \brief Set the motion detect parameters on the CODEC repeater
    \param mparams motion detect parameters to set
    \returns true upon successfully setting the motion detect parameters on the repeater
    */
   bool setMotionDetectParameters
      (
      const EcCodecMotionDetectParameters& mparams
      ) const;

   /*!
    \brief Get the network parameters from the CODEC encoder hardware
    \param nparams network parameters
    \returns true upon successfully getting the network parameters from the hardware
    */
   bool getNetworkParameters
      (
      EcCodecNetworkParameters& nparams
      ) const;

   /*!
    \brief Set the network parameters on the CODEC encoder hardware
    \param nparams network parameters to set
    \returns true upon successfully setting the network parameters on the hardware
    */
   bool setNetworkParameters
      (
      const EcCodecNetworkParameters& nparams
      ) const;

   /*!
    \brief Save the network parameters on the CODEC encoder hardware
    \returns true upon successfully saving the network parameters on the hardware
    */
   bool saveNetworkParameters
      (
      ) const;

   /*!
    \brief Sets the desired bit rate and adjusts video parameters accordingly
    \param channel channel of the desired video parameters to set
    \param kbps desired bit rate (kbps)
    \returns true upon successfully setting the video parameters on the hardware

    This provides a simplified interface for setting the video parameters.  A
    valid throttle table must be set (setThrottleTable) prior to this call.
    */
   bool setThrottleBitRate
      (
      int channel,
      unsigned short kbps
      );

   /*!
    \brief Get the user parameters from the CODEC encoder hardware
    \param uparams user parameters
    \returns true upon successfully getting the user parameters from the hardware
    */
   bool getUserParameters
      (
      EcCodecUserParameters& uparams
      ) const;

   /*!
    \brief Set the user parameters on the CODEC encoder hardware
    \param uparams user parameters to set
    \returns true upon successfully setting the user parameters on the hardware
    */
   bool setUserParameters
      (
      const EcCodecUserParameters& uparams
      ) const;

   /*!
    \brief Save the user parameters on the CODEC encoder hardware
    \returns true upon successfully saving the user parameters on the hardware
    */
   bool saveUserParameters
      (
      ) const;

   /*!
    \brief Get the video parameters from the CODEC encoder hardware
    \param channel channel of the desired video parameters
    \param vparams video parameters
    \returns true upon successfully getting the video parameters from the hardware
    */
   bool getVideoParameters
      (
      int channel,
      EcCodecVideoParameters& vparams
      ) const;

   /*!
    \brief Set the video parameters on the CODEC encoder hardware
    \param channel channel of the desired video parameters to set
    \param vparams video parameters to set
    \returns true upon successfully setting the video parameters on the hardware
    */
   bool setVideoParameters
      (
      int channel,
      const EcCodecVideoParameters& vparams
      ) const;

   /*!
    \brief Save the video parameters on the CODEC encoder hardware
    \returns true upon successfully saving the video parameters on the hardware
    */
   bool saveVideoParameters
      (
      ) const;

   /*!
    \brief Reboot the CODEC encoder hardware
    \returns true upon successfully sending the reboot command to the hardware
    */
   bool reboot
      (
      ) const;

   /*!
    \brief Shutdown the CODEC encoder hardware
    \returns true upon successfully sending the shutdown command to the hardware
    */
   bool shutdown
      (
      ) const;

   /// Returns a flag indicating if the CODEC encoder hardware is currently connected
   bool isConnected
      (
      ) const;

   /// Returns a flag indicating if the CODEC encoder hardware is currently connected tto a repeater
   bool isConnectedToRepeater
      (
      ) const;

   /// Returns thee current login parameters for the connection
   const EcCodecLoginParameters& loginParameters
      (
      ) const;

   /// Returns the current user ID for the connection
   unsigned long codecUserID
      (
      ) const;

   /// Returns the throttle table
   const EcCodecThrottleTable& throttleTable
      (
      ) const;

   /*!
    \brief Sets the throttle table
    \param tt throttle table
    */
   void setThrottleTable
      (
      const EcCodecThrottleTable& tt
      );

private:
   bool shortConnect
      (
      unsigned long cmdId,
      void*         pSendBuffer    = 0,
      unsigned int  sendLength     = 0,
      void*         pReceiveBuffer = 0,
      unsigned int  receiveLength  = 0
      ) const;

   bool shortConnect
      (
      EcCodecTcpSocket& socket,
      unsigned long     cmdId,
      void*             pSendBuffer    = 0,
      unsigned int      sendLength     = 0,
      void*             pReceiveBuffer = 0,
      unsigned int      receiveLength  = 0
      ) const;

   typedef boost::shared_ptr<boost::thread> RealplayThreadPtr;
   typedef boost::array<RealplayThreadPtr, MAX_CHANNUM> RealplayThreadPtrArray;

   bool                           m_IsConnected;
   bool                           m_IsConnectedToRepeater;
   mutable EcCodecLoginParameters m_LParams;
   unsigned long                  m_CodecUserID;
   EcCodecThrottleTable           m_ThrottleTable;
   RealplayThreadPtrArray         m_RealplayThreadPtrArray;
   LostConnectionCallbackType     m_LostConnectionCallback;
};

#endif // ecCodecUser_H_
