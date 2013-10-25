#ifndef ecFrameManagerStatistics_H
#define ecFrameManagerStatistics_H

#include <codec/codec_config.h>

//---------------------------------------------------------------------------
/// Container for managing statistics related to RTP packages
//---------------------------------------------------------------------------
class EcFrameManagerStatistics
{
public:
   EcFrameManagerStatistics
      (
      );

   /// Number of RTP packages that were received
   unsigned long numPackagesReceived;

   /// Number of RTP packages that are currently being managed
   unsigned long numPackagesManaged;

   /// Number of RTP packages that were invalid
   unsigned long numPackagesInvalid;

   /// Number of RTP packages that expired
   unsigned long numPackagesExpired;

   /// Number of RTP packages that were skipped
   unsigned long numPackagesSkipped;

   /// Number of RTP packages that were unmatched
   unsigned long numPackagesUnmatched;

   /// Number of RTP packages that were used in complete and incomplete frames
   unsigned long numPackagesUsed;


   /// Number of frames that were received
   unsigned long numFramesReceived;

   /// Number of frames that are currently being managed
   unsigned long numFramesManaged;

   /// Number of frames that expired
   unsigned long numFramesExpired;

   /// Number of frames that were skipped
   unsigned long numFramesSkipped;

   /// Number of frames that were complete
   unsigned long numFramesComplete;

   /// Number of frames that were incomplete
   unsigned long numFramesIncomplete;
};

#endif // ecFrameManagerStatistics_H
