#ifndef ecCodecThrottleTableWriter_H_
#define ecCodecThrottleTableWriter_H_

#include <codec/codec_config.h>

#include <string>

// Forward declarations
class EcCodecThrottleTable;

namespace EcCodecThrottleTableWriter
{

/*!
 \brief Writes a throttle table to file (*.ect extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void writeToFile
   (
   const EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Writes a throttle table to a binary file (*.bin extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void writeToBinaryFile
   (
   const EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Writes a throttle table to a text file (*.txt extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void writeToTxtFile
   (
   const EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Writes a throttle table to a xml file (*.xml extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void writeToXmlFile
   (
   const EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Writes a throttle table to a compressed binary file (*.bin.bz2 extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void writeToCompressedBinaryFile
   (
   const EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Writes a throttle table to a compressed text file (*.txt.bz2 extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void writeToCompressedTxtFile
   (
   const EcCodecThrottleTable& t,
   const std::string& fileName
   );

/*!
 \brief Writes a throttle table to a compressed xml file (*.xml.bz2 extension)
 \param t throttle table
 \param fileName the file to write the table to
 */
void writeToCompressedXmlFile
   (
   const EcCodecThrottleTable& t,
   const std::string& fileName
   );

}

#endif // ecCodecThrottleTableWriter_H_
