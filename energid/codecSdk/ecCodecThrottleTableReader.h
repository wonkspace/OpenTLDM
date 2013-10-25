#ifndef ecCodecThrottleTableReader_H_
#define ecCodecThrottleTableReader_H_

#include <codec/codec_config.h>

#include <string>

// Forward declarations
class EcCodecThrottleTable;

namespace EcCodecThrottleTableReader
{

/*!
 \brief Reads a throttle table from file (*.ect extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void readFromFile
   (
   EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Reads a throttle table from a binary file (*.bin extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void readFromBinaryFile
   (
   EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Reads a throttle table from a text file (*.txt extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void readFromTxtFile
   (
   EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Reads a throttle table from a xml file (*.xml extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void readFromXmlFile
   (
   EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Reads a throttle table from a compressed binary file (*.bin.bz2 extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void readFromCompressedBinaryFile
   (
   EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Reads a throttle table from a compressed text file (*.txt.bz2 extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void readFromCompressedTxtFile
   (
   EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Reads a throttle table from a compressed xml file (*.xml.bz2 extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void readFromCompressedXmlFile
   (
   EcCodecThrottleTable& t,
   const std::string& fileName
   );

}

#endif // ecCodecThrottleTableReader_H_
