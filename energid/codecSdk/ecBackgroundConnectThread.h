#ifndef EcBackgroundConnectThread_H_
#define EcBackgroundConnectThread_H_

#include <codec/codec_config.h>

#include "ecCodecSdk.h"

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

// Forward declarations
class EcCodecUser;
class EcCodecLoginParameters;

//---------------------------------------------------------------------------
/// Thread functor for connecting to the CODEC encoder hardware in the background
//---------------------------------------------------------------------------
struct EcBackgroundConnectThread
{
   /// Type of the established connection callback: void (*callback)(boost::shared_ptr<EcCodecUser> userPtr)
   typedef boost::function1<void, boost::shared_ptr<EcCodecUser> > CallbackType;

   /*!
    \brief Thread function
    \param lparams login parameters
    \param vparams video parameters to set upon successful connection
    \param aparams audio parameters to set upon successful connection
    \param flags flags indicating which video and audio parameters to attempt
                 to set upon successful connection
    \param callback called when the connection is established
    */
   void operator()
      (
      EcCodecLoginParameters lparams, // Copy instead of reference for thread safety
      EcCodecVideoParameters vparams, // Copy instead of reference for thread safety
      EcCodecAudioParameters aparams, // Copy instead of reference for thread safety
      unsigned int           flags,
      CallbackType           callback
      );
};

#endif // EcBackgroundConnectThread_H_
