#ifndef ecCodecThrottleTableInstances_H_
#define ecCodecThrottleTableInstances_H_

#include <codec/codec_config.h>

// Forward declarations
class EcCodecThrottleTable;

namespace EcCodecThrottleTableInstances
{

/// Returns a throttle table tailored to driving with audio on
EcCodecThrottleTable groundDriveAudioOnTable
   (
   );

/// Returns a throttle table tailored to driving with audio off
EcCodecThrottleTable groundDriveAudioOffTable
   (
   );

}

#endif // ecCodecThrottleTableInstances_H_
