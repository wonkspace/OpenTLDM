#ifndef codec_config_H_
#define codec_config_H_
//     Copyright (c) 2008-2010 Energid Technologies. All rights reserved. ////
//
// Filename:    codec_config.h
//
// Description: Configuration header for the codec hierarchy.
//
// Contents:    
//
/////////////////////////////////////////////////////////////////////////
#include <foundCore/ecConfig.h>

#if defined(WIN32)
#  if defined(EC_BUILD_SHARED_LIBS)
#    define EC_CODEC_DYNAMIC_LIBS
#  endif
#endif

/// Enable all codec dynamic libs
#if defined(EC_CODEC_DYNAMIC_LIBS)
#  define EC_CODEC_CODECSDKC_DYNAMIC_LIBS
#endif

/// codecSdkC directory
#if defined(EC_CODEC_CODECSDKC_DYNAMIC_LIBS)
#  if defined(codec_codecSdkC_EXPORTS)
#    define EC_CODEC_CODECSDKC_DECL        EC_DECL_EXPORTS
#  else
#    define EC_CODEC_CODECSDKC_DECL        EC_DECL_IMPORTS
#  endif
#else  // defined(EC_CODEC_CODECSDKC_DYNAMIC_LIBS)
#  define EC_CODEC_CODECSDKC_DECL
#endif // defined(EC_CODEC_CODECSDKC_DYNAMIC_LIBS)

#endif // codec_config_H_
