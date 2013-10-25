#ifndef ecCodecLoginParameters_H_
#define ecCodecLoginParameters_H_

#include <codec/codec_config.h>

#include <string>

//---------------------------------------------------------------------------
/// Container for login parameters
//---------------------------------------------------------------------------
class EcCodecLoginParameters
{
public:
   /// Constructor
   EcCodecLoginParameters
      (
      );

   /*!
    \brief Constructor
    \param userName user name for logging into the CODEC encoder hardware
    \param password password for logging into the CODEC encoder hardware
    \param codecIp hostname of the CODEC encoder hardware
    \param port1 port for communicating with the CODEC encoder hardware
    \param port2 port for receiving realplay data
    */
   EcCodecLoginParameters
      (
      const std::string& userName,
      const std::string& password,
      const std::string& codecIp,
      unsigned int       port1,
      unsigned int       port2
      );

   /// Returns equality of login parameters
   bool operator==
      (
      const EcCodecLoginParameters& rhs
      ) const;

   /// Returns inequality of login parameters
   bool operator!=
      (
      const EcCodecLoginParameters& rhs
      ) const;

   /// Returns the user name
   const std::string& userName
      (
      ) const;

   /// Returns the password
   const std::string& password
      (
      ) const;

   /// Returns the hostname
   const std::string& codecIp
      (
      ) const;

   /// Returns the communication port
   unsigned int codecPort1
      (
      ) const;

   /// Returns the realplay port
   unsigned int codecPort2
      (
      ) const;

private:
   std::string  m_UserName;
   std::string  m_Password;
   std::string  m_CodecIp;
   unsigned int m_CodecPort1;
   unsigned int m_CodecPort2;
};

#endif // ecCodecLoginParameters_H_
