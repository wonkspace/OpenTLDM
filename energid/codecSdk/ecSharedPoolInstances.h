#ifndef ecSharedPoolInstances_H_
#define ecSharedPoolInstances_H_

#include <codec/codec_config.h>

#include "ecStreamPacketPool.h"

namespace EcSharedPoolInstances
{

EcStreamPacketPool& audioProcessingThreadPacketPool
   (
   );

EcStreamPacketPool& imageProcessingThreadPacketPool
   (
   );

EcStreamPacketPool& streamThreadPacketPool
   (
   );

}

#endif // ecSharedPoolInstances_H_
