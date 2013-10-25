#ifndef ecCodecRealplayThreadFactory_H_
#define ecCodecRealplayThreadFactory_H_

#include <codec/codec_config.h>

#include "ecCodecLoginParameters.h"
#include "ecCodecRealplayMode.h"

#include <boost/cstdint.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

// Forward declarations
class EcCodecRealplayStreamProcessor;

namespace boost
{
   class thread;
};

//---------------------------------------------------------------------------
/// Factory for starting threads for different realplay modes
//---------------------------------------------------------------------------
class EcCodecRealplayThreadFactory
{
public:
   /// Type of the lost connection callback: void (*callback)(void)
   typedef boost::function0<void> LostConnectionCallbackType;

   /*!
    \brief Constructor
    \param channel realplay channel
    \param lparams login parameters
    \param codecUserID user ID of the login session
    */
   EcCodecRealplayThreadFactory
      (
      int                           channel,
      const EcCodecLoginParameters& lparams,
      unsigned long                 codecUserID
      );

   /*!
    \brief Starts a realplay thread
    \param mode realplay mode
    \param procPtr processor that receives all of the stream data
    \param lostConnectionCallback called when the connection is lost
    \returns shared pointer to the realplay thread
    */
   boost::shared_ptr<boost::thread> create
      (
      EcCodecRealplayMode::Enum                         mode,
      boost::shared_ptr<EcCodecRealplayStreamProcessor> procPtr,
      LostConnectionCallbackType                        lostConnectionCallback
      );

private:
   int                    m_Channel;
   EcCodecLoginParameters m_LParams;
   unsigned long          m_CodecUserID;
};

#endif // ecCodecRealplayThreadFactory_H_
