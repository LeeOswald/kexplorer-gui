#pragma once


#include <kesrv/kesrv.hxx>

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef KXCLIENT_EXPORTS
        #define KXCLIENT_EXPORT __declspec(dllexport)
    #else
        #define KXCLIENT_EXPORT __declspec(dllimport)
    #endif
#else
    #define KXCLIENT_EXPORT __attribute__((visibility("default")))
#endif

#define KX_WINDOWS KES_WINDOWS
#define KX_LINUX KES_LINUX

#define KX_DEBUG KES_DEBUG