#ifndef ecCodecSdk_H_
#define ecCodecSdk_H_

#include <codec/codec_config.h>

#include <stdio.h>

#define CMD_VERSION 0x01010001

/*
 *
 */

#define NAME_LEN     32
#define PASSWD_LEN   16
#define MAX_RIGHT    16
#define MAX_USERNUM  16

/*
 *
 */
typedef struct
{
   unsigned int  nChannel;
   unsigned char res0;

   #define AUDIO_SAVEHD  0x1
   #define AUDIO_NETSEND 0x2

   unsigned char nSaveAudio;
   unsigned char res1;
   unsigned char res2;
} EcCodecAudioParameters;

/*
 *
 */
typedef struct
{
   unsigned int   nChannel;
   unsigned int   nVideoFormat;   // 1--PAL; 2--NTSC

   #define PICTURE_FORMAT_CIF     0
   #define PICTURE_FORMAT_QCIF    1
   #define PICTURE_FORMAT_HALFD1  2
   #define PICTURE_FORMAT_2CIF    3
   #define PICTURE_FORMAT_D1      4
   #define PICTURE_FORMAT_VGA     5
   #define PICTURE_FORMAT_HQ      6

   unsigned short nPictureFormat; // 0--6

   unsigned short nMaxBitRate;    // 100-5000 kbit/sec

   unsigned char  nFrameRate;     // 1-30, default 25
   unsigned char  nI_Qual;        // 2-31
   unsigned char  nB_qual;        // 0,2-31
   unsigned char  nP_qual;        // 0,2-31

   #define ENCODE_FIX_FRATE_BRATE 1
   #define ENCODE_FIX_FRATE_QUAL  2
   #define ENCODE_FIX_QUAL_BRATE  3

   unsigned short nEncodeMode;    // 1-3

   unsigned short nKeyInterval;   // 2-200

   unsigned char  nBrightness;    // 0-255
   unsigned char  nContrast;      // 0-255
   unsigned char  nSaturation;    // 0-255
   unsigned char  nHue;           // 0-255
} EcCodecVideoParameters;

/*
 *
 */
typedef struct
{
   char           sDVSName[NAME_LEN];
   int            nSaveLOGCycle;

   unsigned char  DVSIP[16];
   unsigned char  DVSIPMask[16];
   unsigned short nMSGPort[2];
   char           reserved1[6];
   unsigned short nDiskLimit;

   unsigned char  GatewayIP[16];

   unsigned char  DNSIP[16];
   unsigned short nDNSPort;

   unsigned short reserved_port;

   unsigned char  ManageHostIP[16];
   unsigned short nManageHostPort;

   unsigned short nStorageHostPort;
   unsigned char  StorageHostIP[16];

   unsigned int   reserved2;
   char           sStorageUser[NAME_LEN];
   char           sStoragePassword[PASSWD_LEN];
   char           remote_path[32];

   unsigned int   nPPPOE;
   char           sPPPoEUser[NAME_LEN];
   char           sPPPoEPassword[PASSWD_LEN];
   unsigned char  PPPoEIP[16];
} EcCodecNetworkParameters;

/*
 *
 */
typedef struct
{
   unsigned int nValidUser;

   struct
   {
      char         sUserName[NAME_LEN];
      char         sPassword[PASSWD_LEN];
      char         bRight[MAX_RIGHT];
      char         bReserverRight[MAX_RIGHT];

      unsigned int nUserIP;
      char         nMACAddr[6];
      short        reserved;
   } struUser[MAX_USERNUM];
} EcCodecUserParameters;

/*
 *
 */
typedef struct
{
   unsigned char  nDetectionOn;
   unsigned char  nBlackLevel;
   unsigned char  nReferenceFrames;
   unsigned char  nSpatialMedianFilterWidth;
   unsigned char  nSpatialMedianFilterHeight;
   unsigned short nMovementThresholdMs;
   unsigned short nMovementTimeoutMs;
   unsigned int   nMacroChangePercentThresholdNumerator;
   unsigned int   nMicroChangePercentThresholdNumerator;
   unsigned int   nBoxXPercentNumerator;
   unsigned int   nBoxYPercentNumerator;
   unsigned int   nBoxWidthPercentNumerator;
   unsigned int   nBoxHeightPercentNumerator;
   unsigned int   nDenominator;
} EcCodecMotionDetectParameters;

#endif /* ecCodecSdk_H_ */
