#ifndef ecCodecMessages_H_
#define ecCodecMessages_H_

#include <codec/codec_config.h>

#include "ecCodecSdk.h"

/*
 * Message types
 */

#define MSG_T_USER_LOGIN           4100
#define MSG_T_USER_LOGIN_REPLY     4101
#define MSG_T_USER_LOGOUT          4102
#define MSG_T_USER_LOGOUT_REPLY    4103

#define MSG_T_SET_VPARA            4110
#define MSG_T_SET_VPARA_REPLY      4111
#define MSG_T_GET_VPARA            4112
#define MSG_T_GET_VPARA_REPLY      4113

#define MSG_T_SET_RAPARA           4122
#define MSG_T_SET_RAPARA_REPLY     4123
#define MSG_T_GET_RAPARA           4124
#define MSG_T_GET_RAPARA_REPLY     4125

#define MSG_T_SET_NETCONFIG        4146
#define MSG_T_SET_NETCONFIG_REPLY  4147
#define MSG_T_GET_NETCONFIG        4148
#define MSG_T_GET_NETCONFIG_REPLY  4149

#define MSG_T_SET_USERCONFIG       4150
#define MSG_T_SET_USERCONFIG_REPLY 4151
#define MSG_T_GET_USERCONFIG       4152
#define MSG_T_GET_USERCONFIG_REPLY 4153

#define MSG_T_ALARM_EVENT          4160

#define MSG_T_REMOTE_OPERATE       4202
#define MSG_T_REMOTE_OPERATE_REPLY 4203

#define MSG_V_RVIDEO_AUTH          4300
#define MSG_V_RVIDEO_STREAMHEAD    4301

#define MSG_V_RVIDEO_STREAMDATA    4311

#define MSG_T_GET_REPEATER         9800
#define MSG_T_GET_REPEATER_REPLY   9801

#define MSG_T_SET_MDPARA           9810
#define MSG_T_SET_MDPARA_REPLY     9811
#define MSG_T_GET_MDPARA           9812
#define MSG_T_GET_MDPARA_REPLY     9813

/*
 * Message header
 */
typedef struct
{
   unsigned int  nVer;
   unsigned int  nLen;
   unsigned int  nUserID;
   unsigned char cPasswdInfo[4];
   unsigned char cAdditionInfo[8];
   unsigned int  nCmdNo;
   unsigned int  nMsgID;
} Msg_Head_t;

/*
 * Reply header
 */
typedef struct
{
   unsigned int nVer;
   unsigned int nLen;
   unsigned int nCmdNo;
   unsigned int nMsgID;
   unsigned int nErrCode;
} Reply_Head_t;

/*
 * User login message body
 */
typedef struct
{
   char sName[NAME_LEN];
   char sPasswd[PASSWD_LEN];
} TSer_UserLogin_t;

/*
 * User login reply body
 */
typedef struct
{
   unsigned int nUserID;
} TSer_LoginReply_t;

/*
 * Video parameters message body
 */
typedef struct
{
   #define CHANNEL_TYPE_MSK       0xffff0000
   #define CHANNEL_TYPE_MAIN      0x00000000
   #define CHANNEL_TYPE_SECOND    0x00010000

   unsigned int nChannel;

   #define V_FMT_PAL              1
   #define V_FMT_NTSC             2

   unsigned int nVideoFormat;     // 1 PAL 2 NTSC

   #define PICTURE_FORMAT_CIF     0
   #define PICTURE_FORMAT_QCIF    1  // No support yet
   #define PICTURE_FORMAT_HALFD1  2
   #define PICTURE_FORMAT_2CIF    3  // No support yet
   #define PICTURE_FORMAT_D1      4
   #define PICTURE_FORMAT_VGA     5  // Only Support in HYSX
   #define PICTURE_FORMAT_HQ      6  // No support yet

   unsigned short nPictureFormat; // 0--6

   #define MIN_BIT_RATE           100  // kbps
   #define MAX_BIT_RATE           5000 // kbps

   unsigned short nMaxBitRate;    // (100-5000) * 1024bit/sec

   #define MIN_FRAME_RATE         1
   #define MAX_FRAME_RATE         30

   unsigned char nFrameRate;      // 1-30, default 25
   unsigned char nI_Qual;         // 2-31
   unsigned char nB_qual;         // 0,2-31
   unsigned char nP_qual;         // 0,2-31

   #define ENCODE_FIX_FRATE_BRATE 1
   #define ENCODE_FIX_FRATE_QUAL  2
   #define ENCODE_FIX_QUAL_BRATE  3

   unsigned short nEncodeMode;    // 1-3

   unsigned short nKeyInterval;   // 2-200

   unsigned char nBrightness;     // 0-255
   unsigned char nContrast;       // 0-255
   unsigned char nSaturation;     // 0-255
   unsigned char nHue;            // 0-255
} TSer_RVPara_t;

/*
 *
 */
typedef struct
{
   #define TSER_REBOOT_TSER        0x01
   #define TSER_SHUTDOWN_TSER      0x02
   #define TSER_SET_TIME           0x04

   #define FLASH_PARA_DEVICE       0x0001
   #define FLASH_PARA_VIDEO        0x0002
   #define FLASH_PARA_MOTIONDETECT 0x0004
   #define FLASH_PARA_STORAGE      0x0008
   #define FLASH_PARA_ALARMIN      0x0010
   #define FLASH_PARA_PTZ          0x0020
   #define FLASH_PARA_USER         0x0040
   #define FLASH_PARA_NET          0x0080
   #define FLASH_PARA_MASK         0x00ff
   #define FLASH_PARA_NUMBER       8

   #define TSER_RESTORE_PARA       0x22
   #define TSER_SAVE_PARA          0x23

   #define TSER_START_RECORDVIDEO  0x11
   #define TSER_STOP_RECORDVIDEO   0x12

   #define TSER_SEND_SMTP_TEST     0x14

   unsigned int nOpCode;
   unsigned int nOpPara;
} TSer_OperateTser_t;

/*
 * Network parameters message body
 */
typedef struct
{
   char           sDVSName[NAME_LEN];
   int            nSaveLOGCycle;

   unsigned int   nDVSIP;
   unsigned int   nDVSIPMask;

   unsigned short nMSGPort;
   unsigned short nRealVideoPort;

   unsigned char  cMACAddr[6];
   unsigned short nDiskLimit;

   unsigned int   nGatewayIP;

   unsigned int   nDNSIP;
   unsigned short nDNSPort;
   unsigned short nHttpPort;

   unsigned int   nManageHostIP;
   unsigned short nManageHostPort;

   unsigned short nStorageHostPort;
   unsigned int   nStorageHostIP;

   unsigned int   nReserved0;
   char           sStorageUser[NAME_LEN];
   char           sStoragePassword[PASSWD_LEN];
   unsigned char  nReserved[32];

   #define LINK_ETHERNET 0
   #define LINK_ADSL     1

   unsigned short nPPPOE;

   unsigned short nPPPOESMTPNotify;
   char           sPPPoEUser[NAME_LEN];
   char           sPPPoEPassword[PASSWD_LEN];
   unsigned int   nPPPoEIP;
} TSer_NET_Para_t;

/*
 * Audio parameters message body
 */
typedef struct
{
   unsigned int  nChannel;

   unsigned char nMicOrLineIn; // 1-MIC 0-Linein
   unsigned char nSaveAudio;   // bit0 : whether save audio to HD
                               // bit1 : whether send audio to net by default

   unsigned char nMicVol;
   unsigned char nLineINVol;
} TSer_RAPara_t;

/*
 * Motion detection parameters message body
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
} TSer_MDPara_t;

#endif /* ecCodecMessages_H_ */
