#ifndef ecVideoParametersFlags_H_
#define ecVideoParametersFlags_H_

#include <codec/codec_config.h>

// Video flags
static const unsigned int EC_FLAG_CHANNEL        = 0x00000001;
static const unsigned int EC_FLAG_VIDEO_FORMAT   = 0x00000002;
static const unsigned int EC_FLAG_PICTURE_FORMAT = 0x00000004;
static const unsigned int EC_FLAG_MAX_BIT_RATE   = 0x00000008;
static const unsigned int EC_FLAG_FRAME_RATE     = 0x00000010;
static const unsigned int EC_FLAG_I_QUAL         = 0x00000020;
static const unsigned int EC_FLAG_B_QUAL         = 0x00000040;
static const unsigned int EC_FLAG_P_QUAL         = 0x00000080;
static const unsigned int EC_FLAG_ENCODE_MODE    = 0x00000100;
static const unsigned int EC_FLAG_KEY_INTERVAL   = 0x00000200;
static const unsigned int EC_FLAG_BRIGHTNESS     = 0x00000400;
static const unsigned int EC_FLAG_CONTRAST       = 0x00000800;
static const unsigned int EC_FLAG_SATURATION     = 0x00001000;
static const unsigned int EC_FLAG_HUE            = 0x00002000;

// Audio flags
static const unsigned int EC_FLAG_AUDIO          = 0x00010000;

#endif // ecVideoParametersFlags_H_
