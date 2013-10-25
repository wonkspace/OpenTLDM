#ifndef ecCodecTcpSocket_H_
#define ecCodecTcpSocket_H_

#include <codec/codec_config.h>

#include <boost/asio.hpp>
#include <boost/optional.hpp>

#include <string>

//---------------------------------------------------------------------------
/// Class for managing a TCP socket connection
//---------------------------------------------------------------------------
class EcCodecTcpSocket
{
public:
   /// Constructor
   EcCodecTcpSocket
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
   boost::asio::ip::tcp::socket               m_Socket;
   boost::asio::deadline_timer                m_DeadlineTimer;
   boost::optional<boost::system::error_code> m_SocketResult;
   boost::optional<boost::system::error_code> m_TimerResult;
   int                                        m_TimeoutSeconds;
};

#endif // ecCodecTcpSocket_H_
