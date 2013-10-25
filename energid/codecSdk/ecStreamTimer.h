#ifndef ecStreamTimer_H_
#define ecStreamTimer_H_

#include <codec/codec_config.h>

#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

//---------------------------------------------------------------------------
/// Provides microsecond times
//---------------------------------------------------------------------------
class EcStreamTimer
{
public:
   /// Constructor
   EcStreamTimer
      (
      ) :
      m_StartTime(boost::posix_time::not_a_date_time)
   {
   }

   /*!
    \brief Calculates microseconds since start

    This method returns the number of microseconds since start.  It will return zero the first time it is called.

    \returns microseconds since start
    */
   boost::int64_t microseconds
      (
      )
   {
      if (m_StartTime.is_not_a_date_time())
      {
         start();
         return 0;
      }

      return (boost::posix_time::microsec_clock::local_time() - m_StartTime).total_microseconds();
   }

   /// Resets the timer (next call to microseconds() will return zero)
   void reset
      (
      )
   {
      m_StartTime = boost::posix_time::not_a_date_time;
   }

   /// Starts the timer
   void start
      (
      )
   {
      m_StartTime = boost::posix_time::microsec_clock::local_time();
   }

private:
   boost::posix_time::ptime m_StartTime;
};

#endif // ecStreamTimer_H_
