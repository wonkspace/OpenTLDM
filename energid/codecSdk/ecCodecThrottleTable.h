#ifndef ecCodecThrottleTable_H_
#define ecCodecThrottleTable_H_

#include <codec/codec_config.h>

#include "ecCodecThrottleTableEntry.h"

#include <boost/foreach.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

#include <vector>

//---------------------------------------------------------------------------
class EcCodecThrottleTable
{
public:
   /// Constructor
   EcCodecThrottleTable
      (
      );

   /*!
    \brief Determines if a throttle table is equal to this instance
    \param rhs throttle table to compare
    \returns true if rhs is equal to this instance
    */
   bool operator==
      (
      const EcCodecThrottleTable& rhs
      ) const;

   /*!
    \brief Determines if a throttle table is not equal to this instance
    \param rhs throttle table to compare
    \returns true if rhs is not equal to this instance
    */
   bool operator!=
      (
      const EcCodecThrottleTable& rhs
      ) const;

   /// Returns true if this throttle table is valid
   bool isValid
      (
      ) const;

   /*!
    \brief Adds a throttle table entry
    \param bitRate lookup bit rate to use for this throttle table entry (kbps)
    \param entry throttle table entry to add to the table
    */
   void addEntry
      (
      unsigned short bitRate,
      const EcCodecThrottleTableEntry& entry
      );

   /// Clears this throttle table
   void clear
      (
      );

   /*!
    \brief Looks up a throttle table entry for a specified bit rate
    \param bitRate lookup bit rate (kbps)
    \param entry lookup throttle table entry
    \returns true if lookup is successful (entry is only valid if successful)
    */
   bool lookup
      (
      unsigned short bitRate,
      EcCodecThrottleTableEntry& entry
      ) const;

   template <typename ArchiveT>
   void save
      (
      ArchiveT& ar,
      unsigned int version
      ) const;

   template <typename ArchiveT>
   void load
      (
      ArchiveT& ar,
      unsigned int version
      );

   BOOST_SERIALIZATION_SPLIT_MEMBER();

private:
   void checkForDuplicateEntries
      (
      );

   typedef std::pair<unsigned short, EcCodecThrottleTableEntry> EntryPair;

   std::vector<EntryPair> m_TableEntries;
   unsigned short         m_TableBitrateMinimum;
   unsigned short         m_TableBitrateMaximum;
   bool                   m_IsValid;
};

BOOST_CLASS_VERSION(EcCodecThrottleTable, 0)

//---------------------------------------------------------------------------
template <typename ArchiveT>
void EcCodecThrottleTable::save
   (
   ArchiveT& ar,
   unsigned int version
   ) const
{
   ar & boost::serialization::make_nvp("tableEntries", m_TableEntries);
}

//---------------------------------------------------------------------------
template <typename ArchiveT>
void EcCodecThrottleTable::load
   (
   ArchiveT& ar,
   unsigned int version
   )
{
   std::vector<EntryPair> tableEntries;
   ar & boost::serialization::make_nvp("tableEntries", tableEntries);

   clear();
   BOOST_FOREACH (const EntryPair& p, tableEntries)
   {
      addEntry(p.first, p.second);
   }
}

#endif // ecCodecThrottleTable_H_
