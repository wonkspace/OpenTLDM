#ifndef ecStopThread_H
#define ecStopThread_H

#include <codec/codec_config.h>

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

//---------------------------------------------------------------------------
/// Thread functor used for stopping a thread in the background
//---------------------------------------------------------------------------
struct EcReaperThread
{
   /*!
    \brief Stop the thread and wait for it to exit
    \param threadPtr shared pointer to the thread to stop
    */
   void operator()
      (
      boost::shared_ptr<boost::thread> threadPtr
      )
   {
      threadPtr->interrupt();
      threadPtr->join();
   }
};

/// Macro to stop a thread in the background without waiting for the thread to exit
#define EC_STOP_THREAD_BG(threadPtr) if (threadPtr) { boost::thread(EcReaperThread(), threadPtr).detach(); threadPtr.reset(); }

/// Macro to stop a thread in the foreground and wait for the thread to exit
#define EC_STOP_THREAD_FG(threadPtr) if (threadPtr) { threadPtr->interrupt(); threadPtr->join(); threadPtr.reset(); }

/// Macro to stop a thread in the forground or background
#define EC_STOP_THREAD(threadPtr, bgFlag) if (bgFlag) { EC_STOP_THREAD_BG(threadPtr) } else { EC_STOP_THREAD_FG(threadPtr) }

#endif // ecStopThread_H
