#ifndef ecStreamPacketPtr_H_
#define ecStreamPacketPtr_H_

#include <codec/codec_config.h>

#include <boost/shared_ptr.hpp>

// Forward declarations
template <typename T> class EcDataBuffer;

typedef EcDataBuffer<char>                EcStreamPacket;
typedef boost::shared_ptr<EcStreamPacket> EcStreamPacketPtr;

#endif // ecStreamPacketPtr_H_
