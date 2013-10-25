#ifndef ecCodecSdkC_H_
#define ecCodecSdkC_H_

#include <codec/codec_config.h>
#include <codecSdk/ecCodecSdk.h>

typedef unsigned long EcCodecHandle;

#define FILE_NAME_LEN 128

/****************************************************************************
 * Struct for configuring realplay
 *
 * PARAMS
 *   imageCallback      : callback for receiving decoded PIX_FMT_RGB24 images
 *   audioCallback      : callback for receiving decoded mono 16 bit LE 8000Hz audio PCM
 *   movieFileName      : output movie file name (.avi or .mp4 extension)
 *   width              : output movie width
 *   height             : output movie height
 *   frameRate          : output movie frame rate
 *   keyFrameInterval   : output movie key frame interval
 *   audioBitRate       : output movie audio bit rate
 *   videoBitRate       : output movie video bit rate
 *   audioAmplification : 0 = no audio
 *   dumpFileName       : output dump file name
 *
 * IMAGE CALLBACK PARAMS
 *   microseconds       : arrival time of the image
 *   pData              : decoded image address
 *   width              : decoded image width
 *   height             : decoded image height
 *   pStatistics        : pointer to statistics text
 *
 * AUDIO CALLBACK PARAMS
 *   microseconds       : arrival time of the audio data
 *   pData              : audio data (mono 16 bit LE 8000Hz audio PCM samples)
 *   length             : number of bytes in the audio data
 ***************************************************************************/
typedef struct
{
   // Configuration if raw image data callback is desired
   void (*imageCallback)
      (
      long long int        microseconds,
      const unsigned char* pData,
      int                  width,
      int                  height,
      const char*          pStatistics
      );

   // Configuration if raw audio data callback is desired
   void (*audioCallback)
      (
      long long int        microseconds,
      const unsigned char* pData,
      int                  length
      );

   // Configuration if movie output is desired
   char          movieFileName[FILE_NAME_LEN];
   int           width;
   int           height;
   int           frameRate;
   int           keyFrameInterval;
   int           audioBitRate;
   int           videoBitRate;
   short int     audioAmplification;

   // Configuration if dump file is desired
   char          dumpFileName[FILE_NAME_LEN];
} EcCodecRealplayConfiguration;

/****************************************************************************
 * Login to the codec device
 *
 * RETURNS
 *   handle to codec hardware on success
 *   NULL (0) on failure
 *
 * PARAMS
 *   pIpAddress                    : ip address of codec hardware ("192.168.1.92")
 *   port1                         : port used for connections to codec hardware (5600)
 *   port2                         : port used for realplay stream from codec hardware (5601)
 *   pUsername                     : username for logging into codec hardware ("Admin")
 *   pPassword                     : password for logging into codec hardware
 *   establishedConnectionCallback : callback to signal when the connection is established
 *   lostConnectionCallback        : callback to signal when the connection is lost
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL EcCodecHandle codecLogin
   (
   const char* pIpAddress,
   int         port1,
   int         port2,
   const char* pUserName,
   const char* pPassword,
   void (*establishedConnectionCallback)
      (
      ) = 0,
   void (*lostConnectionCallback)
      (
      ) = 0
   );

/****************************************************************************
 * Logout of the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec : codec hardware handle from valid login
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecLogout
   (
   EcCodecHandle hCodec
   );

/****************************************************************************
 * Get the audio parameters from the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   channel : channel number
 *   pParams : pointer to EcCodecAudioParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecGetAudioParameters
   (
   EcCodecHandle           hCodec,
   int                     channel,
   EcCodecAudioParameters* pParams
   );

/****************************************************************************
 * Set the audio parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   channel : channel number
 *   pParams : pointer to EcCodecAudioParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSetAudioParameters
   (
   EcCodecHandle           hCodec,
   int                     channel,
   EcCodecAudioParameters* pParams
   );

/****************************************************************************
 * Save the audio parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec : codec hardware handle from valid login
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSaveAudioParameters
   (
   EcCodecHandle hCodec
   );

/****************************************************************************
 * Get the network parameters from the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   pParams : pointer to EcCodecNetworkParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecGetNetworkParameters
   (
   EcCodecHandle             hCodec,
   EcCodecNetworkParameters* pParams
   );

/****************************************************************************
 * Set the network parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   pParams : pointer to EcCodecNetworkParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSetNetworkParameters
   (
   EcCodecHandle             hCodec,
   EcCodecNetworkParameters* pParams
   );

/****************************************************************************
 * Save the network parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec : codec hardware handle from valid login
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSaveNetworkParameters
   (
   EcCodecHandle hCodec
   );

/****************************************************************************
 * Get the user parameters from the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   pParams : pointer to EcCodecUserParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecGetUserParameters
   (
   EcCodecHandle          hCodec,
   EcCodecUserParameters* pParams
   );

/****************************************************************************
 * Set the user parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   pParams : pointer to EcCodecUserParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSetUserParameters
   (
   EcCodecHandle          hCodec,
   EcCodecUserParameters* pParams
   );

/****************************************************************************
 * Save the user parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec : codec hardware handle from valid login
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSaveUserParameters
   (
   EcCodecHandle hCodec
   );

/****************************************************************************
 * Get the video parameters from the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   channel : channel number
 *   pParams : pointer to EcCodecVideoParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecGetVideoParameters
   (
   EcCodecHandle           hCodec,
   int                     channel,
   EcCodecVideoParameters* pParams
   );

/****************************************************************************
 * Set the video parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   channel : channel number
 *   pParams : pointer to EcCodecVideoParameters struct
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSetVideoParameters
   (
   EcCodecHandle           hCodec,
   int                     channel,
   EcCodecVideoParameters* pParams
   );

/****************************************************************************
 * Save the video parameters on the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec : codec hardware handle from valid login
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecSaveVideoParameters
   (
   EcCodecHandle hCodec
   );

/****************************************************************************
 * Start realplay
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   mode    : 0 = TCP, 1 = UDP
 *   channel : channel number
 *   pConfig : realplay configuration
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecStartRealplay
   (
   EcCodecHandle                       hCodec,
   int                                 mode,
   int                                 channel,
   const EcCodecRealplayConfiguration* pConfig
   );

/****************************************************************************
 * Stop realplay
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 *   channel : channel number
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecStopRealplay
   (
   EcCodecHandle hCodec,
   int           channel
   );

/****************************************************************************
 * Reboot the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecReboot
   (
   EcCodecHandle hCodec
   );

/****************************************************************************
 * Shutdown the codec device
 *
 * RETURNS
 *    1 on success
 *   -1 on failure
 *
 * PARAMS
 *   hCodec  : codec hardware handle from valid login
 ***************************************************************************/
EC_CODEC_CODECSDKC_DECL int codecShutdown
   (
   EcCodecHandle hCodec
   );

#endif /* ecCodecSdkC_H_ */
