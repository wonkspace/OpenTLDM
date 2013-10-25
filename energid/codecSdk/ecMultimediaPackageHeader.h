#ifndef ecMultimediaPackageHeader_H_
#define ecMultimediaPackageHeader_H_

#include <codec/codec_config.h>

#include <boost/cstdint.hpp>

//---------------------------------------------------------------------------
struct EcMultimediaPackageHeader
{
#define VALID_MMPKG_MARK ('E'<<24|'F'<<16|'M'<<8|'M')
   boost::uint32_t mm_pkg_mark;     // stationary flag for valid pkg
   boost::uint32_t session_id;      // identify the encode device
   boost::uint32_t chunk_id;        // identify corresponding chunk this package belonging
   boost::uint32_t chunk_offset;    // package payload offset in the chunk
   boost::uint32_t pkg_payload_len; // package payload len
   boost::int32_t  more_pkg;        // 1 more package left for the chunk,0 the last package for the chunk
};

#endif // ecMultimediaPackageHeader_H_
