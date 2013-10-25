#ifndef ecCodecThrottleTableEntry_H_
#define ecCodecThrottleTableEntry_H_

#include <codec/codec_config.h>

#include <codecSdk/ecCodecSdk.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//---------------------------------------------------------------------------
class EcCodecThrottleTableEntry
{
public:
   enum InterpolationFlags
   {
      INTERP_NONE         = 0,
      INTERP_BIT_RATE     = 0x01,
      INTERP_FRAME_RATE   = 0x02,
      INTERP_IQUAL        = 0x04,
      INTERP_BQUAL        = 0x08,
      INTERP_PQUAL        = 0x10,
      INTERP_QUAL         = 0x1C,
      INTERP_KEY_INTERVAL = 0x20,
      INTERP_ALL          = 0x3F
   };

   /// Constructor
   EcCodecThrottleTableEntry
      (
      );

   /*!
    \brief Determines if a throttle table entry is equal to this instance
    \param rhs throttle table entry to compare
    \returns true if rhs is equal to this instance
    */
   bool operator==
      (
      const EcCodecThrottleTableEntry& rhs
      ) const;

   /*!
    \brief Determines if a throttle table entry is not equal to this instance
    \param rhs throttle table entry to compare
    \returns true if rhs is not equal to this instance
    */
   bool operator!=
      (
      const EcCodecThrottleTableEntry& rhs
      ) const;

   /// Returns true if this throttle table entry is valid
   bool isValid
      (
      ) const;

   /// Clears this throttle table entry
   void clear
      (
      );

   /// Returns the interpolation flags to be used in throttle table entry interpolation routines
   unsigned int interpolationFlags
      (
      ) const;

   /// Sets the interpolation flags to be used in throttle table entry interpolation routines
   void setInterpolationFlags
      (
      unsigned int flags
      );

   /// Returns the picture format
   unsigned short pictureFormat
      (
      ) const;

   /// Sets the picture format (either PICTURE_FORMAT_CIF or PICTURE_FORMAT_HALFD1 for validity)
   void setPictureFormat
      (
      unsigned short format
      );

   /// Returns the maximum bit rate
   unsigned short maxBitRate
      (
      ) const;

   /// Sets the maximum bit rate (100-5000 kbps for validity)
   void setMaxBitRate
      (
      unsigned short kbps
      );

   /// Returns the frame rate
   unsigned char frameRate
      (
      ) const;

   /// Sets the frame rate (1-30 fps for validity)
   void setFrameRate
      (
      unsigned char fps
      );

   /// Returns the I frame quality
   unsigned char iQuality
      (
      ) const;

   /// Sets the I frame quality (2-31 for validity)
   void setIQuality
      (
      unsigned char iqual
      );

   /// Returns the B frame quality
   unsigned char bQuality
      (
      ) const;

   /// Sets the B frame quality (0,2-31 for validity)
   void setBQuality
      (
      unsigned char bqual
      );

   /// Returns the P frame quality
   unsigned char pQuality
      (
      ) const;

   /// Sets the P frame quality (0,2-31 for validity)
   void setPQuality
      (
      unsigned char pqual
      );

   /// Returns the key (I) frame interval
   unsigned short keyInterval
      (
      ) const;

   /// Sets the key (I) frame interval (2-200 for validity)
   void setKeyInterval
      (
      unsigned short interval
      );

   /*!
    \brief Applies a throttle table entry to video parameters
    \param entry throttle table entry to apply
    \param vparams video parameters to receive the throttle table entry
    \returns true upon success
    */
   static bool applyToVideoParameters
      (
      const EcCodecThrottleTableEntry& entry,
      EcCodecVideoParameters& vparams
      );

   /*!
    \brief Interpolates between two throttle table entries
    \param a first throttle table entry and source of interpolation flags
    \param b second throttle table entry
    \param weight (a=0.0) <= weight <= (b=1.0)
    \returns interpolated throttle table entry
    */
   static EcCodecThrottleTableEntry interpolate
      (
      const EcCodecThrottleTableEntry& a,
      const EcCodecThrottleTableEntry& b,
      float weight
      );

   template <typename ArchiveT>
   void serialize
      (
      ArchiveT& ar,
      unsigned int version
      );

private:
   unsigned int   m_InterpolationFlags;
   unsigned short m_PictureFormat;
   unsigned short m_MaxBitRate;
   unsigned char  m_FrameRate;
   unsigned char  m_Iqual;
   unsigned char  m_Bqual;
   unsigned char  m_Pqual;
   unsigned short m_KeyInterval;
};

BOOST_CLASS_VERSION(EcCodecThrottleTableEntry, 0)

//---------------------------------------------------------------------------
template <typename ArchiveT>
void EcCodecThrottleTableEntry::serialize
   (
   ArchiveT& ar,
   unsigned int version
   )
{
   ar & boost::serialization::make_nvp("interpFlags", m_InterpolationFlags)
      & boost::serialization::make_nvp("format",      m_PictureFormat)
      & boost::serialization::make_nvp("bitRate",     m_MaxBitRate)
      & boost::serialization::make_nvp("frameRate",   m_FrameRate)
      & boost::serialization::make_nvp("iQuality",    m_Iqual)
      & boost::serialization::make_nvp("bQuality",    m_Bqual)
      & boost::serialization::make_nvp("pQuality",    m_Pqual)
      & boost::serialization::make_nvp("keyInterval", m_KeyInterval);
}

#endif // ecCodecThrottleTableEntry_H_
