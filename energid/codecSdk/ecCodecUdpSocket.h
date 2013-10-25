#ifndef ecCodecUdpSocket_H_
#define ecCodecUdpSocket_H_

#include <codec/codec_config.h>

#include <boost/asio.hpp>
#include <boost/optional.hpp>

#include <string>

// Forward declarations
class EcCodecUser;

//---------------------------------------------------------------------------
/// Class for managing a UDP socket connection
//---------------------------------------------------------------------------
class EcCodecUdpSocket
{
public:
   /// Constructor
   EcCodecUdpSocket
      (
      );

   /// Returns the timeout for socket operations
   int timeoutSeconds
      (
      ) const;

   /// Sets the timeout for socket operations
   void setTimeoutSeconds
      (
      int seconds
      );

   /// Returns a flag indicating if the socket is currently connected
   bool isConnected
      (
      ) const;

   /*!
    \brief Connect the socket
    \param hostName the host machine to connect to
    \param port the port number to connect to
    \returns true upon successfully connecting the socket
    */
   bool connect
      (
      const std::string& hostName,
      unsigned int       port
      );

   /*!
    \brief Read a specified number of bytes from the socket
    \param pBuffer buffer for storing the read data
    \param length number of bytes to read
    \returns true upon successfully reading the specified number of bytes
    */
   bool read
      (
      void*        pBuffer,
      unsigned int length
      );

   /*!
    \brief Receive bytes from the socket
    \param pBuffer buffer for storing the read data
    \param length length of the allocated buffer
    \returns the number of bytes received
    */
   unsigned int receiveBytes
      (
      void*        pBuffer,
      unsigned int length
      );

   /*!
    \brief Write a specified number of bytes to the socket
    \param pBuffer buffer for the write data
    \param length number of bytes to write
    \returns true upon successfully writing the specified number of bytes
    */
   bool write
      (
      void*        pBuffer,
      unsigned int length
      );

private:
   bool runSocketOperation
      (
      );

   boost::asio::io_service                    m_IoService;
   boost::asio::ip::udp::socket               m_Socket;
   boost::asio::deadline_timer                m_DeadlineTimer;
   boost::optional<boost::system::error_code> m_SocketResult;
   boost::optional<std::size_t>               m_SocketBytes;
   boost::optional<boost::system::error_code> m_TimerResult;
   int                                        m_TimeoutSeconds;
};

#endif // ecCodecUdpSocket_H_
