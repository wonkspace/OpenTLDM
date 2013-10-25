#ifndef ecCodecRealplayMode_H
#define ecCodecRealplayMode_H

#include <codec/codec_config.h>

//---------------------------------------------------------------------------
/// Available realplay modes
//---------------------------------------------------------------------------
struct EcCodecRealplayMode
{
   enum Enum
   {
      TCP = 0,
      UDP
   };
};

#endif // ecCodecRealplayMode_H
