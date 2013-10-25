#ifndef ecConfig_H_
#define ecConfig_H_
//     Copyright (c) 2008-2011 Energid Technologies. All rights reserved. ////
//
// Filename:    ecConfig.h
//
// Description: Specify some global configuration parameters and values.
//
// Contents:    import and export declarations for building shared libs on win32.
//
/////////////////////////////////////////////////////////////////////////

// Global definitions for all platforms.
#define BOOST_ALL_DYN_LINK 1

#if defined(WIN32)
#  define EC_DECL_IMPORTS __declspec(dllimport)
#  define EC_DECL_EXPORTS __declspec(dllexport)
// Visual Studio-specific warnings to disable
#  if defined(_MSC_VER)
#    pragma warning(disable:4251) // exporting stl objects within a dll
#    pragma warning(disable:4275) // non dll-interface class used as base off dll-interface class
#    pragma warning(disable:4231) // extern before template instantiation
#  endif // defined(_MSC_VER)

// General Windows definitions.
#  define NOMINMAX
#  define _SCL_SECURE_NO_WARNINGS
#  define _CRT_SECURE_NO_DEPRECATE
#  define WIN32_LEAN_AND_MEAN
#  define _WIN32_WINNT 0x502 // XP SP2
#  define DATE_TIME_INLINE 1
#  define BOOST_ALL_NO_LIB 1
// NOTE: Unicode support moved out of here since it may cause conflicts with external user code.

// Always build foundCore and plugins shared to handle printing and plugin support properly.
#  ifndef EC_BUILD_SHARED_LIBS
#    define EC_STABLE_FOUNDCORE_DYNAMIC_LIBS
#    define EC_ACTIN_PLUGINS_DYNAMIC_LIBS
#    define EC_GUICOMMON_SLOTMANAGER_DYNAMIC_LIBS
#  endif // EC_BUILD_SHARED_LIBS
#else    // defined(WIN32)
// All other non-Windows platforms
#  define EC_DECL_IMPORTS
#  define EC_DECL_EXPORTS

// Fix for debian-sarge (gcc 3.3.X) boost_thread support
#  if defined(__gnu_linux__) && defined(__GNUC__) && (__GNUC__ == 3) && (__GNUC_MINOR__ == 3)
#    define _PTHREADS
#  endif
#endif   // defined(WIN32)

/// Enable all stable dynamic libs 
#if defined(EC_BUILD_SHARED_LIBS)
#  define EC_FOUNDATION_GEOMETRY_DYNAMIC_LIBS
#  define EC_STABLE_EXCELXML_DYNAMIC_LIBS
#  define EC_STABLE_FILTERSTREAM_DYNAMIC_LIBS
#  define EC_STABLE_FOUNDCORE_DYNAMIC_LIBS
#  define EC_STABLE_MATRIXUTILITIES_DYNAMIC_LIBS
#  define EC_STABLE_SERIAL_DYNAMIC_LIBS
#  define EC_STABLE_SOCKET_DYNAMIC_LIBS
#  define EC_STABLE_STREAM_DYNAMIC_LIBS
#  define EC_STABLE_XML_DYNAMIC_LIBS
#  define EC_STABLE_XMLREADERWRITER_DYNAMIC_LIBS
#endif // defined(EC_BUILD_SHARED_LIBS)

/// excelXml directory
#if defined(EC_STABLE_EXCELXML_DYNAMIC_LIBS)
#  if defined(stableFoundation_excelXml_EXPORTS)
#    define EC_STABLE_EXCELXML_DECL         EC_DECL_EXPORTS
#  else
#    define EC_STABLE_EXCELXML_DECL         EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_EXCELXML_DYNAMIC_LIBS)
#  define EC_STABLE_EXCELXML_DECL
#endif // defined(EC_STABLE_EXCELXML_DYNAMIC_LIBS)

/// filterStream directory
#if defined(EC_STABLE_FILTERSTREAM_DYNAMIC_LIBS)
#  if defined(stableFoundation_filterStream_EXPORTS)
#    define EC_STABLE_FILTERSTREAM_DECL     EC_DECL_EXPORTS
#  else
#    define EC_STABLE_FILTERSTREAM_DECL     EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_FILTERSTREAM_DYNAMIC_LIBS)
#  define EC_STABLE_FILTERSTREAM_DECL
#endif // defined(EC_STABLE_FILTERSTREAM_DYNAMIC_LIBS)

/// foundCore directory
#if defined(EC_STABLE_FOUNDCORE_DYNAMIC_LIBS)
#  if defined(stableFoundation_foundCore_EXPORTS)
#    define EC_STABLE_FOUNDCORE_DECL        EC_DECL_EXPORTS
#  else
#    define EC_STABLE_FOUNDCORE_DECL        EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_FOUNDCORE_DYNAMIC_LIBS)
#  define EC_STABLE_FOUNDCORE_DECL
#endif // defined(EC_STABLE_FOUNDCORE_DYNAMIC_LIBS)

/// matrixUtilities directory
#if defined(EC_STABLE_MATRIXUTILITIES_DYNAMIC_LIBS)
#  if defined(stableFoundation_matrixUtilities_EXPORTS)
#    define EC_STABLE_MATRIXUTILITIES_DECL  EC_DECL_EXPORTS
#  else
#    define EC_STABLE_MATRIXUTILITIES_DECL  EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_MATRIXUTILITIES_DYNAMIC_LIBS)
#  define EC_STABLE_MATRIXUTILITIES_DECL
#endif // defined(EC_STABLE_MATRIXUTILITIES_DYNAMIC_LIBS)

/// serial directory
#if defined(EC_STABLE_SERIAL_DYNAMIC_LIBS)
#  if defined(stableFoundation_serial_EXPORTS)
#    define EC_STABLE_SERIAL_DECL           EC_DECL_EXPORTS
#  else
#    define EC_STABLE_SERIAL_DECL           EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_SERIAL_DYNAMIC_LIBS)
#  define EC_STABLE_SERIAL_DECL
#endif // defined(EC_STABLE_SERIAL_DYNAMIC_LIBS)

/// socket directory
#if defined(EC_STABLE_SOCKET_DYNAMIC_LIBS)
#  if defined(stableFoundation_socket_EXPORTS)
#    define EC_STABLE_SOCKET_DECL           EC_DECL_EXPORTS
#  else
#    define EC_STABLE_SOCKET_DECL           EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_SOCKET_DYNAMIC_LIBS)
#  define EC_STABLE_SOCKET_DECL
#endif // defined(EC_STABLE_SOCKET_DYNAMIC_LIBS)

/// stream directory
#if defined(EC_STABLE_STREAM_DYNAMIC_LIBS)
#  if defined(stableFoundation_stream_EXPORTS)
#    define EC_STABLE_STREAM_DECL           EC_DECL_EXPORTS
#  else
#    define EC_STABLE_STREAM_DECL           EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_STREAM_DYNAMIC_LIBS)
#  define EC_STABLE_STREAM_DECL
#endif // defined(EC_STABLE_STREAM_DYNAMIC_LIBS)

/// xml directory
#if defined(EC_STABLE_XML_DYNAMIC_LIBS)
#  if defined(stableFoundation_xml_EXPORTS)
#    define EC_STABLE_XML_DECL              EC_DECL_EXPORTS
#    define EC_STABLE_XML_TEMPLATE_DECL
#  else
#    define EC_STABLE_XML_DECL              EC_DECL_IMPORTS
#    define EC_STABLE_XML_TEMPLATE_DECL     extern
#  endif
#else  // defined(EC_STABLE_XML_DYNAMIC_LIBS)
#  define EC_STABLE_XML_DECL
#  define EC_STABLE_XML_TEMPLATE_DECL
#endif // defined(EC_STABLE_XML_DYNAMIC_LIBS)

#if defined(EC_STABLE_XMLREADERWRITER_DYNAMIC_LIBS)
#  if defined(stableFoundation_xmlReaderWriter_EXPORTS)
#    define EC_STABLE_XMLREADERWRITER_DECL  EC_DECL_EXPORTS
#  else
#    define EC_STABLE_XMLREADERWRITER_DECL  EC_DECL_IMPORTS
#  endif
#else  // defined(EC_STABLE_XMLREADERWRITER_DYNAMIC_LIBS)
#  define EC_STABLE_XMLREADERWRITER_DECL
#endif // defined(EC_STABLE_XMLREADERWRITER_DYNAMIC_LIBS)

/// geometry directory
#if defined(EC_FOUNDATION_GEOMETRY_DYNAMIC_LIBS)
#  if defined(foundation_geometry_EXPORTS)
#    define EC_FOUNDATION_GEOMETRY_DECL     EC_DECL_EXPORTS
#  else
#    define EC_FOUNDATION_GEOMETRY_DECL     EC_DECL_IMPORTS
#  endif
#else  // defined(EC_FOUNDATION_GEOMETRY_DYNAMIC_LIBS)
#  define EC_FOUNDATION_GEOMETRY_DECL
#endif // defined(EC_FOUNDATION_GEOMETRY_DYNAMIC_LIBS)

#endif // ecConfig_H_
