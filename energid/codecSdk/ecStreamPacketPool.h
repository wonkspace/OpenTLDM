#ifndef ecStreamPacketPool_H_
#define ecStreamPacketPool_H_

#include <codec/codec_config.h>

#include <boost/shared_ptr.hpp>

// Forward declarations
template <typename T> class EcDataBufferPool;

typedef EcDataBufferPool<char>                EcStreamPacketPool;
typedef boost::shared_ptr<EcStreamPacketPool> EcStreamPacketPoolPtr;

#endif // ecStreamPacketPool_H_
